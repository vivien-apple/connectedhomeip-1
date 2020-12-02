
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

#import <CHIP/CHIPDeviceCallback.h>
#import <Foundation/Foundation.h>

@class CHIPDevice;

NS_ASSUME_NONNULL_BEGIN

@interface CHIPBarrierControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)BarrierControlGoToPercent:(CHIPDeviceCallback)onCompletion percentOpen:(uint8_t)percentOpen;
- (BOOL)BarrierControlStop:(CHIPDeviceCallback)onCompletion;

- (BOOL)ReadAttributeBarrierMovingState:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeBarrierSafetyStatus:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeBarrierCapabilities:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeBarrierPosition:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPBasic : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)ResetToFactoryDefaults:(CHIPDeviceCallback)onCompletion;

- (BOOL)ReadAttributeZclVersion:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePowerSource:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPColorControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)MoveColor:(CHIPDeviceCallback)onCompletion
              rateX:(int16_t)rateX
              rateY:(int16_t)rateY
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveColorTemperature:(CHIPDeviceCallback)onCompletion
                    moveMode:(uint8_t)moveMode
                        rate:(uint16_t)rate
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveHue:(CHIPDeviceCallback)onCompletion
           moveMode:(uint8_t)moveMode
               rate:(uint8_t)rate
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveSaturation:(CHIPDeviceCallback)onCompletion
              moveMode:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveToColor:(CHIPDeviceCallback)onCompletion
             colorX:(uint16_t)colorX
             colorY:(uint16_t)colorY
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveToColorTemperature:(CHIPDeviceCallback)onCompletion
              colorTemperature:(uint16_t)colorTemperature
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveToHue:(CHIPDeviceCallback)onCompletion
                hue:(uint8_t)hue
          direction:(uint8_t)direction
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveToHueAndSaturation:(CHIPDeviceCallback)onCompletion
                           hue:(uint8_t)hue
                    saturation:(uint8_t)saturation
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride;
- (BOOL)MoveToSaturation:(CHIPDeviceCallback)onCompletion
              saturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride;
- (BOOL)StepColor:(CHIPDeviceCallback)onCompletion
              stepX:(int16_t)stepX
              stepY:(int16_t)stepY
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)StepColorTemperature:(CHIPDeviceCallback)onCompletion
                    stepMode:(uint8_t)stepMode
                    stepSize:(uint16_t)stepSize
              transitionTime:(uint16_t)transitionTime
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride;
- (BOOL)StepHue:(CHIPDeviceCallback)onCompletion
           stepMode:(uint8_t)stepMode
           stepSize:(uint8_t)stepSize
     transitionTime:(uint8_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride;
- (BOOL)StepSaturation:(CHIPDeviceCallback)onCompletion
              stepMode:(uint8_t)stepMode
              stepSize:(uint8_t)stepSize
        transitionTime:(uint8_t)transitionTime
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride;
- (BOOL)StopMoveStep:(CHIPDeviceCallback)onCompletion optionsMask:(uint8_t)optionsMask optionsOverride:(uint8_t)optionsOverride;

- (BOOL)ReadAttributeCurrentHue:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeCurrentHue:(CHIPDeviceCallback)onCompletion
                      minInterval:(uint16_t)minInterval
                      maxInterval:(uint16_t)maxInterval
                         onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion
                             minInterval:(uint16_t)minInterval
                             maxInterval:(uint16_t)maxInterval
                                onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeRemainingTime:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeCurrentX:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeCurrentX:(CHIPDeviceCallback)onCompletion
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                       onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeCurrentY:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeCurrentY:(CHIPDeviceCallback)onCompletion
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                       onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeDriftCompensation:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeCompensationText:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorTemperature:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeColorTemperature:(CHIPDeviceCallback)onCompletion
                            minInterval:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                               onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeColorMode:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion value:(uint8_t)value;
- (BOOL)ReadAttributeNumberOfPrimaries:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary1X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary1Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary1Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary2X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary2Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary2Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary3X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary3Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary3Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary4X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary4Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary4Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary5X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary5Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary5Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary6X:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary6Y:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributePrimary6Intensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeWhitePointX:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeWhitePointX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeWhitePointY:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeWhitePointY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointRX:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointRX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointRY:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointRY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value;
- (BOOL)ReadAttributeColorPointGX:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointGX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointGY:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointGY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value;
- (BOOL)ReadAttributeColorPointBX:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointBX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointBY:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointBY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value;
- (BOOL)ReadAttributeEnhancedCurrentHue:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeEnhancedColorMode:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorLoopActive:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorLoopDirection:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorLoopTime:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorCapabilities:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorTempPhysicalMin:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeColorTempPhysicalMax:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeCoupleColorTempToLevelMinMireds:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPDoorLock : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)ClearAllPins:(CHIPDeviceCallback)onCompletion;
- (BOOL)ClearAllRfids:(CHIPDeviceCallback)onCompletion;
- (BOOL)ClearHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId;
- (BOOL)ClearPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId;
- (BOOL)ClearRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId;
- (BOOL)ClearWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId;
- (BOOL)ClearYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId;
- (BOOL)GetHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId;
- (BOOL)GetLogRecord:(CHIPDeviceCallback)onCompletion logIndex:(uint16_t)logIndex;
- (BOOL)GetPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId;
- (BOOL)GetRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId;
- (BOOL)GetUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId;
- (BOOL)GetWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId;
- (BOOL)GetYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId;
- (BOOL)LockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin;
- (BOOL)SetHolidaySchedule:(CHIPDeviceCallback)onCompletion
                    scheduleId:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday;
- (BOOL)SetPin:(CHIPDeviceCallback)onCompletion
        userId:(uint16_t)userId
    userStatus:(uint8_t)userStatus
      userType:(uint8_t)userType
           pin:(char *)pin;
- (BOOL)SetRfid:(CHIPDeviceCallback)onCompletion
         userId:(uint16_t)userId
     userStatus:(uint8_t)userStatus
       userType:(uint8_t)userType
             id:(char *)id;
- (BOOL)SetUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId userType:(uint8_t)userType;
- (BOOL)SetWeekdaySchedule:(CHIPDeviceCallback)onCompletion
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
                  daysMask:(uint8_t)daysMask
                 startHour:(uint8_t)startHour
               startMinute:(uint8_t)startMinute
                   endHour:(uint8_t)endHour
                 endMinute:(uint8_t)endMinute;
- (BOOL)SetYeardaySchedule:(CHIPDeviceCallback)onCompletion
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime;
- (BOOL)UnlockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin;
- (BOOL)UnlockWithTimeout:(CHIPDeviceCallback)onCompletion timeoutInSeconds:(uint16_t)timeoutInSeconds pin:(char *)pin;

- (BOOL)ReadAttributeLockState:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeLockState:(CHIPDeviceCallback)onCompletion
                     minInterval:(uint16_t)minInterval
                     maxInterval:(uint16_t)maxInterval
                        onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeLockType:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeActuatorEnabled:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPGroups : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)AddGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName;
- (BOOL)AddGroupIfIdentifying:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName;
- (BOOL)GetGroupMembership:(CHIPDeviceCallback)onCompletion groupCount:(uint8_t)groupCount groupList:(uint16_t)groupList;
- (BOOL)RemoveAllGroups:(CHIPDeviceCallback)onCompletion;
- (BOOL)RemoveGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId;
- (BOOL)ViewGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId;

- (BOOL)ReadAttributeNameSupport:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPIasZone : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;

- (BOOL)ReadAttributeZoneState:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeZoneType:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeZoneStatus:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion value:(uint64_t)value;
- (BOOL)ReadAttributeZoneId:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPIdentify : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)Identify:(CHIPDeviceCallback)onCompletion identifyTime:(uint16_t)identifyTime;
- (BOOL)IdentifyQuery:(CHIPDeviceCallback)onCompletion;

- (BOOL)ReadAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion;
- (BOOL)WriteAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion value:(uint16_t)value;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPLevelControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)Move:(CHIPDeviceCallback)onCompletion
          moveMode:(uint8_t)moveMode
              rate:(uint8_t)rate
        optionMask:(uint8_t)optionMask
    optionOverride:(uint8_t)optionOverride;
- (BOOL)MoveToLevel:(CHIPDeviceCallback)onCompletion
              level:(uint8_t)level
     transitionTime:(uint16_t)transitionTime
         optionMask:(uint8_t)optionMask
     optionOverride:(uint8_t)optionOverride;
- (BOOL)MoveToLevelWithOnOff:(CHIPDeviceCallback)onCompletion level:(uint8_t)level transitionTime:(uint16_t)transitionTime;
- (BOOL)MoveWithOnOff:(CHIPDeviceCallback)onCompletion moveMode:(uint8_t)moveMode rate:(uint8_t)rate;
- (BOOL)Step:(CHIPDeviceCallback)onCompletion
          stepMode:(uint8_t)stepMode
          stepSize:(uint8_t)stepSize
    transitionTime:(uint16_t)transitionTime
        optionMask:(uint8_t)optionMask
    optionOverride:(uint8_t)optionOverride;
- (BOOL)StepWithOnOff:(CHIPDeviceCallback)onCompletion
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime;
- (BOOL)Stop:(CHIPDeviceCallback)onCompletion optionMask:(uint8_t)optionMask optionOverride:(uint8_t)optionOverride;
- (BOOL)StopWithOnOff:(CHIPDeviceCallback)onCompletion;

- (BOOL)ReadAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion
                        minInterval:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                           onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPOnOff : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)Off:(CHIPDeviceCallback)onCompletion;
- (BOOL)On:(CHIPDeviceCallback)onCompletion;
- (BOOL)Toggle:(CHIPDeviceCallback)onCompletion;

- (BOOL)ReadAttributeOnOff:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeOnOff:(CHIPDeviceCallback)onCompletion
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval
                    onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPScenes : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)AddScene:(CHIPDeviceCallback)onCompletion
           groupId:(uint16_t)groupId
           sceneId:(uint8_t)sceneId
    transitionTime:(uint16_t)transitionTime
         sceneName:(char *)sceneName
         clusterId:(uint16_t)clusterId
            length:(uint8_t)length
             value:(uint8_t)value;
- (BOOL)GetSceneMembership:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId;
- (BOOL)RecallScene:(CHIPDeviceCallback)onCompletion
            groupId:(uint16_t)groupId
            sceneId:(uint8_t)sceneId
     transitionTime:(uint16_t)transitionTime;
- (BOOL)RemoveAllScenes:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId;
- (BOOL)RemoveScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId;
- (BOOL)StoreScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId;
- (BOOL)ViewScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId;

- (BOOL)ReadAttributeSceneCount:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeCurrentScene:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeCurrentGroup:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeSceneValid:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeNameSupport:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPTemperatureMeasurement : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;

- (BOOL)ReadAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReportAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion
                         minInterval:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                            onChange:(CHIPDeviceCallback)onChange;
- (BOOL)ReadAttributeMinMeasuredValue:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeMaxMeasuredValue:(CHIPDeviceCallback)onCompletion;
- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* CHIP_CLUSTERS_H */
