
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

#include <stdint.h>

#include "af-structs.h"
#include "call-command-handler.h"
#include "callback.h"
#include "command-id.h"
#include "util.h"

EmberAfStatus emberAfBarrierControlClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfBasicClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfColorControlClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfDoorLockClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfGroupsClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfIASZoneClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfIdentifyClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfLevelControlClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfOnOffClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfScenesClusterServerCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfTemperatureMeasurementClusterServerCommandParse(EmberAfClusterCommand * cmd);

static EmberAfStatus status(bool wasHandled, bool clusterExists, bool mfgSpecific)
{
    if (wasHandled)
    {
        return EMBER_ZCL_STATUS_SUCCESS;
    }
    else if (mfgSpecific)
    {
        return EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND;
    }
    else if (clusterExists)
    {
        return EMBER_ZCL_STATUS_UNSUP_COMMAND;
    }
    else
    {
        return EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER;
    }
}

// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse(EmberAfClusterCommand * cmd)
{
    EmberAfStatus result = status(false, false, cmd->mfgSpecific);
    if (cmd->direction == (uint8_t) ZCL_DIRECTION_SERVER_TO_CLIENT &&
        emberAfContainsClientWithMfgCode(cmd->apsFrame->destinationEndpoint, cmd->apsFrame->clusterId, cmd->mfgCode))
    {
        switch (cmd->apsFrame->clusterId)
        {
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
        }
    }
    else if (cmd->direction == (uint8_t) ZCL_DIRECTION_CLIENT_TO_SERVER &&
             emberAfContainsServerWithMfgCode(cmd->apsFrame->destinationEndpoint, cmd->apsFrame->clusterId, cmd->mfgCode))
    {
        switch (cmd->apsFrame->clusterId)
        {
        case ZCL_BARRIER_CONTROL_CLUSTER_ID:
            result = emberAfBarrierControlClusterServerCommandParse(cmd);
            break;
        case ZCL_BASIC_CLUSTER_ID:
            result = emberAfBasicClusterServerCommandParse(cmd);
            break;
        case ZCL_COLOR_CONTROL_CLUSTER_ID:
            result = emberAfColorControlClusterServerCommandParse(cmd);
            break;
        case ZCL_DOOR_LOCK_CLUSTER_ID:
            result = emberAfDoorLockClusterServerCommandParse(cmd);
            break;
        case ZCL_GROUPS_CLUSTER_ID:
            result = emberAfGroupsClusterServerCommandParse(cmd);
            break;
        case ZCL_IAS_ZONE_CLUSTER_ID:
            result = emberAfIASZoneClusterServerCommandParse(cmd);
            break;
        case ZCL_IDENTIFY_CLUSTER_ID:
            result = emberAfIdentifyClusterServerCommandParse(cmd);
            break;
        case ZCL_LEVEL_CONTROL_CLUSTER_ID:
            result = emberAfLevelControlClusterServerCommandParse(cmd);
            break;
        case ZCL_ON_OFF_CLUSTER_ID:
            result = emberAfOnOffClusterServerCommandParse(cmd);
            break;
        case ZCL_SCENES_CLUSTER_ID:
            result = emberAfScenesClusterServerCommandParse(cmd);
            break;
        case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
            result = emberAfTemperatureMeasurementClusterServerCommandParse(cmd);
            break;
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
        }
    }
    return result;
}

// Cluster specific command parsing

EmberAfStatus emberAfBarrierControlClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_BARRIER_CONTROL_GO_TO_PERCENT_COMMAND_ID: {
            uint32_t argOffset    = 0;
            uint8_t * percentOpen = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfBarrierControlClusterBarrierControlGoToPercentCallback(*percentOpen);
            break;
        }
        case ZCL_BARRIER_CONTROL_STOP_COMMAND_ID: {
            wasHandled = emberAfBarrierControlClusterBarrierControlStopCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfBasicClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID: {
            wasHandled = emberAfBasicClusterResetToFactoryDefaultsCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfColorControlClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_MOVE_COLOR_COMMAND_ID: {
            uint32_t argOffset = 0;
            int16_t * rateX    = (int16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(int16_t);
            int16_t * rateY = (int16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(int16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveColorCallback(*rateX, *rateY, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_COLOR_TEMPERATURE_COMMAND_ID: {
            uint32_t argOffset            = 0;
            EmberAfHueMoveMode * moveMode = (EmberAfHueMoveMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfHueMoveMode);
            uint16_t * rate = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * colorTemperatureMinimum = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * colorTemperatureMaximum = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveColorTemperatureCallback(
                *moveMode, *rate, *colorTemperatureMinimum, *colorTemperatureMaximum, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_HUE_COMMAND_ID: {
            uint32_t argOffset            = 0;
            EmberAfHueMoveMode * moveMode = (EmberAfHueMoveMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfHueMoveMode);
            uint8_t * rate = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveHueCallback(*moveMode, *rate, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_SATURATION_COMMAND_ID: {
            uint32_t argOffset                   = 0;
            EmberAfSaturationMoveMode * moveMode = (EmberAfSaturationMoveMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfSaturationMoveMode);
            uint8_t * rate = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveSaturationCallback(*moveMode, *rate, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_TO_COLOR_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * colorX  = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * colorY = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfColorControlClusterMoveToColorCallback(*colorX, *colorY, *transitionTime, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_TO_COLOR_TEMPERATURE_COMMAND_ID: {
            uint32_t argOffset          = 0;
            uint16_t * colorTemperature = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveToColorTemperatureCallback(*colorTemperature, *transitionTime, *optionsMask,
                                                                                  *optionsOverride);
            break;
        }
        case ZCL_MOVE_TO_HUE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t * hue      = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            EmberAfHueDirection * direction = (EmberAfHueDirection *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfHueDirection);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfColorControlClusterMoveToHueCallback(*hue, *direction, *transitionTime, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_MOVE_TO_HUE_AND_SATURATION_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t * hue      = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * saturation = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterMoveToHueAndSaturationCallback(*hue, *saturation, *transitionTime, *optionsMask,
                                                                                  *optionsOverride);
            break;
        }
        case ZCL_MOVE_TO_SATURATION_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * saturation = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfColorControlClusterMoveToSaturationCallback(*saturation, *transitionTime, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_STEP_COLOR_COMMAND_ID: {
            uint32_t argOffset = 0;
            int16_t * stepX    = (int16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(int16_t);
            int16_t * stepY = (int16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(int16_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfColorControlClusterStepColorCallback(*stepX, *stepY, *transitionTime, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_STEP_COLOR_TEMPERATURE_COMMAND_ID: {
            uint32_t argOffset            = 0;
            EmberAfHueStepMode * stepMode = (EmberAfHueStepMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfHueStepMode);
            uint16_t * stepSize = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * colorTemperatureMinimum = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint16_t * colorTemperatureMaximum = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterStepColorTemperatureCallback(*stepMode, *stepSize, *transitionTime,
                                                                                *colorTemperatureMinimum, *colorTemperatureMaximum,
                                                                                *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_STEP_HUE_COMMAND_ID: {
            uint32_t argOffset            = 0;
            EmberAfHueStepMode * stepMode = (EmberAfHueStepMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfHueStepMode);
            uint8_t * stepSize = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * transitionTime = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfColorControlClusterStepHueCallback(*stepMode, *stepSize, *transitionTime, *optionsMask, *optionsOverride);
            break;
        }
        case ZCL_STEP_SATURATION_COMMAND_ID: {
            uint32_t argOffset                   = 0;
            EmberAfSaturationStepMode * stepMode = (EmberAfSaturationStepMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfSaturationStepMode);
            uint8_t * stepSize = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * transitionTime = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterStepSaturationCallback(*stepMode, *stepSize, *transitionTime, *optionsMask,
                                                                          *optionsOverride);
            break;
        }
        case ZCL_STOP_MOVE_STEP_COMMAND_ID: {
            uint32_t argOffset    = 0;
            uint8_t * optionsMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionsOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfColorControlClusterStopMoveStepCallback(*optionsMask, *optionsOverride);
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfDoorLockClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_CLEAR_HOLIDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterClearHolidayScheduleCallback(*scheduleId);
            break;
        }
        case ZCL_CLEAR_WEEKDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterClearWeekdayScheduleCallback(*scheduleId, *userId);
            break;
        }
        case ZCL_CLEAR_YEARDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterClearYeardayScheduleCallback(*scheduleId, *userId);
            break;
        }
        case ZCL_GET_HOLIDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterGetHolidayScheduleCallback(*scheduleId);
            break;
        }
        case ZCL_GET_USER_TYPE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * userId  = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterGetUserTypeCallback(*userId);
            break;
        }
        case ZCL_GET_WEEKDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterGetWeekdayScheduleCallback(*scheduleId, *userId);
            break;
        }
        case ZCL_GET_YEARDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterGetYeardayScheduleCallback(*scheduleId, *userId);
            break;
        }
        case ZCL_LOCK_DOOR_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t ** PIN     = (uint8_t **) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterLockDoorCallback(*PIN);
            break;
        }
        case ZCL_SET_HOLIDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint32_t * localStartTime = (uint32_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint32_t);
            uint32_t * localEndTime = (uint32_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint32_t);
            uint8_t * operatingModeDuringHoliday = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterSetHolidayScheduleCallback(*scheduleId, *localStartTime, *localEndTime,
                                                                          *operatingModeDuringHoliday);
            break;
        }
        case ZCL_SET_USER_TYPE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * userId  = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            EmberAfDoorLockUserType * userType = (EmberAfDoorLockUserType *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterSetUserTypeCallback(*userId, *userType);
            break;
        }
        case ZCL_SET_WEEKDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * daysMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * startHour = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * startMinute = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * endHour = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * endMinute = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterSetWeekdayScheduleCallback(*scheduleId, *userId, *daysMask, *startHour, *startMinute,
                                                                          *endHour, *endMinute);
            break;
        }
        case ZCL_SET_YEARDAY_SCHEDULE_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * scheduleId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * userId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint32_t * localStartTime = (uint32_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint32_t);
            uint32_t * localEndTime = (uint32_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterSetYeardayScheduleCallback(*scheduleId, *userId, *localStartTime, *localEndTime);
            break;
        }
        case ZCL_UNLOCK_DOOR_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t ** PIN     = (uint8_t **) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterUnlockDoorCallback(*PIN);
            break;
        }
        case ZCL_UNLOCK_WITH_TIMEOUT_COMMAND_ID: {
            uint32_t argOffset          = 0;
            uint16_t * timeoutInSeconds = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t ** pin = (uint8_t **) (cmd->buffer + argOffset);

            wasHandled = emberAfDoorLockClusterUnlockWithTimeoutCallback(*timeoutInSeconds, *pin);
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfGroupsClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_ADD_GROUP_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t ** groupName = (uint8_t **) (cmd->buffer + argOffset);

            wasHandled = emberAfGroupsClusterAddGroupCallback(*groupId, *groupName);
            break;
        }
        case ZCL_ADD_GROUP_IF_IDENTIFYING_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t ** groupName = (uint8_t **) (cmd->buffer + argOffset);

            wasHandled = emberAfGroupsClusterAddGroupIfIdentifyingCallback(*groupId, *groupName);
            break;
        }
        case ZCL_GET_GROUP_MEMBERSHIP_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * groupCount = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * groupList = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfGroupsClusterGetGroupMembershipCallback(*groupCount, *groupList);
            break;
        }
        case ZCL_REMOVE_ALL_GROUPS_COMMAND_ID: {
            wasHandled = emberAfGroupsClusterRemoveAllGroupsCallback();
            break;
        }
        case ZCL_REMOVE_GROUP_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfGroupsClusterRemoveGroupCallback(*groupId);
            break;
        }
        case ZCL_VIEW_GROUP_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfGroupsClusterViewGroupCallback(*groupId);
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfIASZoneClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID: {
            uint32_t argOffset                                = 0;
            EmberAfIasEnrollResponseCode * enrollResponseCode = (EmberAfIasEnrollResponseCode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfIasEnrollResponseCode);
            uint8_t * zoneId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfIASZoneClusterZoneEnrollResponseCallback(*enrollResponseCode, *zoneId);
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfIdentifyClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_IDENTIFY_COMMAND_ID: {
            uint32_t argOffset      = 0;
            uint16_t * identifyTime = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfIdentifyClusterIdentifyCallback(*identifyTime);
            break;
        }
        case ZCL_IDENTIFY_QUERY_COMMAND_ID: {
            wasHandled = emberAfIdentifyClusterIdentifyQueryCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfLevelControlClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_MOVE_COMMAND_ID: {
            uint32_t argOffset         = 0;
            EmberAfMoveMode * moveMode = (EmberAfMoveMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfMoveMode);
            uint8_t * rate = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterMoveCallback(*moveMode, *rate, *optionMask, *optionOverride);
            break;
        }
        case ZCL_MOVE_TO_LEVEL_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t * level    = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterMoveToLevelCallback(*level, *transitionTime, *optionMask, *optionOverride);
            break;
        }
        case ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint8_t * level    = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterMoveToLevelWithOnOffCallback(*level, *transitionTime);
            break;
        }
        case ZCL_MOVE_WITH_ON_OFF_COMMAND_ID: {
            uint32_t argOffset         = 0;
            EmberAfMoveMode * moveMode = (EmberAfMoveMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfMoveMode);
            uint8_t * rate = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterMoveWithOnOffCallback(*moveMode, *rate);
            break;
        }
        case ZCL_STEP_COMMAND_ID: {
            uint32_t argOffset         = 0;
            EmberAfStepMode * stepMode = (EmberAfStepMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfStepMode);
            uint8_t * stepSize = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * optionMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled =
                emberAfLevelControlClusterStepCallback(*stepMode, *stepSize, *transitionTime, *optionMask, *optionOverride);
            break;
        }
        case ZCL_STEP_WITH_ON_OFF_COMMAND_ID: {
            uint32_t argOffset         = 0;
            EmberAfStepMode * stepMode = (EmberAfStepMode *) (cmd->buffer + argOffset);
            argOffset += sizeof(EmberAfStepMode);
            uint8_t * stepSize = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterStepWithOnOffCallback(*stepMode, *stepSize, *transitionTime);
            break;
        }
        case ZCL_STOP_COMMAND_ID: {
            uint32_t argOffset   = 0;
            uint8_t * optionMask = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint8_t * optionOverride = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfLevelControlClusterStopCallback(*optionMask, *optionOverride);
            break;
        }
        case ZCL_STOP_WITH_ON_OFF_COMMAND_ID: {
            wasHandled = emberAfLevelControlClusterStopWithOnOffCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfOnOffClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_OFF_COMMAND_ID: {
            wasHandled = emberAfOnOffClusterOffCallback();
            break;
        }
        case ZCL_ON_COMMAND_ID: {
            wasHandled = emberAfOnOffClusterOnCallback();
            break;
        }
        case ZCL_TOGGLE_COMMAND_ID: {
            wasHandled = emberAfOnOffClusterToggleCallback();
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfScenesClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_ADD_SCENE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * sceneId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t ** sceneName = (uint8_t **) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t *);
            EmberAfSceneExtensionFieldSet * extensionFieldSets = (EmberAfSceneExtensionFieldSet *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterAddSceneCallback(*groupId, *sceneId, *transitionTime, *sceneName, *extensionFieldSets);
            break;
        }
        case ZCL_GET_SCENE_MEMBERSHIP_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterGetSceneMembershipCallback(*groupId);
            break;
        }
        case ZCL_RECALL_SCENE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * sceneId = (uint8_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint8_t);
            uint16_t * transitionTime = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterRecallSceneCallback(*groupId, *sceneId, *transitionTime);
            break;
        }
        case ZCL_REMOVE_ALL_SCENES_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterRemoveAllScenesCallback(*groupId);
            break;
        }
        case ZCL_REMOVE_SCENE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * sceneId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterRemoveSceneCallback(*groupId, *sceneId);
            break;
        }
        case ZCL_STORE_SCENE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * sceneId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterStoreSceneCallback(*groupId, *sceneId);
            break;
        }
        case ZCL_VIEW_SCENE_COMMAND_ID: {
            uint32_t argOffset = 0;
            uint16_t * groupId = (uint16_t *) (cmd->buffer + argOffset);
            argOffset += sizeof(uint16_t);
            uint8_t * sceneId = (uint8_t *) (cmd->buffer + argOffset);

            wasHandled = emberAfScenesClusterViewSceneCallback(*groupId, *sceneId);
            break;
        }
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
EmberAfStatus emberAfTemperatureMeasurementClusterServerCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        default: {
            // Unrecognized command ID, error status will apply.
            break;
        }
        }
    }
    return status(wasHandled, true, cmd->mfgSpecific);
}
