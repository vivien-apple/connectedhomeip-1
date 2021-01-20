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
#include <controller/CHIPClusters.h>

/*----------------------------------------------------------------------------*\
| Cluster Name                                                        |   ID   |
|---------------------------------------------------------------------+--------|
| BarrierControl                                                      | 0x0103 |
| Basic                                                               | 0x0000 |
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
        return cluster.BarrierControlGoToPercent(nullptr, mPercentOpen);
    }

private:
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
        return cluster.BarrierControlStop(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeBarrierMovingState(nullptr);
    }
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
        return cluster.ReadAttributeBarrierSafetyStatus(nullptr);
    }
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
        return cluster.ReadAttributeBarrierCapabilities(nullptr);
    }
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
        return cluster.ReadAttributeBarrierPosition(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.MfgSpecificPing(nullptr);
    }
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
        return cluster.ResetToFactoryDefaults(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeZclVersion(nullptr);
    }
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
        return cluster.ReadAttributePowerSource(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.MoveColor(nullptr, mRateX, mRateY, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveColorTemperature(nullptr, mMoveMode, mRate, mColorTemperatureMinimum, mColorTemperatureMaximum,
                                            mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveHue(nullptr, mMoveMode, mRate, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveSaturation(nullptr, mMoveMode, mRate, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveToColor(nullptr, mColorX, mColorY, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveToColorTemperature(nullptr, mColorTemperature, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveToHue(nullptr, mHue, mDirection, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveToHueAndSaturation(nullptr, mHue, mSaturation, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.MoveToSaturation(nullptr, mSaturation, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.StepColor(nullptr, mStepX, mStepY, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.StepColorTemperature(nullptr, mStepMode, mStepSize, mTransitionTime, mColorTemperatureMinimum,
                                            mColorTemperatureMaximum, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.StepHue(nullptr, mStepMode, mStepSize, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.StepSaturation(nullptr, mStepMode, mStepSize, mTransitionTime, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.StopMoveStep(nullptr, mOptionsMask, mOptionsOverride);
    }

private:
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeCurrentHue(nullptr);
    }
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
        return cluster.ReportAttributeCurrentHue(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeCurrentSaturation(nullptr);
    }
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
        return cluster.ReportAttributeCurrentSaturation(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeRemainingTime(nullptr);
    }
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
        return cluster.ReadAttributeCurrentX(nullptr);
    }
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
        return cluster.ReportAttributeCurrentX(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeCurrentY(nullptr);
    }
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
        return cluster.ReportAttributeCurrentY(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeDriftCompensation(nullptr);
    }
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
        return cluster.ReadAttributeCompensationText(nullptr);
    }
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
        return cluster.ReadAttributeColorTemperature(nullptr);
    }
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
        return cluster.ReportAttributeColorTemperature(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeColorMode(nullptr);
    }
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
        return cluster.ReadAttributeColorControlOptions(nullptr);
    }
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
        return cluster.WriteAttributeColorControlOptions(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeNumberOfPrimaries(nullptr);
    }
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
        return cluster.ReadAttributePrimary1X(nullptr);
    }
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
        return cluster.ReadAttributePrimary1Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary1Intensity(nullptr);
    }
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
        return cluster.ReadAttributePrimary2X(nullptr);
    }
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
        return cluster.ReadAttributePrimary2Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary2Intensity(nullptr);
    }
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
        return cluster.ReadAttributePrimary3X(nullptr);
    }
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
        return cluster.ReadAttributePrimary3Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary3Intensity(nullptr);
    }
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
        return cluster.ReadAttributePrimary4X(nullptr);
    }
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
        return cluster.ReadAttributePrimary4Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary4Intensity(nullptr);
    }
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
        return cluster.ReadAttributePrimary5X(nullptr);
    }
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
        return cluster.ReadAttributePrimary5Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary5Intensity(nullptr);
    }
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
        return cluster.ReadAttributePrimary6X(nullptr);
    }
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
        return cluster.ReadAttributePrimary6Y(nullptr);
    }
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
        return cluster.ReadAttributePrimary6Intensity(nullptr);
    }
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
        return cluster.ReadAttributeWhitePointX(nullptr);
    }
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
        return cluster.WriteAttributeWhitePointX(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeWhitePointY(nullptr);
    }
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
        return cluster.WriteAttributeWhitePointY(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointRX(nullptr);
    }
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
        return cluster.WriteAttributeColorPointRX(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointRY(nullptr);
    }
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
        return cluster.WriteAttributeColorPointRY(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointRIntensity(nullptr);
    }
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
        return cluster.WriteAttributeColorPointRIntensity(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointGX(nullptr);
    }
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
        return cluster.WriteAttributeColorPointGX(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointGY(nullptr);
    }
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
        return cluster.WriteAttributeColorPointGY(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointGIntensity(nullptr);
    }
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
        return cluster.WriteAttributeColorPointGIntensity(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointBX(nullptr);
    }
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
        return cluster.WriteAttributeColorPointBX(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointBY(nullptr);
    }
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
        return cluster.WriteAttributeColorPointBY(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeColorPointBIntensity(nullptr);
    }
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
        return cluster.WriteAttributeColorPointBIntensity(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeEnhancedCurrentHue(nullptr);
    }
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
        return cluster.ReadAttributeEnhancedColorMode(nullptr);
    }
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
        return cluster.ReadAttributeColorLoopActive(nullptr);
    }
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
        return cluster.ReadAttributeColorLoopDirection(nullptr);
    }
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
        return cluster.ReadAttributeColorLoopTime(nullptr);
    }
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
        return cluster.ReadAttributeColorCapabilities(nullptr);
    }
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
        return cluster.ReadAttributeColorTempPhysicalMin(nullptr);
    }
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
        return cluster.ReadAttributeColorTempPhysicalMax(nullptr);
    }
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
        return cluster.ReadAttributeCoupleColorTempToLevelMinMireds(nullptr);
    }
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
        return cluster.ReadAttributeStartUpColorTemperatureMireds(nullptr);
    }
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
        return cluster.WriteAttributeStartUpColorTemperatureMireds(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.ClearAllPins(nullptr);
    }
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
        return cluster.ClearAllRfids(nullptr);
    }
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
        return cluster.ClearHolidaySchedule(nullptr, mScheduleId);
    }

private:
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
        return cluster.ClearPin(nullptr, mUserId);
    }

private:
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
        return cluster.ClearRfid(nullptr, mUserId);
    }

private:
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
        return cluster.ClearWeekdaySchedule(nullptr, mScheduleId, mUserId);
    }

private:
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
        return cluster.ClearYeardaySchedule(nullptr, mScheduleId, mUserId);
    }

private:
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
        return cluster.GetHolidaySchedule(nullptr, mScheduleId);
    }

private:
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
        return cluster.GetLogRecord(nullptr, mLogIndex);
    }

private:
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
        return cluster.GetPin(nullptr, mUserId);
    }

private:
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
        return cluster.GetRfid(nullptr, mUserId);
    }

private:
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
        return cluster.GetUserType(nullptr, mUserId);
    }

private:
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
        return cluster.GetWeekdaySchedule(nullptr, mScheduleId, mUserId);
    }

private:
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
        return cluster.GetYeardaySchedule(nullptr, mScheduleId, mUserId);
    }

private:
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
        return cluster.LockDoor(nullptr, mPin);
    }

private:
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
        return cluster.SetHolidaySchedule(nullptr, mScheduleId, mLocalStartTime, mLocalEndTime, mOperatingModeDuringHoliday);
    }

private:
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
        return cluster.SetPin(nullptr, mUserId, mUserStatus, mUserType, mPin);
    }

private:
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
        return cluster.SetRfid(nullptr, mUserId, mUserStatus, mUserType, mId);
    }

private:
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
        return cluster.SetUserType(nullptr, mUserId, mUserType);
    }

private:
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
        return cluster.SetWeekdaySchedule(nullptr, mScheduleId, mUserId, mDaysMask, mStartHour, mStartMinute, mEndHour, mEndMinute);
    }

private:
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
        return cluster.SetYeardaySchedule(nullptr, mScheduleId, mUserId, mLocalStartTime, mLocalEndTime);
    }

private:
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
        return cluster.UnlockDoor(nullptr, mPin);
    }

private:
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
        return cluster.UnlockWithTimeout(nullptr, mTimeoutInSeconds, mPin);
    }

private:
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeLockState(nullptr);
    }
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
        return cluster.ReportAttributeLockState(nullptr, nullptr, mMinInterval, mMaxInterval);
    }

private:
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
        return cluster.ReadAttributeLockType(nullptr);
    }
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
        return cluster.ReadAttributeActuatorEnabled(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.AddGroup(nullptr, mGroupId, mGroupName);
    }

private:
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
        return cluster.AddGroupIfIdentifying(nullptr, mGroupId, mGroupName);
    }

private:
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
        return cluster.GetGroupMembership(nullptr, mGroupCount, mGroupList);
    }

private:
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
        return cluster.RemoveAllGroups(nullptr);
    }
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
        return cluster.RemoveGroup(nullptr, mGroupId);
    }

private:
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
        return cluster.ViewGroup(nullptr, mGroupId);
    }

private:
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeNameSupport(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.Identify(nullptr, mIdentifyTime);
    }

private:
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
        return cluster.IdentifyQuery(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeIdentifyTime(nullptr);
    }
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
        return cluster.WriteAttributeIdentifyTime(nullptr, mValue);
    }

private:
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.Move(nullptr, mMoveMode, mRate, mOptionMask, mOptionOverride);
    }

private:
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
        return cluster.MoveToLevel(nullptr, mLevel, mTransitionTime, mOptionMask, mOptionOverride);
    }

private:
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
        return cluster.MoveToLevelWithOnOff(nullptr, mLevel, mTransitionTime);
    }

private:
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
        return cluster.MoveWithOnOff(nullptr, mMoveMode, mRate);
    }

private:
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
        return cluster.Step(nullptr, mStepMode, mStepSize, mTransitionTime, mOptionMask, mOptionOverride);
    }

private:
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
        return cluster.StepWithOnOff(nullptr, mStepMode, mStepSize, mTransitionTime);
    }

private:
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
        return cluster.Stop(nullptr, mOptionMask, mOptionOverride);
    }

private:
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
        return cluster.StopWithOnOff(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeCurrentLevel(nullptr);
    }
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
        return cluster.ReportAttributeCurrentLevel(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.Off(nullptr);
    }
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
        return cluster.On(nullptr);
    }
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
        return cluster.Toggle(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeOnOff(nullptr);
    }
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
        return cluster.ReportAttributeOnOff(nullptr, nullptr, mMinInterval, mMaxInterval);
    }

private:
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.AddScene(nullptr, mGroupId, mSceneId, mTransitionTime, mSceneName, mClusterId, mLength, mValue);
    }

private:
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
        return cluster.GetSceneMembership(nullptr, mGroupId);
    }

private:
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
        return cluster.RecallScene(nullptr, mGroupId, mSceneId, mTransitionTime);
    }

private:
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
        return cluster.RemoveAllScenes(nullptr, mGroupId);
    }

private:
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
        return cluster.RemoveScene(nullptr, mGroupId, mSceneId);
    }

private:
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
        return cluster.StoreScene(nullptr, mGroupId, mSceneId);
    }

private:
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
        return cluster.ViewScene(nullptr, mGroupId, mSceneId);
    }

private:
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeSceneCount(nullptr);
    }
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
        return cluster.ReadAttributeCurrentScene(nullptr);
    }
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
        return cluster.ReadAttributeCurrentGroup(nullptr);
    }
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
        return cluster.ReadAttributeSceneValid(nullptr);
    }
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
        return cluster.ReadAttributeNameSupport(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
        return cluster.DiscoverAttributes(nullptr);
    }
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
        return cluster.ReadAttributeMeasuredValue(nullptr);
    }
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
        return cluster.ReportAttributeMeasuredValue(nullptr, nullptr, mMinInterval, mMaxInterval, mChange);
    }

private:
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
        return cluster.ReadAttributeMinMeasuredValue(nullptr);
    }
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
        return cluster.ReadAttributeMaxMeasuredValue(nullptr);
    }
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
        return cluster.ReadAttributeClusterRevision(nullptr);
    }
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
    registerClusterColorControl(commands);
    registerClusterDoorLock(commands);
    registerClusterGroups(commands);
    registerClusterIdentify(commands);
    registerClusterLevelControl(commands);
    registerClusterOnOff(commands);
    registerClusterScenes(commands);
    registerClusterTemperatureMeasurement(commands);
}
