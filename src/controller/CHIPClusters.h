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

// Prevent multiple inclusion
#pragma once

#include <controller/CHIPCluster.h>
#include <core/CHIPCallback.h>

namespace chip {
namespace Controller {

constexpr ClusterId kBarrierControlClusterId         = 0x0103;
constexpr ClusterId kBasicClusterId                  = 0x0000;
constexpr ClusterId kBindingClusterId                = 0xF000;
constexpr ClusterId kColorControlClusterId           = 0x0300;
constexpr ClusterId kDoorLockClusterId               = 0x0101;
constexpr ClusterId kGroupsClusterId                 = 0x0004;
constexpr ClusterId kIasZoneClusterId                = 0x0500;
constexpr ClusterId kIdentifyClusterId               = 0x0003;
constexpr ClusterId kLevelControlClusterId           = 0x0008;
constexpr ClusterId kOnOffClusterId                  = 0x0006;
constexpr ClusterId kScenesClusterId                 = 0x0005;
constexpr ClusterId kTemperatureMeasurementClusterId = 0x0402;

class DLL_EXPORT BarrierControlCluster : public ClusterBase
{
public:
    BarrierControlCluster() : ClusterBase(kBarrierControlClusterId) {}
    ~BarrierControlCluster() {}

    // Cluster Commands
    CHIP_ERROR BarrierControlGoToPercent(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                         uint8_t percentOpen);
    CHIP_ERROR BarrierControlStop(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeBarrierMovingState(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeBarrierSafetyStatus(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeBarrierCapabilities(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeBarrierPosition(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT BasicCluster : public ClusterBase
{
public:
    BasicCluster() : ClusterBase(kBasicClusterId) {}
    ~BasicCluster() {}

    // Cluster Commands
    CHIP_ERROR MfgSpecificPing(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ResetToFactoryDefaults(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeZclVersion(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePowerSource(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT BindingCluster : public ClusterBase
{
public:
    BindingCluster() : ClusterBase(kBindingClusterId) {}
    ~BindingCluster() {}

    // Cluster Commands
    CHIP_ERROR Bind(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, chip::NodeId nodeId,
                    chip::GroupId groupId, chip::EndpointId endpointId, chip::ClusterId clusterId);
    CHIP_ERROR Unbind(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, chip::NodeId nodeId,
                      chip::GroupId groupId, chip::EndpointId endpointId, chip::ClusterId clusterId);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT ColorControlCluster : public ClusterBase
{
public:
    ColorControlCluster() : ClusterBase(kColorControlClusterId) {}
    ~ColorControlCluster() {}

    // Cluster Commands
    CHIP_ERROR MoveColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, int16_t rateX,
                         int16_t rateY, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveColorTemperature(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t moveMode, uint16_t rate, uint16_t colorTemperatureMinimum,
                                    uint16_t colorTemperatureMaximum, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                       uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                              uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t colorX,
                           uint16_t colorY, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToColorTemperature(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t colorTemperature, uint16_t transitionTime, uint8_t optionsMask,
                                      uint8_t optionsOverride);
    CHIP_ERROR MoveToHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t hue,
                         uint8_t direction, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR MoveToHueAndSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint8_t hue, uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask,
                                      uint8_t optionsOverride);
    CHIP_ERROR MoveToSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, int16_t stepX,
                         int16_t stepY, uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepColorTemperature(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t stepMode, uint16_t stepSize, uint16_t transitionTime, uint16_t colorTemperatureMinimum,
                                    uint16_t colorTemperatureMaximum, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                       uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StepSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                              uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride);
    CHIP_ERROR StopMoveStep(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t optionsMask,
                            uint8_t optionsOverride);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeRemainingTime(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeDriftCompensation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCompensationText(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorTemperature(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorMode(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorControlOptions(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeNumberOfPrimaries(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary1X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary1Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary1Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary2X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary2Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary2Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary3X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary3Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary3Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary4X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary4Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary4Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary5X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary5Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary5Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary6X(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary6Y(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributePrimary6Intensity(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeWhitePointX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeWhitePointY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointRX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointRY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointRIntensity(Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointGX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointGY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointGIntensity(Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointBX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointBY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorPointBIntensity(Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeEnhancedCurrentHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeEnhancedColorMode(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorLoopActive(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorLoopDirection(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorLoopTime(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorCapabilities(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorTempPhysicalMin(Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeColorTempPhysicalMax(Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCoupleColorTempToLevelMinMireds(Callback::Cancelable * onSuccessCallback,
                                                            Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeStartUpColorTemperatureMireds(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR WriteAttributeColorControlOptions(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint8_t value);
    CHIP_ERROR WriteAttributeWhitePointX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                         uint16_t value);
    CHIP_ERROR WriteAttributeWhitePointY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                         uint16_t value);
    CHIP_ERROR WriteAttributeColorPointRX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointRY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointRIntensity(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback, uint8_t value);
    CHIP_ERROR WriteAttributeColorPointGX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointGY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointGIntensity(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback, uint8_t value);
    CHIP_ERROR WriteAttributeColorPointBX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointBY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
    CHIP_ERROR WriteAttributeColorPointBIntensity(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback, uint8_t value);
    CHIP_ERROR WriteAttributeStartUpColorTemperatureMireds(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value);
    CHIP_ERROR ConfigureAttributeCurrentHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                            uint16_t minInterval, uint16_t maxInterval, uint8_t change);
    CHIP_ERROR ReportAttributeCurrentHue(Callback::Cancelable * onReportCallback);
    CHIP_ERROR ConfigureAttributeCurrentSaturation(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback, uint16_t minInterval,
                                                   uint16_t maxInterval, uint8_t change);
    CHIP_ERROR ReportAttributeCurrentSaturation(Callback::Cancelable * onReportCallback);
    CHIP_ERROR ConfigureAttributeCurrentX(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t minInterval, uint16_t maxInterval, uint16_t change);
    CHIP_ERROR ReportAttributeCurrentX(Callback::Cancelable * onReportCallback);
    CHIP_ERROR ConfigureAttributeCurrentY(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t minInterval, uint16_t maxInterval, uint16_t change);
    CHIP_ERROR ReportAttributeCurrentY(Callback::Cancelable * onReportCallback);
    CHIP_ERROR ConfigureAttributeColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback, uint16_t minInterval,
                                                  uint16_t maxInterval, uint16_t change);
    CHIP_ERROR ReportAttributeColorTemperature(Callback::Cancelable * onReportCallback);
};

class DLL_EXPORT DoorLockCluster : public ClusterBase
{
public:
    DoorLockCluster() : ClusterBase(kDoorLockClusterId) {}
    ~DoorLockCluster() {}

    // Cluster Commands
    CHIP_ERROR ClearAllPins(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ClearAllRfids(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ClearHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t scheduleId);
    CHIP_ERROR ClearPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId);
    CHIP_ERROR ClearRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId);
    CHIP_ERROR ClearWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t scheduleId, uint16_t userId);
    CHIP_ERROR ClearYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t scheduleId, uint16_t userId);
    CHIP_ERROR GetHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId);
    CHIP_ERROR GetLogRecord(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t logIndex);
    CHIP_ERROR GetPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId);
    CHIP_ERROR GetRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId);
    CHIP_ERROR GetUserType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId);
    CHIP_ERROR GetWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId, uint16_t userId);
    CHIP_ERROR GetYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId, uint16_t userId);
    CHIP_ERROR LockDoor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, char * pin);
    CHIP_ERROR SetHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId, uint32_t localStartTime, uint32_t localEndTime,
                                  uint8_t operatingModeDuringHoliday);
    CHIP_ERROR SetPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId,
                      uint8_t userStatus, uint8_t userType, char * pin);
    CHIP_ERROR SetRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId,
                       uint8_t userStatus, uint8_t userType, char * id);
    CHIP_ERROR SetUserType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t userId,
                           uint8_t userType);
    CHIP_ERROR SetWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId, uint16_t userId, uint8_t daysMask, uint8_t startHour, uint8_t startMinute,
                                  uint8_t endHour, uint8_t endMinute);
    CHIP_ERROR SetYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t scheduleId, uint16_t userId, uint32_t localStartTime, uint32_t localEndTime);
    CHIP_ERROR UnlockDoor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, char * pin);
    CHIP_ERROR UnlockWithTimeout(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                 uint16_t timeoutInSeconds, char * pin);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeLockState(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeLockType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeActuatorEnabled(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ConfigureAttributeLockState(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                           uint16_t minInterval, uint16_t maxInterval);
    CHIP_ERROR ReportAttributeLockState(Callback::Cancelable * onReportCallback);
};

class DLL_EXPORT GroupsCluster : public ClusterBase
{
public:
    GroupsCluster() : ClusterBase(kGroupsClusterId) {}
    ~GroupsCluster() {}

    // Cluster Commands
    CHIP_ERROR AddGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                        char * groupName);
    CHIP_ERROR AddGroupIfIdentifying(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint16_t groupId, char * groupName);
    CHIP_ERROR GetGroupMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint8_t groupCount, uint16_t groupList);
    CHIP_ERROR RemoveAllGroups(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR RemoveGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId);
    CHIP_ERROR ViewGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeNameSupport(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT IasZoneCluster : public ClusterBase
{
public:
    IasZoneCluster() : ClusterBase(kIasZoneClusterId) {}
    ~IasZoneCluster() {}

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeZoneState(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeZoneType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeZoneStatus(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeIasCieAddress(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeZoneId(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR WriteAttributeIasCieAddress(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                           uint64_t value);
};

class DLL_EXPORT IdentifyCluster : public ClusterBase
{
public:
    IdentifyCluster() : ClusterBase(kIdentifyClusterId) {}
    ~IdentifyCluster() {}

    // Cluster Commands
    CHIP_ERROR Identify(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t identifyTime);
    CHIP_ERROR IdentifyQuery(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeIdentifyTime(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR WriteAttributeIdentifyTime(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t value);
};

class DLL_EXPORT LevelControlCluster : public ClusterBase
{
public:
    LevelControlCluster() : ClusterBase(kLevelControlClusterId) {}
    ~LevelControlCluster() {}

    // Cluster Commands
    CHIP_ERROR Move(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                    uint8_t rate, uint8_t optionMask, uint8_t optionOverride);
    CHIP_ERROR MoveToLevel(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t level,
                           uint16_t transitionTime, uint8_t optionMask, uint8_t optionOverride);
    CHIP_ERROR MoveToLevelWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint8_t level, uint16_t transitionTime);
    CHIP_ERROR MoveWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t moveMode,
                             uint8_t rate);
    CHIP_ERROR Step(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                    uint8_t stepSize, uint16_t transitionTime, uint8_t optionMask, uint8_t optionOverride);
    CHIP_ERROR StepWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t stepMode,
                             uint8_t stepSize, uint16_t transitionTime);
    CHIP_ERROR Stop(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint8_t optionMask,
                    uint8_t optionOverride);
    CHIP_ERROR StopWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentLevel(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ConfigureAttributeCurrentLevel(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint16_t minInterval, uint16_t maxInterval, uint8_t change);
    CHIP_ERROR ReportAttributeCurrentLevel(Callback::Cancelable * onReportCallback);
};

class DLL_EXPORT OnOffCluster : public ClusterBase
{
public:
    OnOffCluster() : ClusterBase(kOnOffClusterId) {}
    ~OnOffCluster() {}

    // Cluster Commands
    CHIP_ERROR Off(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR On(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR Toggle(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ConfigureAttributeOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                       uint16_t minInterval, uint16_t maxInterval);
    CHIP_ERROR ReportAttributeOnOff(Callback::Cancelable * onReportCallback);
};

class DLL_EXPORT ScenesCluster : public ClusterBase
{
public:
    ScenesCluster() : ClusterBase(kScenesClusterId) {}
    ~ScenesCluster() {}

    // Cluster Commands
    CHIP_ERROR AddScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                        uint8_t sceneId, uint16_t transitionTime, char * sceneName, chip::ClusterId clusterId, uint8_t length,
                        uint8_t value);
    CHIP_ERROR GetSceneMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  uint16_t groupId);
    CHIP_ERROR RecallScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                           uint8_t sceneId, uint16_t transitionTime);
    CHIP_ERROR RemoveAllScenes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                               uint16_t groupId);
    CHIP_ERROR RemoveScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                           uint8_t sceneId);
    CHIP_ERROR StoreScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                          uint8_t sceneId);
    CHIP_ERROR ViewScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, uint16_t groupId,
                         uint8_t sceneId);

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeSceneCount(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeCurrentGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeSceneValid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeNameSupport(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
};

class DLL_EXPORT TemperatureMeasurementCluster : public ClusterBase
{
public:
    TemperatureMeasurementCluster() : ClusterBase(kTemperatureMeasurementClusterId) {}
    ~TemperatureMeasurementCluster() {}

    // Cluster Attributes
    CHIP_ERROR DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback);
    CHIP_ERROR ConfigureAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint16_t minInterval, uint16_t maxInterval, int16_t change);
    CHIP_ERROR ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback);
};

} // namespace Controller
} // namespace chip
