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

#import <CoreBluetooth/CoreBluetooth.h>

@interface JSONAdvertisement : NSObject
+ (NSData *)toJSON:(NSDictionary<NSString *, id> *)advertisement;
+ (NSDictionary<NSString *, id> *)fromJSON:(NSData *)json;
@end

@interface JSONCharacteristics : NSObject
+ (NSData *)toJSON:(NSArray<CBCharacteristic *> *)characteristics;
+ (NSArray<CBCharacteristic *> *)fromJSON:(NSData *)json;
@end

@interface JSONUUID : NSObject
+ (NSString *)toJSON:(CBUUID *)UUID;
+ (CBUUID *)fromJSON:(NSString *)jsonData;
@end

@interface JSONBool : NSObject
+ (NSNumber *)toJSON:(BOOL)value;
+ (BOOL)fromJSON:(NSNumber *)jsonData;
@end

@interface JSONData : NSObject
+ (NSString *)toJSON:(NSData *)data;
+ (NSData *)fromJSON:(NSString *)jsonData;
@end

@interface JSONCharacteristicProperties : NSObject
+ (NSNumber *)toJSON:(CBCharacteristicProperties)properties;
+ (CBCharacteristicProperties)fromJSON:(NSNumber *)jsonData;
@end

@interface JSONService : NSObject
+ (NSDictionary *)toJSON:(CBService *)service;
+ (CBMutableService *)fromJSON:(NSDictionary *)jsonData;
@end

@interface JSONServices : NSObject
+ (NSData *)toJSON:(NSArray<CBService *> *)services;
+ (NSArray<CBService *> *)fromJSON:(NSData *)jsonData;
@end
