/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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

#ifndef CHIP_CLUSTERS_H
#define CHIP_CLUSTERS_H

#import <Foundation/Foundation.h>
#include <stdbool.h>

// Global Response Handlers
typedef void (^DefaultSuccessHandler)(void);
typedef void (^DefaultFailureHandler)(uint8_t status);
typedef void (^BooleanAttributeHandler)(bool value);
typedef void (^Int8uAttributeHandler)(uint8_t value);
typedef void (^Int8sAttributeHandler)(int8_t value);
typedef void (^Int16uAttributeHandler)(uint16_t value);
typedef void (^Int16sAttributeHandler)(int16_t value);
typedef void (^Int32uAttributeHandler)(uint32_t value);
typedef void (^Int32sAttributeHandler)(int32_t value);
typedef void (^Int64uAttributeHandler)(uint64_t value);
typedef void (^Int64sAttributeHandler)(int64_t value);
typedef void (^ReadReportingConfigurationReportedHandler)(uint16_t minInterval, uint16_t maxInterval);
typedef void (^ReadReportingConfigurationReceivedHandler)(uint16_t timeout);

// Cluster Specific Response Handlers

// This is a temporary workarounds for attributes that are not correctly handled yet.
typedef void (^UnsupportedAttributeHandler)(void);

@class CHIPDevice;

NS_ASSUME_NONNULL_BEGIN

@interface CHIPOnOff : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)off:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)on:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)toggle:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeOnOff:(BooleanAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeOnOff:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
            onReportCallback:(BooleanAttributeHandler)onReportCallback
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* CHIP_CLUSTERS_H */
