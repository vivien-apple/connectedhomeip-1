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
#include "cluster-id.h"
#include "command-id.h"
#include "util.h"

using namespace chip;

EmberAfStatus emberAfBarrierControlClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfBasicClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfBindingClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfColorControlClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfDoorLockClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfGroupsClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfIdentifyClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfLevelControlClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfOnOffClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfScenesClusterClientCommandParse(EmberAfClusterCommand * cmd);
EmberAfStatus emberAfTemperatureMeasurementClusterClientCommandParse(EmberAfClusterCommand * cmd);

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
        case ZCL_BARRIER_CONTROL_CLUSTER_ID:
            // No commands are enabled for cluster Barrier Control
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_BASIC_CLUSTER_ID:
            // No commands are enabled for cluster Basic
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_BINDING_CLUSTER_ID:
            // No commands are enabled for cluster Binding
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_COLOR_CONTROL_CLUSTER_ID:
            // No commands are enabled for cluster Color Control
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_DOOR_LOCK_CLUSTER_ID:
            result = emberAfDoorLockClusterClientCommandParse(cmd);
            break;
        case ZCL_GROUPS_CLUSTER_ID:
            result = emberAfGroupsClusterClientCommandParse(cmd);
            break;
        case ZCL_IDENTIFY_CLUSTER_ID:
            result = emberAfIdentifyClusterClientCommandParse(cmd);
            break;
        case ZCL_LEVEL_CONTROL_CLUSTER_ID:
            // No commands are enabled for cluster Level Control
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_ON_OFF_CLUSTER_ID:
            // No commands are enabled for cluster On/off
            result = status(false, true, cmd->mfgSpecific);
            break;
        case ZCL_SCENES_CLUSTER_ID:
            result = emberAfScenesClusterClientCommandParse(cmd);
            break;
        case ZCL_TEMP_MEASUREMENT_CLUSTER_ID:
            // No commands are enabled for cluster Temperature Measurement
            result = status(false, true, cmd->mfgSpecific);
            break;
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
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
        }
    }
    return result;
}

// Cluster specific command parsing

EmberAfStatus emberAfDoorLockClusterClientCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_CLEAR_ALL_PINS_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearAllPinsResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_ALL_RFIDS_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearAllRfidsResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_HOLIDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearHolidayScheduleResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_PIN_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearPinResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_RFID_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearRfidResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_WEEKDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearWeekdayScheduleResponseCallback(status);
            break;
        }
        case ZCL_CLEAR_YEARDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterClearYeardayScheduleResponseCallback(status);
            break;
        }
        case ZCL_GET_HOLIDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t scheduleId;
            uint8_t status;
            uint32_t localStartTime;
            uint32_t localEndTime;
            uint8_t operatingModeDuringHoliday;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            scheduleId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 4)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            localStartTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 4;
            if (cmd->bufLen < payloadOffset + 4)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            localEndTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 4;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            operatingModeDuringHoliday = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetHolidayScheduleResponseCallback(scheduleId, status, localStartTime, localEndTime,
                                                                                  operatingModeDuringHoliday);
            break;
        }
        case ZCL_GET_LOG_RECORD_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint16_t logEntryId;
            uint32_t timestamp;
            uint8_t eventType;
            uint8_t source;
            uint8_t eventIdOrAlarmCode;
            uint16_t userId;
            uint8_t * pin;

            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            logEntryId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 4)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            timestamp = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 4;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            eventType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            source = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            eventIdOrAlarmCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1u)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            pin = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetLogRecordResponseCallback(logEntryId, timestamp, eventType, source,
                                                                            eventIdOrAlarmCode, userId, pin);
            break;
        }
        case ZCL_GET_PIN_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint16_t userId;
            uint8_t userStatus;
            uint8_t userType;
            uint8_t * pin;

            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1u)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            pin = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetPinResponseCallback(userId, userStatus, userType, pin);
            break;
        }
        case ZCL_GET_RFID_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint16_t userId;
            uint8_t userStatus;
            uint8_t userType;
            uint8_t * rfid;

            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userStatus = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1u)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            rfid = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetRfidResponseCallback(userId, userStatus, userType, rfid);
            break;
        }
        case ZCL_GET_USER_TYPE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint16_t userId;
            uint8_t userType;

            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userType = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetUserTypeResponseCallback(userId, userType);
            break;
        }
        case ZCL_GET_WEEKDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t scheduleId;
            uint16_t userId;
            uint8_t status;
            uint8_t daysMask;
            uint8_t startHour;
            uint8_t startMinute;
            uint8_t endHour;
            uint8_t endMinute;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            scheduleId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            daysMask = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            startHour = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            startMinute = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            endHour = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            endMinute = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterGetWeekdayScheduleResponseCallback(scheduleId, userId, status, daysMask, startHour,
                                                                                  startMinute, endHour, endMinute);
            break;
        }
        case ZCL_GET_YEARDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t scheduleId;
            uint16_t userId;
            uint8_t status;
            uint32_t localStartTime;
            uint32_t localEndTime;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            scheduleId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            userId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 4)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            localStartTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 4;
            if (cmd->bufLen < payloadOffset + 4)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            localEndTime = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled =
                emberAfDoorLockClusterGetYeardayScheduleResponseCallback(scheduleId, userId, status, localStartTime, localEndTime);
            break;
        }
        case ZCL_LOCK_DOOR_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterLockDoorResponseCallback(status);
            break;
        }
        case ZCL_SET_HOLIDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetHolidayScheduleResponseCallback(status);
            break;
        }
        case ZCL_SET_PIN_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetPinResponseCallback(status);
            break;
        }
        case ZCL_SET_RFID_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetRfidResponseCallback(status);
            break;
        }
        case ZCL_SET_USER_TYPE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetUserTypeResponseCallback(status);
            break;
        }
        case ZCL_SET_WEEKDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetWeekdayScheduleResponseCallback(status);
            break;
        }
        case ZCL_SET_YEARDAY_SCHEDULE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterSetYeardayScheduleResponseCallback(status);
            break;
        }
        case ZCL_UNLOCK_DOOR_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterUnlockDoorResponseCallback(status);
            break;
        }
        case ZCL_UNLOCK_WITH_TIMEOUT_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfDoorLockClusterUnlockWithTimeoutResponseCallback(status);
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
EmberAfStatus emberAfGroupsClusterClientCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_ADD_GROUP_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfGroupsClusterAddGroupResponseCallback(status, groupId);
            break;
        }
        case ZCL_GET_GROUP_MEMBERSHIP_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t capacity;
            uint8_t groupCount;
            /* TYPE WARNING: array array defaults to */ uint8_t * groupList;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            capacity = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            groupList = cmd->buffer + payloadOffset;

            wasHandled = emberAfGroupsClusterGetGroupMembershipResponseCallback(capacity, groupCount, groupList);
            break;
        }
        case ZCL_REMOVE_GROUP_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfGroupsClusterRemoveGroupResponseCallback(status, groupId);
            break;
        }
        case ZCL_VIEW_GROUP_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;
            uint8_t * groupName;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1u)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfGroupsClusterViewGroupResponseCallback(status, groupId, groupName);
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
EmberAfStatus emberAfIdentifyClusterClientCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_IDENTIFY_QUERY_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint16_t timeout;

            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            timeout = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfIdentifyClusterIdentifyQueryResponseCallback(timeout);
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
EmberAfStatus emberAfScenesClusterClientCommandParse(EmberAfClusterCommand * cmd)
{
    bool wasHandled = false;

    if (!cmd->mfgSpecific)
    {
        switch (cmd->commandId)
        {
        case ZCL_ADD_SCENE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;
            uint8_t sceneId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfScenesClusterAddSceneResponseCallback(status, groupId, sceneId);
            break;
        }
        case ZCL_GET_SCENE_MEMBERSHIP_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint8_t capacity;
            uint16_t groupId;
            uint8_t sceneCount;
            /* TYPE WARNING: array array defaults to */ uint8_t * sceneList;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            capacity = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (status == 0)
            {
                if (cmd->bufLen < payloadOffset + 1)
                {
                    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
                }
                sceneCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
                payloadOffset += 1;
            }
            else
            {
                sceneCount = UINT8_MAX;
            }
            if (status == 0)
            {
                sceneList = cmd->buffer + payloadOffset;
            }
            else
            {
                sceneList = NULL;
            }

            wasHandled = emberAfScenesClusterGetSceneMembershipResponseCallback(status, capacity, groupId, sceneCount, sceneList);
            break;
        }
        case ZCL_REMOVE_ALL_SCENES_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfScenesClusterRemoveAllScenesResponseCallback(status, groupId);
            break;
        }
        case ZCL_REMOVE_SCENE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;
            uint8_t sceneId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfScenesClusterRemoveSceneResponseCallback(status, groupId, sceneId);
            break;
        }
        case ZCL_STORE_SCENE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;
            uint8_t sceneId;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);

            wasHandled = emberAfScenesClusterStoreSceneResponseCallback(status, groupId, sceneId);
            break;
        }
        case ZCL_VIEW_SCENE_RESPONSE_COMMAND_ID: {
            uint16_t payloadOffset = cmd->payloadStartIndex;
            uint8_t status;
            uint16_t groupId;
            uint8_t sceneId;
            uint16_t transitionTime;
            uint8_t * sceneName;
            /* TYPE WARNING: array array defaults to */ uint8_t * extensionFieldSets;

            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (cmd->bufLen < payloadOffset + 2)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            groupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 2;
            if (cmd->bufLen < payloadOffset + 1)
            {
                return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
            }
            sceneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
            payloadOffset += 1;
            if (status == 0)
            {
                if (cmd->bufLen < payloadOffset + 2)
                {
                    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
                }
                transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
                payloadOffset += 2;
            }
            else
            {
                transitionTime = UINT16_MAX;
            }
            if (status == 0)
            {
                if (cmd->bufLen < payloadOffset + 1u)
                {
                    return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
                }
                sceneName = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
                payloadOffset += emberAfStringLength(sceneName) + 1u;
            }
            else
            {
                sceneName = NULL;
            }
            if (status == 0)
            {
                extensionFieldSets = cmd->buffer + payloadOffset;
            }
            else
            {
                extensionFieldSets = NULL;
            }

            wasHandled = emberAfScenesClusterViewSceneResponseCallback(status, groupId, sceneId, transitionTime, sceneName,
                                                                       extensionFieldSets);
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
