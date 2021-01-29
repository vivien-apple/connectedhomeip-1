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

@interface CHIPBarrierControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)barrierControlGoToPercent:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                      percentOpen:(uint8_t)percentOpen;
- (BOOL)barrierControlStop:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeBarrierMovingState:(Int8uAttributeHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeBarrierSafetyStatus:(Int16uAttributeHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeBarrierCapabilities:(Int8uAttributeHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeBarrierPosition:(Int8uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPBasic : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)mfgSpecificPing:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)resetToFactoryDefaults:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeZclVersion:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePowerSource:(Int8uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPBinding : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)bind:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               nodeId:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId;
- (BOOL)unbind:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               nodeId:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId;

- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPColorControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)moveColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                rateX:(int16_t)rateX
                rateY:(int16_t)rateY
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveColorTemperature:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    moveMode:(uint8_t)moveMode
                        rate:(uint16_t)rate
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveSaturation:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
              moveMode:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveToColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               colorX:(uint16_t)colorX
               colorY:(uint16_t)colorY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveToColorTemperature:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
              colorTemperature:(uint16_t)colorTemperature
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveToHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  hue:(uint8_t)hue
            direction:(uint8_t)direction
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveToHueAndSaturation:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
                           hue:(uint8_t)hue
                    saturation:(uint8_t)saturation
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride;
- (BOOL)moveToSaturation:(DefaultSuccessHandler)onSuccessCallback
       onFailureCallback:(DefaultFailureHandler)onFailureCallback
              saturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride;
- (BOOL)stepColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                stepX:(int16_t)stepX
                stepY:(int16_t)stepY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)stepColorTemperature:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    stepMode:(uint8_t)stepMode
                    stepSize:(uint16_t)stepSize
              transitionTime:(uint16_t)transitionTime
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride;
- (BOOL)stepHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint8_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;
- (BOOL)stepSaturation:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
              stepMode:(uint8_t)stepMode
              stepSize:(uint8_t)stepSize
        transitionTime:(uint8_t)transitionTime
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride;
- (BOOL)stopMoveStep:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride;

- (BOOL)readAttributeCurrentHue:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeCurrentHue:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                 onReportCallback:(Int8uAttributeHandler)onReportCallback
                      minInterval:(uint16_t)minInterval
                      maxInterval:(uint16_t)maxInterval
                           change:(uint8_t)change;
- (BOOL)readAttributeCurrentSaturation:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeCurrentSaturation:(DefaultSuccessHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback
                        onReportCallback:(Int8uAttributeHandler)onReportCallback
                             minInterval:(uint16_t)minInterval
                             maxInterval:(uint16_t)maxInterval
                                  change:(uint8_t)change;
- (BOOL)readAttributeRemainingTime:(Int16uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeCurrentX:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeCurrentX:(DefaultSuccessHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback
               onReportCallback:(Int16uAttributeHandler)onReportCallback
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change;
- (BOOL)readAttributeCurrentY:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeCurrentY:(DefaultSuccessHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback
               onReportCallback:(Int16uAttributeHandler)onReportCallback
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change;
- (BOOL)readAttributeDriftCompensation:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeCompensationText:(UnsupportedAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorTemperature:(Int16uAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeColorTemperature:(DefaultSuccessHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       onReportCallback:(Int16uAttributeHandler)onReportCallback
                            minInterval:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                                 change:(uint16_t)change;
- (BOOL)readAttributeColorMode:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorControlOptions:(Int8uAttributeHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorControlOptions:(DefaultSuccessHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                    value:(uint8_t)value;
- (BOOL)readAttributeNumberOfPrimaries:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary1X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary1Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary1Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary2X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary2Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary2Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary3X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary3Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary3Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary4X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary4Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary4Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary5X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary5Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary5Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary6X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary6Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributePrimary6Intensity:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeWhitePointX:(Int16uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeWhitePointX:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                            value:(uint16_t)value;
- (BOOL)readAttributeWhitePointY:(Int16uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeWhitePointY:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                            value:(uint16_t)value;
- (BOOL)readAttributeColorPointRX:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointRX:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointRY:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointRY:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointRIntensity:(Int8uAttributeHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointRIntensity:(DefaultSuccessHandler)onSuccessCallback
                         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                     value:(uint8_t)value;
- (BOOL)readAttributeColorPointGX:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointGX:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointGY:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointGY:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointGIntensity:(Int8uAttributeHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointGIntensity:(DefaultSuccessHandler)onSuccessCallback
                         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                     value:(uint8_t)value;
- (BOOL)readAttributeColorPointBX:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointBX:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointBY:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointBY:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeColorPointBIntensity:(Int8uAttributeHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeColorPointBIntensity:(DefaultSuccessHandler)onSuccessCallback
                         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                     value:(uint8_t)value;
- (BOOL)readAttributeEnhancedCurrentHue:(Int16uAttributeHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeEnhancedColorMode:(Int8uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorLoopActive:(Int8uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorLoopDirection:(Int8uAttributeHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorLoopTime:(Int16uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorCapabilities:(Int16uAttributeHandler)onSuccessCallback
                     onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorTempPhysicalMin:(Int16uAttributeHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeColorTempPhysicalMax:(Int16uAttributeHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeCoupleColorTempToLevelMinMireds:(Int16uAttributeHandler)onSuccessCallback
                                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeStartUpColorTemperatureMireds:(Int16uAttributeHandler)onSuccessCallback
                                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeStartUpColorTemperatureMireds:(DefaultSuccessHandler)onSuccessCallback
                                  onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                              value:(uint16_t)value;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPDoorLock : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)clearAllPins:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)clearAllRfids:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)clearHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId;
- (BOOL)clearPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId;
- (BOOL)clearRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId;
- (BOOL)clearWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId
                      userId:(uint16_t)userId;
- (BOOL)clearYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId
                      userId:(uint16_t)userId;
- (BOOL)getHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId;
- (BOOL)getLogRecord:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             logIndex:(uint16_t)logIndex;
- (BOOL)getPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId;
- (BOOL)getRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId;
- (BOOL)getUserType:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId;
- (BOOL)getWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId;
- (BOOL)getYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId;
- (BOOL)lockDoor:(DoorLockClusterLockDoorResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  pin:(char *)pin;
- (BOOL)setHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    scheduleId:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday;
- (BOOL)setPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                  pin:(char *)pin;
- (BOOL)setRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                   id:(char *)id;
- (BOOL)setUserType:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
             userType:(uint8_t)userType;
- (BOOL)setWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
                  daysMask:(uint8_t)daysMask
                 startHour:(uint8_t)startHour
               startMinute:(uint8_t)startMinute
                   endHour:(uint8_t)endHour
                 endMinute:(uint8_t)endMinute;
- (BOOL)setYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime;
- (BOOL)unlockDoor:(DoorLockClusterUnlockDoorResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  pin:(char *)pin;
- (BOOL)unlockWithTimeout:(DefaultSuccessHandler)onSuccessCallback
        onFailureCallback:(DefaultFailureHandler)onFailureCallback
         timeoutInSeconds:(uint16_t)timeoutInSeconds
                      pin:(char *)pin;

- (BOOL)readAttributeLockState:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeLockState:(DefaultSuccessHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback
                onReportCallback:(Int8uAttributeHandler)onReportCallback
                     minInterval:(uint16_t)minInterval
                     maxInterval:(uint16_t)maxInterval;
- (BOOL)readAttributeLockType:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeActuatorEnabled:(BooleanAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPGroups : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)addGroup:(GroupsClusterAddGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
            groupName:(char *)groupName;
- (BOOL)addGroupIfIdentifying:(DefaultSuccessHandler)onSuccessCallback
            onFailureCallback:(DefaultFailureHandler)onFailureCallback
                      groupId:(uint16_t)groupId
                    groupName:(char *)groupName;
- (BOOL)getGroupMembership:(GroupsClusterGetGroupMembershipResponseHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                groupCount:(uint8_t)groupCount
                 groupList:(uint16_t)groupList;
- (BOOL)removeAllGroups:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)removeGroup:(GroupsClusterRemoveGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId;
- (BOOL)viewGroup:(GroupsClusterViewGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId;

- (BOOL)readAttributeNameSupport:(Int8uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPIasZone : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;

- (BOOL)readAttributeZoneState:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeZoneType:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeZoneStatus:(Int16uAttributeHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeIasCieAddress:(Int64uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeIasCieAddress:(DefaultSuccessHandler)onSuccessCallback
                  onFailureCallback:(DefaultFailureHandler)onFailureCallback
                              value:(uint64_t)value;
- (BOOL)readAttributeZoneId:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPIdentify : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)identify:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
         identifyTime:(uint16_t)identifyTime;
- (BOOL)identifyQuery:(IdentifyClusterIdentifyQueryResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (BOOL)readAttributeIdentifyTime:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)writeAttributeIdentifyTime:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint16_t)value;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

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

NS_ASSUME_NONNULL_BEGIN

@interface CHIPScenes : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)addScene:(ScenesClusterAddSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
       transitionTime:(uint16_t)transitionTime
            sceneName:(char *)sceneName
            clusterId:(uint16_t)clusterId
               length:(uint8_t)length
                value:(uint8_t)value;
- (BOOL)getSceneMembership:(ScenesClusterGetSceneMembershipResponseHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                   groupId:(uint16_t)groupId;
- (BOOL)recallScene:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
       transitionTime:(uint16_t)transitionTime;
- (BOOL)removeAllScenes:(ScenesClusterRemoveAllScenesResponseHandler)onSuccessCallback
      onFailureCallback:(DefaultFailureHandler)onFailureCallback
                groupId:(uint16_t)groupId;
- (BOOL)removeScene:(ScenesClusterRemoveSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId;
- (BOOL)storeScene:(ScenesClusterStoreSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId;
- (BOOL)viewScene:(ScenesClusterViewSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId;

- (BOOL)readAttributeSceneCount:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeCurrentScene:(Int8uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeCurrentGroup:(Int16uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeSceneValid:(BooleanAttributeHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeNameSupport:(Int8uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPTemperatureMeasurement : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;

- (BOOL)readAttributeMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)reportAttributeMeasuredValue:(DefaultSuccessHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    onReportCallback:(Int16sAttributeHandler)onReportCallback
                         minInterval:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                              change:(int16_t)change;
- (BOOL)readAttributeMinMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeMaxMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback;
- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* CHIP_CLUSTERS_H */
