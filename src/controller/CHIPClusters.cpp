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

// BarrierControl Cluster Commands
CHIP_ERROR BarrierControlCluster::BarrierControlGoToPercent(Callback::Cancelable * onSuccessCallback,
                                                            Callback::Cancelable * onFailureCallback, uint8_t percentOpen)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterBarrierControlGoToPercentCommand(mEndpoint, percentOpen);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BarrierControlCluster::BarrierControlStop(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterBarrierControlStopCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// BarrierControl Cluster Attributes
CHIP_ERROR BarrierControlCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierMovingState(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterReadBarrierMovingStateAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierSafetyStatus(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterReadBarrierSafetyStatusAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierCapabilities(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterReadBarrierCapabilitiesAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BarrierControlCluster::ReadAttributeBarrierPosition(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterReadBarrierPositionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BarrierControlCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBarrierControlClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Basic Cluster Commands
CHIP_ERROR BasicCluster::MfgSpecificPing(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterMfgSpecificPingCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BasicCluster::ResetToFactoryDefaults(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterResetToFactoryDefaultsCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Basic Cluster Attributes
CHIP_ERROR BasicCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR BasicCluster::ReadAttributeZclVersion(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterReadZclVersionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BasicCluster::ReadAttributePowerSource(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterReadPowerSourceAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BasicCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBasicClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Binding Cluster Commands
CHIP_ERROR BindingCluster::Bind(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                chip::NodeId nodeId, chip::GroupId groupId, chip::EndpointId endpointId, chip::ClusterId clusterId)
{
    System::PacketBufferHandle payload = encodeBindingClusterBindCommand(mEndpoint, nodeId, groupId, endpointId, clusterId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR BindingCluster::Unbind(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                  chip::NodeId nodeId, chip::GroupId groupId, chip::EndpointId endpointId,
                                  chip::ClusterId clusterId)
{
    System::PacketBufferHandle payload = encodeBindingClusterUnbindCommand(mEndpoint, nodeId, groupId, endpointId, clusterId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Binding Cluster Attributes
CHIP_ERROR BindingCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBindingClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR BindingCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                        Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeBindingClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// ColorControl Cluster Commands
CHIP_ERROR ColorControlCluster::MoveColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          int16_t rateX, int16_t rateY, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveColorCommand(mEndpoint, rateX, rateY, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback, uint8_t moveMode, uint16_t rate,
                                                     uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum,
                                                     uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload = encodeColorControlClusterMoveColorTemperatureCommand(
        mEndpoint, moveMode, rate, colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                        uint8_t moveMode, uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveHueCommand(mEndpoint, moveMode, rate, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t moveMode, uint8_t rate, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveSaturationCommand(mEndpoint, moveMode, rate, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveToColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                            uint16_t colorX, uint16_t colorY, uint16_t transitionTime, uint8_t optionsMask,
                                            uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveToColorCommand(mEndpoint, colorX, colorY, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveToColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback, uint16_t colorTemperature,
                                                       uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload = encodeColorControlClusterMoveToColorTemperatureCommand(
        mEndpoint, colorTemperature, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveToHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint8_t hue, uint8_t direction, uint16_t transitionTime, uint8_t optionsMask,
                                          uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveToHueCommand(mEndpoint, hue, direction, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveToHueAndSaturation(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback, uint8_t hue, uint8_t saturation,
                                                       uint16_t transitionTime, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload = encodeColorControlClusterMoveToHueAndSaturationCommand(
        mEndpoint, hue, saturation, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::MoveToSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask,
                                                 uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterMoveToSaturationCommand(mEndpoint, saturation, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::StepColor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          int16_t stepX, int16_t stepY, uint16_t transitionTime, uint8_t optionsMask,
                                          uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterStepColorCommand(mEndpoint, stepX, stepY, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::StepColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback, uint8_t stepMode, uint16_t stepSize,
                                                     uint16_t transitionTime, uint16_t colorTemperatureMinimum,
                                                     uint16_t colorTemperatureMaximum, uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterStepColorTemperatureCommand(mEndpoint, stepMode, stepSize, transitionTime, colorTemperatureMinimum,
                                                             colorTemperatureMaximum, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::StepHue(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                        uint8_t stepMode, uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask,
                                        uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterStepHueCommand(mEndpoint, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::StepSaturation(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t stepMode, uint8_t stepSize, uint8_t transitionTime, uint8_t optionsMask,
                                               uint8_t optionsOverride)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterStepSaturationCommand(mEndpoint, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::StopMoveStep(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                             uint8_t optionsMask, uint8_t optionsOverride)
{
    System::PacketBufferHandle payload = encodeColorControlClusterStopMoveStepCommand(mEndpoint, optionsMask, optionsOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// ColorControl Cluster Attributes
CHIP_ERROR ColorControlCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR ColorControlCluster::ReadAttributeCurrentHue(Callback::Cancelable * onSuccessCallback,
                                                        Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCurrentHueAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentHue(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback,
                                                          Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                          uint16_t maxInterval, uint8_t change)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterReportCurrentHueAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0000, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentSaturation(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCurrentSaturationAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentSaturation(Callback::Cancelable * onSuccessCallback,
                                                                 Callback::Cancelable * onFailureCallback,
                                                                 Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                                 uint16_t maxInterval, uint8_t change)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterReportCurrentSaturationAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0001, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeRemainingTime(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadRemainingTimeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentX(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCurrentXAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentX(Callback::Cancelable * onSuccessCallback,
                                                        Callback::Cancelable * onFailureCallback,
                                                        Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                        uint16_t maxInterval, uint16_t change)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterReportCurrentXAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0003, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeCurrentY(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCurrentYAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReportAttributeCurrentY(Callback::Cancelable * onSuccessCallback,
                                                        Callback::Cancelable * onFailureCallback,
                                                        Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                        uint16_t maxInterval, uint16_t change)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterReportCurrentYAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0004, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeDriftCompensation(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadDriftCompensationAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeCompensationText(Callback::Cancelable * onSuccessCallback,
                                                              Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCompensationTextAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                              Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorTemperatureAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReportAttributeColorTemperature(Callback::Cancelable * onSuccessCallback,
                                                                Callback::Cancelable * onFailureCallback,
                                                                Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                                uint16_t maxInterval, uint16_t change)
{
    System::PacketBufferHandle payload =
        encodeColorControlClusterReportColorTemperatureAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0007, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorMode(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorModeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorControlOptions(Callback::Cancelable * onSuccessCallback,
                                                                 Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorControlOptionsAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorControlOptions(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback, uint8_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorControlOptionsAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeNumberOfPrimaries(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadNumberOfPrimariesAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary1XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary1YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary1Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary1IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary2XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary2YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary2Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary2IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary3XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary3YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary3Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary3IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary4XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary4YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary4Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary4IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary5XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary5YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary5Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary5IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6X(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary6XAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6Y(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary6YAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributePrimary6Intensity(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadPrimary6IntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeWhitePointX(Callback::Cancelable * onSuccessCallback,
                                                         Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadWhitePointXAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeWhitePointX(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteWhitePointXAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeWhitePointY(Callback::Cancelable * onSuccessCallback,
                                                         Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadWhitePointYAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeWhitePointY(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteWhitePointYAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRX(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointRXAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRX(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointRXAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRY(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointRYAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRY(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointRYAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointRIntensity(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointRIntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointRIntensity(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback, uint8_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointRIntensityAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGX(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointGXAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGX(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointGXAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGY(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointGYAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGY(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointGYAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointGIntensity(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointGIntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointGIntensity(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback, uint8_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointGIntensityAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBX(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointBXAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBX(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointBXAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBY(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointBYAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBY(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointBYAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorPointBIntensity(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorPointBIntensityAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeColorPointBIntensity(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback, uint8_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteColorPointBIntensityAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeEnhancedCurrentHue(Callback::Cancelable * onSuccessCallback,
                                                                Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadEnhancedCurrentHueAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeEnhancedColorMode(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadEnhancedColorModeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopActive(Callback::Cancelable * onSuccessCallback,
                                                             Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorLoopActiveAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopDirection(Callback::Cancelable * onSuccessCallback,
                                                                Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorLoopDirectionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorLoopTime(Callback::Cancelable * onSuccessCallback,
                                                           Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorLoopTimeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorCapabilities(Callback::Cancelable * onSuccessCallback,
                                                               Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorCapabilitiesAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTempPhysicalMin(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorTempPhysicalMinAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeColorTempPhysicalMax(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadColorTempPhysicalMaxAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeCoupleColorTempToLevelMinMireds(Callback::Cancelable * onSuccessCallback,
                                                                             Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadCoupleColorTempToLevelMinMiredsAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeStartUpColorTemperatureMireds(Callback::Cancelable * onSuccessCallback,
                                                                           Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadStartUpColorTemperatureMiredsAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::WriteAttributeStartUpColorTemperatureMireds(Callback::Cancelable * onSuccessCallback,
                                                                            Callback::Cancelable * onFailureCallback,
                                                                            uint16_t value)
{
    System::PacketBufferHandle payload = encodeColorControlClusterWriteStartUpColorTemperatureMiredsAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ColorControlCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                             Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeColorControlClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// DoorLock Cluster Commands
CHIP_ERROR DoorLockCluster::ClearAllPins(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearAllPinsCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearAllRfids(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearAllRfidsCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint8_t scheduleId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearHolidayScheduleCommand(mEndpoint, scheduleId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearPinCommand(mEndpoint, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearRfidCommand(mEndpoint, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint8_t scheduleId, uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearWeekdayScheduleCommand(mEndpoint, scheduleId, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ClearYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                 uint8_t scheduleId, uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterClearYeardayScheduleCommand(mEndpoint, scheduleId, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetHolidayScheduleCommand(mEndpoint, scheduleId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetLogRecord(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                         uint16_t logIndex)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetLogRecordCommand(mEndpoint, logIndex);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetPinCommand(mEndpoint, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetRfidCommand(mEndpoint, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetUserType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                        uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetUserTypeCommand(mEndpoint, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId, uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetWeekdayScheduleCommand(mEndpoint, scheduleId, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::GetYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId, uint16_t userId)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterGetYeardayScheduleCommand(mEndpoint, scheduleId, userId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::LockDoor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback, char * pin)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterLockDoorCommand(mEndpoint, pin);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetHolidaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId, uint32_t localStartTime, uint32_t localEndTime,
                                               uint8_t operatingModeDuringHoliday)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterSetHolidayScheduleCommand(mEndpoint, scheduleId, localStartTime,
                                                                                        localEndTime, operatingModeDuringHoliday);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetPin(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   uint16_t userId, uint8_t userStatus, uint8_t userType, char * pin)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterSetPinCommand(mEndpoint, userId, userStatus, userType, pin);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetRfid(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint16_t userId, uint8_t userStatus, uint8_t userType, char * id)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterSetRfidCommand(mEndpoint, userId, userStatus, userType, id);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetUserType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                        uint16_t userId, uint8_t userType)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterSetUserTypeCommand(mEndpoint, userId, userType);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetWeekdaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId, uint16_t userId, uint8_t daysMask, uint8_t startHour,
                                               uint8_t startMinute, uint8_t endHour, uint8_t endMinute)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterSetWeekdayScheduleCommand(mEndpoint, scheduleId, userId, daysMask,
                                                                                        startHour, startMinute, endHour, endMinute);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::SetYeardaySchedule(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                               uint8_t scheduleId, uint16_t userId, uint32_t localStartTime, uint32_t localEndTime)
{
    System::PacketBufferHandle payload =
        encodeDoorLockClusterSetYeardayScheduleCommand(mEndpoint, scheduleId, userId, localStartTime, localEndTime);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::UnlockDoor(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                       char * pin)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterUnlockDoorCommand(mEndpoint, pin);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::UnlockWithTimeout(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint16_t timeoutInSeconds, char * pin)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterUnlockWithTimeoutCommand(mEndpoint, timeoutInSeconds, pin);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// DoorLock Cluster Attributes
CHIP_ERROR DoorLockCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR DoorLockCluster::ReadAttributeLockState(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterReadLockStateAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ReportAttributeLockState(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback,
                                                     Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                     uint16_t maxInterval)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterReportLockStateAttribute(mEndpoint, minInterval, maxInterval);
    return RequestAttributeReporting(std::move(payload), 0x0000, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR DoorLockCluster::ReadAttributeLockType(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterReadLockTypeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ReadAttributeActuatorEnabled(Callback::Cancelable * onSuccessCallback,
                                                         Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterReadActuatorEnabledAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR DoorLockCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                         Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeDoorLockClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Groups Cluster Commands
CHIP_ERROR GroupsCluster::AddGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   uint16_t groupId, char * groupName)
{
    System::PacketBufferHandle payload = encodeGroupsClusterAddGroupCommand(mEndpoint, groupId, groupName);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::AddGroupIfIdentifying(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                                uint16_t groupId, char * groupName)
{
    System::PacketBufferHandle payload = encodeGroupsClusterAddGroupIfIdentifyingCommand(mEndpoint, groupId, groupName);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::GetGroupMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                             uint8_t groupCount, uint16_t groupList)
{
    System::PacketBufferHandle payload = encodeGroupsClusterGetGroupMembershipCommand(mEndpoint, groupCount, groupList);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::RemoveAllGroups(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeGroupsClusterRemoveAllGroupsCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::RemoveGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t groupId)
{
    System::PacketBufferHandle payload = encodeGroupsClusterRemoveGroupCommand(mEndpoint, groupId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::ViewGroup(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint16_t groupId)
{
    System::PacketBufferHandle payload = encodeGroupsClusterViewGroupCommand(mEndpoint, groupId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Groups Cluster Attributes
CHIP_ERROR GroupsCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeGroupsClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR GroupsCluster::ReadAttributeNameSupport(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeGroupsClusterReadNameSupportAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR GroupsCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeGroupsClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// IasZone Cluster Commands
// IasZone Cluster Attributes
CHIP_ERROR IasZoneCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR IasZoneCluster::ReadAttributeZoneState(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadZoneStateAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneType(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadZoneTypeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneStatus(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadZoneStatusAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::ReadAttributeIasCieAddress(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadIasCieAddressAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::WriteAttributeIasCieAddress(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback, uint64_t value)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterWriteIasCieAddressAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::ReadAttributeZoneId(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadZoneIdAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IasZoneCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                        Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIasZoneClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Identify Cluster Commands
CHIP_ERROR IdentifyCluster::Identify(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint16_t identifyTime)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterIdentifyCommand(mEndpoint, identifyTime);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IdentifyCluster::IdentifyQuery(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterIdentifyQueryCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Identify Cluster Attributes
CHIP_ERROR IdentifyCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR IdentifyCluster::ReadAttributeIdentifyTime(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterReadIdentifyTimeAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IdentifyCluster::WriteAttributeIdentifyTime(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback, uint16_t value)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterWriteIdentifyTimeAttribute(mEndpoint, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR IdentifyCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                         Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeIdentifyClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// LevelControl Cluster Commands
CHIP_ERROR LevelControlCluster::Move(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint8_t moveMode, uint8_t rate, uint8_t optionMask, uint8_t optionOverride)
{
    System::PacketBufferHandle payload =
        encodeLevelControlClusterMoveCommand(mEndpoint, moveMode, rate, optionMask, optionOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::MoveToLevel(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                            uint8_t level, uint16_t transitionTime, uint8_t optionMask, uint8_t optionOverride)
{
    System::PacketBufferHandle payload =
        encodeLevelControlClusterMoveToLevelCommand(mEndpoint, level, transitionTime, optionMask, optionOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::MoveToLevelWithOnOff(Callback::Cancelable * onSuccessCallback,
                                                     Callback::Cancelable * onFailureCallback, uint8_t level,
                                                     uint16_t transitionTime)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterMoveToLevelWithOnOffCommand(mEndpoint, level, transitionTime);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::MoveWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint8_t moveMode, uint8_t rate)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterMoveWithOnOffCommand(mEndpoint, moveMode, rate);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::Step(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint8_t stepMode, uint8_t stepSize, uint16_t transitionTime, uint8_t optionMask,
                                     uint8_t optionOverride)
{
    System::PacketBufferHandle payload =
        encodeLevelControlClusterStepCommand(mEndpoint, stepMode, stepSize, transitionTime, optionMask, optionOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::StepWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              uint8_t stepMode, uint8_t stepSize, uint16_t transitionTime)
{
    System::PacketBufferHandle payload =
        encodeLevelControlClusterStepWithOnOffCommand(mEndpoint, stepMode, stepSize, transitionTime);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::Stop(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint8_t optionMask, uint8_t optionOverride)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterStopCommand(mEndpoint, optionMask, optionOverride);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::StopWithOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterStopWithOnOffCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// LevelControl Cluster Attributes
CHIP_ERROR LevelControlCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR LevelControlCluster::ReadAttributeCurrentLevel(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterReadCurrentLevelAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR LevelControlCluster::ReportAttributeCurrentLevel(Callback::Cancelable * onSuccessCallback,
                                                            Callback::Cancelable * onFailureCallback,
                                                            Callback::Cancelable * onReportCallback, uint16_t minInterval,
                                                            uint16_t maxInterval, uint8_t change)
{
    System::PacketBufferHandle payload =
        encodeLevelControlClusterReportCurrentLevelAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0000, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR LevelControlCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                             Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeLevelControlClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// OnOff Cluster Commands
CHIP_ERROR OnOffCluster::Off(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterOffCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR OnOffCluster::On(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterOnCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR OnOffCluster::Toggle(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterToggleCommand(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// OnOff Cluster Attributes
CHIP_ERROR OnOffCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR OnOffCluster::ReadAttributeOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterReadOnOffAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR OnOffCluster::ReportAttributeOnOff(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                              Callback::Cancelable * onReportCallback, uint16_t minInterval, uint16_t maxInterval)
{
    System::PacketBufferHandle payload = encodeOnOffClusterReportOnOffAttribute(mEndpoint, minInterval, maxInterval);
    return RequestAttributeReporting(std::move(payload), 0x0000, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR OnOffCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeOnOffClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Scenes Cluster Commands
CHIP_ERROR ScenesCluster::AddScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                   uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, char * sceneName,
                                   chip::ClusterId clusterId, uint8_t length, uint8_t value)
{
    System::PacketBufferHandle payload =
        encodeScenesClusterAddSceneCommand(mEndpoint, groupId, sceneId, transitionTime, sceneName, clusterId, length, value);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::GetSceneMembership(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                             uint16_t groupId)
{
    System::PacketBufferHandle payload = encodeScenesClusterGetSceneMembershipCommand(mEndpoint, groupId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::RecallScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t groupId, uint8_t sceneId, uint16_t transitionTime)
{
    System::PacketBufferHandle payload = encodeScenesClusterRecallSceneCommand(mEndpoint, groupId, sceneId, transitionTime);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::RemoveAllScenes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                          uint16_t groupId)
{
    System::PacketBufferHandle payload = encodeScenesClusterRemoveAllScenesCommand(mEndpoint, groupId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::RemoveScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                      uint16_t groupId, uint8_t sceneId)
{
    System::PacketBufferHandle payload = encodeScenesClusterRemoveSceneCommand(mEndpoint, groupId, sceneId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::StoreScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                     uint16_t groupId, uint8_t sceneId)
{
    System::PacketBufferHandle payload = encodeScenesClusterStoreSceneCommand(mEndpoint, groupId, sceneId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ViewScene(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback,
                                    uint16_t groupId, uint8_t sceneId)
{
    System::PacketBufferHandle payload = encodeScenesClusterViewSceneCommand(mEndpoint, groupId, sceneId);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// Scenes Cluster Attributes
CHIP_ERROR ScenesCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback, Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR ScenesCluster::ReadAttributeSceneCount(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadSceneCountAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ReadAttributeCurrentScene(Callback::Cancelable * onSuccessCallback,
                                                    Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadCurrentSceneAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ReadAttributeCurrentGroup(Callback::Cancelable * onSuccessCallback,
                                                    Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadCurrentGroupAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ReadAttributeSceneValid(Callback::Cancelable * onSuccessCallback,
                                                  Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadSceneValidAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ReadAttributeNameSupport(Callback::Cancelable * onSuccessCallback,
                                                   Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadNameSupportAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR ScenesCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeScenesClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

// TemperatureMeasurement Cluster Commands
// TemperatureMeasurement Cluster Attributes
CHIP_ERROR TemperatureMeasurementCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                             Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeTemperatureMeasurementClusterDiscoverAttributes(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}
CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                     Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeTemperatureMeasurementClusterReadMeasuredValueAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                       Callback::Cancelable * onFailureCallback,
                                                                       Callback::Cancelable * onReportCallback,
                                                                       uint16_t minInterval, uint16_t maxInterval, int16_t change)
{
    System::PacketBufferHandle payload =
        encodeTemperatureMeasurementClusterReportMeasuredValueAttribute(mEndpoint, minInterval, maxInterval, change);
    return RequestAttributeReporting(std::move(payload), 0x0000, onSuccessCallback, onFailureCallback, onReportCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                        Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeTemperatureMeasurementClusterReadMinMeasuredValueAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                        Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeTemperatureMeasurementClusterReadMaxMeasuredValueAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                       Callback::Cancelable * onFailureCallback)
{
    System::PacketBufferHandle payload = encodeTemperatureMeasurementClusterReadClusterRevisionAttribute(mEndpoint);
    return SendCommand(std::move(payload), onSuccessCallback, onFailureCallback);
}

} // namespace Controller
} // namespace chip
