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

#pragma once

#include "ModelCommand.h"
#include "ResponseCallbacks.h"
#include <controller/CHIPClusters.h>

static void OnDefaultSuccessResponse(void * context)
{
    ChipLogProgress(chipTool, "Default Success Response");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDefaultFailureResponse(void * context, uint8_t status)
{
    ChipLogProgress(chipTool, "Default Failure Response: 0x%02x", status);

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(false);
}

typedef void (*UnsupportedAttributeCallback)(void * context);
static void OnUnsupportedAttributeResponse(void * context)
{
    ChipLogError(chipTool, "Unsupported attribute Response. This should never happen !");
}

static void OnBooleanAttributeResponse(void * context, bool value)
{
    ChipLogProgress(chipTool, "Boolean attribute Response: %d", value);

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnInt8uAttributeResponse(void * context, uint8_t value)
{
    ChipLogProgress(chipTool, "Int8u attribute Response: %" PRIu8, value);

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnInt16uAttributeResponse(void * context, uint16_t value)
{
    ChipLogProgress(chipTool, "Int16u attribute Response: %" PRIu16, value);

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnInt16sAttributeResponse(void * context, int16_t value)
{
    ChipLogProgress(chipTool, "Int16s attribute Response: %" PRId16, value);

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearAllPinsResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearAllPinsResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearAllRfidsResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearAllRfidsResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearHolidayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearHolidayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearPinResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearPinResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearRfidResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearRfidResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearWeekdayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearWeekdayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterClearYeardayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterClearYeardayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetHolidayScheduleResponse(void * context, uint8_t scheduleId, uint32_t localStartTime,
                                                        uint32_t localEndTime, uint8_t operatingModeDuringHoliday)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetHolidayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetLogRecordResponse(void * context, uint16_t logEntryId, uint32_t timestamp, uint8_t eventType,
                                                  uint8_t source, uint8_t eventIdOrAlarmCode, uint16_t userId, uint8_t * pin)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetLogRecordResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetPinResponse(void * context, uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * pin)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetPinResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetRfidResponse(void * context, uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * rfid)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetRfidResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetUserTypeResponse(void * context, uint16_t userId, uint8_t userType)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetUserTypeResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetWeekdayScheduleResponse(void * context, uint8_t scheduleId, uint16_t userId, uint8_t daysMask,
                                                        uint8_t startHour, uint8_t startMinute, uint8_t endHour, uint8_t endMinute)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetWeekdayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterGetYeardayScheduleResponse(void * context, uint8_t scheduleId, uint16_t userId,
                                                        uint32_t localStartTime, uint32_t localEndTime)
{
    ChipLogProgress(chipTool, "DoorLockClusterGetYeardayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterLockDoorResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterLockDoorResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetHolidayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetHolidayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetPinResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetPinResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetRfidResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetRfidResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetUserTypeResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetUserTypeResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetWeekdayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetWeekdayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterSetYeardayScheduleResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterSetYeardayScheduleResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterUnlockDoorResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterUnlockDoorResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnDoorLockClusterUnlockWithTimeoutResponse(void * context)
{
    ChipLogProgress(chipTool, "DoorLockClusterUnlockWithTimeoutResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnGroupsClusterAddGroupResponse(void * context, uint16_t groupId)
{
    ChipLogProgress(chipTool, "GroupsClusterAddGroupResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnGroupsClusterGetGroupMembershipResponse(void * context, uint8_t capacity, uint8_t groupCount,
                                                      /* TYPE WARNING: array array defaults to */ uint8_t * groupList)
{
    ChipLogProgress(chipTool, "GroupsClusterGetGroupMembershipResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnGroupsClusterRemoveGroupResponse(void * context, uint16_t groupId)
{
    ChipLogProgress(chipTool, "GroupsClusterRemoveGroupResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnGroupsClusterViewGroupResponse(void * context, uint16_t groupId, uint8_t * groupName)
{
    ChipLogProgress(chipTool, "GroupsClusterViewGroupResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnIdentifyClusterIdentifyQueryResponse(void * context, uint16_t timeout)
{
    ChipLogProgress(chipTool, "IdentifyClusterIdentifyQueryResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterAddSceneResponse(void * context, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "ScenesClusterAddSceneResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterGetSceneMembershipResponse(void * context, uint8_t capacity, uint16_t groupId, uint8_t sceneCount,
                                                      /* TYPE WARNING: array array defaults to */ uint8_t * sceneList)
{
    ChipLogProgress(chipTool, "ScenesClusterGetSceneMembershipResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterRemoveAllScenesResponse(void * context, uint16_t groupId)
{
    ChipLogProgress(chipTool, "ScenesClusterRemoveAllScenesResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterRemoveSceneResponse(void * context, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "ScenesClusterRemoveSceneResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterStoreSceneResponse(void * context, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "ScenesClusterStoreSceneResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

static void OnScenesClusterViewSceneResponse(void * context, uint16_t groupId, uint8_t sceneId, uint16_t transitionTime,
                                             uint8_t * sceneName,
                                             /* TYPE WARNING: array array defaults to */ uint8_t * extensionFieldSets)
{
    ChipLogProgress(chipTool, "ScenesClusterViewSceneResponse");

    ModelCommand * command = reinterpret_cast<ModelCommand *>(context);
    command->SetCommandExitStatus(true);
}

/*----------------------------------------------------------------------------*\
| Cluster Name                                                        |   ID   |
|---------------------------------------------------------------------+--------|
| BarrierControl                                                      | 0x0103 |
| Basic                                                               | 0x0000 |
| Binding                                                             | 0xF000 |
| ColorControl                                                        | 0x0300 |
| DoorLock                                                            | 0x0101 |
| Groups                                                              | 0x0004 |
| Identify                                                            | 0x0003 |
| LevelControl                                                        | 0x0008 |
| OnOff                                                               | 0x0006 |
| Scenes                                                              | 0x0005 |
| TemperatureMeasurement                                              | 0x0402 |
\*----------------------------------------------------------------------------*/

constexpr chip::ClusterId kBarrierControlClusterId         = 0x0103;
constexpr chip::ClusterId kBasicClusterId                  = 0x0000;
constexpr chip::ClusterId kBindingClusterId                = 0xF000;
constexpr chip::ClusterId kColorControlClusterId           = 0x0300;
constexpr chip::ClusterId kDoorLockClusterId               = 0x0101;
constexpr chip::ClusterId kGroupsClusterId                 = 0x0004;
constexpr chip::ClusterId kIdentifyClusterId               = 0x0003;
constexpr chip::ClusterId kLevelControlClusterId           = 0x0008;
constexpr chip::ClusterId kOnOffClusterId                  = 0x0006;
constexpr chip::ClusterId kScenesClusterId                 = 0x0005;
constexpr chip::ClusterId kTemperatureMeasurementClusterId = 0x0402;

/*----------------------------------------------------------------------------*\
| Cluster BarrierControl                                              | 0x0103 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * BarrierControlGoToPercent                                         |   0x00 |
| * BarrierControlStop                                                |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * BarrierMovingState                                                | 0x0001 |
| * BarrierSafetyStatus                                               | 0x0002 |
| * BarrierCapabilities                                               | 0x0003 |
| * BarrierPosition                                                   | 0x000A |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command BarrierControlGoToPercent
 */
class BarrierControlBarrierControlGoToPercent : public ModelCommand
{
public:
    BarrierControlBarrierControlGoToPercent() : ModelCommand("barrier-control-go-to-percent")
    {
        AddArgument("percentOpen", 0, UINT8_MAX, &mPercentOpen);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.BarrierControlGoToPercent(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mPercentOpen);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mPercentOpen;
};

/*
 * Command BarrierControlStop
 */
class BarrierControlBarrierControlStop : public ModelCommand
{
public:
    BarrierControlBarrierControlStop() : ModelCommand("barrier-control-stop") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.BarrierControlStop(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Discover Attributes
 */
class DiscoverBarrierControlAttributes : public ModelCommand
{
public:
    DiscoverBarrierControlAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute BarrierMovingState
 */
class ReadBarrierControlBarrierMovingState : public ModelCommand
{
public:
    ReadBarrierControlBarrierMovingState() : ModelCommand("read")
    {
        AddArgument("attr-name", "barrier-moving-state");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeBarrierMovingState(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute BarrierSafetyStatus
 */
class ReadBarrierControlBarrierSafetyStatus : public ModelCommand
{
public:
    ReadBarrierControlBarrierSafetyStatus() : ModelCommand("read")
    {
        AddArgument("attr-name", "barrier-safety-status");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeBarrierSafetyStatus(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute BarrierCapabilities
 */
class ReadBarrierControlBarrierCapabilities : public ModelCommand
{
public:
    ReadBarrierControlBarrierCapabilities() : ModelCommand("read")
    {
        AddArgument("attr-name", "barrier-capabilities");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeBarrierCapabilities(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute BarrierPosition
 */
class ReadBarrierControlBarrierPosition : public ModelCommand
{
public:
    ReadBarrierControlBarrierPosition() : ModelCommand("read")
    {
        AddArgument("attr-name", "barrier-position");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeBarrierPosition(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadBarrierControlClusterRevision : public ModelCommand
{
public:
    ReadBarrierControlClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0103) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BarrierControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster Basic                                                       | 0x0000 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * MfgSpecificPing                                                   |   0x00 |
| * ResetToFactoryDefaults                                            |   0x00 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * ZclVersion                                                        | 0x0000 |
| * PowerSource                                                       | 0x0007 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command MfgSpecificPing
 */
class BasicMfgSpecificPing : public ModelCommand
{
public:
    BasicMfgSpecificPing() : ModelCommand("mfg-specific-ping") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MfgSpecificPing(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command ResetToFactoryDefaults
 */
class BasicResetToFactoryDefaults : public ModelCommand
{
public:
    BasicResetToFactoryDefaults() : ModelCommand("reset-to-factory-defaults") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ResetToFactoryDefaults(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Discover Attributes
 */
class DiscoverBasicAttributes : public ModelCommand
{
public:
    DiscoverBasicAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ZclVersion
 */
class ReadBasicZclVersion : public ModelCommand
{
public:
    ReadBasicZclVersion() : ModelCommand("read")
    {
        AddArgument("attr-name", "zcl-version");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeZclVersion(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute PowerSource
 */
class ReadBasicPowerSource : public ModelCommand
{
public:
    ReadBasicPowerSource() : ModelCommand("read")
    {
        AddArgument("attr-name", "power-source");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePowerSource(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadBasicClusterRevision : public ModelCommand
{
public:
    ReadBasicClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BasicCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster Binding                                                     | 0xF000 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * Bind                                                              |   0x00 |
| * Unbind                                                            |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command Bind
 */
class BindingBind : public ModelCommand
{
public:
    BindingBind() : ModelCommand("bind")
    {
        AddArgument("nodeId", 0, UINT64_MAX, &mNodeId);
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("endpointId", 0, UINT8_MAX, &mEndpointId);
        AddArgument("clusterId", 0, UINT16_MAX, &mClusterId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0xF000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BindingCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Bind(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mNodeId, mGroupId, mEndpointId, mClusterId);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::NodeId mNodeId;
    chip::GroupId mGroupId;
    chip::EndpointId mEndpointId;
    chip::ClusterId mClusterId;
};

/*
 * Command Unbind
 */
class BindingUnbind : public ModelCommand
{
public:
    BindingUnbind() : ModelCommand("unbind")
    {
        AddArgument("nodeId", 0, UINT64_MAX, &mNodeId);
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("endpointId", 0, UINT8_MAX, &mEndpointId);
        AddArgument("clusterId", 0, UINT16_MAX, &mClusterId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0xF000) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::BindingCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Unbind(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mNodeId, mGroupId, mEndpointId, mClusterId);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::NodeId mNodeId;
    chip::GroupId mGroupId;
    chip::EndpointId mEndpointId;
    chip::ClusterId mClusterId;
};

/*
 * Discover Attributes
 */
class DiscoverBindingAttributes : public ModelCommand
{
public:
    DiscoverBindingAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::BindingCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadBindingClusterRevision : public ModelCommand
{
public:
    ReadBindingClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0xF000) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::BindingCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster ColorControl                                                | 0x0300 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * MoveColor                                                         |   0x08 |
| * MoveColorTemperature                                              |   0x4B |
| * MoveHue                                                           |   0x01 |
| * MoveSaturation                                                    |   0x04 |
| * MoveToColor                                                       |   0x07 |
| * MoveToColorTemperature                                            |   0x0A |
| * MoveToHue                                                         |   0x00 |
| * MoveToHueAndSaturation                                            |   0x06 |
| * MoveToSaturation                                                  |   0x03 |
| * StepColor                                                         |   0x09 |
| * StepColorTemperature                                              |   0x4C |
| * StepHue                                                           |   0x02 |
| * StepSaturation                                                    |   0x05 |
| * StopMoveStep                                                      |   0x47 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * CurrentHue                                                        | 0x0000 |
| * CurrentSaturation                                                 | 0x0001 |
| * RemainingTime                                                     | 0x0002 |
| * CurrentX                                                          | 0x0003 |
| * CurrentY                                                          | 0x0004 |
| * DriftCompensation                                                 | 0x0005 |
| * CompensationText                                                  | 0x0006 |
| * ColorTemperature                                                  | 0x0007 |
| * ColorMode                                                         | 0x0008 |
| * ColorControlOptions                                               | 0x000F |
| * NumberOfPrimaries                                                 | 0x0010 |
| * Primary1X                                                         | 0x0011 |
| * Primary1Y                                                         | 0x0012 |
| * Primary1Intensity                                                 | 0x0013 |
| * Primary2X                                                         | 0x0015 |
| * Primary2Y                                                         | 0x0016 |
| * Primary2Intensity                                                 | 0x0017 |
| * Primary3X                                                         | 0x0019 |
| * Primary3Y                                                         | 0x001A |
| * Primary3Intensity                                                 | 0x001B |
| * Primary4X                                                         | 0x0020 |
| * Primary4Y                                                         | 0x0021 |
| * Primary4Intensity                                                 | 0x0022 |
| * Primary5X                                                         | 0x0024 |
| * Primary5Y                                                         | 0x0025 |
| * Primary5Intensity                                                 | 0x0026 |
| * Primary6X                                                         | 0x0028 |
| * Primary6Y                                                         | 0x0029 |
| * Primary6Intensity                                                 | 0x002A |
| * WhitePointX                                                       | 0x0030 |
| * WhitePointY                                                       | 0x0031 |
| * ColorPointRX                                                      | 0x0032 |
| * ColorPointRY                                                      | 0x0033 |
| * ColorPointRIntensity                                              | 0x0034 |
| * ColorPointGX                                                      | 0x0036 |
| * ColorPointGY                                                      | 0x0037 |
| * ColorPointGIntensity                                              | 0x0038 |
| * ColorPointBX                                                      | 0x003A |
| * ColorPointBY                                                      | 0x003B |
| * ColorPointBIntensity                                              | 0x003C |
| * EnhancedCurrentHue                                                | 0x4000 |
| * EnhancedColorMode                                                 | 0x4001 |
| * ColorLoopActive                                                   | 0x4002 |
| * ColorLoopDirection                                                | 0x4003 |
| * ColorLoopTime                                                     | 0x4004 |
| * ColorCapabilities                                                 | 0x400A |
| * ColorTempPhysicalMin                                              | 0x400B |
| * ColorTempPhysicalMax                                              | 0x400C |
| * CoupleColorTempToLevelMinMireds                                   | 0x400D |
| * StartUpColorTemperatureMireds                                     | 0x4010 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command MoveColor
 */
class ColorControlMoveColor : public ModelCommand
{
public:
    ColorControlMoveColor() : ModelCommand("move-color")
    {
        AddArgument("rateX", INT16_MIN, INT16_MAX, &mRateX);
        AddArgument("rateY", INT16_MIN, INT16_MAX, &mRateY);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x08) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveColor(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mRateX, mRateY, mOptionsMask,
                                 mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    int16_t mRateX;
    int16_t mRateY;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveColorTemperature
 */
class ColorControlMoveColorTemperature : public ModelCommand
{
public:
    ColorControlMoveColorTemperature() : ModelCommand("move-color-temperature")
    {
        AddArgument("moveMode", 0, UINT8_MAX, &mMoveMode);
        AddArgument("rate", 0, UINT16_MAX, &mRate);
        AddArgument("colorTemperatureMinimum", 0, UINT16_MAX, &mColorTemperatureMinimum);
        AddArgument("colorTemperatureMaximum", 0, UINT16_MAX, &mColorTemperatureMaximum);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x4B) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveColorTemperature(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMoveMode, mRate,
                                            mColorTemperatureMinimum, mColorTemperatureMaximum, mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mMoveMode;
    uint16_t mRate;
    uint16_t mColorTemperatureMinimum;
    uint16_t mColorTemperatureMaximum;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveHue
 */
class ColorControlMoveHue : public ModelCommand
{
public:
    ColorControlMoveHue() : ModelCommand("move-hue")
    {
        AddArgument("moveMode", 0, UINT8_MAX, &mMoveMode);
        AddArgument("rate", 0, UINT8_MAX, &mRate);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMoveMode, mRate, mOptionsMask,
                               mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mMoveMode;
    uint8_t mRate;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveSaturation
 */
class ColorControlMoveSaturation : public ModelCommand
{
public:
    ColorControlMoveSaturation() : ModelCommand("move-saturation")
    {
        AddArgument("moveMode", 0, UINT8_MAX, &mMoveMode);
        AddArgument("rate", 0, UINT8_MAX, &mRate);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x04) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMoveMode, mRate, mOptionsMask,
                                      mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mMoveMode;
    uint8_t mRate;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveToColor
 */
class ColorControlMoveToColor : public ModelCommand
{
public:
    ColorControlMoveToColor() : ModelCommand("move-to-color")
    {
        AddArgument("colorX", 0, UINT16_MAX, &mColorX);
        AddArgument("colorY", 0, UINT16_MAX, &mColorY);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x07) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToColor(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mColorX, mColorY, mTransitionTime,
                                   mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mColorX;
    uint16_t mColorY;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveToColorTemperature
 */
class ColorControlMoveToColorTemperature : public ModelCommand
{
public:
    ColorControlMoveToColorTemperature() : ModelCommand("move-to-color-temperature")
    {
        AddArgument("colorTemperature", 0, UINT16_MAX, &mColorTemperature);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x0A) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToColorTemperature(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mColorTemperature,
                                              mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mColorTemperature;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveToHue
 */
class ColorControlMoveToHue : public ModelCommand
{
public:
    ColorControlMoveToHue() : ModelCommand("move-to-hue")
    {
        AddArgument("hue", 0, UINT8_MAX, &mHue);
        AddArgument("direction", 0, UINT8_MAX, &mDirection);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mHue, mDirection, mTransitionTime,
                                 mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mHue;
    uint8_t mDirection;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveToHueAndSaturation
 */
class ColorControlMoveToHueAndSaturation : public ModelCommand
{
public:
    ColorControlMoveToHueAndSaturation() : ModelCommand("move-to-hue-and-saturation")
    {
        AddArgument("hue", 0, UINT8_MAX, &mHue);
        AddArgument("saturation", 0, UINT8_MAX, &mSaturation);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToHueAndSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mHue, mSaturation,
                                              mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mHue;
    uint8_t mSaturation;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command MoveToSaturation
 */
class ColorControlMoveToSaturation : public ModelCommand
{
public:
    ColorControlMoveToSaturation() : ModelCommand("move-to-saturation")
    {
        AddArgument("saturation", 0, UINT8_MAX, &mSaturation);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x03) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mSaturation, mTransitionTime,
                                        mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mSaturation;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command StepColor
 */
class ColorControlStepColor : public ModelCommand
{
public:
    ColorControlStepColor() : ModelCommand("step-color")
    {
        AddArgument("stepX", INT16_MIN, INT16_MAX, &mStepX);
        AddArgument("stepY", INT16_MIN, INT16_MAX, &mStepY);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x09) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StepColor(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepX, mStepY, mTransitionTime,
                                 mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    int16_t mStepX;
    int16_t mStepY;
    uint16_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command StepColorTemperature
 */
class ColorControlStepColorTemperature : public ModelCommand
{
public:
    ColorControlStepColorTemperature() : ModelCommand("step-color-temperature")
    {
        AddArgument("stepMode", 0, UINT8_MAX, &mStepMode);
        AddArgument("stepSize", 0, UINT16_MAX, &mStepSize);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("colorTemperatureMinimum", 0, UINT16_MAX, &mColorTemperatureMinimum);
        AddArgument("colorTemperatureMaximum", 0, UINT16_MAX, &mColorTemperatureMaximum);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x4C) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StepColorTemperature(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepMode, mStepSize,
                                            mTransitionTime, mColorTemperatureMinimum, mColorTemperatureMaximum, mOptionsMask,
                                            mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mStepMode;
    uint16_t mStepSize;
    uint16_t mTransitionTime;
    uint16_t mColorTemperatureMinimum;
    uint16_t mColorTemperatureMaximum;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command StepHue
 */
class ColorControlStepHue : public ModelCommand
{
public:
    ColorControlStepHue() : ModelCommand("step-hue")
    {
        AddArgument("stepMode", 0, UINT8_MAX, &mStepMode);
        AddArgument("stepSize", 0, UINT8_MAX, &mStepSize);
        AddArgument("transitionTime", 0, UINT8_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x02) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StepHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepMode, mStepSize, mTransitionTime,
                               mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mStepMode;
    uint8_t mStepSize;
    uint8_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command StepSaturation
 */
class ColorControlStepSaturation : public ModelCommand
{
public:
    ColorControlStepSaturation() : ModelCommand("step-saturation")
    {
        AddArgument("stepMode", 0, UINT8_MAX, &mStepMode);
        AddArgument("stepSize", 0, UINT8_MAX, &mStepSize);
        AddArgument("transitionTime", 0, UINT8_MAX, &mTransitionTime);
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x05) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StepSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepMode, mStepSize,
                                      mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mStepMode;
    uint8_t mStepSize;
    uint8_t mTransitionTime;
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Command StopMoveStep
 */
class ColorControlStopMoveStep : public ModelCommand
{
public:
    ColorControlStopMoveStep() : ModelCommand("stop-move-step")
    {
        AddArgument("optionsMask", 0, UINT8_MAX, &mOptionsMask);
        AddArgument("optionsOverride", 0, UINT8_MAX, &mOptionsOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x47) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StopMoveStep(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mOptionsMask, mOptionsOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mOptionsMask;
    uint8_t mOptionsOverride;
};

/*
 * Discover Attributes
 */
class DiscoverColorControlAttributes : public ModelCommand
{
public:
    DiscoverColorControlAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CurrentHue
 */
class ReadColorControlCurrentHue : public ModelCommand
{
public:
    ReadColorControlCurrentHue() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-hue");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportColorControlCurrentHue : public ModelCommand
{
public:
    ReportColorControlCurrentHue() : ModelCommand("report")
    {
        AddArgument("attr-name", "current-hue");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT8_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeCurrentHue(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeCurrentHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                    mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int8uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint8_t mChange;
};

/*
 * Attribute CurrentSaturation
 */
class ReadColorControlCurrentSaturation : public ModelCommand
{
public:
    ReadColorControlCurrentSaturation() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-saturation");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportColorControlCurrentSaturation : public ModelCommand
{
public:
    ReportColorControlCurrentSaturation() : ModelCommand("report")
    {
        AddArgument("attr-name", "current-saturation");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT8_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeCurrentSaturation(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeCurrentSaturation(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                           mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int8uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint8_t mChange;
};

/*
 * Attribute RemainingTime
 */
class ReadColorControlRemainingTime : public ModelCommand
{
public:
    ReadColorControlRemainingTime() : ModelCommand("read")
    {
        AddArgument("attr-name", "remaining-time");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeRemainingTime(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CurrentX
 */
class ReadColorControlCurrentX : public ModelCommand
{
public:
    ReadColorControlCurrentX() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentX(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportColorControlCurrentX : public ModelCommand
{
public:
    ReportColorControlCurrentX() : ModelCommand("report")
    {
        AddArgument("attr-name", "current-x");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT16_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeCurrentX(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeCurrentX(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                  mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int16uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint16_t mChange;
};

/*
 * Attribute CurrentY
 */
class ReadColorControlCurrentY : public ModelCommand
{
public:
    ReadColorControlCurrentY() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentY(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportColorControlCurrentY : public ModelCommand
{
public:
    ReportColorControlCurrentY() : ModelCommand("report")
    {
        AddArgument("attr-name", "current-y");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT16_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeCurrentY(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeCurrentY(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                  mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int16uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint16_t mChange;
};

/*
 * Attribute DriftCompensation
 */
class ReadColorControlDriftCompensation : public ModelCommand
{
public:
    ReadColorControlDriftCompensation() : ModelCommand("read")
    {
        AddArgument("attr-name", "drift-compensation");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeDriftCompensation(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CompensationText
 */
class ReadColorControlCompensationText : public ModelCommand
{
public:
    ReadColorControlCompensationText() : ModelCommand("read")
    {
        AddArgument("attr-name", "compensation-text");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCompensationText(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<UnsupportedAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<UnsupportedAttributeCallback>(OnUnsupportedAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorTemperature
 */
class ReadColorControlColorTemperature : public ModelCommand
{
public:
    ReadColorControlColorTemperature() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-temperature");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorTemperature(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportColorControlColorTemperature : public ModelCommand
{
public:
    ReportColorControlColorTemperature() : ModelCommand("report")
    {
        AddArgument("attr-name", "color-temperature");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT16_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeColorTemperature(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeColorTemperature(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                          mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int16uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint16_t mChange;
};

/*
 * Attribute ColorMode
 */
class ReadColorControlColorMode : public ModelCommand
{
public:
    ReadColorControlColorMode() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-mode");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorMode(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorControlOptions
 */
class ReadColorControlColorControlOptions : public ModelCommand
{
public:
    ReadColorControlColorControlOptions() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-control-options");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorControlOptions(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorControlOptions : public ModelCommand
{
public:
    WriteColorControlColorControlOptions() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-control-options");
        AddArgument("attr-value", 0, UINT8_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorControlOptions(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mValue;
};

/*
 * Attribute NumberOfPrimaries
 */
class ReadColorControlNumberOfPrimaries : public ModelCommand
{
public:
    ReadColorControlNumberOfPrimaries() : ModelCommand("read")
    {
        AddArgument("attr-name", "number-of-primaries");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeNumberOfPrimaries(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary1X
 */
class ReadColorControlPrimary1X : public ModelCommand
{
public:
    ReadColorControlPrimary1X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary1x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary1X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary1Y
 */
class ReadColorControlPrimary1Y : public ModelCommand
{
public:
    ReadColorControlPrimary1Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary1y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary1Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary1Intensity
 */
class ReadColorControlPrimary1Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary1Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary1intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary1Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary2X
 */
class ReadColorControlPrimary2X : public ModelCommand
{
public:
    ReadColorControlPrimary2X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary2x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary2X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary2Y
 */
class ReadColorControlPrimary2Y : public ModelCommand
{
public:
    ReadColorControlPrimary2Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary2y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary2Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary2Intensity
 */
class ReadColorControlPrimary2Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary2Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary2intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary2Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary3X
 */
class ReadColorControlPrimary3X : public ModelCommand
{
public:
    ReadColorControlPrimary3X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary3x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary3X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary3Y
 */
class ReadColorControlPrimary3Y : public ModelCommand
{
public:
    ReadColorControlPrimary3Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary3y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary3Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary3Intensity
 */
class ReadColorControlPrimary3Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary3Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary3intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary3Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary4X
 */
class ReadColorControlPrimary4X : public ModelCommand
{
public:
    ReadColorControlPrimary4X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary4x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary4X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary4Y
 */
class ReadColorControlPrimary4Y : public ModelCommand
{
public:
    ReadColorControlPrimary4Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary4y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary4Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary4Intensity
 */
class ReadColorControlPrimary4Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary4Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary4intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary4Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary5X
 */
class ReadColorControlPrimary5X : public ModelCommand
{
public:
    ReadColorControlPrimary5X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary5x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary5X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary5Y
 */
class ReadColorControlPrimary5Y : public ModelCommand
{
public:
    ReadColorControlPrimary5Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary5y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary5Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary5Intensity
 */
class ReadColorControlPrimary5Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary5Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary5intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary5Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary6X
 */
class ReadColorControlPrimary6X : public ModelCommand
{
public:
    ReadColorControlPrimary6X() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary6x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary6X(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary6Y
 */
class ReadColorControlPrimary6Y : public ModelCommand
{
public:
    ReadColorControlPrimary6Y() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary6y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary6Y(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute Primary6Intensity
 */
class ReadColorControlPrimary6Intensity : public ModelCommand
{
public:
    ReadColorControlPrimary6Intensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "primary6intensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributePrimary6Intensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute WhitePointX
 */
class ReadColorControlWhitePointX : public ModelCommand
{
public:
    ReadColorControlWhitePointX() : ModelCommand("read")
    {
        AddArgument("attr-name", "white-point-x");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeWhitePointX(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlWhitePointX : public ModelCommand
{
public:
    WriteColorControlWhitePointX() : ModelCommand("write")
    {
        AddArgument("attr-name", "white-point-x");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeWhitePointX(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute WhitePointY
 */
class ReadColorControlWhitePointY : public ModelCommand
{
public:
    ReadColorControlWhitePointY() : ModelCommand("read")
    {
        AddArgument("attr-name", "white-point-y");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeWhitePointY(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlWhitePointY : public ModelCommand
{
public:
    WriteColorControlWhitePointY() : ModelCommand("write")
    {
        AddArgument("attr-name", "white-point-y");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeWhitePointY(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointRX
 */
class ReadColorControlColorPointRX : public ModelCommand
{
public:
    ReadColorControlColorPointRX() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-rx");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointRX(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointRX : public ModelCommand
{
public:
    WriteColorControlColorPointRX() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-rx");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointRX(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointRY
 */
class ReadColorControlColorPointRY : public ModelCommand
{
public:
    ReadColorControlColorPointRY() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-ry");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointRY(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointRY : public ModelCommand
{
public:
    WriteColorControlColorPointRY() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-ry");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointRY(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointRIntensity
 */
class ReadColorControlColorPointRIntensity : public ModelCommand
{
public:
    ReadColorControlColorPointRIntensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-rintensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointRIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointRIntensity : public ModelCommand
{
public:
    WriteColorControlColorPointRIntensity() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-rintensity");
        AddArgument("attr-value", 0, UINT8_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointRIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mValue;
};

/*
 * Attribute ColorPointGX
 */
class ReadColorControlColorPointGX : public ModelCommand
{
public:
    ReadColorControlColorPointGX() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-gx");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointGX(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointGX : public ModelCommand
{
public:
    WriteColorControlColorPointGX() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-gx");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointGX(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointGY
 */
class ReadColorControlColorPointGY : public ModelCommand
{
public:
    ReadColorControlColorPointGY() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-gy");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointGY(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointGY : public ModelCommand
{
public:
    WriteColorControlColorPointGY() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-gy");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointGY(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointGIntensity
 */
class ReadColorControlColorPointGIntensity : public ModelCommand
{
public:
    ReadColorControlColorPointGIntensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-gintensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointGIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointGIntensity : public ModelCommand
{
public:
    WriteColorControlColorPointGIntensity() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-gintensity");
        AddArgument("attr-value", 0, UINT8_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointGIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mValue;
};

/*
 * Attribute ColorPointBX
 */
class ReadColorControlColorPointBX : public ModelCommand
{
public:
    ReadColorControlColorPointBX() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-bx");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointBX(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointBX : public ModelCommand
{
public:
    WriteColorControlColorPointBX() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-bx");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointBX(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointBY
 */
class ReadColorControlColorPointBY : public ModelCommand
{
public:
    ReadColorControlColorPointBY() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-by");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointBY(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointBY : public ModelCommand
{
public:
    WriteColorControlColorPointBY() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-by");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointBY(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ColorPointBIntensity
 */
class ReadColorControlColorPointBIntensity : public ModelCommand
{
public:
    ReadColorControlColorPointBIntensity() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-point-bintensity");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorPointBIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlColorPointBIntensity : public ModelCommand
{
public:
    WriteColorControlColorPointBIntensity() : ModelCommand("write")
    {
        AddArgument("attr-name", "color-point-bintensity");
        AddArgument("attr-value", 0, UINT8_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeColorPointBIntensity(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mValue;
};

/*
 * Attribute EnhancedCurrentHue
 */
class ReadColorControlEnhancedCurrentHue : public ModelCommand
{
public:
    ReadColorControlEnhancedCurrentHue() : ModelCommand("read")
    {
        AddArgument("attr-name", "enhanced-current-hue");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeEnhancedCurrentHue(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute EnhancedColorMode
 */
class ReadColorControlEnhancedColorMode : public ModelCommand
{
public:
    ReadColorControlEnhancedColorMode() : ModelCommand("read")
    {
        AddArgument("attr-name", "enhanced-color-mode");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeEnhancedColorMode(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorLoopActive
 */
class ReadColorControlColorLoopActive : public ModelCommand
{
public:
    ReadColorControlColorLoopActive() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-loop-active");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorLoopActive(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorLoopDirection
 */
class ReadColorControlColorLoopDirection : public ModelCommand
{
public:
    ReadColorControlColorLoopDirection() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-loop-direction");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorLoopDirection(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorLoopTime
 */
class ReadColorControlColorLoopTime : public ModelCommand
{
public:
    ReadColorControlColorLoopTime() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-loop-time");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorLoopTime(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorCapabilities
 */
class ReadColorControlColorCapabilities : public ModelCommand
{
public:
    ReadColorControlColorCapabilities() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-capabilities");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorCapabilities(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorTempPhysicalMin
 */
class ReadColorControlColorTempPhysicalMin : public ModelCommand
{
public:
    ReadColorControlColorTempPhysicalMin() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-temp-physical-min");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorTempPhysicalMin(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ColorTempPhysicalMax
 */
class ReadColorControlColorTempPhysicalMax : public ModelCommand
{
public:
    ReadColorControlColorTempPhysicalMax() : ModelCommand("read")
    {
        AddArgument("attr-name", "color-temp-physical-max");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeColorTempPhysicalMax(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CoupleColorTempToLevelMinMireds
 */
class ReadColorControlCoupleColorTempToLevelMinMireds : public ModelCommand
{
public:
    ReadColorControlCoupleColorTempToLevelMinMireds() : ModelCommand("read")
    {
        AddArgument("attr-name", "couple-color-temp-to-level-min-mireds");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCoupleColorTempToLevelMinMireds(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute StartUpColorTemperatureMireds
 */
class ReadColorControlStartUpColorTemperatureMireds : public ModelCommand
{
public:
    ReadColorControlStartUpColorTemperatureMireds() : ModelCommand("read")
    {
        AddArgument("attr-name", "start-up-color-temperature-mireds");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeStartUpColorTemperatureMireds(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteColorControlStartUpColorTemperatureMireds : public ModelCommand
{
public:
    WriteColorControlStartUpColorTemperatureMireds() : ModelCommand("write")
    {
        AddArgument("attr-name", "start-up-color-temperature-mireds");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeStartUpColorTemperatureMireds(onSuccessCallback->Cancel(), onFailureCallback->Cancel(),
                                                                   mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ClusterRevision
 */
class ReadColorControlClusterRevision : public ModelCommand
{
public:
    ReadColorControlClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0300) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ColorControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster DoorLock                                                    | 0x0101 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * ClearAllPins                                                      |   0x08 |
| * ClearAllRfids                                                     |   0x19 |
| * ClearHolidaySchedule                                              |   0x13 |
| * ClearPin                                                          |   0x07 |
| * ClearRfid                                                         |   0x18 |
| * ClearWeekdaySchedule                                              |   0x0D |
| * ClearYeardaySchedule                                              |   0x10 |
| * GetHolidaySchedule                                                |   0x12 |
| * GetLogRecord                                                      |   0x04 |
| * GetPin                                                            |   0x06 |
| * GetRfid                                                           |   0x17 |
| * GetUserType                                                       |   0x15 |
| * GetWeekdaySchedule                                                |   0x0C |
| * GetYeardaySchedule                                                |   0x0F |
| * LockDoor                                                          |   0x00 |
| * SetHolidaySchedule                                                |   0x11 |
| * SetPin                                                            |   0x05 |
| * SetRfid                                                           |   0x16 |
| * SetUserType                                                       |   0x14 |
| * SetWeekdaySchedule                                                |   0x0B |
| * SetYeardaySchedule                                                |   0x0E |
| * UnlockDoor                                                        |   0x01 |
| * UnlockWithTimeout                                                 |   0x03 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * LockState                                                         | 0x0000 |
| * LockType                                                          | 0x0001 |
| * ActuatorEnabled                                                   | 0x0002 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command ClearAllPins
 */
class DoorLockClearAllPins : public ModelCommand
{
public:
    DoorLockClearAllPins() : ModelCommand("clear-all-pins") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x08) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearAllPins(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DoorLockClusterClearAllPinsResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearAllPinsResponseCallback>(OnDoorLockClusterClearAllPinsResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command ClearAllRfids
 */
class DoorLockClearAllRfids : public ModelCommand
{
public:
    DoorLockClearAllRfids() : ModelCommand("clear-all-rfids") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x19) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearAllRfids(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback>(OnDoorLockClusterClearAllRfidsResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command ClearHolidaySchedule
 */
class DoorLockClearHolidaySchedule : public ModelCommand
{
public:
    DoorLockClearHolidaySchedule() : ModelCommand("clear-holiday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x13) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearHolidaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId);
    }

private:
    chip::Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback>(
            OnDoorLockClusterClearHolidayScheduleResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
};

/*
 * Command ClearPin
 */
class DoorLockClearPin : public ModelCommand
{
public:
    DoorLockClearPin() : ModelCommand("clear-pin")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x07) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearPin(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterClearPinResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearPinResponseCallback>(OnDoorLockClusterClearPinResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
};

/*
 * Command ClearRfid
 */
class DoorLockClearRfid : public ModelCommand
{
public:
    DoorLockClearRfid() : ModelCommand("clear-rfid")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x18) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearRfid(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterClearRfidResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearRfidResponseCallback>(OnDoorLockClusterClearRfidResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
};

/*
 * Command ClearWeekdaySchedule
 */
class DoorLockClearWeekdaySchedule : public ModelCommand
{
public:
    DoorLockClearWeekdaySchedule() : ModelCommand("clear-weekday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x0D) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearWeekdaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback>(
            OnDoorLockClusterClearWeekdayScheduleResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
};

/*
 * Command ClearYeardaySchedule
 */
class DoorLockClearYeardaySchedule : public ModelCommand
{
public:
    DoorLockClearYeardaySchedule() : ModelCommand("clear-yearday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x10) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ClearYeardaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback>(
            OnDoorLockClusterClearYeardayScheduleResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
};

/*
 * Command GetHolidaySchedule
 */
class DoorLockGetHolidaySchedule : public ModelCommand
{
public:
    DoorLockGetHolidaySchedule() : ModelCommand("get-holiday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x12) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetHolidaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback>(OnDoorLockClusterGetHolidayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
};

/*
 * Command GetLogRecord
 */
class DoorLockGetLogRecord : public ModelCommand
{
public:
    DoorLockGetLogRecord() : ModelCommand("get-log-record")
    {
        AddArgument("logIndex", 0, UINT16_MAX, &mLogIndex);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x04) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetLogRecord(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mLogIndex);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetLogRecordResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetLogRecordResponseCallback>(OnDoorLockClusterGetLogRecordResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mLogIndex;
};

/*
 * Command GetPin
 */
class DoorLockGetPin : public ModelCommand
{
public:
    DoorLockGetPin() : ModelCommand("get-pin")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetPin(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetPinResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetPinResponseCallback>(OnDoorLockClusterGetPinResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
};

/*
 * Command GetRfid
 */
class DoorLockGetRfid : public ModelCommand
{
public:
    DoorLockGetRfid() : ModelCommand("get-rfid")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x17) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetRfid(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetRfidResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetRfidResponseCallback>(OnDoorLockClusterGetRfidResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
};

/*
 * Command GetUserType
 */
class DoorLockGetUserType : public ModelCommand
{
public:
    DoorLockGetUserType() : ModelCommand("get-user-type")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x15) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetUserType(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetUserTypeResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetUserTypeResponseCallback>(OnDoorLockClusterGetUserTypeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
};

/*
 * Command GetWeekdaySchedule
 */
class DoorLockGetWeekdaySchedule : public ModelCommand
{
public:
    DoorLockGetWeekdaySchedule() : ModelCommand("get-weekday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetWeekdaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback>(OnDoorLockClusterGetWeekdayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
};

/*
 * Command GetYeardaySchedule
 */
class DoorLockGetYeardaySchedule : public ModelCommand
{
public:
    DoorLockGetYeardaySchedule() : ModelCommand("get-yearday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x0F) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetYeardaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId);
    }

private:
    chip::Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback>(OnDoorLockClusterGetYeardayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
};

/*
 * Command LockDoor
 */
class DoorLockLockDoor : public ModelCommand
{
public:
    DoorLockLockDoor() : ModelCommand("lock-door")
    {
        AddArgument("pin", &mPin);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.LockDoor(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mPin);
    }

private:
    chip::Callback::Callback<DoorLockClusterLockDoorResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterLockDoorResponseCallback>(OnDoorLockClusterLockDoorResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    char * mPin;
};

/*
 * Command SetHolidaySchedule
 */
class DoorLockSetHolidaySchedule : public ModelCommand
{
public:
    DoorLockSetHolidaySchedule() : ModelCommand("set-holiday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("localStartTime", 0, UINT32_MAX, &mLocalStartTime);
        AddArgument("localEndTime", 0, UINT32_MAX, &mLocalEndTime);
        AddArgument("operatingModeDuringHoliday", 0, UINT8_MAX, &mOperatingModeDuringHoliday);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x11) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetHolidaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mLocalStartTime,
                                          mLocalEndTime, mOperatingModeDuringHoliday);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback>(OnDoorLockClusterSetHolidayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint32_t mLocalStartTime;
    uint32_t mLocalEndTime;
    uint8_t mOperatingModeDuringHoliday;
};

/*
 * Command SetPin
 */
class DoorLockSetPin : public ModelCommand
{
public:
    DoorLockSetPin() : ModelCommand("set-pin")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        AddArgument("userStatus", 0, UINT8_MAX, &mUserStatus);
        AddArgument("userType", 0, UINT8_MAX, &mUserType);
        AddArgument("pin", &mPin);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x05) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetPin(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId, mUserStatus, mUserType, mPin);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetPinResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetPinResponseCallback>(OnDoorLockClusterSetPinResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
    uint8_t mUserStatus;
    uint8_t mUserType;
    char * mPin;
};

/*
 * Command SetRfid
 */
class DoorLockSetRfid : public ModelCommand
{
public:
    DoorLockSetRfid() : ModelCommand("set-rfid")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        AddArgument("userStatus", 0, UINT8_MAX, &mUserStatus);
        AddArgument("userType", 0, UINT8_MAX, &mUserType);
        AddArgument("id", &mId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x16) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetRfid(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId, mUserStatus, mUserType, mId);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetRfidResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetRfidResponseCallback>(OnDoorLockClusterSetRfidResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
    uint8_t mUserStatus;
    uint8_t mUserType;
    char * mId;
};

/*
 * Command SetUserType
 */
class DoorLockSetUserType : public ModelCommand
{
public:
    DoorLockSetUserType() : ModelCommand("set-user-type")
    {
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        AddArgument("userType", 0, UINT8_MAX, &mUserType);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x14) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetUserType(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mUserId, mUserType);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetUserTypeResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetUserTypeResponseCallback>(OnDoorLockClusterSetUserTypeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mUserId;
    uint8_t mUserType;
};

/*
 * Command SetWeekdaySchedule
 */
class DoorLockSetWeekdaySchedule : public ModelCommand
{
public:
    DoorLockSetWeekdaySchedule() : ModelCommand("set-weekday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        AddArgument("daysMask", 0, UINT8_MAX, &mDaysMask);
        AddArgument("startHour", 0, UINT8_MAX, &mStartHour);
        AddArgument("startMinute", 0, UINT8_MAX, &mStartMinute);
        AddArgument("endHour", 0, UINT8_MAX, &mEndHour);
        AddArgument("endMinute", 0, UINT8_MAX, &mEndMinute);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x0B) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetWeekdaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId, mDaysMask,
                                          mStartHour, mStartMinute, mEndHour, mEndMinute);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback>(OnDoorLockClusterSetWeekdayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
    uint8_t mDaysMask;
    uint8_t mStartHour;
    uint8_t mStartMinute;
    uint8_t mEndHour;
    uint8_t mEndMinute;
};

/*
 * Command SetYeardaySchedule
 */
class DoorLockSetYeardaySchedule : public ModelCommand
{
public:
    DoorLockSetYeardaySchedule() : ModelCommand("set-yearday-schedule")
    {
        AddArgument("scheduleId", 0, UINT8_MAX, &mScheduleId);
        AddArgument("userId", 0, UINT16_MAX, &mUserId);
        AddArgument("localStartTime", 0, UINT32_MAX, &mLocalStartTime);
        AddArgument("localEndTime", 0, UINT32_MAX, &mLocalEndTime);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x0E) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.SetYeardaySchedule(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mScheduleId, mUserId,
                                          mLocalStartTime, mLocalEndTime);
    }

private:
    chip::Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback>(OnDoorLockClusterSetYeardayScheduleResponse,
                                                                                        this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mScheduleId;
    uint16_t mUserId;
    uint32_t mLocalStartTime;
    uint32_t mLocalEndTime;
};

/*
 * Command UnlockDoor
 */
class DoorLockUnlockDoor : public ModelCommand
{
public:
    DoorLockUnlockDoor() : ModelCommand("unlock-door")
    {
        AddArgument("pin", &mPin);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.UnlockDoor(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mPin);
    }

private:
    chip::Callback::Callback<DoorLockClusterUnlockDoorResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterUnlockDoorResponseCallback>(OnDoorLockClusterUnlockDoorResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    char * mPin;
};

/*
 * Command UnlockWithTimeout
 */
class DoorLockUnlockWithTimeout : public ModelCommand
{
public:
    DoorLockUnlockWithTimeout() : ModelCommand("unlock-with-timeout")
    {
        AddArgument("timeoutInSeconds", 0, UINT16_MAX, &mTimeoutInSeconds);
        AddArgument("pin", &mPin);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x03) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.UnlockWithTimeout(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mTimeoutInSeconds, mPin);
    }

private:
    chip::Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback>(OnDoorLockClusterUnlockWithTimeoutResponse,
                                                                                       this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mTimeoutInSeconds;
    char * mPin;
};

/*
 * Discover Attributes
 */
class DiscoverDoorLockAttributes : public ModelCommand
{
public:
    DiscoverDoorLockAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute LockState
 */
class ReadDoorLockLockState : public ModelCommand
{
public:
    ReadDoorLockLockState() : ModelCommand("read")
    {
        AddArgument("attr-name", "lock-state");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeLockState(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportDoorLockLockState : public ModelCommand
{
public:
    ReportDoorLockLockState() : ModelCommand("report")
    {
        AddArgument("attr-name", "lock-state");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeLockState(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeLockState(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                   mMaxInterval);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int8uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
};

/*
 * Attribute LockType
 */
class ReadDoorLockLockType : public ModelCommand
{
public:
    ReadDoorLockLockType() : ModelCommand("read")
    {
        AddArgument("attr-name", "lock-type");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeLockType(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ActuatorEnabled
 */
class ReadDoorLockActuatorEnabled : public ModelCommand
{
public:
    ReadDoorLockActuatorEnabled() : ModelCommand("read")
    {
        AddArgument("attr-name", "actuator-enabled");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeActuatorEnabled(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<BooleanAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<BooleanAttributeCallback>(OnBooleanAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadDoorLockClusterRevision : public ModelCommand
{
public:
    ReadDoorLockClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0101) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::DoorLockCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster Groups                                                      | 0x0004 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * AddGroup                                                          |   0x00 |
| * AddGroupIfIdentifying                                             |   0x05 |
| * GetGroupMembership                                                |   0x02 |
| * RemoveAllGroups                                                   |   0x04 |
| * RemoveGroup                                                       |   0x03 |
| * ViewGroup                                                         |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * NameSupport                                                       | 0x0000 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command AddGroup
 */
class GroupsAddGroup : public ModelCommand
{
public:
    GroupsAddGroup() : ModelCommand("add-group")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("groupName", &mGroupName);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.AddGroup(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mGroupName);
    }

private:
    chip::Callback::Callback<GroupsClusterAddGroupResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<GroupsClusterAddGroupResponseCallback>(OnGroupsClusterAddGroupResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    char * mGroupName;
};

/*
 * Command AddGroupIfIdentifying
 */
class GroupsAddGroupIfIdentifying : public ModelCommand
{
public:
    GroupsAddGroupIfIdentifying() : ModelCommand("add-group-if-identifying")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("groupName", &mGroupName);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x05) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.AddGroupIfIdentifying(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mGroupName);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    char * mGroupName;
};

/*
 * Command GetGroupMembership
 */
class GroupsGetGroupMembership : public ModelCommand
{
public:
    GroupsGetGroupMembership() : ModelCommand("get-group-membership")
    {
        AddArgument("groupCount", 0, UINT8_MAX, &mGroupCount);
        AddArgument("groupList", 0, UINT16_MAX, &mGroupList);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x02) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetGroupMembership(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupCount, mGroupList);
    }

private:
    chip::Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback>(OnGroupsClusterGetGroupMembershipResponse,
                                                                                      this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mGroupCount;
    uint16_t mGroupList;
};

/*
 * Command RemoveAllGroups
 */
class GroupsRemoveAllGroups : public ModelCommand
{
public:
    GroupsRemoveAllGroups() : ModelCommand("remove-all-groups") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x04) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.RemoveAllGroups(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command RemoveGroup
 */
class GroupsRemoveGroup : public ModelCommand
{
public:
    GroupsRemoveGroup() : ModelCommand("remove-group")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x03) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.RemoveGroup(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId);
    }

private:
    chip::Callback::Callback<GroupsClusterRemoveGroupResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<GroupsClusterRemoveGroupResponseCallback>(OnGroupsClusterRemoveGroupResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
};

/*
 * Command ViewGroup
 */
class GroupsViewGroup : public ModelCommand
{
public:
    GroupsViewGroup() : ModelCommand("view-group")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ViewGroup(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId);
    }

private:
    chip::Callback::Callback<GroupsClusterViewGroupResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<GroupsClusterViewGroupResponseCallback>(OnGroupsClusterViewGroupResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
};

/*
 * Discover Attributes
 */
class DiscoverGroupsAttributes : public ModelCommand
{
public:
    DiscoverGroupsAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute NameSupport
 */
class ReadGroupsNameSupport : public ModelCommand
{
public:
    ReadGroupsNameSupport() : ModelCommand("read")
    {
        AddArgument("attr-name", "name-support");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeNameSupport(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadGroupsClusterRevision : public ModelCommand
{
public:
    ReadGroupsClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0004) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::GroupsCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster Identify                                                    | 0x0003 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * Identify                                                          |   0x00 |
| * IdentifyQuery                                                     |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * IdentifyTime                                                      | 0x0000 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command Identify
 */
class IdentifyIdentify : public ModelCommand
{
public:
    IdentifyIdentify() : ModelCommand("identify")
    {
        AddArgument("identifyTime", 0, UINT16_MAX, &mIdentifyTime);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0003) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Identify(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mIdentifyTime);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mIdentifyTime;
};

/*
 * Command IdentifyQuery
 */
class IdentifyIdentifyQuery : public ModelCommand
{
public:
    IdentifyIdentifyQuery() : ModelCommand("identify-query") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0003) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.IdentifyQuery(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback>(OnIdentifyClusterIdentifyQueryResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Discover Attributes
 */
class DiscoverIdentifyAttributes : public ModelCommand
{
public:
    DiscoverIdentifyAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute IdentifyTime
 */
class ReadIdentifyIdentifyTime : public ModelCommand
{
public:
    ReadIdentifyIdentifyTime() : ModelCommand("read")
    {
        AddArgument("attr-name", "identify-time");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0003) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeIdentifyTime(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class WriteIdentifyIdentifyTime : public ModelCommand
{
public:
    WriteIdentifyIdentifyTime() : ModelCommand("write")
    {
        AddArgument("attr-name", "identify-time");
        AddArgument("attr-value", 0, UINT16_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0003) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.WriteAttributeIdentifyTime(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mValue);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mValue;
};

/*
 * Attribute ClusterRevision
 */
class ReadIdentifyClusterRevision : public ModelCommand
{
public:
    ReadIdentifyClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0003) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::IdentifyCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster LevelControl                                                | 0x0008 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * Move                                                              |   0x01 |
| * MoveToLevel                                                       |   0x00 |
| * MoveToLevelWithOnOff                                              |   0x04 |
| * MoveWithOnOff                                                     |   0x05 |
| * Step                                                              |   0x02 |
| * StepWithOnOff                                                     |   0x06 |
| * Stop                                                              |   0x03 |
| * StopWithOnOff                                                     |   0x07 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * CurrentLevel                                                      | 0x0000 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command Move
 */
class LevelControlMove : public ModelCommand
{
public:
    LevelControlMove() : ModelCommand("move")
    {
        AddArgument("moveMode", 0, UINT8_MAX, &mMoveMode);
        AddArgument("rate", 0, UINT8_MAX, &mRate);
        AddArgument("optionMask", 0, UINT8_MAX, &mOptionMask);
        AddArgument("optionOverride", 0, UINT8_MAX, &mOptionOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Move(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMoveMode, mRate, mOptionMask,
                            mOptionOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mMoveMode;
    uint8_t mRate;
    uint8_t mOptionMask;
    uint8_t mOptionOverride;
};

/*
 * Command MoveToLevel
 */
class LevelControlMoveToLevel : public ModelCommand
{
public:
    LevelControlMoveToLevel() : ModelCommand("move-to-level")
    {
        AddArgument("level", 0, UINT8_MAX, &mLevel);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionMask", 0, UINT8_MAX, &mOptionMask);
        AddArgument("optionOverride", 0, UINT8_MAX, &mOptionOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToLevel(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mLevel, mTransitionTime, mOptionMask,
                                   mOptionOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mLevel;
    uint16_t mTransitionTime;
    uint8_t mOptionMask;
    uint8_t mOptionOverride;
};

/*
 * Command MoveToLevelWithOnOff
 */
class LevelControlMoveToLevelWithOnOff : public ModelCommand
{
public:
    LevelControlMoveToLevelWithOnOff() : ModelCommand("move-to-level-with-on-off")
    {
        AddArgument("level", 0, UINT8_MAX, &mLevel);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x04) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveToLevelWithOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mLevel, mTransitionTime);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mLevel;
    uint16_t mTransitionTime;
};

/*
 * Command MoveWithOnOff
 */
class LevelControlMoveWithOnOff : public ModelCommand
{
public:
    LevelControlMoveWithOnOff() : ModelCommand("move-with-on-off")
    {
        AddArgument("moveMode", 0, UINT8_MAX, &mMoveMode);
        AddArgument("rate", 0, UINT8_MAX, &mRate);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x05) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.MoveWithOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMoveMode, mRate);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mMoveMode;
    uint8_t mRate;
};

/*
 * Command Step
 */
class LevelControlStep : public ModelCommand
{
public:
    LevelControlStep() : ModelCommand("step")
    {
        AddArgument("stepMode", 0, UINT8_MAX, &mStepMode);
        AddArgument("stepSize", 0, UINT8_MAX, &mStepSize);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("optionMask", 0, UINT8_MAX, &mOptionMask);
        AddArgument("optionOverride", 0, UINT8_MAX, &mOptionOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x02) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Step(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepMode, mStepSize, mTransitionTime,
                            mOptionMask, mOptionOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mStepMode;
    uint8_t mStepSize;
    uint16_t mTransitionTime;
    uint8_t mOptionMask;
    uint8_t mOptionOverride;
};

/*
 * Command StepWithOnOff
 */
class LevelControlStepWithOnOff : public ModelCommand
{
public:
    LevelControlStepWithOnOff() : ModelCommand("step-with-on-off")
    {
        AddArgument("stepMode", 0, UINT8_MAX, &mStepMode);
        AddArgument("stepSize", 0, UINT8_MAX, &mStepSize);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StepWithOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mStepMode, mStepSize,
                                     mTransitionTime);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mStepMode;
    uint8_t mStepSize;
    uint16_t mTransitionTime;
};

/*
 * Command Stop
 */
class LevelControlStop : public ModelCommand
{
public:
    LevelControlStop() : ModelCommand("stop")
    {
        AddArgument("optionMask", 0, UINT8_MAX, &mOptionMask);
        AddArgument("optionOverride", 0, UINT8_MAX, &mOptionOverride);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x03) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Stop(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mOptionMask, mOptionOverride);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint8_t mOptionMask;
    uint8_t mOptionOverride;
};

/*
 * Command StopWithOnOff
 */
class LevelControlStopWithOnOff : public ModelCommand
{
public:
    LevelControlStopWithOnOff() : ModelCommand("stop-with-on-off") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x07) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StopWithOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Discover Attributes
 */
class DiscoverLevelControlAttributes : public ModelCommand
{
public:
    DiscoverLevelControlAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CurrentLevel
 */
class ReadLevelControlCurrentLevel : public ModelCommand
{
public:
    ReadLevelControlCurrentLevel() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-level");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentLevel(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportLevelControlCurrentLevel : public ModelCommand
{
public:
    ReportLevelControlCurrentLevel() : ModelCommand("report")
    {
        AddArgument("attr-name", "current-level");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", 0, UINT8_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeCurrentLevel(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeCurrentLevel(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                      mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int8uAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    uint8_t mChange;
};

/*
 * Attribute ClusterRevision
 */
class ReadLevelControlClusterRevision : public ModelCommand
{
public:
    ReadLevelControlClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0008) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::LevelControlCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster OnOff                                                       | 0x0006 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * Off                                                               |   0x00 |
| * On                                                                |   0x01 |
| * Toggle                                                            |   0x02 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * OnOff                                                             | 0x0000 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command Off
 */
class OnOffOff : public ModelCommand
{
public:
    OnOffOff() : ModelCommand("off") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Off(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command On
 */
class OnOffOn : public ModelCommand
{
public:
    OnOffOn() : ModelCommand("on") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.On(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Command Toggle
 */
class OnOffToggle : public ModelCommand
{
public:
    OnOffToggle() : ModelCommand("toggle") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x02) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.Toggle(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Discover Attributes
 */
class DiscoverOnOffAttributes : public ModelCommand
{
public:
    DiscoverOnOffAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute OnOff
 */
class ReadOnOffOnOff : public ModelCommand
{
public:
    ReadOnOffOnOff() : ModelCommand("read")
    {
        AddArgument("attr-name", "on-off");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<BooleanAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<BooleanAttributeCallback>(OnBooleanAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportOnOffOnOff : public ModelCommand
{
public:
    ReportOnOffOnOff() : ModelCommand("report")
    {
        AddArgument("attr-name", "on-off");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeOnOff(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeOnOff(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                               mMaxInterval);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<BooleanAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<BooleanAttributeCallback>(OnBooleanAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
};

/*
 * Attribute ClusterRevision
 */
class ReadOnOffClusterRevision : public ModelCommand
{
public:
    ReadOnOffClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0006) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::OnOffCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster Scenes                                                      | 0x0005 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * AddScene                                                          |   0x00 |
| * GetSceneMembership                                                |   0x06 |
| * RecallScene                                                       |   0x05 |
| * RemoveAllScenes                                                   |   0x03 |
| * RemoveScene                                                       |   0x02 |
| * StoreScene                                                        |   0x04 |
| * ViewScene                                                         |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * SceneCount                                                        | 0x0000 |
| * CurrentScene                                                      | 0x0001 |
| * CurrentGroup                                                      | 0x0002 |
| * SceneValid                                                        | 0x0003 |
| * NameSupport                                                       | 0x0004 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Command AddScene
 */
class ScenesAddScene : public ModelCommand
{
public:
    ScenesAddScene() : ModelCommand("add-scene")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("sceneId", 0, UINT8_MAX, &mSceneId);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        AddArgument("sceneName", &mSceneName);
        AddArgument("clusterId", 0, UINT16_MAX, &mClusterId);
        AddArgument("length", 0, UINT8_MAX, &mLength);
        AddArgument("value", 0, UINT8_MAX, &mValue);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.AddScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mSceneId, mTransitionTime,
                                mSceneName, mClusterId, mLength, mValue);
    }

private:
    chip::Callback::Callback<ScenesClusterAddSceneResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterAddSceneResponseCallback>(OnScenesClusterAddSceneResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    uint8_t mSceneId;
    uint16_t mTransitionTime;
    char * mSceneName;
    chip::ClusterId mClusterId;
    uint8_t mLength;
    uint8_t mValue;
};

/*
 * Command GetSceneMembership
 */
class ScenesGetSceneMembership : public ModelCommand
{
public:
    ScenesGetSceneMembership() : ModelCommand("get-scene-membership")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.GetSceneMembership(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId);
    }

private:
    chip::Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback>(OnScenesClusterGetSceneMembershipResponse,
                                                                                      this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
};

/*
 * Command RecallScene
 */
class ScenesRecallScene : public ModelCommand
{
public:
    ScenesRecallScene() : ModelCommand("recall-scene")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("sceneId", 0, UINT8_MAX, &mSceneId);
        AddArgument("transitionTime", 0, UINT16_MAX, &mTransitionTime);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x05) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.RecallScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mSceneId, mTransitionTime);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    uint8_t mSceneId;
    uint16_t mTransitionTime;
};

/*
 * Command RemoveAllScenes
 */
class ScenesRemoveAllScenes : public ModelCommand
{
public:
    ScenesRemoveAllScenes() : ModelCommand("remove-all-scenes")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x03) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.RemoveAllScenes(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId);
    }

private:
    chip::Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback>(OnScenesClusterRemoveAllScenesResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
};

/*
 * Command RemoveScene
 */
class ScenesRemoveScene : public ModelCommand
{
public:
    ScenesRemoveScene() : ModelCommand("remove-scene")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("sceneId", 0, UINT8_MAX, &mSceneId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x02) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.RemoveScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mSceneId);
    }

private:
    chip::Callback::Callback<ScenesClusterRemoveSceneResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterRemoveSceneResponseCallback>(OnScenesClusterRemoveSceneResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    uint8_t mSceneId;
};

/*
 * Command StoreScene
 */
class ScenesStoreScene : public ModelCommand
{
public:
    ScenesStoreScene() : ModelCommand("store-scene")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("sceneId", 0, UINT8_MAX, &mSceneId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x04) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.StoreScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mSceneId);
    }

private:
    chip::Callback::Callback<ScenesClusterStoreSceneResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterStoreSceneResponseCallback>(OnScenesClusterStoreSceneResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    uint8_t mSceneId;
};

/*
 * Command ViewScene
 */
class ScenesViewScene : public ModelCommand
{
public:
    ScenesViewScene() : ModelCommand("view-scene")
    {
        AddArgument("groupId", 0, UINT16_MAX, &mGroupId);
        AddArgument("sceneId", 0, UINT8_MAX, &mSceneId);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x01) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ViewScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mGroupId, mSceneId);
    }

private:
    chip::Callback::Callback<ScenesClusterViewSceneResponseCallback> * onSuccessCallback =
        new chip::Callback::Callback<ScenesClusterViewSceneResponseCallback>(OnScenesClusterViewSceneResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    uint16_t mGroupId;
    uint8_t mSceneId;
};

/*
 * Discover Attributes
 */
class DiscoverScenesAttributes : public ModelCommand
{
public:
    DiscoverScenesAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute SceneCount
 */
class ReadScenesSceneCount : public ModelCommand
{
public:
    ReadScenesSceneCount() : ModelCommand("read")
    {
        AddArgument("attr-name", "scene-count");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeSceneCount(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CurrentScene
 */
class ReadScenesCurrentScene : public ModelCommand
{
public:
    ReadScenesCurrentScene() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-scene");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentScene(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute CurrentGroup
 */
class ReadScenesCurrentGroup : public ModelCommand
{
public:
    ReadScenesCurrentGroup() : ModelCommand("read")
    {
        AddArgument("attr-name", "current-group");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeCurrentGroup(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute SceneValid
 */
class ReadScenesSceneValid : public ModelCommand
{
public:
    ReadScenesSceneValid() : ModelCommand("read")
    {
        AddArgument("attr-name", "scene-valid");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeSceneValid(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<BooleanAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<BooleanAttributeCallback>(OnBooleanAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute NameSupport
 */
class ReadScenesNameSupport : public ModelCommand
{
public:
    ReadScenesNameSupport() : ModelCommand("read")
    {
        AddArgument("attr-name", "name-support");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeNameSupport(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int8uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int8uAttributeCallback>(OnInt8uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadScenesClusterRevision : public ModelCommand
{
public:
    ReadScenesClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0005) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::ScenesCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Cluster TemperatureMeasurement                                      | 0x0402 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * MeasuredValue                                                     | 0x0000 |
| * MinMeasuredValue                                                  | 0x0001 |
| * MaxMeasuredValue                                                  | 0x0002 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

/*
 * Discover Attributes
 */
class DiscoverTemperatureMeasurementAttributes : public ModelCommand
{
public:
    DiscoverTemperatureMeasurementAttributes() : ModelCommand("discover") { ModelCommand::AddArguments(); }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0000) command (0x0C) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.DiscoverAttributes(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute MeasuredValue
 */
class ReadTemperatureMeasurementMeasuredValue : public ModelCommand
{
public:
    ReadTemperatureMeasurementMeasuredValue() : ModelCommand("read")
    {
        AddArgument("attr-name", "measured-value");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0402) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeMeasuredValue(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16sAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16sAttributeCallback>(OnInt16sAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

class ReportTemperatureMeasurementMeasuredValue : public ModelCommand
{
public:
    ReportTemperatureMeasurementMeasuredValue() : ModelCommand("report")
    {
        AddArgument("attr-name", "measured-value");
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("change", INT16_MIN, INT16_MAX, &mChange);
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0402) command (0x06) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);

        CHIP_ERROR err = cluster.ReportAttributeMeasuredValue(onReportCallback->Cancel());
        if (err != CHIP_NO_ERROR)
        {
            return err;
        }

        return cluster.ConfigureAttributeMeasuredValue(onSuccessCallback->Cancel(), onFailureCallback->Cancel(), mMinInterval,
                                                       mMaxInterval, mChange);
    }

private:
    chip::Callback::Callback<DefaultSuccessCallback> * onSuccessCallback =
        new chip::Callback::Callback<DefaultSuccessCallback>(OnDefaultSuccessResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
    chip::Callback::Callback<Int16sAttributeCallback> * onReportCallback =
        new chip::Callback::Callback<Int16sAttributeCallback>(OnInt16sAttributeResponse, this);
    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    int16_t mChange;
};

/*
 * Attribute MinMeasuredValue
 */
class ReadTemperatureMeasurementMinMeasuredValue : public ModelCommand
{
public:
    ReadTemperatureMeasurementMinMeasuredValue() : ModelCommand("read")
    {
        AddArgument("attr-name", "min-measured-value");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0402) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeMinMeasuredValue(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16sAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16sAttributeCallback>(OnInt16sAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute MaxMeasuredValue
 */
class ReadTemperatureMeasurementMaxMeasuredValue : public ModelCommand
{
public:
    ReadTemperatureMeasurementMaxMeasuredValue() : ModelCommand("read")
    {
        AddArgument("attr-name", "max-measured-value");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0402) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeMaxMeasuredValue(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16sAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16sAttributeCallback>(OnInt16sAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*
 * Attribute ClusterRevision
 */
class ReadTemperatureMeasurementClusterRevision : public ModelCommand
{
public:
    ReadTemperatureMeasurementClusterRevision() : ModelCommand("read")
    {
        AddArgument("attr-name", "cluster-revision");
        ModelCommand::AddArguments();
    }

    CHIP_ERROR SendCommand(ChipDevice * device, uint8_t endpointId) override
    {
        ChipLogProgress(chipTool, "Sending cluster (0x0402) command (0x00) on endpoint %" PRIu16, endpointId);

        chip::Controller::TemperatureMeasurementCluster cluster;
        cluster.Associate(device, endpointId);
        return cluster.ReadAttributeClusterRevision(onSuccessCallback->Cancel(), onFailureCallback->Cancel());
    }

private:
    chip::Callback::Callback<Int16uAttributeCallback> * onSuccessCallback =
        new chip::Callback::Callback<Int16uAttributeCallback>(OnInt16uAttributeResponse, this);
    chip::Callback::Callback<DefaultFailureCallback> * onFailureCallback =
        new chip::Callback::Callback<DefaultFailureCallback>(OnDefaultFailureResponse, this);
};

/*----------------------------------------------------------------------------*\
| Register all Clusters commands                                               |
\*----------------------------------------------------------------------------*/
void registerClusterBarrierControl(Commands & commands)
{
    const char * clusterName = "BarrierControl";

    commands_list clusterCommands = {
        make_unique<BarrierControlBarrierControlGoToPercent>(), make_unique<BarrierControlBarrierControlStop>(),
        make_unique<DiscoverBarrierControlAttributes>(),        make_unique<ReadBarrierControlBarrierMovingState>(),
        make_unique<ReadBarrierControlBarrierSafetyStatus>(),   make_unique<ReadBarrierControlBarrierCapabilities>(),
        make_unique<ReadBarrierControlBarrierPosition>(),       make_unique<ReadBarrierControlClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterBasic(Commands & commands)
{
    const char * clusterName = "Basic";

    commands_list clusterCommands = {
        make_unique<BasicMfgSpecificPing>(), make_unique<BasicResetToFactoryDefaults>(), make_unique<DiscoverBasicAttributes>(),
        make_unique<ReadBasicZclVersion>(),  make_unique<ReadBasicPowerSource>(),        make_unique<ReadBasicClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterBinding(Commands & commands)
{
    const char * clusterName = "Binding";

    commands_list clusterCommands = {
        make_unique<BindingBind>(),
        make_unique<BindingUnbind>(),
        make_unique<DiscoverBindingAttributes>(),
        make_unique<ReadBindingClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterColorControl(Commands & commands)
{
    const char * clusterName = "ColorControl";

    commands_list clusterCommands = {
        make_unique<ColorControlMoveColor>(),
        make_unique<ColorControlMoveColorTemperature>(),
        make_unique<ColorControlMoveHue>(),
        make_unique<ColorControlMoveSaturation>(),
        make_unique<ColorControlMoveToColor>(),
        make_unique<ColorControlMoveToColorTemperature>(),
        make_unique<ColorControlMoveToHue>(),
        make_unique<ColorControlMoveToHueAndSaturation>(),
        make_unique<ColorControlMoveToSaturation>(),
        make_unique<ColorControlStepColor>(),
        make_unique<ColorControlStepColorTemperature>(),
        make_unique<ColorControlStepHue>(),
        make_unique<ColorControlStepSaturation>(),
        make_unique<ColorControlStopMoveStep>(),
        make_unique<DiscoverColorControlAttributes>(),
        make_unique<ReadColorControlCurrentHue>(),
        make_unique<ReportColorControlCurrentHue>(),
        make_unique<ReadColorControlCurrentSaturation>(),
        make_unique<ReportColorControlCurrentSaturation>(),
        make_unique<ReadColorControlRemainingTime>(),
        make_unique<ReadColorControlCurrentX>(),
        make_unique<ReportColorControlCurrentX>(),
        make_unique<ReadColorControlCurrentY>(),
        make_unique<ReportColorControlCurrentY>(),
        make_unique<ReadColorControlDriftCompensation>(),
        make_unique<ReadColorControlCompensationText>(),
        make_unique<ReadColorControlColorTemperature>(),
        make_unique<ReportColorControlColorTemperature>(),
        make_unique<ReadColorControlColorMode>(),
        make_unique<ReadColorControlColorControlOptions>(),
        make_unique<WriteColorControlColorControlOptions>(),
        make_unique<ReadColorControlNumberOfPrimaries>(),
        make_unique<ReadColorControlPrimary1X>(),
        make_unique<ReadColorControlPrimary1Y>(),
        make_unique<ReadColorControlPrimary1Intensity>(),
        make_unique<ReadColorControlPrimary2X>(),
        make_unique<ReadColorControlPrimary2Y>(),
        make_unique<ReadColorControlPrimary2Intensity>(),
        make_unique<ReadColorControlPrimary3X>(),
        make_unique<ReadColorControlPrimary3Y>(),
        make_unique<ReadColorControlPrimary3Intensity>(),
        make_unique<ReadColorControlPrimary4X>(),
        make_unique<ReadColorControlPrimary4Y>(),
        make_unique<ReadColorControlPrimary4Intensity>(),
        make_unique<ReadColorControlPrimary5X>(),
        make_unique<ReadColorControlPrimary5Y>(),
        make_unique<ReadColorControlPrimary5Intensity>(),
        make_unique<ReadColorControlPrimary6X>(),
        make_unique<ReadColorControlPrimary6Y>(),
        make_unique<ReadColorControlPrimary6Intensity>(),
        make_unique<ReadColorControlWhitePointX>(),
        make_unique<WriteColorControlWhitePointX>(),
        make_unique<ReadColorControlWhitePointY>(),
        make_unique<WriteColorControlWhitePointY>(),
        make_unique<ReadColorControlColorPointRX>(),
        make_unique<WriteColorControlColorPointRX>(),
        make_unique<ReadColorControlColorPointRY>(),
        make_unique<WriteColorControlColorPointRY>(),
        make_unique<ReadColorControlColorPointRIntensity>(),
        make_unique<WriteColorControlColorPointRIntensity>(),
        make_unique<ReadColorControlColorPointGX>(),
        make_unique<WriteColorControlColorPointGX>(),
        make_unique<ReadColorControlColorPointGY>(),
        make_unique<WriteColorControlColorPointGY>(),
        make_unique<ReadColorControlColorPointGIntensity>(),
        make_unique<WriteColorControlColorPointGIntensity>(),
        make_unique<ReadColorControlColorPointBX>(),
        make_unique<WriteColorControlColorPointBX>(),
        make_unique<ReadColorControlColorPointBY>(),
        make_unique<WriteColorControlColorPointBY>(),
        make_unique<ReadColorControlColorPointBIntensity>(),
        make_unique<WriteColorControlColorPointBIntensity>(),
        make_unique<ReadColorControlEnhancedCurrentHue>(),
        make_unique<ReadColorControlEnhancedColorMode>(),
        make_unique<ReadColorControlColorLoopActive>(),
        make_unique<ReadColorControlColorLoopDirection>(),
        make_unique<ReadColorControlColorLoopTime>(),
        make_unique<ReadColorControlColorCapabilities>(),
        make_unique<ReadColorControlColorTempPhysicalMin>(),
        make_unique<ReadColorControlColorTempPhysicalMax>(),
        make_unique<ReadColorControlCoupleColorTempToLevelMinMireds>(),
        make_unique<ReadColorControlStartUpColorTemperatureMireds>(),
        make_unique<WriteColorControlStartUpColorTemperatureMireds>(),
        make_unique<ReadColorControlClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterDoorLock(Commands & commands)
{
    const char * clusterName = "DoorLock";

    commands_list clusterCommands = {
        make_unique<DoorLockClearAllPins>(),
        make_unique<DoorLockClearAllRfids>(),
        make_unique<DoorLockClearHolidaySchedule>(),
        make_unique<DoorLockClearPin>(),
        make_unique<DoorLockClearRfid>(),
        make_unique<DoorLockClearWeekdaySchedule>(),
        make_unique<DoorLockClearYeardaySchedule>(),
        make_unique<DoorLockGetHolidaySchedule>(),
        make_unique<DoorLockGetLogRecord>(),
        make_unique<DoorLockGetPin>(),
        make_unique<DoorLockGetRfid>(),
        make_unique<DoorLockGetUserType>(),
        make_unique<DoorLockGetWeekdaySchedule>(),
        make_unique<DoorLockGetYeardaySchedule>(),
        make_unique<DoorLockLockDoor>(),
        make_unique<DoorLockSetHolidaySchedule>(),
        make_unique<DoorLockSetPin>(),
        make_unique<DoorLockSetRfid>(),
        make_unique<DoorLockSetUserType>(),
        make_unique<DoorLockSetWeekdaySchedule>(),
        make_unique<DoorLockSetYeardaySchedule>(),
        make_unique<DoorLockUnlockDoor>(),
        make_unique<DoorLockUnlockWithTimeout>(),
        make_unique<DiscoverDoorLockAttributes>(),
        make_unique<ReadDoorLockLockState>(),
        make_unique<ReportDoorLockLockState>(),
        make_unique<ReadDoorLockLockType>(),
        make_unique<ReadDoorLockActuatorEnabled>(),
        make_unique<ReadDoorLockClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterGroups(Commands & commands)
{
    const char * clusterName = "Groups";

    commands_list clusterCommands = {
        make_unique<GroupsAddGroup>(),
        make_unique<GroupsAddGroupIfIdentifying>(),
        make_unique<GroupsGetGroupMembership>(),
        make_unique<GroupsRemoveAllGroups>(),
        make_unique<GroupsRemoveGroup>(),
        make_unique<GroupsViewGroup>(),
        make_unique<DiscoverGroupsAttributes>(),
        make_unique<ReadGroupsNameSupport>(),
        make_unique<ReadGroupsClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterIdentify(Commands & commands)
{
    const char * clusterName = "Identify";

    commands_list clusterCommands = {
        make_unique<IdentifyIdentify>(),           make_unique<IdentifyIdentifyQuery>(),
        make_unique<DiscoverIdentifyAttributes>(), make_unique<ReadIdentifyIdentifyTime>(),
        make_unique<WriteIdentifyIdentifyTime>(),  make_unique<ReadIdentifyClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterLevelControl(Commands & commands)
{
    const char * clusterName = "LevelControl";

    commands_list clusterCommands = {
        make_unique<LevelControlMove>(),
        make_unique<LevelControlMoveToLevel>(),
        make_unique<LevelControlMoveToLevelWithOnOff>(),
        make_unique<LevelControlMoveWithOnOff>(),
        make_unique<LevelControlStep>(),
        make_unique<LevelControlStepWithOnOff>(),
        make_unique<LevelControlStop>(),
        make_unique<LevelControlStopWithOnOff>(),
        make_unique<DiscoverLevelControlAttributes>(),
        make_unique<ReadLevelControlCurrentLevel>(),
        make_unique<ReportLevelControlCurrentLevel>(),
        make_unique<ReadLevelControlClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterOnOff(Commands & commands)
{
    const char * clusterName = "OnOff";

    commands_list clusterCommands = {
        make_unique<OnOffOff>(),
        make_unique<OnOffOn>(),
        make_unique<OnOffToggle>(),
        make_unique<DiscoverOnOffAttributes>(),
        make_unique<ReadOnOffOnOff>(),
        make_unique<ReportOnOffOnOff>(),
        make_unique<ReadOnOffClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterScenes(Commands & commands)
{
    const char * clusterName = "Scenes";

    commands_list clusterCommands = {
        make_unique<ScenesAddScene>(),         make_unique<ScenesGetSceneMembership>(),  make_unique<ScenesRecallScene>(),
        make_unique<ScenesRemoveAllScenes>(),  make_unique<ScenesRemoveScene>(),         make_unique<ScenesStoreScene>(),
        make_unique<ScenesViewScene>(),        make_unique<DiscoverScenesAttributes>(),  make_unique<ReadScenesSceneCount>(),
        make_unique<ReadScenesCurrentScene>(), make_unique<ReadScenesCurrentGroup>(),    make_unique<ReadScenesSceneValid>(),
        make_unique<ReadScenesNameSupport>(),  make_unique<ReadScenesClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}
void registerClusterTemperatureMeasurement(Commands & commands)
{
    const char * clusterName = "TemperatureMeasurement";

    commands_list clusterCommands = {
        make_unique<DiscoverTemperatureMeasurementAttributes>(),   make_unique<ReadTemperatureMeasurementMeasuredValue>(),
        make_unique<ReportTemperatureMeasurementMeasuredValue>(),  make_unique<ReadTemperatureMeasurementMinMeasuredValue>(),
        make_unique<ReadTemperatureMeasurementMaxMeasuredValue>(), make_unique<ReadTemperatureMeasurementClusterRevision>(),
    };

    commands.Register(clusterName, clusterCommands);
}

void registerClusters(Commands & commands)
{
    registerClusterBarrierControl(commands);
    registerClusterBasic(commands);
    registerClusterBinding(commands);
    registerClusterColorControl(commands);
    registerClusterDoorLock(commands);
    registerClusterGroups(commands);
    registerClusterIdentify(commands);
    registerClusterLevelControl(commands);
    registerClusterOnOff(commands);
    registerClusterScenes(commands);
    registerClusterTemperatureMeasurement(commands);
}
