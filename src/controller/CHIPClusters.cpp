
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
#include "CHIPClusters.h"

#include <app/chip-zcl-zpro-codec-api.h>

namespace chip {
namespace Controller {

// TODO: Find a way to calculate maximum message length for clusters
//       https://github.com/project-chip/connectedhomeip/issues/965
constexpr uint16_t kMaxMessageLength = 1024;

/*----------------------------------------------------------------------------*\
| Cluster Name                                                        |   ID   |
|---------------------------------------------------------------------+--------|
| BarrierControl                                                      | 0x0103 |
| Basic                                                               | 0x0000 |
| ColorControl                                                        | 0x0300 |
| DoorLock                                                            | 0x0101 |
| Groups                                                              | 0x0004 |
| IasZone                                                             | 0x0500 |
| Identify                                                            | 0x0003 |
| LevelControl                                                        | 0x0008 |
| OnOff                                                               | 0x0006 |
| Scenes                                                              | 0x0005 |
| TemperatureMeasurement                                              | 0x0402 |
\*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
| Cluster BarrierControl                                              | 0x0103 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// BarrierControl Cluster Commands
CHIP_ERROR BarrierControlCluster::BarrierControlGoToPercent(Callback::Callback<> * onCompletion, uint8_t percentOpen)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeBarrierControlClusterBarrierControlGoToPercentCommand(buffer->Start(), kMaxMessageLength, mEndpoint, percentOpen);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BarrierControlCluster::BarrierControlStop(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterBarrierControlStopCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// BarrierControl Cluster Attributes
CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierMovingState(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterReadBarrierMovingStateAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierSafetyStatus(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterReadBarrierSafetyStatusAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierCapabilities(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterReadBarrierCapabilitiesAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierPosition(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterReadBarrierPositionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BarrierControlCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBarrierControlClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster Basic                                                       | 0x0000 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * ResetToFactoryDefaults                                            |   0x00 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * ZclVersion                                                        | 0x0000 |
| * PowerSource                                                       | 0x0007 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

// Basic Cluster Commands
CHIP_ERROR BasicCluster::ResetToFactoryDefaults(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBasicClusterResetToFactoryDefaultsCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// Basic Cluster Attributes
CHIP_ERROR BasicCluster::ReadAttributeZclVersion(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBasicClusterReadZclVersionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BasicCluster::ReadAttributePowerSource(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBasicClusterReadPowerSourceAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR BasicCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeBasicClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster ColorControl                                                | 0x0300 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// ColorControl Cluster Commands
CHIP_ERROR ColorControlCluster::MoveColor(Callback::Callback<> * onCompletion, int16_t rateX, int16_t rateY, uint8_t optionsMask,
                                          uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveColorCommand(buffer->Start(), kMaxMessageLength, mEndpoint, rateX, rateY,
                                                              optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveColorTemperature(Callback::Callback<> * onCompletion, uint8_t moveMode, uint16_t rate,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum,
                                                     uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveColorTemperatureCommand(buffer->Start(), kMaxMessageLength, mEndpoint, moveMode,
                                                                         rate, colorTemperatureMinimum, colorTemperatureMaximum,
                                                                         optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveHue(Callback::Callback<> * onCompletion, uint8_t moveMode, uint8_t rate, uint8_t optionsMask,
                                        uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveHueCommand(buffer->Start(), kMaxMessageLength, mEndpoint, moveMode, rate,
                                                            optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveSaturation(Callback::Callback<> * onCompletion, uint8_t moveMode, uint8_t rate,
                                               uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveSaturationCommand(buffer->Start(), kMaxMessageLength, mEndpoint, moveMode, rate,
                                                                   optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveToColor(Callback::Callback<> * onCompletion, uint16_t colorX, uint16_t colorY,
                                            uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveToColorCommand(buffer->Start(), kMaxMessageLength, mEndpoint, colorX, colorY,
                                                                transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveToColorTemperature(Callback::Callback<> * onCompletion, uint16_t colorTemperature,
                                                       uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveToColorTemperatureCommand(
        buffer->Start(), kMaxMessageLength, mEndpoint, colorTemperature, transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveToHue(Callback::Callback<> * onCompletion, uint8_t hue, uint8_t direction,
                                          uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveToHueCommand(buffer->Start(), kMaxMessageLength, mEndpoint, hue, direction,
                                                              transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveToHueAndSaturation(Callback::Callback<> * onCompletion, uint8_t hue, uint8_t saturation,
                                                       uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveToHueAndSaturationCommand(
        buffer->Start(), kMaxMessageLength, mEndpoint, hue, saturation, transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::MoveToSaturation(Callback::Callback<> * onCompletion, uint8_t saturation, uint16_t transitionTime,
                                                 uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterMoveToSaturationCommand(buffer->Start(), kMaxMessageLength, mEndpoint, saturation,
                                                                     transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::StepColor(Callback::Callback<> * onCompletion, int16_t stepX, int16_t stepY,
                                          uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterStepColorCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepX, stepY,
                                                              transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::StepColorTemperature(Callback::Callback<> * onCompletion, uint8_t stepMode, uint16_t stepSize,
                                                     uint16_t transitionTime, uint16_t colorTemperatureMinimum,
                                                     uint16_t colorTemperatureMaximum, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterStepColorTemperatureCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepMode,
                                                                         stepSize, transitionTime, colorTemperatureMinimum,
                                                                         colorTemperatureMaximum, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::StepHue(Callback::Callback<> * onCompletion, uint8_t stepMode, uint8_t stepSize,
                                        uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterStepHueCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepMode, stepSize,
                                                            transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::StepSaturation(Callback::Callback<> * onCompletion, uint8_t stepMode, uint8_t stepSize,
                                               uint8_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterStepSaturationCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepMode,
                                                                   stepSize, transitionTime, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::StopMoveStep(Callback::Callback<> * onCompletion, uint8_t optionsMask, uint8_t optionsOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterStopMoveStepCommand(buffer->Start(), kMaxMessageLength, mEndpoint, optionsMask, optionsOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// ColorControl Cluster Attributes
CHIP_ERROR ColorControlCluster::ReadAttributeCurrentHue(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadCurrentHueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentHue(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                          uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterReportCurrentHueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentSaturation(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadCurrentSaturationAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentSaturation(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                                 uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReportCurrentSaturationAttribute(buffer->Start(), kMaxMessageLength, mEndpoint,
                                                                              minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeRemainingTime(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadRemainingTimeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentX(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadCurrentXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentX(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                        uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterReportCurrentXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentY(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadCurrentYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentY(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                        uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterReportCurrentYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeDriftCompensation(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadDriftCompensationAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeCompensationText(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadCompensationTextAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTemperature(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorTemperatureAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReportAttributeColorTemperature(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                                uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReportColorTemperatureAttribute(buffer->Start(), kMaxMessageLength, mEndpoint,
                                                                             minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorMode(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorModeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorControlOptions(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorControlOptionsAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorControlOptions(Callback::Callback<> * onCompletion, uint8_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterWriteColorControlOptionsAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeNumberOfPrimaries(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadNumberOfPrimariesAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary1XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary1YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary1IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary2XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary2YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary2IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary3XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary3YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary3IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary4XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary4YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary4IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary5XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary5YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary5IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6X(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary6XAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6Y(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary6YAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6Intensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadPrimary6IntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeWhitePointX(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadWhitePointXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeWhitePointX(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteWhitePointXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeWhitePointY(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadWhitePointYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeWhitePointY(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteWhitePointYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRX(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointRXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRX(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointRXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRY(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointRYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRY(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointRYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRIntensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointRIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRIntensity(Callback::Callback<> * onCompletion, uint8_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterWriteColorPointRIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGX(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointGXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGX(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointGXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGY(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointGYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGY(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointGYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGIntensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointGIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGIntensity(Callback::Callback<> * onCompletion, uint8_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterWriteColorPointGIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBX(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointBXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBX(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointBXAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBY(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointBYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBY(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterWriteColorPointBYAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBIntensity(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorPointBIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBIntensity(Callback::Callback<> * onCompletion, uint8_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterWriteColorPointBIntensityAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeEnhancedCurrentHue(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadEnhancedCurrentHueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeEnhancedColorMode(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadEnhancedColorModeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopActive(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorLoopActiveAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopDirection(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorLoopDirectionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopTime(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorLoopTimeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorCapabilities(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorCapabilitiesAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTempPhysicalMin(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorTempPhysicalMinAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTempPhysicalMax(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadColorTempPhysicalMaxAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeCoupleColorTempToLevelMinMireds(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterReadCoupleColorTempToLevelMinMiredsAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeStartUpColorTemperatureMireds(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterReadStartUpColorTemperatureMiredsAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::WriteAttributeStartUpColorTemperatureMireds(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeColorControlClusterWriteStartUpColorTemperatureMiredsAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ColorControlCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeColorControlClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster DoorLock                                                    | 0x0101 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// DoorLock Cluster Commands
CHIP_ERROR DoorLockCluster::ClearAllPins(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterClearAllPinsCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearAllRfids(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterClearAllRfidsCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearHolidaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterClearHolidayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearPin(Callback::Callback<> * onCompletion, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterClearPinCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearRfid(Callback::Callback<> * onCompletion, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterClearRfidCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearWeekdaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterClearWeekdayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ClearYeardaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterClearYeardayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetHolidaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterGetHolidayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetLogRecord(Callback::Callback<> * onCompletion, uint16_t logIndex)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterGetLogRecordCommand(buffer->Start(), kMaxMessageLength, mEndpoint, logIndex);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetPin(Callback::Callback<> * onCompletion, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterGetPinCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetRfid(Callback::Callback<> * onCompletion, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterGetRfidCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetUserType(Callback::Callback<> * onCompletion, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterGetUserTypeCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetWeekdaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterGetWeekdayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::GetYeardaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterGetYeardayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId, userId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::LockDoor(Callback::Callback<> * onCompletion, char * pin)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterLockDoorCommand(buffer->Start(), kMaxMessageLength, mEndpoint, pin);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetHolidaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint32_t localStartTime,
                                               uint32_t localEndTime, uint8_t operatingModeDuringHoliday)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterSetHolidayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId,
                                                                   localStartTime, localEndTime, operatingModeDuringHoliday);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetPin(Callback::Callback<> * onCompletion, uint16_t userId, uint8_t userStatus, uint8_t userType,
                                   char * pin)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterSetPinCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId, userStatus, userType, pin);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetRfid(Callback::Callback<> * onCompletion, uint16_t userId, uint8_t userStatus, uint8_t userType,
                                    char * id)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterSetRfidCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId, userStatus, userType, id);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetUserType(Callback::Callback<> * onCompletion, uint16_t userId, uint8_t userType)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterSetUserTypeCommand(buffer->Start(), kMaxMessageLength, mEndpoint, userId, userType);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetWeekdaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId,
                                               uint8_t daysMask, uint8_t startHour, uint8_t startMinute, uint8_t endHour,
                                               uint8_t endMinute)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterSetWeekdayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId,
                                                                   userId, daysMask, startHour, startMinute, endHour, endMinute);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::SetYeardaySchedule(Callback::Callback<> * onCompletion, uint8_t scheduleId, uint16_t userId,
                                               uint32_t localStartTime, uint32_t localEndTime)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterSetYeardayScheduleCommand(buffer->Start(), kMaxMessageLength, mEndpoint, scheduleId,
                                                                   userId, localStartTime, localEndTime);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::UnlockDoor(Callback::Callback<> * onCompletion, char * pin)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterUnlockDoorCommand(buffer->Start(), kMaxMessageLength, mEndpoint, pin);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::UnlockWithTimeout(Callback::Callback<> * onCompletion, uint16_t timeoutInSeconds, char * pin)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterUnlockWithTimeoutCommand(buffer->Start(), kMaxMessageLength, mEndpoint, timeoutInSeconds, pin);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// DoorLock Cluster Attributes
CHIP_ERROR DoorLockCluster::ReadAttributeLockState(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterReadLockStateAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ReportAttributeLockState(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                     uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeDoorLockClusterReportLockStateAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ReadAttributeLockType(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterReadLockTypeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ReadAttributeActuatorEnabled(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterReadActuatorEnabledAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR DoorLockCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeDoorLockClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster Groups                                                      | 0x0004 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// Groups Cluster Commands
CHIP_ERROR GroupsCluster::AddGroup(Callback::Callback<> * onCompletion, uint16_t groupId, char * groupName)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterAddGroupCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, groupName);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::AddGroupIfIdentifying(Callback::Callback<> * onCompletion, uint16_t groupId, char * groupName)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeGroupsClusterAddGroupIfIdentifyingCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, groupName);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::GetGroupMembership(Callback::Callback<> * onCompletion, uint8_t groupCount, uint16_t groupList)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeGroupsClusterGetGroupMembershipCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupCount, groupList);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::RemoveAllGroups(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterRemoveAllGroupsCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::RemoveGroup(Callback::Callback<> * onCompletion, uint16_t groupId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterRemoveGroupCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::ViewGroup(Callback::Callback<> * onCompletion, uint16_t groupId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterViewGroupCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// Groups Cluster Attributes
CHIP_ERROR GroupsCluster::ReadAttributeNameSupport(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterReadNameSupportAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR GroupsCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeGroupsClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster IasZone                                                     | 0x0500 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
| * ZoneEnrollResponse                                                |   0x00 |
|                                                                     |        |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * ZoneState                                                         | 0x0000 |
| * ZoneType                                                          | 0x0001 |
| * ZoneStatus                                                        | 0x0002 |
| * IasCieAddress                                                     | 0x0010 |
| * ZoneId                                                            | 0x0011 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

// IasZone Cluster Commands
// IasZone Cluster Attributes
CHIP_ERROR IasZoneCluster::ReadAttributeZoneState(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadZoneStateAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneType(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadZoneTypeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneStatus(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadZoneStatusAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::ReadAttributeIasCieAddress(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadIasCieAddressAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::WriteAttributeIasCieAddress(Callback::Callback<> * onCompletion, uint64_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterWriteIasCieAddressAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneId(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadZoneIdAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IasZoneCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIasZoneClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster Identify                                                    | 0x0003 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
| * Identify                                                          |   0x00 |
| * IdentifyQuery                                                     |   0x01 |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * IdentifyTime                                                      | 0x0000 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

// Identify Cluster Commands
CHIP_ERROR IdentifyCluster::Identify(Callback::Callback<> * onCompletion, uint16_t identifyTime)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIdentifyClusterIdentifyCommand(buffer->Start(), kMaxMessageLength, mEndpoint, identifyTime);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IdentifyCluster::IdentifyQuery(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIdentifyClusterIdentifyQueryCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// Identify Cluster Attributes
CHIP_ERROR IdentifyCluster::ReadAttributeIdentifyTime(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIdentifyClusterReadIdentifyTimeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IdentifyCluster::WriteAttributeIdentifyTime(Callback::Callback<> * onCompletion, uint16_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIdentifyClusterWriteIdentifyTimeAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR IdentifyCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeIdentifyClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster LevelControl                                                | 0x0008 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// LevelControl Cluster Commands
CHIP_ERROR LevelControlCluster::Move(Callback::Callback<> * onCompletion, uint8_t moveMode, uint8_t rate, uint8_t optionMask,
                                     uint8_t optionOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterMoveCommand(buffer->Start(), kMaxMessageLength, mEndpoint, moveMode, rate, optionMask,
                                                         optionOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::MoveToLevel(Callback::Callback<> * onCompletion, uint8_t level, uint16_t transitionTime,
                                            uint8_t optionMask, uint8_t optionOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterMoveToLevelCommand(buffer->Start(), kMaxMessageLength, mEndpoint, level,
                                                                transitionTime, optionMask, optionOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::MoveToLevelWithOnOff(Callback::Callback<> * onCompletion, uint8_t level, uint16_t transitionTime)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeLevelControlClusterMoveToLevelWithOnOffCommand(buffer->Start(), kMaxMessageLength, mEndpoint, level, transitionTime);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::MoveWithOnOff(Callback::Callback<> * onCompletion, uint8_t moveMode, uint8_t rate)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterMoveWithOnOffCommand(buffer->Start(), kMaxMessageLength, mEndpoint, moveMode, rate);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::Step(Callback::Callback<> * onCompletion, uint8_t stepMode, uint8_t stepSize,
                                     uint16_t transitionTime, uint8_t optionMask, uint8_t optionOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterStepCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepMode, stepSize,
                                                         transitionTime, optionMask, optionOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::StepWithOnOff(Callback::Callback<> * onCompletion, uint8_t stepMode, uint8_t stepSize,
                                              uint16_t transitionTime)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterStepWithOnOffCommand(buffer->Start(), kMaxMessageLength, mEndpoint, stepMode, stepSize,
                                                                  transitionTime);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::Stop(Callback::Callback<> * onCompletion, uint8_t optionMask, uint8_t optionOverride)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterStopCommand(buffer->Start(), kMaxMessageLength, mEndpoint, optionMask, optionOverride);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::StopWithOnOff(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterStopWithOnOffCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// LevelControl Cluster Attributes
CHIP_ERROR LevelControlCluster::ReadAttributeCurrentLevel(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterReadCurrentLevelAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::ReportAttributeCurrentLevel(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                            uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterReportCurrentLevelAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval,
                                                                         maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR LevelControlCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeLevelControlClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster OnOff                                                       | 0x0006 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// OnOff Cluster Commands
CHIP_ERROR OnOffCluster::Off(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterOffCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR OnOffCluster::On(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterOnCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR OnOffCluster::Toggle(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterToggleCommand(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// OnOff Cluster Attributes
CHIP_ERROR OnOffCluster::ReadAttributeOnOff(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterReadOnOffAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR OnOffCluster::ReportAttributeOnOff(Callback::Callback<> * onCompletion, uint16_t minInterval, uint16_t maxInterval,
                                              Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterReportOnOffAttribute(buffer->Start(), kMaxMessageLength, mEndpoint, minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR OnOffCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeOnOffClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster Scenes                                                      | 0x0005 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
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

// Scenes Cluster Commands
CHIP_ERROR ScenesCluster::AddScene(Callback::Callback<> * onCompletion, uint16_t groupId, uint8_t sceneId, uint16_t transitionTime,
                                   char * sceneName, chip::ClusterId clusterId, uint8_t length, uint8_t value)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterAddSceneCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, sceneId,
                                                       transitionTime, sceneName, clusterId, length, value);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::GetSceneMembership(Callback::Callback<> * onCompletion, uint16_t groupId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterGetSceneMembershipCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::RecallScene(Callback::Callback<> * onCompletion, uint16_t groupId, uint8_t sceneId,
                                      uint16_t transitionTime)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength =
        encodeScenesClusterRecallSceneCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, sceneId, transitionTime);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::RemoveAllScenes(Callback::Callback<> * onCompletion, uint16_t groupId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterRemoveAllScenesCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::RemoveScene(Callback::Callback<> * onCompletion, uint16_t groupId, uint8_t sceneId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterRemoveSceneCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, sceneId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::StoreScene(Callback::Callback<> * onCompletion, uint16_t groupId, uint8_t sceneId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterStoreSceneCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, sceneId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ViewScene(Callback::Callback<> * onCompletion, uint16_t groupId, uint8_t sceneId)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterViewSceneCommand(buffer->Start(), kMaxMessageLength, mEndpoint, groupId, sceneId);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

// Scenes Cluster Attributes
CHIP_ERROR ScenesCluster::ReadAttributeSceneCount(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadSceneCountAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ReadAttributeCurrentScene(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadCurrentSceneAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ReadAttributeCurrentGroup(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadCurrentGroupAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ReadAttributeSceneValid(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadSceneValidAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ReadAttributeNameSupport(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadNameSupportAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR ScenesCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeScenesClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

/*----------------------------------------------------------------------------*\
| Cluster TemperatureMeasurement                                      | 0x0402 |
|------------------------------------------------------------------------------|
| Responses:                                                          |        |
|                                                                     |        |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * MeasuredValue                                                     | 0x0000 |
| * MinMeasuredValue                                                  | 0x0001 |
| * MaxMeasuredValue                                                  | 0x0002 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

// TemperatureMeasurement Cluster Commands
// TemperatureMeasurement Cluster Attributes
CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMeasuredValue(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeTemperatureMeasurementClusterReadMeasuredValueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Callback<> * onCompletion, uint16_t minInterval,
                                                                       uint16_t maxInterval, Callback::Callback<> * onChange)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeTemperatureMeasurementClusterReportMeasuredValueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint,
                                                                                    minInterval, maxInterval);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);
    SuccessOrExit(err);

    if (onChange != nullptr)
    {
        err = RequestAttributeReporting(onChange);
        SuccessOrExit(err);
    }

exit:
    return err;
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMinMeasuredValue(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeTemperatureMeasurementClusterReadMinMeasuredValueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMaxMeasuredValue(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeTemperatureMeasurementClusterReadMaxMeasuredValueAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeClusterRevision(Callback::Callback<> * onCompletion)
{
    CHIP_ERROR err         = CHIP_NO_ERROR;
    uint16_t payloadLength = 0;

    System::PacketBufferHandle buffer = System::PacketBuffer::NewWithAvailableSize(kMaxMessageLength);
    VerifyOrExit(!buffer.IsNull(), err = CHIP_ERROR_NO_MEMORY);

    payloadLength = encodeTemperatureMeasurementClusterReadClusterRevisionAttribute(buffer->Start(), kMaxMessageLength, mEndpoint);
    VerifyOrExit(payloadLength != 0, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
    VerifyOrExit(payloadLength <= kMaxMessageLength, err = CHIP_ERROR_INTERNAL);

    buffer->SetDataLength(payloadLength);
    VerifyOrExit(buffer->DataLength() >= payloadLength, err = CHIP_ERROR_NO_MEMORY);

    err = SendCommand(buffer, onCompletion);

exit:
    return err;
}

} // namespace Controller
} // namespace chip
