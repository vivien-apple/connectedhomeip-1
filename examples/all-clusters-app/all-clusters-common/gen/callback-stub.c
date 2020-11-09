
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

#include "callback.h"
#include "cluster-id.h"
#include "debug-printing.h"

// Cluster Init Functions
void emberAfClusterInitCallback(uint8_t endpoint, EmberAfClusterId clusterId)
{
    switch (clusterId)
    {
    case ZCL_BARRIER_CONTROL_CLUSTER_ID:
        emberAfBarrierControlClusterInitCallback(endpoint);
        break;
    case ZCL_BASIC_CLUSTER_ID:
        emberAfBasicClusterInitCallback(endpoint);
        break;
    case ZCL_COLOR_CONTROL_CLUSTER_ID:
        emberAfColorControlClusterInitCallback(endpoint);
        break;
    case ZCL_DOOR_LOCK_CLUSTER_ID:
        emberAfDoorLockClusterInitCallback(endpoint);
        break;
    case ZCL_GROUPS_CLUSTER_ID:
        emberAfGroupsClusterInitCallback(endpoint);
        break;
    case ZCL_IAS_ZONE_CLUSTER_ID:
        emberAfIASZoneClusterInitCallback(endpoint);
        break;
    case ZCL_IDENTIFY_CLUSTER_ID:
        emberAfIdentifyClusterInitCallback(endpoint);
        break;
    case ZCL_LEVEL_CONTROL_CLUSTER_ID:
        emberAfLevelControlClusterInitCallback(endpoint);
        break;
    case ZCL_ON_OFF_CLUSTER_ID:
        emberAfOnOffClusterInitCallback(endpoint);
        break;
    case ZCL_SCENES_CLUSTER_ID:
        emberAfScenesClusterInitCallback(endpoint);
        break;
    case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
        emberAfTemperatureMeasurementClusterInitCallback(endpoint);
        break;
    default:
        // Unrecognized cluster ID
        break;
    }
}

void __attribute__((weak)) emberAfBarrierControlClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfBasicClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfColorControlClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfDoorLockClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfGroupsClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfIASZoneClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfIdentifyClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfLevelControlClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfOnOffClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfScenesClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}
void __attribute__((weak)) emberAfTemperatureMeasurementClusterInitCallback(uint8_t endpoint)
{
    // To prevent warning
    (void) endpoint;
}

// Cluster Command callback

/**
 * @brief Barrier Control Cluster BarrierControlGoToPercent Command callback
 * @param percentOpen
 */

bool __attribute__((weak)) emberAfBarrierControlClusterBarrierControlGoToPercentCallback(uint8_t percentOpen)
{
    // To prevent warning
    (void) percentOpen;

    return false;
}

/**
 * @brief Barrier Control Cluster BarrierControlStop Command callback
 */

bool __attribute__((weak)) emberAfBarrierControlClusterBarrierControlStopCallback()
{
    return false;
}

/**
 * @brief Basic Cluster ResetToFactoryDefaults Command callback
 */

bool __attribute__((weak)) emberAfBasicClusterResetToFactoryDefaultsCallback()
{
    return false;
}

/**
 * @brief Color Control Cluster MoveColor Command callback
 * @param rateX
 * @param rateY
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveColorCallback(int16_t rateX, int16_t rateY, uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) rateX;
    (void) rateY;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveColorTemperature Command callback
 * @param moveMode
 * @param rate
 * @param colorTemperatureMinimum
 * @param colorTemperatureMaximum
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveColorTemperatureCallback(EmberAfHueMoveMode moveMode, uint16_t rate, uint16_t colorTemperatureMinimum,
                                                       uint16_t colorTemperatureMaximum, uint8_t optionsMask,
                                                       uint8_t optionsOverride)
{
    // To prevent warning
    (void) moveMode;
    (void) rate;
    (void) colorTemperatureMinimum;
    (void) colorTemperatureMaximum;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveHue Command callback
 * @param moveMode
 * @param rate
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveHueCallback(EmberAfHueMoveMode moveMode, uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) moveMode;
    (void) rate;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveSaturation Command callback
 * @param moveMode
 * @param rate
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak)) emberAfColorControlClusterMoveSaturationCallback(EmberAfSaturationMoveMode moveMode, uint8_t rate,
                                                                            uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) moveMode;
    (void) rate;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveToColor Command callback
 * @param colorX
 * @param colorY
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak)) emberAfColorControlClusterMoveToColorCallback(uint16_t colorX, uint16_t colorY, uint16_t transitionTime,
                                                                         uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) colorX;
    (void) colorY;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveToColorTemperature Command callback
 * @param colorTemperature
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveToColorTemperatureCallback(uint16_t colorTemperature, uint16_t transitionTime, uint8_t optionsMask,
                                                         uint8_t optionsOverride)
{
    // To prevent warning
    (void) colorTemperature;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveToHue Command callback
 * @param hue
 * @param direction
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveToHueCallback(uint8_t hue, EmberAfHueDirection direction, uint16_t transitionTime,
                                            uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) hue;
    (void) direction;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveToHueAndSaturation Command callback
 * @param hue
 * @param saturation
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterMoveToHueAndSaturationCallback(uint8_t hue, uint8_t saturation, uint16_t transitionTime,
                                                         uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) hue;
    (void) saturation;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster MoveToSaturation Command callback
 * @param saturation
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak)) emberAfColorControlClusterMoveToSaturationCallback(uint8_t saturation, uint16_t transitionTime,
                                                                              uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) saturation;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster StepColor Command callback
 * @param stepX
 * @param stepY
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak)) emberAfColorControlClusterStepColorCallback(int16_t stepX, int16_t stepY, uint16_t transitionTime,
                                                                       uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) stepX;
    (void) stepY;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster StepColorTemperature Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param colorTemperatureMinimum
 * @param colorTemperatureMaximum
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterStepColorTemperatureCallback(EmberAfHueStepMode stepMode, uint16_t stepSize, uint16_t transitionTime,
                                                       uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum,
                                                       uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) stepMode;
    (void) stepSize;
    (void) transitionTime;
    (void) colorTemperatureMinimum;
    (void) colorTemperatureMaximum;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster StepHue Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterStepHueCallback(EmberAfHueStepMode stepMode, uint8_t stepSize, uint8_t transitionTime,
                                          uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) stepMode;
    (void) stepSize;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster StepSaturation Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak))
emberAfColorControlClusterStepSaturationCallback(EmberAfSaturationStepMode stepMode, uint8_t stepSize, uint8_t transitionTime,
                                                 uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) stepMode;
    (void) stepSize;
    (void) transitionTime;
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Color Control Cluster StopMoveStep Command callback
 * @param optionsMask
 * @param optionsOverride
 */

bool __attribute__((weak)) emberAfColorControlClusterStopMoveStepCallback(uint8_t optionsMask, uint8_t optionsOverride)
{
    // To prevent warning
    (void) optionsMask;
    (void) optionsOverride;

    return false;
}

/**
 * @brief Door Lock Cluster ClearHolidaySchedule Command callback
 * @param scheduleId
 */

bool __attribute__((weak)) emberAfDoorLockClusterClearHolidayScheduleCallback(uint8_t scheduleId)
{
    // To prevent warning
    (void) scheduleId;

    return false;
}

/**
 * @brief Door Lock Cluster ClearWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool __attribute__((weak)) emberAfDoorLockClusterClearWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;

    return false;
}

/**
 * @brief Door Lock Cluster ClearYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool __attribute__((weak)) emberAfDoorLockClusterClearYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;

    return false;
}

/**
 * @brief Door Lock Cluster GetHolidaySchedule Command callback
 * @param scheduleId
 */

bool __attribute__((weak)) emberAfDoorLockClusterGetHolidayScheduleCallback(uint8_t scheduleId)
{
    // To prevent warning
    (void) scheduleId;

    return false;
}

/**
 * @brief Door Lock Cluster GetUserType Command callback
 * @param userId
 */

bool __attribute__((weak)) emberAfDoorLockClusterGetUserTypeCallback(uint16_t userId)
{
    // To prevent warning
    (void) userId;

    return false;
}

/**
 * @brief Door Lock Cluster GetWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool __attribute__((weak)) emberAfDoorLockClusterGetWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;

    return false;
}

/**
 * @brief Door Lock Cluster GetYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool __attribute__((weak)) emberAfDoorLockClusterGetYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;

    return false;
}

/**
 * @brief Door Lock Cluster LockDoor Command callback
 * @param pIN
 */

bool __attribute__((weak)) emberAfDoorLockClusterLockDoorCallback(uint8_t * PIN)
{
    // To prevent warning
    (void) PIN;

    return false;
}

/**
 * @brief Door Lock Cluster SetHolidaySchedule Command callback
 * @param scheduleId
 * @param localStartTime
 * @param localEndTime
 * @param operatingModeDuringHoliday
 */

bool __attribute__((weak))
emberAfDoorLockClusterSetHolidayScheduleCallback(uint8_t scheduleId, uint32_t localStartTime, uint32_t localEndTime,
                                                 uint8_t operatingModeDuringHoliday)
{
    // To prevent warning
    (void) scheduleId;
    (void) localStartTime;
    (void) localEndTime;
    (void) operatingModeDuringHoliday;

    return false;
}

/**
 * @brief Door Lock Cluster SetUserType Command callback
 * @param userId
 * @param userType
 */

bool __attribute__((weak)) emberAfDoorLockClusterSetUserTypeCallback(uint16_t userId, EmberAfDoorLockUserType userType)
{
    // To prevent warning
    (void) userId;
    (void) userType;

    return false;
}

/**
 * @brief Door Lock Cluster SetWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 * @param daysMask
 * @param startHour
 * @param startMinute
 * @param endHour
 * @param endMinute
 */

bool __attribute__((weak))
emberAfDoorLockClusterSetWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId, uint8_t daysMask, uint8_t startHour,
                                                 uint8_t startMinute, uint8_t endHour, uint8_t endMinute)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;
    (void) daysMask;
    (void) startHour;
    (void) startMinute;
    (void) endHour;
    (void) endMinute;

    return false;
}

/**
 * @brief Door Lock Cluster SetYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 * @param localStartTime
 * @param localEndTime
 */

bool __attribute__((weak)) emberAfDoorLockClusterSetYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId,
                                                                            uint32_t localStartTime, uint32_t localEndTime)
{
    // To prevent warning
    (void) scheduleId;
    (void) userId;
    (void) localStartTime;
    (void) localEndTime;

    return false;
}

/**
 * @brief Door Lock Cluster UnlockDoor Command callback
 * @param pIN
 */

bool __attribute__((weak)) emberAfDoorLockClusterUnlockDoorCallback(uint8_t * PIN)
{
    // To prevent warning
    (void) PIN;

    return false;
}

/**
 * @brief Door Lock Cluster UnlockWithTimeout Command callback
 * @param timeoutInSeconds
 * @param pin
 */

bool __attribute__((weak)) emberAfDoorLockClusterUnlockWithTimeoutCallback(uint16_t timeoutInSeconds, uint8_t * pin)
{
    // To prevent warning
    (void) timeoutInSeconds;
    (void) pin;

    return false;
}

/**
 * @brief Groups Cluster AddGroup Command callback
 * @param groupId
 * @param groupName
 */

bool __attribute__((weak)) emberAfGroupsClusterAddGroupCallback(uint16_t groupId, uint8_t * groupName)
{
    // To prevent warning
    (void) groupId;
    (void) groupName;

    return false;
}

/**
 * @brief Groups Cluster AddGroupIfIdentifying Command callback
 * @param groupId
 * @param groupName
 */

bool __attribute__((weak)) emberAfGroupsClusterAddGroupIfIdentifyingCallback(uint16_t groupId, uint8_t * groupName)
{
    // To prevent warning
    (void) groupId;
    (void) groupName;

    return false;
}

/**
 * @brief Groups Cluster GetGroupMembership Command callback
 * @param groupCount
 * @param groupList
 */

bool __attribute__((weak)) emberAfGroupsClusterGetGroupMembershipCallback(uint8_t groupCount, uint16_t groupList)
{
    // To prevent warning
    (void) groupCount;
    (void) groupList;

    return false;
}

/**
 * @brief Groups Cluster RemoveAllGroups Command callback
 */

bool __attribute__((weak)) emberAfGroupsClusterRemoveAllGroupsCallback()
{
    return false;
}

/**
 * @brief Groups Cluster RemoveGroup Command callback
 * @param groupId
 */

bool __attribute__((weak)) emberAfGroupsClusterRemoveGroupCallback(uint16_t groupId)
{
    // To prevent warning
    (void) groupId;

    return false;
}

/**
 * @brief Groups Cluster ViewGroup Command callback
 * @param groupId
 */

bool __attribute__((weak)) emberAfGroupsClusterViewGroupCallback(uint16_t groupId)
{
    // To prevent warning
    (void) groupId;

    return false;
}

/**
 * @brief IAS Zone Cluster ZoneEnrollResponse Command callback
 * @param enrollResponseCode
 * @param zoneId
 */

bool __attribute__((weak))
emberAfIASZoneClusterZoneEnrollResponseCallback(EmberAfIasEnrollResponseCode enrollResponseCode, uint8_t zoneId)
{
    // To prevent warning
    (void) enrollResponseCode;
    (void) zoneId;

    return false;
}

/**
 * @brief Identify Cluster Identify Command callback
 * @param identifyTime
 */

bool __attribute__((weak)) emberAfIdentifyClusterIdentifyCallback(uint16_t identifyTime)
{
    // To prevent warning
    (void) identifyTime;

    return false;
}

/**
 * @brief Identify Cluster IdentifyQuery Command callback
 */

bool __attribute__((weak)) emberAfIdentifyClusterIdentifyQueryCallback()
{
    return false;
}

/**
 * @brief Level Control Cluster Move Command callback
 * @param moveMode
 * @param rate
 * @param optionMask
 * @param optionOverride
 */

bool __attribute__((weak))
emberAfLevelControlClusterMoveCallback(EmberAfMoveMode moveMode, uint8_t rate, uint8_t optionMask, uint8_t optionOverride)
{
    // To prevent warning
    (void) moveMode;
    (void) rate;
    (void) optionMask;
    (void) optionOverride;

    return false;
}

/**
 * @brief Level Control Cluster MoveToLevel Command callback
 * @param level
 * @param transitionTime
 * @param optionMask
 * @param optionOverride
 */

bool __attribute__((weak))
emberAfLevelControlClusterMoveToLevelCallback(uint8_t level, uint16_t transitionTime, uint8_t optionMask, uint8_t optionOverride)
{
    // To prevent warning
    (void) level;
    (void) transitionTime;
    (void) optionMask;
    (void) optionOverride;

    return false;
}

/**
 * @brief Level Control Cluster MoveToLevelWithOnOff Command callback
 * @param level
 * @param transitionTime
 */

bool __attribute__((weak)) emberAfLevelControlClusterMoveToLevelWithOnOffCallback(uint8_t level, uint16_t transitionTime)
{
    // To prevent warning
    (void) level;
    (void) transitionTime;

    return false;
}

/**
 * @brief Level Control Cluster MoveWithOnOff Command callback
 * @param moveMode
 * @param rate
 */

bool __attribute__((weak)) emberAfLevelControlClusterMoveWithOnOffCallback(EmberAfMoveMode moveMode, uint8_t rate)
{
    // To prevent warning
    (void) moveMode;
    (void) rate;

    return false;
}

/**
 * @brief Level Control Cluster Step Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionMask
 * @param optionOverride
 */

bool __attribute__((weak))
emberAfLevelControlClusterStepCallback(EmberAfStepMode stepMode, uint8_t stepSize, uint16_t transitionTime, uint8_t optionMask,
                                       uint8_t optionOverride)
{
    // To prevent warning
    (void) stepMode;
    (void) stepSize;
    (void) transitionTime;
    (void) optionMask;
    (void) optionOverride;

    return false;
}

/**
 * @brief Level Control Cluster StepWithOnOff Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 */

bool __attribute__((weak))
emberAfLevelControlClusterStepWithOnOffCallback(EmberAfStepMode stepMode, uint8_t stepSize, uint16_t transitionTime)
{
    // To prevent warning
    (void) stepMode;
    (void) stepSize;
    (void) transitionTime;

    return false;
}

/**
 * @brief Level Control Cluster Stop Command callback
 * @param optionMask
 * @param optionOverride
 */

bool __attribute__((weak)) emberAfLevelControlClusterStopCallback(uint8_t optionMask, uint8_t optionOverride)
{
    // To prevent warning
    (void) optionMask;
    (void) optionOverride;

    return false;
}

/**
 * @brief Level Control Cluster StopWithOnOff Command callback
 */

bool __attribute__((weak)) emberAfLevelControlClusterStopWithOnOffCallback()
{
    return false;
}

/**
 * @brief On/off Cluster Off Command callback
 */

bool __attribute__((weak)) emberAfOnOffClusterOffCallback()
{
    return false;
}

/**
 * @brief On/off Cluster On Command callback
 */

bool __attribute__((weak)) emberAfOnOffClusterOnCallback()
{
    return false;
}

/**
 * @brief On/off Cluster Toggle Command callback
 */

bool __attribute__((weak)) emberAfOnOffClusterToggleCallback()
{
    return false;
}

/**
 * @brief Scenes Cluster AddScene Command callback
 * @param groupId
 * @param sceneId
 * @param transitionTime
 * @param sceneName
 * @param extensionFieldSets
 */

bool __attribute__((weak))
emberAfScenesClusterAddSceneCallback(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, uint8_t * sceneName,
                                     EmberAfSceneExtensionFieldSet extensionFieldSets)
{
    // To prevent warning
    (void) groupId;
    (void) sceneId;
    (void) transitionTime;
    (void) sceneName;
    (void) extensionFieldSets;

    return false;
}

/**
 * @brief Scenes Cluster GetSceneMembership Command callback
 * @param groupId
 */

bool __attribute__((weak)) emberAfScenesClusterGetSceneMembershipCallback(uint16_t groupId)
{
    // To prevent warning
    (void) groupId;

    return false;
}

/**
 * @brief Scenes Cluster RecallScene Command callback
 * @param groupId
 * @param sceneId
 * @param transitionTime
 */

bool __attribute__((weak)) emberAfScenesClusterRecallSceneCallback(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime)
{
    // To prevent warning
    (void) groupId;
    (void) sceneId;
    (void) transitionTime;

    return false;
}

/**
 * @brief Scenes Cluster RemoveAllScenes Command callback
 * @param groupId
 */

bool __attribute__((weak)) emberAfScenesClusterRemoveAllScenesCallback(uint16_t groupId)
{
    // To prevent warning
    (void) groupId;

    return false;
}

/**
 * @brief Scenes Cluster RemoveScene Command callback
 * @param groupId
 * @param sceneId
 */

bool __attribute__((weak)) emberAfScenesClusterRemoveSceneCallback(uint16_t groupId, uint8_t sceneId)
{
    // To prevent warning
    (void) groupId;
    (void) sceneId;

    return false;
}

/**
 * @brief Scenes Cluster StoreScene Command callback
 * @param groupId
 * @param sceneId
 */

bool __attribute__((weak)) emberAfScenesClusterStoreSceneCallback(uint16_t groupId, uint8_t sceneId)
{
    // To prevent warning
    (void) groupId;
    (void) sceneId;

    return false;
}

/**
 * @brief Scenes Cluster ViewScene Command callback
 * @param groupId
 * @param sceneId
 */

bool __attribute__((weak)) emberAfScenesClusterViewSceneCallback(uint16_t groupId, uint8_t sceneId)
{
    // To prevent warning
    (void) groupId;
    (void) sceneId;

    return false;
}

void emberAfPluginBarrierControlServerInitCallback(){};
/** @brief Compute Pwm from HSV
 *
 * This function is called from the color server when it is time for the PWMs to
 * be driven with a new value from the HSV values.
 *
 * @param endpoint The identifying endpoint Ver.: always
 */
void emberAfPluginColorControlServerComputePwmFromHsvCallback(uint8_t endpoint) {}

/** @brief Compute Pwm from HSV
 *
 * This function is called from the color server when it is time for the PWMs to
 * be driven with a new value from the color temperature.
 *
 * @param endpoint The identifying endpoint Ver.: always
 */
void emberAfPluginColorControlServerComputePwmFromTempCallback(uint8_t endpoint) {}

/** @brief Compute Pwm from HSV
 *
 * This function is called from the color server when it is time for the PWMs to
 * be driven with a new value from the color X and color Y values.
 *
 * @param endpoint The identifying endpoint Ver.: always
 */
void emberAfPluginColorControlServerComputePwmFromXyCallback(uint8_t endpoint) {}

/** @brief Get Group Name
 *
 * This function returns the name of a group with the provided group ID, should
 * it exist.
 *
 * @param endpoint Endpoint Ver.: always
 * @param groupId Group ID Ver.: always
 * @param groupName Group Name Ver.: always
 */
void emberAfPluginGroupsServerGetGroupNameCallback(uint8_t endpoint, uint16_t groupId, uint8_t * groupName) {}

/** @brief Group Names Supported
 *
 * This function is called by the framework when it is necessary to determine
 * whether or not group names are supported.
 *
 * @param endpoint The endpoint. Ver.: always
 */
bool emberAfPluginGroupsServerGroupNamesSupportedCallback(uint8_t endpoint)
{
    return false;
}

/** @brief Set Group Name
 *
 * This function sets the name of a group with the provided group ID.
 *
 * @param endpoint Endpoint Ver.: always
 * @param groupId Group ID Ver.: always
 * @param groupName Group Name Ver.: always
 */
void emberAfPluginGroupsServerSetGroupNameCallback(uint8_t endpoint, uint16_t groupId, uint8_t * groupName){};
void emberAfPluginIasZoneClientZdoCallback(EmberNodeId emberNodeId, EmberApsFrame * apsFrame, uint8_t * message, uint16_t length) {}

void emberAfPluginIasZoneClientWriteAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen) {}

void emberAfPluginIasZoneClientReadAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen) {}
/** @brief Identify Cluster Start Feedback Callback
 *
 *
 *
 * @param endpoint Endpoint id
 * @param identifyTime Identify time
 */
bool emberAfPluginIdentifyStartFeedbackCallback(uint8_t endpoint, uint16_t identifyTime)
{
    return false;
}

/** @brief Identify Cluster Stop Feedback Callback
 *
 *
 *
 * @param endpoint Endpoint id
 */
bool emberAfPluginIdentifyStopFeedbackCallback(uint8_t endpoint)
{
    return false;
}
void emberAfPluginLevelControlClusterServerPostInitCallback(CHIPEndpointId endpoint){};
void emberAfPluginOnOffClusterServerPostInitCallback(CHIPEndpointId endpoint){};

/** @brief Get Source Route Overhead
 *
 * This function is called by the framework to determine the overhead required
 * in the network frame for source routing to a particular destination.
 *
 * @param destination The node id of the destination  Ver.: always
 */
uint8_t emberAfGetSourceRouteOverheadCallback(EmberNodeId destination)
{
    return 0;
}

/** @brief Cluster Security Custom
 *
 * This callback is fired when determining if APS encryption is required for a
 * cluster outside of the specification's required clusters.  In other words,
 * for the Smart Energy profile this would be a cluster beyond the list that
 * normally requires APS encryption.
 *
 * @param profileId The profile ID  Ver.: always
 * @param clusterId The cluster ID  Ver.: always
 * @param incoming Whether this is an incoming or outgoing message.  Ver.:
 * always
 * @param commandId The ZCL command ID being sent/received.  Ver.: always
 */
bool emberAfClusterSecurityCustomCallback(EmberAfProfileId profileId, EmberAfClusterId clusterId, bool incoming, uint8_t commandId)
{
    // By default, assume APS encryption is not required.
    return false;
}

/** @brief Interpan Send Message
 *
 * This function will send a raw MAC message with interpan frame format using
 * the passed parameters.
 *
 * @param header Interpan header info  Ver.: always
 * @param messageLength The length of the message received or to send  Ver.:
 * always
 * @param message The message data received or to send.  Ver.: always
 */
EmberStatus emberAfInterpanSendMessageCallback(EmberAfInterpanHeader * header, uint16_t messageLength, uint8_t * message)
{
    return EMBER_LIBRARY_NOT_PRESENT;
}

/** @brief Pre Command Received
 *
 * This callback is the second in the Application Framework's message processing
 * chain. At this point in the processing of incoming over-the-air messages, the
 * application has determined that the incoming message is a ZCL command. It
 * parses enough of the message to populate an EmberAfClusterCommand struct. The
 * Application Framework defines this struct value in a local scope to the
 * command processing but also makes it available through a global pointer
 * called emberAfCurrentCommand, in app/framework/util/util.c. When command
 * processing is complete, this pointer is cleared.
 *
 * @param cmd   Ver.: always
 */
bool emberAfPreCommandReceivedCallback(EmberAfClusterCommand * cmd)
{
    return false;
}

/** @brief Registration Abort
 *
 * This callback is called when the device should abort the registration
 * process.
 *
 */
void emberAfRegistrationAbortCallback() {}

/** @brief Discover Commands Generated Response
 *
 * This function is called by the framework when Discover Commands Generated
 * Response is received.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param manufacturerCode Manufacturer code  Ver.: always
 * @param discoveryComplete Indicates whether there are more commands to be
 * discovered.  Ver.: always
 * @param commandIds Buffer containing the list of command identifiers.  Ver.:
 * always
 * @param commandIdCount The length of bytes of the list, whish is the same as
 * the number of identifiers.  Ver.: always
 */
bool emberAfDiscoverCommandsGeneratedResponseCallback(EmberAfClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                      uint8_t * commandIds, uint16_t commandIdCount)
{
    return false;
}

/** @brief Discover Commands Received Response
 *
 * This function is called by the framework when Discover Commands Received
 * Response is received.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param manufacturerCode Manufacturer code  Ver.: always
 * @param discoveryComplete Indicates whether there are more commands to be
 * discovered.  Ver.: always
 * @param commandIds Buffer containing the list of command identifiers.  Ver.:
 * always
 * @param commandIdCount The length of bytes of the list, whish is the same as
 * the number of identifiers.  Ver.: always
 */
bool emberAfDiscoverCommandsReceivedResponseCallback(EmberAfClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                     uint8_t * commandIds, uint16_t commandIdCount)
{
    return false;
}

/** @brief Default Response
 *
 * This function is called by the application framework when a Default Response
 * command is received from an external device.  The application should return
 * true if the message was processed or false if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param commandId The command identifier to which this is a response.  Ver.:
 * always
 * @param status Specifies either SUCCESS or the nature of the error that was
 * detected in the received command.  Ver.: always
 */
bool emberAfDefaultResponseCallback(EmberAfClusterId clusterId, uint8_t commandId, EmberAfStatus status)
{
    return false;
}

/** @brief Report Attributes
 *
 * This function is called by the application framework when a Report Attributes
 * command is received from an external device.  The application should return
 * true if the message was processed or false if it was not.
 *
 * @param clusterId The cluster identifier of this command.  Ver.: always
 * @param buffer Buffer containing the list of attribute report records.  Ver.:
 * always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
bool emberAfReportAttributesCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
    return false;
}

/** @brief Read Attributes Response
 *
 * This function is called by the application framework when a Read Attributes
 * Response command is received from an external device.  The application should
 * return true if the message was processed or false if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of read attribute status records.
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
bool emberAfReadAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
    return false;
}

/** @brief Discover Attributes Response
 *
 * This function is called by the application framework when a Discover
 * Attributes Response or Discover Attributes Extended Response command is
 * received from an external device.  The Discover Attributes Response command
 * contains a bool indicating if discovery is complete and a list of zero or
 * more attribute identifier/type records. The final argument indicates whether
 * the response is in the extended format or not.  The application should return
 * true if the message was processed or false if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param discoveryComplete Indicates whether there are more attributes to be
 * discovered.  true if there are no more attributes to be discovered.  Ver.:
 * always
 * @param buffer Buffer containing the list of attribute identifier/type
 * records.  Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 * @param extended Indicates whether the response is in the extended format or
 * not.  Ver.: always
 */
bool emberAfDiscoverAttributesResponseCallback(EmberAfClusterId clusterId, bool discoveryComplete, uint8_t * buffer,
                                               uint16_t bufLen, bool extended)
{
    return false;
}

/** @brief Write Attributes Response
 *
 * This function is called by the application framework when a Write Attributes
 * Response command is received from an external device.  The application should
 * return true if the message was processed or false if it was not.
 *
 * @param clusterId The cluster identifier of this response.  Ver.: always
 * @param buffer Buffer containing the list of write attribute status records.
 * Ver.: always
 * @param bufLen The length in bytes of the list.  Ver.: always
 */
bool emberAfWriteAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
    return false;
}

/** @brief External Attribute Read
 *
 * Like emberAfExternalAttributeWriteCallback above, this function is called
 * when the framework needs to read an attribute that is not stored within the
 * Application Framework's data structures.
        All of the important
 * information about the attribute itself is passed as a pointer to an
 * EmberAfAttributeMetadata struct, which is stored within the application and
 * used to manage the attribute. A complete description of the
 * EmberAfAttributeMetadata struct is provided in
 * app/framework/include/af-types.h
        This function assumes that the
 * application is able to read the attribute, write it into the passed buffer,
 * and return immediately. Any attributes that require a state machine for
 * reading and writing are not really candidates for externalization at the
 * present time. The Application Framework does not currently include a state
 * machine for reading or writing attributes that must take place across a
 * series of application ticks. Attributes that cannot be read in a timely
 * manner should be stored within the Application Framework and updated
 * occasionally by the application code from within the
 * emberAfMainTickCallback.
        If the application was successfully able to
 * read the attribute and write it into the passed buffer, it should return a
 * value of EMBER_ZCL_STATUS_SUCCESS. Ensure that the size of the externally
 * managed attribute value is smaller than what the buffer can hold. In the case
 * of a buffer overflow throw an appropriate error such as
 * EMBER_ZCL_STATUS_INSUFFICIENT_SPACE. Any other return value indicates the
 * application was not able to read the attribute.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeMetadata   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param buffer   Ver.: always
 * @param maxReadLength   Ver.: always
 */
EmberAfStatus emberAfExternalAttributeReadCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                   EmberAfAttributeMetadata * attributeMetadata, uint16_t manufacturerCode,
                                                   uint8_t * buffer, uint16_t maxReadLength)
{
    return EMBER_ZCL_STATUS_FAILURE;
}

/** @brief External Attribute Write
 *
 * This function is called whenever the Application Framework needs to write an
 * attribute which is not stored within the data structures of the Application
 * Framework itself. One of the new features in Version 2 is the ability to
 * store attributes outside the Framework. This is particularly useful for
 * attributes that do not need to be stored because they can be read off the
 * hardware when they are needed, or are stored in some central location used by
 * many modules within the system. In this case, you can indicate that the
 * attribute is stored externally. When the framework needs to write an external
 * attribute, it makes a call to this callback.
        This callback is very
 * useful for host micros which need to store attributes in persistent memory.
 * Because each host micro (used with an Ember NCP) has its own type of
 * persistent memory storage, the Application Framework does not include the
 * ability to mark attributes as stored in flash the way that it does for Ember
 * SoCs like the EM35x. On a host micro, any attributes that need to be stored
 * in persistent memory should be marked as external and accessed through the
 * external read and write callbacks. Any host code associated with the
 * persistent storage should be implemented within this callback.
        All of
 * the important information about the attribute itself is passed as a pointer
 * to an EmberAfAttributeMetadata struct, which is stored within the application
 * and used to manage the attribute. A complete description of the
 * EmberAfAttributeMetadata struct is provided in
 * app/framework/include/af-types.h.
        This function assumes that the
 * application is able to write the attribute and return immediately. Any
 * attributes that require a state machine for reading and writing are not
 * candidates for externalization at the present time. The Application Framework
 * does not currently include a state machine for reading or writing attributes
 * that must take place across a series of application ticks. Attributes that
 * cannot be written immediately should be stored within the Application
 * Framework and updated occasionally by the application code from within the
 * emberAfMainTickCallback.
        If the application was successfully able to
 * write the attribute, it returns a value of EMBER_ZCL_STATUS_SUCCESS. Any
 * other return value indicates the application was not able to write the
 * attribute.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeMetadata   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param buffer   Ver.: always
 */
EmberAfStatus emberAfExternalAttributeWriteCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                    EmberAfAttributeMetadata * attributeMetadata, uint16_t manufacturerCode,
                                                    uint8_t * buffer)
{
    return EMBER_ZCL_STATUS_FAILURE;
}

/** @brief Attribute Read Access
 *
 * This function is called whenever the Application Framework needs to check
 * access permission for an attribute read.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param attributeId   Ver.: always
 */
bool emberAfAttributeReadAccessCallback(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode,
                                        uint16_t attributeId)
{
    return true;
}

/** @brief Attribute Write Access
 *
 * This function is called whenever the Application Framework needs to check
 * access permission for an attribute write.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param attributeId   Ver.: always
 */
bool emberAfAttributeWriteAccessCallback(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode,
                                         uint16_t attributeId)
{
    return true;
}

/** @brief Pre Attribute Change
 *
 * This function is called by the application framework before it changes an
 * attribute value.  The value passed into this callback is the value to which
 * the attribute is to be set by the framework.  The application should return
 * ::EMBER_ZCL_STATUS_SUCCESS to permit the change or any other ::EmberAfStatus
 * to reject it.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param type   Ver.: always
 * @param size   Ver.: always
 * @param value   Ver.: always
 */
EmberAfStatus emberAfPreAttributeChangeCallback(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attributeId,
                                                uint8_t mask, uint16_t manufacturerCode, uint8_t type, uint8_t size,
                                                uint8_t * value)
{
    return EMBER_ZCL_STATUS_SUCCESS;
}

/** @brief Allow Network Write Attribute
 *
 * This function is called by the application framework before it writes an
 * attribute in response to a write attribute request from an external device.
 * The value passed into this callback is the value to which the attribute is to
 * be set by the framework.
        Example:	In mirroring simple metering data
 * on an Energy Services Interface (ESI) (formerly called Energy Service Portal
 * (ESP) in SE 1.0).), a mirrored simple meter needs to write read-only
 * attributes on its mirror. The-meter-mirror sample application, located in
 * app/framework/sample-apps, uses this callback to allow the mirrored device to
 * write simple metering attributes on the mirror regardless of the fact that
 * most simple metering attributes are defined as read-only by the ZigBee
 * specification.
        Note:	The ZCL specification does not (as of this
 * writing) specify any permission-level security for writing writeable
 * attributes. As far as the ZCL specification is concerned, if an attribute is
 * writeable, any device that has a link key for the device should be able to
 * write that attribute. Furthermore if an attribute is read only, it should not
 * be written over the air. Thus, if you implement permissions for writing
 * attributes as a feature, you MAY be operating outside the specification. This
 * is unlikely to be a problem for writing read-only attributes, but it may be a
 * problem for attributes that are writeable according to the specification but
 * restricted by the application implementing this callback.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 * @param attributeId   Ver.: always
 * @param mask   Ver.: always
 * @param manufacturerCode   Ver.: always
 * @param value   Ver.: always
 * @param type   Ver.: always
 */
EmberAfAttributeWritePermission emberAfAllowNetworkWriteAttributeCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                                          EmberAfAttributeId attributeId, uint8_t mask,
                                                                          uint16_t manufacturerCode, uint8_t * value, uint8_t type)
{
    return EMBER_ZCL_ATTRIBUTE_WRITE_PERMISSION_ALLOW_WRITE_NORMAL; // Default
}

/** @brief Add To Current App Tasks
 *
 * This function is only useful to sleepy end devices.  This function will note
 * the passed item as part of a set of tasks the application has outstanding
 * (e.g. message sent requiring APS acknwoledgement).  This will affect how the
 * application behaves with regard to sleeping and polling.  Until the
 * outstanding task is completed, the device may poll more frequently and sleep
 * less often.
 *
 * @param tasks   Ver.: always
 */
void emberAfAddToCurrentAppTasksCallback(EmberAfApplicationTask tasks) {}

/** @brief Remove From Current App Tasks
 *
 * This function is only useful to sleepy end devices.  This function will
 * remove the passed item from the set of tasks the application has outstanding
 * (e.g. message sent requiring APS acknwoledgement).  This will affect how the
 * application behaves with regard to sleeping and polling.  Removing the item
 * from the list of outstanding tasks may allow the device to sleep longer and
 * poll less frequently.  If there are other outstanding tasks the system may
 * still have to stay away and poll more often.
 *
 * @param tasks   Ver.: always
 */
void emberAfRemoveFromCurrentAppTasksCallback(EmberAfApplicationTask tasks) {}

/** @brief Message Sent
 *
 * This function is called by the application framework from the message sent
 * handler, when it is informed by the stack regarding the message sent status.
 * All of the values passed to the emberMessageSentHandler are passed on to this
 * callback. This provides an opportunity for the application to verify that its
 * message has been sent successfully and take the appropriate action. This
 * callback should return a bool value of true or false. A value of true
 * indicates that the message sent notification has been handled and should not
 * be handled by the application framework.
 *
 * @param type   Ver.: always
 * @param indexOrDestination   Ver.: always
 * @param apsFrame   Ver.: always
 * @param msgLen   Ver.: always
 * @param message   Ver.: always
 * @param status   Ver.: always
 */
bool emberAfMessageSentCallback(EmberOutgoingMessageType type, uint16_t indexOrDestination, EmberApsFrame * apsFrame,
                                uint16_t msgLen, uint8_t * message, EmberStatus status)
{
    return false;
}

/** @brief Trust Center Keepalive Abort
 *
 * This callback is called when the device should abort the trust center
 * keepalive process.
 *
 */
void emberAfTrustCenterKeepaliveAbortCallback() {}

/** @brief Pre Message Send
 *
 * This function is called by the framework when it is about to pass a message
 * to the stack primitives for sending.   This message may or may not be ZCL,
 * ZDO, or some other protocol.  This is called prior to
        any ZigBee
 * fragmentation that may be done.  If the function returns true it is assumed
 * the callback has consumed and processed the message.  The callback must also
 * set the EmberStatus status code to be passed back to the caller.  The
 * framework will do no further processing on the message.
        If the
 * function returns false then it is assumed that the callback has not processed
 * the mesasge and the framework will continue to process accordingly.
 *
 * @param messageStruct The structure containing the parameters of the APS
 * message to be sent.  Ver.: always
 * @param status A pointer to the status code value that will be returned to the
 * caller.  Ver.: always
 */
bool emberAfPreMessageSendCallback(EmberAfMessageStruct * messageStruct, EmberStatus * status)
{
    return false;
}

/** @brief Get Endpoint Info
 *
 * This function is a callback to an application implemented endpoint that
 * operates outside the normal application framework.  When the framework wishes
 * to perform operations with that endpoint it uses this callback to retrieve
 * the endpoint's information.  If the endpoint exists and the application can
 * provide data then true shall be returned.  Otherwise the callback must return
 * false.
 *
 * @param endpoint The endpoint to retrieve data for.  Ver.: always
 * @param returnNetworkIndex The index corresponding to the ZigBee network the
 * endpoint belongs to.  If not using a multi-network device, 0 must be
 * returned.  Otherwise on a multi-network device the stack will switch to this
 * network before sending the message.  Ver.: always
 * @param returnEndpointInfo A pointer to a data struct that will be written
 * with information about the endpoint.  Ver.: always
 */
bool emberAfGetEndpointInfoCallback(uint8_t endpoint, uint8_t * returnNetworkIndex, EmberAfEndpointInfoStruct * returnEndpointInfo)
{
    return false;
}

/** @brief Get Current Time
 *
 * This callback is called when device attempts to get current time from the
 * hardware. If this device has means to retrieve exact time, then this method
 * should implement it. If the callback can't provide the exact time it should
 * return 0 to indicate failure. Default action is to return 0, which indicates
 * that device does not have access to real time.
 *
 */
uint32_t emberAfGetCurrentTimeCallback()
{
    return 0;
}

/** @brief Start Move
 *
 * This function is called to initiate the process for a device to move (rejoin)
 * to a new parent.
 *
 */
bool emberAfStartMoveCallback()
{
    return false;
}

bool emberAfConfigureReportingResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
     return false;
}

bool emberAfReadReportingConfigurationResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen)
{
     return false;
}

void emberAfIasZoneClusterClientInitCallback(uint8_t endpoint) {}

void emberAfIasZoneClusterServerMessageSentCallback(EmberOutgoingMessageType type, uint16_t indexOrDestination,
                                                    EmberApsFrame * apsFrame, uint16_t msgLen, uint8_t * message,
                                                    EmberStatus status)
{}
