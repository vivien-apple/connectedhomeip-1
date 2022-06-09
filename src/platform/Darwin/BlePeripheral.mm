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

#include <platform/CHIPDeviceLayer.h>
#include <platform/CommissionableDataProvider.h>
#include <platform/Darwin/BlePeripheral.h>
#include <platform/Darwin/BlePlatformDelegate.h>

#import "UUIDHelper.h"

@interface BleListener : NSObject <CBPeripheralManagerDelegate, CBPeripheralDelegate>

@property (strong, nonatomic) CBPeripheralManager * peripheralManager;
@property (strong, nonatomic) CBMutableService * service;
@property (strong, nonatomic) CBMutableCharacteristic * c1;
@property (strong, nonatomic) CBMutableCharacteristic * c2;
@property (strong, nonatomic) NSMutableArray * messageQueue;

@property (strong, nonatomic) NSString * deviceName;
@property (nonatomic) BOOL isAdvertisingEnabled;
@property (nonatomic) uint16_t deviceDiscriminator;

- (id)initWithDiscriminator:(uint16_t)discriminator;
- (void)startAdvertising;
- (void)stopAdvertising;
- (BOOL)isAdvertising;
- (void)updateAdvertisingState;
- (BOOL)updateC2WithValue:(NSData *)value;

@end

using namespace chip::DeviceLayer;
using namespace chip::Ble;

namespace {
BleListener * bleListener = nil;
}

namespace chip {
namespace DeviceLayer {
    namespace Internal {
        bool BlePlatformDelegateImpl::SendIndication(
            BLE_CONNECTION_OBJECT connObj, const ChipBleUUID * svcId, const ChipBleUUID * charId, PacketBufferHandle pBuf)
        {
            if (nullptr == svcId || nullptr == charId || pBuf.IsNull()) {
                return false;
            }

            auto data = [NSData dataWithBytes:pBuf->Start() length:pBuf->DataLength()];
            if (![bleListener updateC2WithValue:data]) {
                // If updateValue has not succeeded, it means the queue is full and peripheralManagerIsReadyToUpdateSubscribers will
                // be called once it is ready. Keep the data into a queue until it has been sent.
                [bleListener.messageQueue addObject:data];
            }
            return true;
        }

        CHIP_ERROR BlePeripheral::Init()
        {
            uint16_t discriminator;
            ReturnErrorOnFailure(GetCommissionableDataProvider()->GetSetupDiscriminator(discriminator));
            bleListener = [[BleListener alloc] initWithDiscriminator:discriminator];

            auto workQueue = dispatch_queue_create("com.chip.ble.peripheral.work_queue", DISPATCH_QUEUE_SERIAL);
            bleListener.peripheralManager = [[CBPeripheralManager alloc] initWithDelegate:bleListener queue:workQueue];
            return CHIP_NO_ERROR;
        }

        CHIP_ERROR BlePeripheral::SetAdvertisingEnabled(bool enabled)
        {
            ReturnErrorCodeIf(bleListener == nil, CHIP_ERROR_INCORRECT_STATE);

            bleListener.isAdvertisingEnabled = enabled;
            [bleListener updateAdvertisingState];

            return CHIP_NO_ERROR;
        }

        bool BlePeripheral::IsAdvertisingEnabled() { return bleListener != nil ? bleListener.isAdvertisingEnabled : false; }

        bool BlePeripheral::IsAdvertising() { return bleListener != nil ? [bleListener isAdvertising] : false; }

        CHIP_ERROR BlePeripheral::SetAdvertisingMode(ConnectivityManager::BLEAdvertisingMode mode)
        {
            ReturnErrorCodeIf(bleListener == nil, CHIP_ERROR_INCORRECT_STATE);

            // TODO Do something with the advertising mode
            return CHIP_NO_ERROR;
        }

        CHIP_ERROR BlePeripheral::GetDeviceName(char * buffer, size_t bufferSize)
        {
            ReturnErrorCodeIf(bleListener == nil, CHIP_ERROR_INCORRECT_STATE);

            auto deviceName = [bleListener.deviceName UTF8String];
            ReturnErrorCodeIf(strlen(deviceName) >= bufferSize, CHIP_ERROR_BUFFER_TOO_SMALL);
            strcpy(buffer, deviceName);
            return CHIP_NO_ERROR;
        }

        CHIP_ERROR BlePeripheral::SetDeviceName(const char * deviceName)
        {
            ReturnErrorCodeIf(bleListener == nil, CHIP_ERROR_INCORRECT_STATE);

            NSString * name = nil;

            if (deviceName != nullptr && deviceName[0] != 0) {
                name = [NSString stringWithUTF8String:deviceName];
            } else {
                uint16_t discriminator;
                ReturnErrorOnFailure(GetCommissionableDataProvider()->GetSetupDiscriminator(discriminator));
                name = [NSString stringWithFormat:@"%s%04u", CHIP_DEVICE_CONFIG_BLE_DEVICE_NAME_PREFIX, discriminator];
            }

            bleListener.deviceName = name;
            return CHIP_NO_ERROR;
        }
    }
}
}

@implementation BleListener

- (id)initWithDiscriminator:(uint16_t)discriminator
{
    self = [super init];
    if (self) {
        _isAdvertisingEnabled = NO;
        _deviceDiscriminator = discriminator;
        _messageQueue = [NSMutableArray arrayWithCapacity:1];

        auto shortServiceUUID = [UUIDHelper GetShortestServiceUUID:&CHIP_BLE_SVC_ID];
        auto c1_UUID = [CBUUID UUIDWithString:@"18EE2EF5-263D-4559-959F-4F9C429F9D11"];
        auto c2_UUID = [CBUUID UUIDWithString:@"18EE2EF5-263D-4559-959F-4F9C429F9D12"];

        _c1 = [[CBMutableCharacteristic alloc] initWithType:c1_UUID
                                                 properties:CBCharacteristicPropertyWrite
                                                      value:nil
                                                permissions:CBAttributePermissionsWriteable];
        _c2 = [[CBMutableCharacteristic alloc] initWithType:c2_UUID
                                                 properties:CBCharacteristicPropertyRead | CBCharacteristicPropertyIndicate
                                                      value:nil
                                                permissions:CBAttributePermissionsReadable];
        _service = [[CBMutableService alloc] initWithType:shortServiceUUID primary:YES];

        _service.characteristics = @[ _c1, _c2 ];
    }

    return self;
}

- (BOOL)isAdvertising
{
    return [_peripheralManager isAdvertising];
}

- (void)startAdvertising
{
    // If the device is already advertising, just returns.
    if ([self isAdvertising]) {
        return;
    }

    [_peripheralManager removeService:_service];
    [_peripheralManager addService:_service];
}

- (void)stopAdvertising
{
    // If the device is already NOT advertising, just returns.
    if (![self isAdvertising]) {
        return;
    }

    [_peripheralManager stopAdvertising];

    ChipDeviceEvent event;
    event.Type = DeviceEventType::kCHIPoBLEAdvertisingChange;
    event.CHIPoBLEAdvertisingChange.Result = kActivity_Stopped;
    PlatformMgrImpl().PostEventOrDie(&event);
}

- (void)updateAdvertisingState
{
    VerifyOrReturn(_isAdvertisingEnabled, [self stopAdvertising]);
    VerifyOrReturn(CBManagerStatePoweredOn == _peripheralManager.state, [self stopAdvertising]);

    [self startAdvertising];
}

- (BOOL)updateC2WithValue:(NSData *)value
{
    if (![_peripheralManager updateValue:value forCharacteristic:_c2 onSubscribedCentrals:nil]) {
        return NO;
    }

    // CBPeripheralManager API does not provide an API to know if the indication has been received, so just assume it
    // does.
    ChipDeviceEvent event;
    event.Type = DeviceEventType::kCHIPoBLEIndicateConfirm;
    event.CHIPoBLEIndicateConfirm.ConId = (__bridge void *) _peripheralManager;
    PlatformMgrImpl().PostEventOrDie(&event);

    return YES;
}

// Start CBPeripheralManagerDelegate
- (void)peripheralManagerDidUpdateState:(CBPeripheralManager *)peripheral
{
    [self updateAdvertisingState];
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didAddService:(CBService *)service error:(NSError *)error
{
    VerifyOrReturn(nil == error, ChipLogError(Ble, "Add service error: [%s]", [error.localizedDescription UTF8String]));


// Normaly the peripheral will advertise using CBAdvertisementDataServiceDataKey but this is not possible using CoreBluetooth.
#if CONFIG_USE_BLE_MOCK
    uint8_t opcode = 0;
    uint8_t bytes[8] = {};
    bytes[0] = opcode;
    bytes[1] = (_deviceDiscriminator & 0xFF);
    bytes[2] = (_deviceDiscriminator >> 8) & 0xFF;

    NSData * value = [NSData dataWithBytes:bytes length:sizeof(bytes)];

    NSDictionary * advertisement =
        @{ CBAdvertisementDataLocalNameKey : _deviceName, CBAdvertisementDataServiceDataKey : @{ _service.UUID: value } };
#else
    NSArray * services = @[ service.UUID ];
    NSDictionary * advertisement =
        @{ CBAdvertisementDataLocalNameKey : _deviceName, CBAdvertisementDataServiceUUIDsKey : services };
#endif

    [_peripheralManager startAdvertising:advertisement];
}

- (void)peripheralManagerDidStartAdvertising:(CBPeripheralManager *)peripheral error:(NSError *)error
{
    VerifyOrReturn(nil == error, ChipLogError(Ble, "Start advertising error: [%s]", [error.localizedDescription UTF8String]));

    ChipDeviceEvent event;
    event.Type = DeviceEventType::kCHIPoBLEAdvertisingChange;
    event.CHIPoBLEAdvertisingChange.Result = kActivity_Started;
    PlatformMgrImpl().PostEventOrDie(&event);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral
                         central:(CBCentral *)central
    didSubscribeToCharacteristic:(CBCharacteristic *)characteristic
{
    ChipDeviceEvent event;
    event.Type = DeviceEventType::kCHIPoBLESubscribe;
    event.CHIPoBLESubscribe.ConId = (__bridge void *) peripheral;
    PlatformMgrImpl().PostEventOrDie(&event);
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral
                             central:(CBCentral *)central
    didUnsubscribeFromCharacteristic:(CBCharacteristic *)characteristic
{
    ChipDeviceEvent event;
    event.Type = DeviceEventType::kCHIPoBLEUnsubscribe;
    event.CHIPoBLEUnsubscribe.ConId = (__bridge void *) peripheral;
    PlatformMgrImpl().PostEventOrDie(&event);
}

- (void)peripheralManagerIsReadyToUpdateSubscribers:(CBPeripheralManager *)peripheral
{
    while ([_messageQueue count]) {
        if (![self updateC2WithValue:_messageQueue[0]]) {
            break;
        }
        [_messageQueue removeObjectAtIndex:0];
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveWriteRequests:(NSArray<CBATTRequest *> *)requests
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);

    for (CBATTRequest * request in requests) {
        auto bytes = (const uint8_t *) [request.value bytes];
        auto bytesLen = [request.value length];
        auto packet = chip::System::PacketBufferHandle::NewWithData(bytes, bytesLen);

        ChipDeviceEvent event;
        event.Type = DeviceEventType::kCHIPoBLEWriteReceived;
        event.CHIPoBLEWriteReceived.ConId = (__bridge void *) peripheral;
        event.CHIPoBLEWriteReceived.Data = std::move(packet).UnsafeRelease();
        PlatformMgrImpl().PostEventOrDie(&event);

        [peripheral respondToRequest:request withResult:CBATTErrorSuccess];
    }
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral didReceiveReadRequest:(CBATTRequest *)request
{
    // Nothing to do.
}

- (void)peripheralManager:(CBPeripheralManager *)peripheral willRestoreState:(NSDictionary<NSString *, id> *)dict
{
    // Nothing to do.
}

@end
