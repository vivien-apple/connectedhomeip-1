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

@interface CHIPLevelControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)move:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride;
- (BOOL)moveToLevel:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                level:(uint8_t)level
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride;
- (BOOL)moveToLevelWithOnOff:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       level:(uint8_t)level
              transitionTime:(uint16_t)transitionTime;
- (BOOL)moveWithOnOff:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate;
- (BOOL)step:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride;
- (BOOL)stepWithOnOff:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime;
- (BOOL)stop:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride;
- (BOOL)stopWithOnOff:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeCurrentLevel:(Int8uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeCurrentLevel:(DefaultSuccessHandler)onSuccessCallback
                  onFailureCallback:(DefaultFailureHandler)onFailureCallback
                   onReportCallback:(Int8uAttributeHandler)onReportCallback
                        minInterval:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                             change:(uint8_t)change;
- (BOOL)readAttributeRemainingTime:(Int16uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeOptions:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeOptions:(DefaultSuccessHandler)onSuccessCallback
            onFailureCallback:(DefaultFailureHandler)onFailureCallback
                        value:(uint8_t)value;
- (BOOL)readAttributeStartUpCurrentLevel:(Int8uAttributeHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeStartUpCurrentLevel:(DefaultSuccessHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                    value:(uint8_t)value;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPOnOff : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)off:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)offWithEffect:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             effectId:(uint8_t)effectId
        effectVariant:(uint8_t)effectVariant;
- (BOOL)on:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)onWithRecallGlobalScene:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)onWithTimedOff:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
          onOffControl:(uint8_t)onOffControl
                onTime:(uint16_t)onTime
           offWaitTime:(uint16_t)offWaitTime;
- (BOOL)toggle:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeOnOff:(BooleanAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeOnOff:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
            onReportCallback:(BooleanAttributeHandler)onReportCallback
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval;
- (BOOL)readAttributeGlobalSceneControl:(BooleanAttributeHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeOnTime:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeOnTime:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       value:(uint16_t)value;
- (BOOL)readAttributeOffWaitTime:(Int16uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeOffWaitTime:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                            value:(uint16_t)value;
- (BOOL)readAttributeStartUpOnOff:(Int8uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeStartUpOnOff:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint8_t)value;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* CHIP_CLUSTERS_H */
