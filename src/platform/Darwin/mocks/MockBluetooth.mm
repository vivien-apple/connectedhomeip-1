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
 *          Provides a mock implementation of CoreBluetooth for Darwin platforms.
 */

#import "MockBluetoothNetwork.h"

#import <lib/support/CHIPMem.h>
#import <lib/support/CodeUtils.h>
#import <lib/support/logging/CHIPLogging.h>

NSString * const CBAdvertisementDataIsConnectable = @"kCBAdvDataIsConnectable";
NSString * const CBAdvertisementDataServiceDataKey = @"kCBAdvDataServiceData";
NSString * const CBAdvertisementDataLocalNameKey = @"kCBAdvDataLocalName";
NSString * const CBAdvertisementDataServiceUUIDsKey = @"kCBAdvDataServiceUUIDs";

@interface CBUUID ()
+ (NSString *)toHexString:(NSData *)data;
+ (NSData *)fromHexString:(NSString *)string;
@end

@interface CBCharacteristic ()
@property (assign, readwrite, nonatomic) CBService * service;
@property (readwrite) BOOL isNotifying;
@property (retain, readwrite, nullable) NSData * value;
@end

@interface CBService ()
@property (assign, nonatomic) BOOL isPrimary;
@property (retain, nonatomic, readwrite, nullable) NSArray<CBCharacteristic *> * characteristics;
@end

@interface CBManager ()
@property (nonatomic, assign, readwrite) CBManagerState state;
@property (strong, nonatomic) dispatch_queue_t queue;
@end

@interface CBPeripheral ()
@property (weak, nonatomic) CBCentralManager * manager;
@property (retain, readwrite, nullable) NSArray<CBService *> * services;
@end

@interface CBCentralManager () <CentralManagerServerDelegate>
@property (unsafe_unretained, nonatomic) PeripheralManagerClient * client;
@property (unsafe_unretained, nonatomic) CentralManagerServer * server;
@property (strong, nonatomic) CBPeripheral * peripheral;
@end

@interface CBPeripheralManager () <PeripheralManagerServerDelegate>
@property (strong, nonatomic) CBMutableService * service;
@property (strong, nonatomic) NSDictionary<NSString *, id> * advertisementData;
@property (unsafe_unretained, nonatomic) PeripheralManagerServer server;
@property (unsafe_unretained, nonatomic) CentralManagerClient client;
@end

//
// +====================================+
// | CBUUID                             |
// +------------------------------------+
//

@implementation CBUUID : NSObject
+ (CBUUID *)UUIDWithString:(NSString *)string
{
    CBUUID * instance = [[self alloc] init];
    instance->_UUIDString = string;
    instance->_data = [CBUUID fromHexString:string];
    return instance;
}

+ (CBUUID *)UUIDWithData:(NSData *)data
{
    CBUUID * instance = [[self alloc] init];
    instance->_UUIDString = [CBUUID toHexString:data];
    instance->_data = data;
    return instance;
}

+ (CBUUID *)UUIDWithCFUUID:(CFUUIDRef)theUUID
{
    return [self init];
}

+ (CBUUID *)UUIDWithNSUUID:(NSUUID *)theUUID
{
    return [self init];
}

- (id)copyWithZone:(nullable NSZone *)zone
{
    CBUUID * newUUID = [[CBUUID alloc] init];
    newUUID->_data = [_data copyWithZone:zone];
    newUUID->_UUIDString = [_UUIDString copyWithZone:zone];
    return newUUID;
}

+ (NSString *)toHexString:(NSData *)data
{
    if (data == nil) {
        return nil;
    }

    NSMutableString * hexString = [[NSMutableString alloc] init];

    const char * bytes = static_cast<const char *>([data bytes]);
    for (NSUInteger i = 0; i < [data length]; i++) {
        if (i == 4 || i == 6 || i == 8 || i == 10) {
            [hexString appendString:@"-"];
        }
        [hexString appendFormat:@"%02hhx", bytes[i]];
    }

    return [hexString uppercaseString];
}

+ (NSData *)fromHexString:(NSString *)string
{
    string = [string lowercaseString];
    string = [string stringByReplacingOccurrencesOfString:@"-" withString:@""];

    NSMutableData * data = [[NSMutableData alloc] init];

    char byte_chars[3] = { '\0', '\0', '\0' };
    int i = 0;
    int length = (int) string.length;

    while (i < length - 1) {
        byte_chars[0] = [string characterAtIndex:i++];
        byte_chars[1] = [string characterAtIndex:i++];

        auto value = strtol(byte_chars, NULL, 16);
        [data appendBytes:&value length:1];
    }

    return data;
}

@end

//
// +====================================+
// | CBManager                          |
// +------------------------------------+
//

@implementation CBManager
+ (CBManagerAuthorization)authorization
{
    return CBManagerAuthorizationNotDetermined;
}

- (id)initWithOptions:(nullable NSDictionary<NSString *, id> *)options
{
    if (self = [super init]) {
    }

    return self;
}
@end

//
// +====================================+
// | CBPeripheral                       |
// +------------------------------------+
//

@implementation CBPeripheral

- (instancetype)initWithManager:(CBCentralManager *)manager
{
    _manager = manager;

    return self;
}

- (void)setDelegate:(id<CBPeripheralDelegate>)delegate
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    self->_delegate = delegate;
}

- (void)readRSSI
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (id)valueForKey:(NSString *)key
{
    if ([key isEqual:@"mtuLength"]) {
        return @2048;
    } else if ([key isEqual:@"manager"]) {
        return _manager;
    } else {
        return nil;
    }
}

- (void)discoverServices:(nullable NSArray<CBUUID *> *)serviceUUIDs
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _manager.client->DiscoverServices(serviceUUIDs);
}

- (void)writeValue:(NSData *)data forCharacteristic:(CBCharacteristic *)characteristic type:(CBCharacteristicWriteType)type
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    // TODO Handle without response
    _manager.client->WriteValue(characteristic, data);
}

- (void)discoverCharacteristics:(nullable NSArray<CBUUID *> *)characteristicUUIDs forService:(CBService *)service
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _manager.client->DiscoverCharacteristics(characteristicUUIDs, service);
}

- (void)readValueForCharacteristic:(CBCharacteristic *)characteristic
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)setNotifyValue:(BOOL)enabled forCharacteristic:(CBCharacteristic *)characteristic
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    enabled ? _manager.client->SubscribeValue(characteristic) : _manager.client->UnsubscribeValue(characteristic);

    dispatch_async(_manager.queue, ^{
        characteristic.isNotifying = enabled;
        if (_delegate && [_delegate respondsToSelector:@selector(peripheral:didUpdateNotificationStateForCharacteristic:error:)]) {
            [_delegate peripheral:self didUpdateNotificationStateForCharacteristic:characteristic error:nil];
        }
    });
}

- (NSUInteger)maximumWriteValueLengthForType:(CBCharacteristicWriteType)type
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
    return 0;
}

- (void)openL2CAPChannel:(CBL2CAPPSM)PSM
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)discoverDescriptorsForCharacteristic:(CBCharacteristic *)characteristic
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)readValueForDescriptor:(CBDescriptor *)descriptor
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)writeValue:(NSData *)data forDescriptor:(CBDescriptor *)descriptor
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)discoverIncludedServices:(nullable NSArray<CBUUID *> *)includedServiceUUIDs forService:(CBService *)service
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

@end

//
// +====================================+
// | CBCentralManager                   |
// +------------------------------------+
//

@implementation CBCentralManager
- (instancetype)init
{
    return [self initWithDelegate:nil queue:nil options:nil];
}

- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate queue:(nullable dispatch_queue_t)queue
{
    return [self initWithDelegate:delegate queue:queue options:nil];
}

- (instancetype)initWithDelegate:(nullable id<CBCentralManagerDelegate>)delegate
                           queue:(nullable dispatch_queue_t)queue
                         options:(nullable NSDictionary<NSString *, id> *)options
{
    if (self = [super initWithOptions:options]) {
        self.queue = queue;
        _delegate = delegate;
        _client = chip::Platform::New<PeripheralManagerClient>();
        _client->SetDispatchQueue(queue);
        _client->SetDelegate(self);

        _server = chip::Platform::New<CentralManagerServer>();
        _server->SetDispatchQueue(queue);
        _server->SetDelegate(self);
        _server->Start();

        dispatch_async(queue, ^{
            self.state = CBManagerStatePoweredOn;
            if (delegate && [delegate respondsToSelector:@selector(centralManagerDidUpdateState:)]) {
                [delegate centralManagerDidUpdateState:self];
            }
        });
    }

    return self;
}

- (void)dealloc
{
    _server->Stop();
    chip::Platform::Delete<CentralManagerServer>(_server);
    chip::Platform::Delete<PeripheralManagerClient>(_client);
}

- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _peripheral = nil;
    dispatch_async(self.queue, ^{
        if (_delegate && [_delegate respondsToSelector:@selector(centralManager:didDisconnectPeripheral:error:)]) {
            [_delegate centralManager:self didDisconnectPeripheral:peripheral error:nil];
        }
    });
}

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(nullable NSDictionary<NSString *, id> *)options
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _peripheral = peripheral;
    dispatch_async(self.queue, ^{
        if (_delegate && [_delegate respondsToSelector:@selector(centralManager:didConnectPeripheral:)]) {
            [_delegate centralManager:self didConnectPeripheral:peripheral];
        }
    });
}

- (void)stopScan
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _isScanning = false;
}

- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs
                               options:(nullable NSDictionary<NSString *, id> *)options
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _isScanning = true;
    _client->ScanAdvertisement();
}

- (NSArray<CBPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
    return nil;
}

- (NSArray<CBPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
    return nil;
}

// Start CentralManagerServerDelegate

- (void)onAdvertisementDataResponse:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI
{
    if (_isScanning) {
        CBPeripheral * peripheral = [[CBPeripheral alloc] initWithManager:self];
        if (_delegate && [_delegate respondsToSelector:@selector(centralManager:didDiscoverPeripheral:advertisementData:RSSI:)]) {
            [_delegate centralManager:self didDiscoverPeripheral:peripheral advertisementData:advertisementData RSSI:RSSI];
        }
    }
}

- (void)onDiscoverServicesResponse:(NSArray<CBService *> *)services
{
    _peripheral.services = services;
    [_peripheral.delegate peripheral:_peripheral didDiscoverServices:nil];
}

- (void)onDiscoverCharacteristicsResponse:(NSArray<CBCharacteristic *> *)characteristics
{
    _peripheral.services[0].characteristics = characteristics;
    if (_peripheral.delegate &&
        [_peripheral.delegate respondsToSelector:@selector(peripheral:didDiscoverCharacteristicsForService:error:)]) {
        [_peripheral.delegate peripheral:_peripheral didDiscoverCharacteristicsForService:_peripheral.services[0] error:nil];
    }
}

- (void)onWriteValueResponse
{
    auto characteristic = _peripheral.services[0].characteristics[0];
    if (_peripheral.delegate &&
        [_peripheral.delegate respondsToSelector:@selector(peripheral:didWriteValueForCharacteristic:error:)]) {
        [_peripheral.delegate peripheral:_peripheral didWriteValueForCharacteristic:characteristic error:nil];
    }
}

- (void)onUpdateValue:(NSData *)value
{
    auto characteristic = _peripheral.services[0].characteristics[1];
    characteristic.value = value;
    if (_peripheral.delegate &&
        [_peripheral.delegate respondsToSelector:@selector(peripheral:didUpdateValueForCharacteristic:error:)]) {
        [_peripheral.delegate peripheral:_peripheral didUpdateValueForCharacteristic:characteristic error:nil];
    }
}

// End CentralManagerServerDelegate

@end

//
// +====================================+
// | CBPeer                             |
// +------------------------------------+
//

@implementation CBPeer
- (id)copyWithZone:(NSZone *)zone
{
    return [self init];
}
@end

//
// +====================================+
// | CBCentral                          |
// +------------------------------------+
//

@implementation CBCentral
@end

//
// +====================================+
// | CBPeripheralManager                |
// +------------------------------------+
//

@implementation CBPeripheralManager

- (instancetype)init
{
    return [self initWithDelegate:nil queue:nil options:nil];
}

- (instancetype)initWithDelegate:(id<CBPeripheralManagerDelegate>)delegate queue:(dispatch_queue_t)queue
{
    return [self initWithDelegate:delegate queue:queue options:nil];
}

- (instancetype)initWithDelegate:(id<CBPeripheralManagerDelegate>)delegate
                           queue:(dispatch_queue_t)queue
                         options:(NSDictionary<NSString *, id> *)options
{
    if (self = [super initWithOptions:options]) {
        _delegate = delegate;
        self.queue = queue;

        _client.SetDispatchQueue(queue);

        _server.SetDispatchQueue(queue);
        _server.SetDelegate(self);
        _server.Start();

        dispatch_async(self.queue, ^{
            self.state = CBManagerStatePoweredOn;
            if (_delegate && [_delegate respondsToSelector:@selector(peripheralManagerDidUpdateState:)]) {
                [_delegate peripheralManagerDidUpdateState:self];
            }
        });
    }
    return self;
}

- (void)startAdvertising:(NSDictionary<NSString *, id> *)advertisementData
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _isAdvertising = YES;
    dispatch_async(self.queue, ^{
        _advertisementData = advertisementData;
        if (_delegate && [_delegate respondsToSelector:@selector(peripheralManagerDidStartAdvertising:error:)]) {
            [_delegate peripheralManagerDidStartAdvertising:self error:nil];
        }
    });
}

- (void)stopAdvertising
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _isAdvertising = NO;
    dispatch_async(self.queue, ^{
        _advertisementData = nil;
    });
}

- (void)addService:(CBMutableService *)service
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    dispatch_async(self.queue, ^{
        _service = service;
        if (_delegate && [_delegate respondsToSelector:@selector(peripheralManager:didAddService:error:)]) {
            [_delegate peripheralManager:self didAddService:service error:nil];
        }
    });
}

- (void)removeService:(CBMutableService *)service
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    dispatch_async(self.queue, ^{
        _service = nil;
    });
}

- (void)removeAllServices
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    dispatch_async(self.queue, ^{
        _service = nil;
    });
}

- (void)respondToRequest:(CBATTRequest *)request withResult:(CBATTError)result
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _client.WriteResponse();
}

- (BOOL)updateValue:(NSData *)value
       forCharacteristic:(CBMutableCharacteristic *)characteristic
    onSubscribedCentrals:(NSArray<CBCentral *> *)centrals
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    _client.UpdateValue(value);
    return YES;
}

- (void)setDesiredConnectionLatency:(CBPeripheralManagerConnectionLatency)latency forCentral:(CBCentral *)central
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)publishL2CAPChannelWithEncryption:(BOOL)encryptionRequired
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

- (void)unpublishL2CAPChannel:(CBL2CAPPSM)PSM
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    chipDie();
}

+ (CBPeripheralManagerAuthorizationStatus)authorizationStatus
{
    ChipLogProgress(Ble, "%s", __FUNCTION__);
    return CBPeripheralManagerAuthorizationStatusNotDetermined;
}

// Start PeripheralManagerServerDelegate

- (void)onAdvertisementDataRequest
{
    if (_advertisementData) {
        _client.AdvertisementData(_advertisementData);
    }
}

- (void)onDiscoverServicesRequest
{
    if (_service) {
        _client.DiscoverServices(@[ _service ]);
    }
}

- (void)onDiscoverCharacteristicsRequest
{
    if (_service && _service.characteristics) {
        _client.DiscoverCharacteristics(_service.characteristics);
    }
}

- (void)onSubscribeCharacteristicRequest
{
    if (_service && _service.characteristics) {
        CBCentral * central = [CBCentral alloc];
        if (_delegate && [_delegate respondsToSelector:@selector(peripheralManager:central:didSubscribeToCharacteristic:)]) {
            [_delegate peripheralManager:self central:central didSubscribeToCharacteristic:_service.characteristics[1]];
        }
    }
}

- (void)onUnsubscribeCharacteristicRequest
{
    if (_service && _service.characteristics) {
        CBCentral * central = [CBCentral alloc];
        if (_delegate && [_delegate respondsToSelector:@selector(peripheralManager:central:didUnsubscribeFromCharacteristic:)]) {
            [_delegate peripheralManager:self central:central didUnsubscribeFromCharacteristic:_service.characteristics[1]];
        }
    }
}

- (void)onWriteValueRequest:(NSData *)data
{
    if (_service && _service.characteristics) {
        CBATTRequest * request = [CBATTRequest alloc];
        request.value = data;
        if (_delegate && [_delegate respondsToSelector:@selector(peripheralManager:didReceiveWriteRequests:)]) {
            [_delegate peripheralManager:self didReceiveWriteRequests:@[ request ]];
        }
    }
}

// End PeripheralManagerServerDelegate

@end

//
// +====================================+
// | CBAttribute                        |
// +------------------------------------+
//

@implementation CBAttribute
- (instancetype)initWithUUID:(CBUUID *)UUID
{
    if (self = [super init]) {
        _UUID = UUID;
    }

    return self;
}
@end

//
// +====================================+
// | CBService                          |
// +------------------------------------+
//

@implementation CBService
- (void)setCharacteristics:(NSArray<CBMutableCharacteristic *> *)characteristics
{
    _characteristics = characteristics;
    for (CBMutableCharacteristic * characteristic in characteristics) {
        characteristic.service = self;
    }
}
@end

//
// +====================================+
// | CBMutableService                   |
// +------------------------------------+
//

@implementation CBMutableService
- (instancetype)initWithType:(CBUUID *)UUID primary:(BOOL)isPrimary
{
    if (self = [super initWithUUID:UUID]) {
        self.isPrimary = isPrimary;
    }

    return self;
}
@end

//
// +====================================+
// | CBCharacteristic                   |
// +------------------------------------+
//

@implementation CBCharacteristic
@end

//
// +====================================+
// | CBMutableCharacteristic            |
// +------------------------------------+
//

@implementation CBMutableCharacteristic
- (instancetype)initWithType:(CBUUID *)UUID
                  properties:(CBCharacteristicProperties)properties
                       value:(NSData *)value
                 permissions:(CBAttributePermissions)permissions
{
    if (self = [super initWithUUID:UUID]) {
    }

    return self;
}
@end

//
// +====================================+
// | CBATTRequest                       |
// +------------------------------------+
//
@implementation CBATTRequest
@end
