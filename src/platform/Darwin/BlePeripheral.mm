/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Provides an implementation of BlePeripheral for Darwin platforms.
 */

#if !__has_feature(objc_arc)
#error This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif

#include <ble/BleConfig.h>
#include <ble/BleError.h>
#include <ble/BleLayer.h>
#include <ble/BleUUID.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/Darwin/BlePeripheral.h>

#import "UUIDHelper.h"

const chip::Ble::ChipBleUUID chipUUID_CHIPoBLEChar_RX
    = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F, 0x9D, 0x11 } };

const chip::Ble::ChipBleUUID chipUUID_CHIPoBLEChar_TX
    = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F, 0x9D, 0x12 } };

@interface BleListener : NSObject <CBPeripheralManagerDelegate, CBPeripheralDelegate>

@property (strong, nonatomic) dispatch_queue_t workQueue;
@property (strong, nonatomic) dispatch_queue_t chipWorkQueue;
@property (strong, nonatomic) CBPeripheralManager * peripheralManager;
@property (strong, nonatomic) CBUUID * shortServiceUUID;

@property (unsafe_unretained, nonatomic) chip::Ble::BleLayer * mBleLayer;
@property (unsafe_unretained, nonatomic) void * appState;
@property (unsafe_unretained, nonatomic) uint16_t deviceDiscriminator;

@property (strong, nonatomic) CBMutableCharacteristic * characteristic1;
@property (strong, nonatomic) CBMutableCharacteristic * characteristic2;

@property (strong, nonatomic) NSMutableArray * messageQueue;

- (id)initWithDiscriminator:(uint16_t)deviceDiscriminator;
- (void)setBleLayer:(chip::Ble::BleLayer *)bleLayer;
- (void)start;
- (void)stop;

@end

namespace chip {
namespace DeviceLayer {
    namespace Internal {

        BleListener * bleListener;

        CHIP_ERROR BlePeripheral::Init(Ble::BleLayer * bleLayer, void * appState, const uint16_t deviceDiscriminator)
        {
            ChipLogProgress(Ble, "%s", __FUNCTION__);
            bleListener = [[BleListener alloc] initWithDiscriminator:deviceDiscriminator];
            [bleListener setBleLayer:bleLayer];
            bleListener.appState = appState;
            bleListener.peripheralManager = [bleListener.peripheralManager initWithDelegate:bleListener
                                                                                      queue:bleListener.workQueue];

            return CHIP_NO_ERROR;
        }

        CHIP_ERROR BlePeripheral::UpdateAdvertising()
        {
            ChipLogProgress(chipTool, ">> BlePeripheral::UpdateAdvertising");
            return CHIP_NO_ERROR;
        }

        void BlePeripheral::SendIndication(PacketBufferHandle pBuf)
        {
            NSData * data = [NSData dataWithBytes:pBuf->Start() length:pBuf->DataLength()];
            CBMutableCharacteristic * characteristic = bleListener.characteristic2;

            if (![bleListener.peripheralManager updateValue:data forCharacteristic:characteristic onSubscribedCentrals:nil]) {
                ChipLogError(Ble, "MessageHasBeen added to the queeu");
                // If udpateValue has not succeeded, it means the queue is full and peripheralManagerIsReadyToUpdateSubscribers will
                // be called once it is ready. Keep the data into a queue until it has been sent.
                [bleListener.messageQueue addObject:data];
                return;
            }

            // CBPeripheralManager API does not provide an API to know if the indication has been received, so just assume it
            // does.
            dispatch_async(bleListener.chipWorkQueue, ^{
                void * connObj = (__bridge void *) bleListener.peripheralManager;
                bleListener.mBleLayer->HandleIndicationConfirmation(
                    connObj, &chip::Ble::CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);
            });
        }

        CHIP_ERROR BlePeripheral::StartAdvertising()
        {
            ChipLogProgress(chipTool, ">> BlePeripheral::StartAdvertising");
            return CHIP_NO_ERROR;
        }

        CHIP_ERROR BlePeripheral::StopAdvertising()
        {
            ChipLogProgress(chipTool, ">> BlePeripheral::StopAdvertising");
            return CHIP_NO_ERROR;
        }

    }
}
}

@implementation BleListener

- (id)initWithDiscriminator:(uint16_t)deviceDiscriminator
{
    self = [super init];
    if (self) {
        self.shortServiceUUID = [UUIDHelper GetShortestServiceUUID:&chip::Ble::CHIP_BLE_SVC_ID];
        _deviceDiscriminator = deviceDiscriminator;
        _workQueue = dispatch_queue_create("com.chip.ble.work_queue", DISPATCH_QUEUE_SERIAL);
        _chipWorkQueue = chip::DeviceLayer::PlatformMgrImpl().GetWorkQueue();
        _peripheralManager = [CBPeripheralManager alloc];
        _messageQueue = [NSMutableArray arrayWithCapacity:1];
    }

    return self;
}

- (void)setBleLayer:(chip::Ble::BleLayer *)bleLayer
{
    _mBleLayer = bleLayer;
}

- (void)start
{
    ChipLogError(Ble, "%u", _deviceDiscriminator);

    uint8_t opcode = 0;

    uint8_t bytes[3] = {};
    bytes[0] = opcode;
    bytes[1] = (_deviceDiscriminator & 0xFF);
    bytes[2] = (_deviceDiscriminator >> 8) & 0xFF;

    NSData * value = [NSData dataWithBytes:bytes length:sizeof(bytes)];
    IgnoreUnusedVariable(value);

    _characteristic1 = [[CBMutableCharacteristic alloc] initWithType:[CBUUID UUIDWithString:@"18EE2EF5-263D-4559-959F-4F9C429F9D11"]
                                                          properties:CBCharacteristicPropertyWrite
                                                               value:nil
                                                         permissions:CBAttributePermissionsWriteable];

    _characteristic2 = [[CBMutableCharacteristic alloc] initWithType:[CBUUID UUIDWithString:@"18EE2EF5-263D-4559-959F-4F9C429F9D12"]
                                                          properties:CBCharacteristicPropertyRead | CBCharacteristicPropertyIndicate
                                                               value:nil
                                                         permissions:CBAttributePermissionsReadable];

    CBMutableService * service = [[CBMutableService alloc] initWithType:_shortServiceUUID primary:YES];
    service.characteristics = @[ _characteristic1, _characteristic2 ];
    [self.peripheralManager addService:service];
}

- (void)stop
{
}

// Start CBPeripheralManagerDelegate
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    switch (peripheral.state) {
    case CBManagerStatePoweredOn:
        ChipLogDetail(Ble, "CBManagerState: ON");
        [self start];
        break;
    case CBManagerStatePoweredOff:
        ChipLogDetail(Ble, "CBManagerState: OFF");
        [self stop];
        break;
    case CBManagerStateUnauthorized:
        ChipLogDetail(Ble, "CBManagerState: Unauthorized");
        break;
    case CBManagerStateResetting:
        ChipLogDetail(Ble, "CBManagerState: RESETTING");
        break;
    case CBManagerStateUnsupported:
        ChipLogDetail(Ble, "CBManagerState: UNSUPPORTED");
        break;
    case CBManagerStateUnknown:
        ChipLogDetail(Ble, "CBManagerState: UNKNOWN");
        break;
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary<NSString *, id> *)dict
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    if (nil != error) {
        ChipLogError(Ble, "BLE:Error Adding service to the peripheral: [%s]", [error.localizedDescription UTF8String]);
    }

    NSArray * services = @[ _shortServiceUUID ];

    // Ideally the peripheral will advertise using CBAdvertisementDataServiceDataKey but this is not possible using CoreBluetooth.
    [self.peripheralManager
        startAdvertising:@{ CBAdvertisementDataLocalNameKey : @"Foo", CBAdvertisementDataServiceUUIDsKey : services }];
}

- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    if (nil != error) {
        ChipLogError(Ble, "BLE:Error Adding service to the peripheral: [%s]", [error.localizedDescription UTF8String]);
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral
                         central:(CBCentral *)central
    didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    dispatch_async(_chipWorkQueue, ^{
        _mBleLayer->HandleSubscribeReceived(
            (__bridge void *) self.peripheralManager, &chip::Ble::CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);
    });
    dispatch_async(_chipWorkQueue, ^{
    {
        chip::DeviceLayer::ChipDeviceEvent connectionEvent;
        connectionEvent.Type = chip::DeviceLayer::DeviceEventType::kCHIPoBLEConnectionEstablished;
        chip::DeviceLayer::PlatformMgr().PostEventOrDie(&connectionEvent);
}
});
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral
                             central:(CBCentral *)central
    didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    dispatch_async(_chipWorkQueue, ^{
        _mBleLayer->HandleUnsubscribeReceived(
            (__bridge void *) self.peripheralManager, &chip::Ble::CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);
    });
}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    while ([_messageQueue count]) {
        ChipLogError(Ble, "MessageHasBeen should be send...");
        if (![peripheral updateValue:_messageQueue[0] forCharacteristic:_characteristic2 onSubscribedCentrals:nil]) {
            ChipLogError(Ble, "MessageHas Not been sent..");
            break;
        }
        ChipLogError(Ble, "Message has been sent..");

        dispatch_async(_chipWorkQueue, ^{
            void * connObj = (__bridge void *) peripheral;
            _mBleLayer->HandleIndicationConfirmation(connObj, &chip::Ble::CHIP_BLE_SVC_ID, &chipUUID_CHIPoBLEChar_TX);
        });

        [_messageQueue removeObjectAtIndex:0];
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray<CBATTRequest *> *)requests
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);

    for (CBATTRequest * request in requests) {
        dispatch_async(_chipWorkQueue, ^{
            const uint8_t * bytes = (const uint8_t *) [request.value bytes];
            uint16_t len = [request.value length];

            ChipLogProgress(Ble, "Receive a packet of len: %u", len);
            auto packet = chip::System::PacketBufferHandle::NewWithData(bytes, len);
            _mBleLayer->HandleWriteReceived((__bridge void *) self.peripheralManager, &chip::Ble::CHIP_BLE_SVC_ID,
                &chipUUID_CHIPoBLEChar_RX, std::move(packet));
            // XXX Check errros...
            [peripheral respondToRequest:request withResult:CBATTErrorSuccess];
        });
    }
}

@end
