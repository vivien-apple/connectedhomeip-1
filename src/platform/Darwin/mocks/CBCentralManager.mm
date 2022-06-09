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
 *          Provides a mock implementation of CBCentralManager for Darwin platforms.
 */

#import "../UUIDHelper.h"

#import <lib/support/CodeUtils.h>

static CBManagerAuthorization gAuthorization = CBManagerAuthorizationNotDetermined;

@interface CBManager ()

@property (nonatomic, assign, readwrite) CBManagerState state;

@end

@implementation CBManager

+ (CBManagerAuthorization)authorization
{
    return gAuthorization;
}

- (id)initWithOptions:(nullable NSDictionary<NSString *, id> *)options
{
    self = [super init];
    return self;
}

@end

@interface CBCentralManager ()

@property (strong, nonatomic) dispatch_queue_t queue;

@end

@implementation CBCentralManager

- (void)cancelPeripheralConnection:(CBPeripheral *)peripheral
{
    ChipLogProgress(chipTool, "CancelPeripheralConnection");
}

- (void)connectPeripheral:(CBPeripheral *)peripheral options:(nullable NSDictionary<NSString *, id> *)options
{
    ChipLogProgress(chipTool, "ConnectPeripheral");
}

- (void)stopScan
{
    ChipLogProgress(chipTool, "StopScan");
}

- (void)scanForPeripheralsWithServices:(nullable NSArray<CBUUID *> *)serviceUUIDs
                               options:(nullable NSDictionary<NSString *, id> *)options
{
    ChipLogProgress(chipTool, "ScanForPeripheralsWithServices");

    // TODO Convert this call to a server call such that the device can be filtered
}

- (NSArray<CBPeripheral *> *)retrieveConnectedPeripheralsWithServices:(NSArray<CBUUID *> *)serviceUUIDs
{
    ChipLogProgress(chipTool, "RetrieveConnectedPeripheralsWithServices");
    return nil;
}

- (NSArray<CBPeripheral *> *)retrievePeripheralsWithIdentifiers:(NSArray<NSUUID *> *)identifiers
{
    ChipLogProgress(chipTool, "RetrievePeripheralsWithIdentifiers");
    return nil;
}

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
    self = [super initWithOptions:options];

    self.queue = queue;

    // TODO Add some server listener so the value of 'state' can be changed from the outside
    dispatch_async(queue, ^{
        self.state = CBManagerStatePoweredOn;
        [delegate centralManagerDidUpdateState:self];
    });

    return self;
}

@end

NSString * const CBAdvertisementDataIsConnectable = nil;
NSString * const CBAdvertisementDataServiceDataKey = nil;

@interface CBUUID ()

@property (strong, nonatomic) NSUUID * uuid;

@end

@implementation CBUUID : NSObject

+ (CBUUID *)UUIDWithString:(NSString *)theString
{
    CBUUID * instance = [[self alloc] init];
    instance.uuid = [[NSUUID alloc] initWithUUIDString:theString];
    return instance;
}

+ (CBUUID *)UUIDWithData:(NSData *)theData
{
    CBUUID * instance = [[self alloc] init];
    instance.uuid = [[NSUUID alloc] initWithUUIDBytes:(unsigned char *) theData.bytes];
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
    return [self init];
}

@end
