/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

// THIS FILE IS GENERATED BY ZAP

#include <app/chip-zcl-zpro-codec.h>

#include <support/BufferWriter.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>

#include <app/util/basic-types.h>
#include <lib/support/Span.h>

using namespace chip;
using namespace chip::System;
using namespace chip::Encoding::LittleEndian;

#define COMMAND_HEADER(name, clusterId)                                                                                            \
    const char * kName = name;                                                                                                     \
                                                                                                                                   \
    PacketBufferWriter buf(System::PacketBufferHandle::New(kMaxBufferSize));                                                       \
    if (buf.IsNull())                                                                                                              \
    {                                                                                                                              \
        ChipLogError(Zcl, "Could not allocate packet buffer while trying to encode %s command", kName);                            \
        return PacketBufferHandle();                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    if (doEncodeApsFrame(buf, clusterId, kSourceEndpoint, destinationEndpoint, 0, 0, 0, 0, false))                                 \
    {

#define COMMAND_FOOTER()                                                                                                           \
    }                                                                                                                              \
    if (!buf.Fit())                                                                                                                \
    {                                                                                                                              \
        ChipLogError(Zcl, "Command %s can't fit in the allocated buffer", kName);                                                  \
    }                                                                                                                              \
    return buf.Finalize();

/*----------------------------------------------------------------------------*\
| Cluster Name                                                        |   ID   |
|---------------------------------------------------------------------+--------|
| Basic                                                               | 0x0028 |
| DiagnosticLogs                                                      | 0x0032 |
| EthernetNetworkDiagnostics                                          | 0x0037 |
| FlowMeasurement                                                     | 0x0404 |
| GeneralCommissioning                                                | 0x0030 |
| GeneralDiagnostics                                                  | 0x0033 |
| LevelControl                                                        | 0x0008 |
| NetworkCommissioning                                                | 0x0031 |
| OnOff                                                               | 0x0006 |
| OperationalCredentials                                              | 0x003E |
| PressureMeasurement                                                 | 0x0403 |
| PumpConfigurationAndControl                                         | 0x0200 |
| SoftwareDiagnostics                                                 | 0x0034 |
| TemperatureMeasurement                                              | 0x0402 |
| ThreadNetworkDiagnostics                                            | 0x0035 |
| WiFiNetworkDiagnostics                                              | 0x0036 |
\*----------------------------------------------------------------------------*/

#define EMBER_ZCL_REPORTING_DIRECTION_REPORTED 0x00

#define ZCL_READ_ATTRIBUTES_COMMAND_ID (0x00)
#define ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID (0x01)
#define ZCL_WRITE_ATTRIBUTES_COMMAND_ID (0x02)
#define ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID (0x03)
#define ZCL_WRITE_ATTRIBUTES_RESPONSE_COMMAND_ID (0x04)
#define ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID (0x05)
#define ZCL_CONFIGURE_REPORTING_COMMAND_ID (0x06)
#define ZCL_CONFIGURE_REPORTING_RESPONSE_COMMAND_ID (0x07)
#define ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID (0x08)
#define ZCL_READ_REPORTING_CONFIGURATION_RESPONSE_COMMAND_ID (0x09)
#define ZCL_REPORT_ATTRIBUTES_COMMAND_ID (0x0A)
#define ZCL_DEFAULT_RESPONSE_COMMAND_ID (0x0B)
#define ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID (0x0C)
#define ZCL_DISCOVER_ATTRIBUTES_RESPONSE_COMMAND_ID (0x0D)
#define ZCL_READ_ATTRIBUTES_STRUCTURED_COMMAND_ID (0x0E)
#define ZCL_WRITE_ATTRIBUTES_STRUCTURED_COMMAND_ID (0x0F)
#define ZCL_WRITE_ATTRIBUTES_STRUCTURED_RESPONSE_COMMAND_ID (0x10)
#define ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID (0x11)
#define ZCL_DISCOVER_COMMANDS_RECEIVED_RESPONSE_COMMAND_ID (0x12)
#define ZCL_DISCOVER_COMMANDS_GENERATED_COMMAND_ID (0x13)
#define ZCL_DISCOVER_COMMANDS_GENERATED_RESPONSE_COMMAND_ID (0x14)
#define ZCL_DISCOVER_ATTRIBUTES_EXTENDED_COMMAND_ID (0x15)
#define ZCL_DISCOVER_ATTRIBUTES_EXTENDED_RESPONSE_COMMAND_ID (0x16)

#define FLOW_MEASUREMENT_CLUSTER_ID 0x0404

#define LEVEL_CONTROL_CLUSTER_ID 0x0008
#define ZCL_MOVE_COMMAND_ID (0x01)
#define ZCL_MOVE_TO_LEVEL_COMMAND_ID (0x00)
#define ZCL_MOVE_TO_LEVEL_WITH_ON_OFF_COMMAND_ID (0x04)
#define ZCL_MOVE_WITH_ON_OFF_COMMAND_ID (0x05)
#define ZCL_STEP_COMMAND_ID (0x02)
#define ZCL_STEP_WITH_ON_OFF_COMMAND_ID (0x06)
#define ZCL_STOP_COMMAND_ID (0x03)
#define ZCL_STOP_WITH_ON_OFF_COMMAND_ID (0x07)

#define ON_OFF_CLUSTER_ID 0x0006
#define ZCL_OFF_COMMAND_ID (0x00)
#define ZCL_ON_COMMAND_ID (0x01)
#define ZCL_TOGGLE_COMMAND_ID (0x02)

#define PRESSURE_MEASUREMENT_CLUSTER_ID 0x0403

#define PUMP_CONFIG_CONTROL_CLUSTER_ID 0x0200

#define TEMP_MEASUREMENT_CLUSTER_ID 0x0402

// TODO: Find a way to calculate maximum message length for clusters
//       https://github.com/project-chip/connectedhomeip/issues/965
constexpr uint16_t kMaxBufferSize = 1024;

// This is a global command, so the low bits are 0b00.  The command is
// standard, so does not need a manufacturer code, and we're sending client
// to server, so all the remaining bits are 0.
constexpr uint8_t kFrameControlGlobalCommand = 0x00;

// Pick source endpoint as 1 for now
constexpr EndpointId kSourceEndpoint = 1;

/*----------------------------------------------------------------------------*\
| Cluster FlowMeasurement                                             | 0x0404 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * MeasuredValue                                                     | 0x0000 |
| * MinMeasuredValue                                                  | 0x0001 |
| * MaxMeasuredValue                                                  | 0x0002 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

PacketBufferHandle encodeFlowMeasurementClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverFlowMeasurementAttributes", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute MeasuredValue
 */
PacketBufferHandle encodeFlowMeasurementClusterReadMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadFlowMeasurementMeasuredValue", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

PacketBufferHandle encodeFlowMeasurementClusterConfigureMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint,
                                                                               uint16_t minInterval, uint16_t maxInterval,
                                                                               int16_t change)
{
    COMMAND_HEADER("ReportFlowMeasurementMeasuredValue", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_CONFIGURE_REPORTING_COMMAND_ID)
        .Put8(EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        .Put32(0x0000)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

/*
 * Attribute MinMeasuredValue
 */
PacketBufferHandle encodeFlowMeasurementClusterReadMinMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadFlowMeasurementMinMeasuredValue", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0001);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxMeasuredValue
 */
PacketBufferHandle encodeFlowMeasurementClusterReadMaxMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadFlowMeasurementMaxMeasuredValue", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0002);
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodeFlowMeasurementClusterReadClusterRevisionAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadFlowMeasurementClusterRevision", FLOW_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}

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

PacketBufferHandle encodeLevelControlClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverLevelControlAttributes", LEVEL_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute CurrentLevel
 */
PacketBufferHandle encodeLevelControlClusterReadCurrentLevelAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadLevelControlCurrentLevel", LEVEL_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

PacketBufferHandle encodeLevelControlClusterConfigureCurrentLevelAttribute(uint8_t seqNum, EndpointId destinationEndpoint,
                                                                           uint16_t minInterval, uint16_t maxInterval,
                                                                           uint8_t change)
{
    COMMAND_HEADER("ReportLevelControlCurrentLevel", LEVEL_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_CONFIGURE_REPORTING_COMMAND_ID)
        .Put8(EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        .Put32(0x0000)
        .Put8(32)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put8(static_cast<uint8_t>(change));
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodeLevelControlClusterReadClusterRevisionAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadLevelControlClusterRevision", LEVEL_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}

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

PacketBufferHandle encodeOnOffClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverOnOffAttributes", ON_OFF_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute OnOff
 */
PacketBufferHandle encodeOnOffClusterReadOnOffAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadOnOffOnOff", ON_OFF_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodeOnOffClusterReadClusterRevisionAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadOnOffClusterRevision", ON_OFF_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}

/*----------------------------------------------------------------------------*\
| Cluster PressureMeasurement                                         | 0x0403 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * MeasuredValue                                                     | 0x0000 |
| * MinMeasuredValue                                                  | 0x0001 |
| * MaxMeasuredValue                                                  | 0x0002 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

PacketBufferHandle encodePressureMeasurementClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverPressureMeasurementAttributes", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute MeasuredValue
 */
PacketBufferHandle encodePressureMeasurementClusterReadMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPressureMeasurementMeasuredValue", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

PacketBufferHandle encodePressureMeasurementClusterConfigureMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint,
                                                                                   uint16_t minInterval, uint16_t maxInterval,
                                                                                   int16_t change)
{
    COMMAND_HEADER("ReportPressureMeasurementMeasuredValue", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_CONFIGURE_REPORTING_COMMAND_ID)
        .Put8(EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        .Put32(0x0000)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

/*
 * Attribute MinMeasuredValue
 */
PacketBufferHandle encodePressureMeasurementClusterReadMinMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPressureMeasurementMinMeasuredValue", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0001);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxMeasuredValue
 */
PacketBufferHandle encodePressureMeasurementClusterReadMaxMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPressureMeasurementMaxMeasuredValue", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0002);
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodePressureMeasurementClusterReadClusterRevisionAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPressureMeasurementClusterRevision", PRESSURE_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}

/*----------------------------------------------------------------------------*\
| Cluster PumpConfigurationAndControl                                 | 0x0200 |
|------------------------------------------------------------------------------|
| Commands:                                                           |        |
|------------------------------------------------------------------------------|
| Attributes:                                                         |        |
| * MaxPressure                                                       | 0x0000 |
| * MaxSpeed                                                          | 0x0001 |
| * MaxFlow                                                           | 0x0002 |
| * EffectiveOperationMode                                            | 0x0011 |
| * EffectiveControlMode                                              | 0x0012 |
| * Capacity                                                          | 0x0013 |
| * OperationMode                                                     | 0x0020 |
| * ClusterRevision                                                   | 0xFFFD |
\*----------------------------------------------------------------------------*/

PacketBufferHandle encodePumpConfigurationAndControlClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverPumpConfigurationAndControlAttributes", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxPressure
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadMaxPressureAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlMaxPressure", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxSpeed
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadMaxSpeedAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlMaxSpeed", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0001);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxFlow
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadMaxFlowAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlMaxFlow", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0002);
    COMMAND_FOOTER();
}

/*
 * Attribute EffectiveOperationMode
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadEffectiveOperationModeAttribute(uint8_t seqNum,
                                                                                               EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlEffectiveOperationMode", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0011);
    COMMAND_FOOTER();
}

/*
 * Attribute EffectiveControlMode
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadEffectiveControlModeAttribute(uint8_t seqNum,
                                                                                             EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlEffectiveControlMode", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0012);
    COMMAND_FOOTER();
}

/*
 * Attribute Capacity
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadCapacityAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlCapacity", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0013);
    COMMAND_FOOTER();
}

PacketBufferHandle encodePumpConfigurationAndControlClusterConfigureCapacityAttribute(uint8_t seqNum,
                                                                                      EndpointId destinationEndpoint,
                                                                                      uint16_t minInterval, uint16_t maxInterval,
                                                                                      int16_t change)
{
    COMMAND_HEADER("ReportPumpConfigurationAndControlCapacity", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_CONFIGURE_REPORTING_COMMAND_ID)
        .Put8(EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        .Put32(0x0013)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

/*
 * Attribute OperationMode
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadOperationModeAttribute(uint8_t seqNum,
                                                                                      EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlOperationMode", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0020);
    COMMAND_FOOTER();
}

PacketBufferHandle encodePumpConfigurationAndControlClusterWriteOperationModeAttribute(uint8_t seqNum,
                                                                                       EndpointId destinationEndpoint,
                                                                                       uint8_t operationMode)
{
    COMMAND_HEADER("WritePumpConfigurationAndControlOperationMode", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_WRITE_ATTRIBUTES_COMMAND_ID)
        .Put32(0x0020)
        .Put8(48)
        .Put8(static_cast<uint8_t>(operationMode));
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodePumpConfigurationAndControlClusterReadClusterRevisionAttribute(uint8_t seqNum,
                                                                                        EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadPumpConfigurationAndControlClusterRevision", PUMP_CONFIG_CONTROL_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}

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

PacketBufferHandle encodeTemperatureMeasurementClusterDiscoverAttributes(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("DiscoverTemperatureMeasurementAttributes", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

/*
 * Attribute MeasuredValue
 */
PacketBufferHandle encodeTemperatureMeasurementClusterReadMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadTemperatureMeasurementMeasuredValue", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0000);
    COMMAND_FOOTER();
}

PacketBufferHandle encodeTemperatureMeasurementClusterConfigureMeasuredValueAttribute(uint8_t seqNum,
                                                                                      EndpointId destinationEndpoint,
                                                                                      uint16_t minInterval, uint16_t maxInterval,
                                                                                      int16_t change)
{
    COMMAND_HEADER("ReportTemperatureMeasurementMeasuredValue", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(ZCL_CONFIGURE_REPORTING_COMMAND_ID)
        .Put8(EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        .Put32(0x0000)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

/*
 * Attribute MinMeasuredValue
 */
PacketBufferHandle encodeTemperatureMeasurementClusterReadMinMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadTemperatureMeasurementMinMeasuredValue", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0001);
    COMMAND_FOOTER();
}

/*
 * Attribute MaxMeasuredValue
 */
PacketBufferHandle encodeTemperatureMeasurementClusterReadMaxMeasuredValueAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadTemperatureMeasurementMaxMeasuredValue", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0x0002);
    COMMAND_FOOTER();
}

/*
 * Attribute ClusterRevision
 */
PacketBufferHandle encodeTemperatureMeasurementClusterReadClusterRevisionAttribute(uint8_t seqNum, EndpointId destinationEndpoint)
{
    COMMAND_HEADER("ReadTemperatureMeasurementClusterRevision", TEMP_MEASUREMENT_CLUSTER_ID);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(ZCL_READ_ATTRIBUTES_COMMAND_ID).Put32(0xFFFD);
    COMMAND_FOOTER();
}
