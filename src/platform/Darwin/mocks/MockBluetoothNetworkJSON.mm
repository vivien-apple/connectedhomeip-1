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

#if !__has_feature(objc_arc)
#error This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif

#import "MockBluetoothNetworkJSON.h"

@implementation JSONAdvertisement
+ (NSData *)toJSON:(NSDictionary<NSString *, id> *)advertisement
{
    NSMutableDictionary * jsonServicesData = [[NSMutableDictionary alloc] init];

    NSDictionary * servicesData = advertisement[CBAdvertisementDataServiceDataKey];
    for (CBUUID * serviceUUID in servicesData) {
        NSString * key = serviceUUID.UUIDString;
        NSString * value = [JSONData toJSON:[servicesData objectForKey:serviceUUID]];
        jsonServicesData[key] = value;
    }

    NSDictionary * json = @{
        CBAdvertisementDataIsConnectable : @1,
        CBAdvertisementDataLocalNameKey : advertisement[CBAdvertisementDataLocalNameKey],
        CBAdvertisementDataServiceDataKey : jsonServicesData,
    };

    NSData * jsonData = [NSJSONSerialization dataWithJSONObject:json options:0 error:NULL];
    return jsonData;
}

+ (NSDictionary<NSString *, id> *)fromJSON:(NSData *)jsonData
{
    NSDictionary * json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];

    NSMutableDictionary * servicesData = [[NSMutableDictionary alloc] init];

    for (NSString * key in json[CBAdvertisementDataServiceDataKey]) {
        CBUUID * uuid = [CBUUID UUIDWithString:key];
        NSData * value = [JSONData fromJSON:json[CBAdvertisementDataServiceDataKey][key]];
        servicesData[uuid] = value;
    }

    NSDictionary * advertisement = @{
        CBAdvertisementDataIsConnectable : json[CBAdvertisementDataIsConnectable],
        CBAdvertisementDataLocalNameKey : json[CBAdvertisementDataLocalNameKey],
        CBAdvertisementDataServiceDataKey : servicesData,
    };

    return advertisement;
}
@end

@implementation JSONUUID
+ (NSString *)toJSON:(CBUUID *)UUID
{
    return UUID.UUIDString;
}

+ (CBUUID *)fromJSON:(NSString *)jsonData
{
    return [CBUUID UUIDWithString:jsonData];
}
@end

@implementation JSONCharacteristicProperties
+ (NSNumber *)toJSON:(CBCharacteristicProperties)properties
{
    return [[NSNumber alloc] initWithUnsignedInteger:properties];
}

+ (CBCharacteristicProperties)fromJSON:(NSNumber *)jsonData
{
    return [jsonData unsignedLongValue];
}
@end

@implementation JSONData
+ (NSString *)toJSON:(NSData *)data
{
    if (data == nil) {
        return @"";
    }

    return [data base64EncodedStringWithOptions:0];
}

+ (NSData *)fromJSON:(NSString *)jsonData
{
    if ([jsonData isEqual:@""]) {
        return nil;
    }

    return [[NSData alloc] initWithBase64EncodedString:jsonData options:0];
}
@end

@implementation JSONCharacteristics
+ (NSData *)toJSON:(NSArray<CBCharacteristic *> *)characteristics
{
    NSMutableArray<NSDictionary *> * json = [[NSMutableArray alloc] init];

    for (CBCharacteristic * characteristic in characteristics) {
        NSDictionary * jsonCharacteristic = @{
            @"uuid" : [JSONUUID toJSON:characteristic.UUID],
            @"properties" : [JSONCharacteristicProperties toJSON:characteristic.properties],
            @"value" : [JSONData toJSON:characteristic.value],
            @"service" : [JSONService toJSON:characteristic.service],
        };

        [json addObject:jsonCharacteristic];
    }

    NSData * jsonData = [NSJSONSerialization dataWithJSONObject:json options:0 error:NULL];
    return jsonData;
}

+ (NSArray<CBCharacteristic *> *)fromJSON:(NSData *)jsonData
{
    NSArray * json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];

    NSMutableArray<CBCharacteristic *> * characteristics = [[NSMutableArray alloc] init];

    CBMutableService * service = nil;

    for (NSDictionary * jsonCharacteristic in json) {
        CBUUID * uuid = [JSONUUID fromJSON:jsonCharacteristic[@"uuid"]];
        CBCharacteristicProperties properties = [JSONCharacteristicProperties fromJSON:jsonCharacteristic[@"properties"]];
        NSData * value = [JSONData fromJSON:jsonCharacteristic[@"value"]];

        // How to identify permissions ?
        CBMutableCharacteristic * characteristic = [[CBMutableCharacteristic alloc] initWithType:uuid
                                                                                      properties:properties
                                                                                           value:value
                                                                                     permissions:0];

        if (service == nil) {
            service = [JSONService fromJSON:jsonCharacteristic[@"service"]];
        }

        [characteristics addObject:characteristic];
    }

    service.characteristics = characteristics;

    return characteristics;
}
@end

@implementation JSONBool : NSObject
+ (NSNumber *)toJSON:(BOOL)value
{
    return [NSNumber numberWithBool:value];
}

+ (BOOL)fromJSON:(NSNumber *)jsonData
{
    if (jsonData == nil) {
        return NO;
    }

    return [jsonData boolValue];
}
@end

@implementation JSONService
+ (NSDictionary *)toJSON:(CBService *)service
{
    NSDictionary * json = @{
        @"uuid" : [JSONUUID toJSON:service.UUID],
        @"isPrimary" : [JSONBool toJSON:service.isPrimary],
    };

    return json;
}

+ (CBMutableService *)fromJSON:(NSDictionary *)jsonData
{
    CBUUID * uuid = [JSONUUID fromJSON:jsonData[@"uuid"]];
    BOOL isPrimary = [JSONBool fromJSON:jsonData[@"isPrimary"]];

    CBMutableService * service = [[CBMutableService alloc] initWithType:uuid primary:isPrimary];

    return service;
}
@end

@implementation JSONServices
+ (NSData *)toJSON:(NSArray<CBService *> *)services
{
    NSMutableArray<NSDictionary *> * json = [[NSMutableArray alloc] init];

    for (CBService * service in services) {
        NSDictionary * jsonService = [JSONService toJSON:service];
        [json addObject:jsonService];
    }

    NSData * jsonData = [NSJSONSerialization dataWithJSONObject:json options:0 error:NULL];
    return jsonData;
}

+ (NSArray<CBService *> *)fromJSON:(NSData *)jsonData
{
    NSArray * json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];

    NSMutableArray<CBService *> * services = [[NSMutableArray alloc] init];

    for (NSDictionary * jsonService in json) {
        CBUUID * uuid = [JSONUUID fromJSON:jsonService[@"uuid"]];
        NSNumber * primary;
        if ([jsonService objectForKey:@"isPrimary"] != nil) {
            primary = [NSNumber numberWithBool:jsonService[@"isPrimary"] || NO];
        }

        CBMutableService * service = [[CBMutableService alloc] initWithType:uuid primary:[primary boolValue]];

        [services addObject:service];
    }

    return services;
}
@end
