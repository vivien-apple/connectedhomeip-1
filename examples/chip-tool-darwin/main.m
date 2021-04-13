/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#import <CHIP/CHIPDevice.h>
#import <CHIP/CHIPDeviceController.h>
#import <CHIP/CHIPDevicePairingDelegate.h>
#import <CHIP/CHIPError.h>
#import <CHIP/CHIPManualSetupPayloadParser.h>
#import <CHIP/CHIPPersistentStorageDelegate.h>
#import <CHIP/CHIPQRCodeSetupPayloadParser.h>
#import <CHIP/CHIPSetupPayload.h>
#import <CHIP/gen/CHIPClustersObjc.h>
#import <Foundation/Foundation.h>

NSString * const kCHIPToolDefaultsDomain = @"com.apple.chiptool";

id CHIPGetDomainValueForKey(NSString * domain, NSString * key)
{
    id value = (id) CFBridgingRelease(CFPreferencesCopyAppValue((CFStringRef) key, (CFStringRef) domain));
    if (value) {
        return value;
    }
    return nil;
}

void CHIPSetDomainValueForKey(NSString * domain, NSString * key, id value)
{
    CFPreferencesSetAppValue((CFStringRef) key, (__bridge CFPropertyListRef _Nullable)(value), (CFStringRef) domain);
    CFPreferencesAppSynchronize((CFStringRef) domain);
}

void CHIPRemoveDomainValueForKey(NSString * domain, NSString * key)
{
    CFPreferencesSetAppValue((CFStringRef) key, NULL, (CFStringRef) domain);
    CFPreferencesAppSynchronize((CFStringRef) domain);
}

@interface CHIPToolPersistentStorageDelegate : NSObject <CHIPPersistentStorageDelegate>
@end

@implementation CHIPToolPersistentStorageDelegate

// MARK: CHIPPersistentStorageDelegate
- (void)CHIPGetKeyValue:(NSString *)key handler:(SendKeyValue)completionHandler
{
    NSString * value = CHIPGetDomainValueForKey(kCHIPToolDefaultsDomain, key);
    NSLog(@"CHIPPersistentStorageDelegate Get Value for Key: %@, value %@", key, value);
    completionHandler(key, value);
}

- (NSString *)CHIPGetKeyValue:(NSString *)key
{
    NSString * value = CHIPGetDomainValueForKey(kCHIPToolDefaultsDomain, key);
    NSLog(@"CHIPPersistentStorageDelegate Get Value for Key: %@, value %@", key, value);
    return value;
}

- (void)CHIPSetKeyValue:(NSString *)key value:(NSString *)value handler:(CHIPSendSetStatus)completionHandler
{
    NSLog(@"CHIPPersistentStorageDelegate Set Value for Key: %@, value %@", key, value);
    CHIPSetDomainValueForKey(kCHIPToolDefaultsDomain, key, value);
    completionHandler(key, [CHIPError errorForCHIPErrorCode:0]);
}

- (void)CHIPDeleteKeyValue:(NSString *)key handler:(CHIPSendDeleteStatus)completionHandler
{
    CHIPRemoveDomainValueForKey(kCHIPToolDefaultsDomain, key);
    completionHandler(key, [CHIPError errorForCHIPErrorCode:0]);
}
@end

CHIPDevice * CHIPGetPairedDevice()
{
    uint64_t deviceId = 12344321;
    NSError * pairingError;
    CHIPDeviceController * controller = [CHIPDeviceController sharedController];
    CHIPDevice * device = [controller getPairedDevice:deviceId error:&pairingError];
    return device;
}

@interface CHIPToolPairingDelegate : NSObject <CHIPDevicePairingDelegate>
@property (nonatomic, strong) CHIPNetworkCommissioning * cluster;
@property (readonly) dispatch_queue_t queue;
- (void)onAddNetworkResponse:(NSError *)error values:(NSDictionary *)values;
@end

@implementation CHIPToolPairingDelegate
- (instancetype)initWithQueue:(dispatch_queue_t)queue
{
    if (self = [super init]) {
        _queue = queue;
    }
    return self;
}

- (void)onNetworkCredentialsRequested:(CHIPNetworkCredentialType)type
{
    NSLog(@"onNetworkCredentialsRequested: %lu", type);
}

- (void)onPairingComplete:(NSError *)error
{
    NSLog(@"onPairingComplete: %@", error);

    dispatch_async(_queue, ^{
        self.cluster = [[CHIPNetworkCommissioning alloc] initWithDevice:CHIPGetPairedDevice()
                                                               endpoint:1
                                                                  queue:dispatch_get_main_queue()];

        __weak typeof(self) weakSelf = self;
        NSData * ssid = [@"Noupy" dataUsingEncoding:NSUTF8StringEncoding];
        NSData * credentials = [@"claireetvivien" dataUsingEncoding:NSUTF8StringEncoding];

        [_cluster addWiFiNetwork:ssid
                     credentials:credentials
                      breadcrumb:0
                       timeoutMs:6000
               completionHandler:^(NSError * err, NSDictionary * values) {
                   [weakSelf onAddNetworkResponse:err values:values];
               }];
    });
}

- (void)onAddNetworkResponse:(NSError *)error values:(NSDictionary *)values
{
    NSLog(@"WiFi added response");
    if (error == nil) {
        NSLog(@"WiFi added success");

        __weak typeof(self) weakSelf = self;
        NSData * ssid = [@"Noupy" dataUsingEncoding:NSUTF8StringEncoding];
        [_cluster enableNetwork:ssid
                     breadcrumb:0
                      timeoutMs:6000
              completionHandler:^(NSError * err, NSDictionary * evalues) {
                  [weakSelf onEnableNetworkResponse:err values:values];
              }];
    }
}

- (void)onEnableNetworkResponse:(NSError *)error values:(NSDictionary *)values
{
    NSLog(@"WiFi enable response");
    if (error == nil) {
        NSLog(@"WiFi enabled success");
        uint64_t deviceId = 12344321;
        CHIPDeviceController * controller = [CHIPDeviceController sharedController];
        [controller updateDevice:deviceId fabricId:0];
    }
}

- (void)onAddressUpdated:(NSError *)error
{
    NSLog(@"mdns response");
    if (error.code == CHIPSuccess) {
        NSLog(@"mdns success");
    }
}

@end

int main(int argc, const char * argv[])
{
    static dispatch_queue_t callbackQueue;
    static CHIPToolPersistentStorageDelegate * storage = nil;
    static CHIPToolPairingDelegate * pairing = nil;

    @autoreleasepool {
        CHIPDeviceController * controller = [CHIPDeviceController sharedController];

        callbackQueue = dispatch_queue_create("com.chip.persistentstorage.callback", DISPATCH_QUEUE_SERIAL);
        storage = [[CHIPToolPersistentStorageDelegate alloc] init];
        pairing = [[CHIPToolPairingDelegate alloc] initWithQueue:callbackQueue];

        [controller startup:storage queue:callbackQueue];
        [controller setPairingDelegate:pairing queue:callbackQueue];

        NSError * error;
        uint64_t deviceId = 12344321;
        uint16_t discriminator = 3840;
        uint32_t setupPINCode = 12345678;
        if ([controller pairDevice:deviceId discriminator:discriminator setupPINCode:setupPINCode error:&error]) {
            NSLog(@"Pairing starts...");
        }

        /*
            uint64_t deviceId = 12344321;
            NSError * pairingError;
           CHIPDevice * device = [controller getPairedDevice:deviceId error:&pairingError];
           CHIPBasic * cluster = [[CHIPBasic alloc] initWithDevice:device endpoint:1 queue:dispatch_get_main_queue()];
           [cluster mfgSpecificPing:^(NSError * error, NSDictionary * values) {
               NSString * resultString = (error == nil) ? @"MfgSpecificPing command: success!"
                                                        : [NSString stringWithFormat:@"An error occured: 0x%02lx", error.code];
               NSLog(@"Result: %@", resultString);
               [controller shutdown];
                exit(EXIT_SUCCESS);
            }];
        */

        [[NSRunLoop currentRunLoop] run];

        return EXIT_SUCCESS;
    }
}
