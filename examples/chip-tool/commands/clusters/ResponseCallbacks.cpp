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

#include "ResponseCallbacks.h"
#include "gen/enums.h"
#include <app/util/basic-types.h>
#include <core/CHIPEncoding.h>
#include <inttypes.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>

using namespace ::chip;

bool sCommandSuccess = true;

#define CHECK_MESSAGE_LENGTH(value)                                                                                                \
    if (!chip::CanCastTo<uint16_t>(value))                                                                                         \
    {                                                                                                                              \
        ChipLogError(chipTool, "CHECK_MESSAGE_LENGTH expects a uint16_t value, got: %d", value);                                   \
        sCommandSuccess = false;                                                                                                   \
        return false;                                                                                                              \
    }                                                                                                                              \
                                                                                                                                   \
    if (messageLen < value)                                                                                                        \
    {                                                                                                                              \
        ChipLogError(chipTool, "Unexpected response length: %d", messageLen);                                                      \
        sCommandSuccess = false;                                                                                                   \
        return false;                                                                                                              \
    }                                                                                                                              \
                                                                                                                                   \
    messageLen = static_cast<uint16_t>(messageLen - static_cast<uint16_t>(value));

void LogStatus(uint8_t status)
{
    switch (status)
    {
    case EMBER_ZCL_STATUS_SUCCESS:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_SUCCESS (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_FAILURE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NOT_AUTHORIZED:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_NOT_AUTHORIZED (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_MALFORMED_COMMAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_MALFORMED_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_COMMAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_GENERAL_COMMAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUP_GENERAL_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_MANUF_GENERAL_COMMAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUP_MANUF_GENERAL_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_FIELD:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INVALID_FIELD (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_VALUE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INVALID_VALUE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_READ_ONLY:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_READ_ONLY (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INSUFFICIENT_SPACE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INSUFFICIENT_SPACE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_DUPLICATE_EXISTS:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_DUPLICATE_EXISTS (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NOT_FOUND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_NOT_FOUND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNREPORTABLE_ATTRIBUTE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNREPORTABLE_ATTRIBUTE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_DATA_TYPE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INVALID_DATA_TYPE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_SELECTOR:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INVALID_SELECTOR (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_WRITE_ONLY:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_WRITE_ONLY (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INCONSISTENT_STARTUP_STATE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INCONSISTENT_STARTUP_STATE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_DEFINED_OUT_OF_BAND:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_DEFINED_OUT_Of_BAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_ACTION_DENIED:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_ACTION_DENIED (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_TIMEOUT:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_TIMEOUT (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_ABORT:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_ABORT (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_IMAGE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_INVALID_IMAGE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_WAIT_FOR_DATA:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_WAIT_FOR_DATA (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_REQUIRE_MORE_IMAGE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_REQUIRE_MORE_IMAGE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_HARDWARE_FAILURE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_HARDWARE_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_SOFTWARE_FAILURE:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_SOFTWARE_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_LIMIT_REACHED:
        ChipLogProgress(chipTool, "  status: EMBER_ZCL_STATUS_LIMIT_REACHED (0x%02x)", status);
        break;
    default:
        ChipLogError(chipTool, "Unknow status: 0x%02x", status);
        break;
    }
}

bool ReadAttributeValue(uint8_t *& message, uint16_t & messageLen)
{
    CHECK_MESSAGE_LENGTH(1);
    uint8_t type = chip::Encoding::Read8(message);
    ChipLogProgress(chipTool, "  type: 0x%02x", type);

    // FIXME: Should we have a mapping of type ids to types, based on
    // table 2.6.2.2 in Rev 8 of the ZCL spec?
    switch (type)
    {
    case 0x00: // nodata / No data
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x08: // data8 / 8-bit data
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: 0x%02x", chip::Encoding::Read8(message));
        return true;
        break;
    case 0x09: // data16 / 16-bit data
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0x0A: // data24 / 24-bit data
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 3;
        break;
    case 0x0B: // data32 / 32-bit data
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: 0x%08x", chip::Encoding::LittleEndian::Read32(message));
        return true;
        break;
    case 0x0C: // data40 / 40-bit data
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 5;
        break;
    case 0x0D: // data48 / 48-bit data
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 6;
        break;
    case 0x0E: // data56 / 56-bit data
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 7;
        break;
    case 0x0F: // data64 / 64-bit data
        CHECK_MESSAGE_LENGTH(8);
        ChipLogProgress(chipTool, "  value: 0x%16x", chip::Encoding::LittleEndian::Read64(message));
        return true;
        break;
    case 0x10: // bool / Boolean
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: 0x%02x", chip::Encoding::Read8(message));
        return true;
        break;
    case 0x18: // map8 / 8-bit bitmap
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: 0x%02x", chip::Encoding::Read8(message));
        return true;
        break;
    case 0x19: // map16 / 16-bit bitmap
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0x1A: // map24 / 24-bit bitmap
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 3;
        break;
    case 0x1B: // map32 / 32-bit bitmap
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: 0x%08x", chip::Encoding::LittleEndian::Read32(message));
        return true;
        break;
    case 0x1C: // map40 / 40-bit bitmap
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 5;
        break;
    case 0x1D: // map48 / 48-bit bitmap
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 6;
        break;
    case 0x1E: // map56 / 56-bit bitmap
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 7;
        break;
    case 0x1F: // map64 / 64-bit bitmap
        CHECK_MESSAGE_LENGTH(8);
        ChipLogProgress(chipTool, "  value: 0x%16x", chip::Encoding::LittleEndian::Read64(message));
        return true;
        break;
    case 0x20: // uint8 / Unsigned  8-bit integer
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: 0x%02x", chip::Encoding::Read8(message));
        return true;
        break;
    case 0x21: // uint16 / Unsigned 16-bit integer
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0x22: // uint24 / Unsigned 24-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 3;
        break;
    case 0x23: // uint32 / Unsigned 32-bit integer
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: 0x%08x", chip::Encoding::LittleEndian::Read32(message));
        return true;
        break;
    case 0x24: // uint40 / Unsigned 40-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 5;
        break;
    case 0x25: // uint48 / Unsigned 48-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 6;
        break;
    case 0x26: // uint56 / Unsigned 56-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 7;
        break;
    case 0x27: // uint64 / Unsigned 64-bit integer
        CHECK_MESSAGE_LENGTH(8);
        ChipLogProgress(chipTool, "  value: 0x%16x", chip::Encoding::LittleEndian::Read64(message));
        return true;
        break;
    case 0x28: // int8 / Signed 8-bit integer
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: %d", chip::CastToSigned(chip::Encoding::Read8(message)));
        return true;
        break;
    case 0x29: // int16 / Signed 16-bit integer
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: %d", chip::CastToSigned(chip::Encoding::LittleEndian::Read16(message)));
        return true;
        break;
    case 0x2A: // int24 / Signed 24-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 3;
        break;
    case 0x2B: // int32 / Signed 32-bit integer
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: %d", chip::CastToSigned(chip::Encoding::LittleEndian::Read32(message)));
        return true;
        break;
    case 0x2C: // int40 / Signed 40-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 5;
        break;
    case 0x2D: // int48 / Signed 48-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 6;
        break;
    case 0x2E: // int56 / Signed 56-bit integer
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 7;
        break;
    case 0x2F: // int64 / Signed 64-bit integer
        CHECK_MESSAGE_LENGTH(8);
        ChipLogProgress(chipTool, "  value: %d", chip::CastToSigned(chip::Encoding::LittleEndian::Read64(message)));
        return true;
        break;
    case 0x30: // enum8 / 8-bit enumeration
        CHECK_MESSAGE_LENGTH(1);
        ChipLogProgress(chipTool, "  value: 0x%02x", chip::Encoding::Read8(message));
        return true;
        break;
    case 0x31: // enum16 / 16-bit enumeration
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0x38: // semi / Semi-precision
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x39: // single / Single precision
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x3A: // double / Double precision
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x41: // octstr / Octet string
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x42: // string / Character string
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x43: // octstr16 / Long octet string
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 2;
        break;
    case 0x44: // string16 / Long character string
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 2;
        break;
    case 0x48: // array / Array
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x49: // struct / Structure
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x50: // set / Set
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0x51: // bag / Bag
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0xE0: // ToD / Time of day
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0xE1: // date / Date
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: 0x%08x", chip::Encoding::LittleEndian::Read32(message));
        return true;
        break;
    case 0xE2: // UTC / UTCTime
        CHECK_MESSAGE_LENGTH(4);
        ChipLogProgress(chipTool, "  value: 0x%08x", chip::Encoding::LittleEndian::Read32(message));
        return true;
        break;
    case 0xE8: // clusterId / Cluster ID
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0xE9: // attribId / Attribute ID
        CHECK_MESSAGE_LENGTH(2);
        ChipLogProgress(chipTool, "  value: 0x%04x", chip::Encoding::LittleEndian::Read16(message));
        return true;
        break;
    case 0xEA: // bacOID / BACnet OID
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    case 0xF0: // EUI64 / IEEE address
        CHECK_MESSAGE_LENGTH(8);
        ChipLogProgress(chipTool, "  value: 0x%16x", chip::Encoding::LittleEndian::Read64(message));
        return true;
        break;
    case 0xF1: // key128 / 128-bit security key
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 16;
        break;
    case 0xFF: // unk / Unknown
        ChipLogError(chipTool, "Type 0x%02x is not supported", type);
        message += 0;
        break;
    }

    return false;
}

bool emberAfDefaultResponseCallback(ClusterId clusterId, CommandId commandId, EmberAfStatus status)
{
    ChipLogProgress(chipTool, "DefaultResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  CommandId: 0x%02x", commandId);
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfReadAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ReadAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    // struct readAttributeResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);

        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status == EMBER_ZCL_STATUS_SUCCESS)
        {
            if (!ReadAttributeValue(message, messageLen))
            {
                sCommandSuccess = false;
            }
        }
        else
        {
            sCommandSuccess = false;
        }
    }

    return false;
}

bool emberAfWriteAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "WriteAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    // struct writeAttributeResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status != EMBER_ZCL_STATUS_SUCCESS)
        {
            sCommandSuccess = false;

            CHECK_MESSAGE_LENGTH(2);
            uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
            ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);
        }
    }

    return false;
}

bool emberAfConfigureReportingResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ConfigureReportingResponseCallback:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    // struct configureReportingResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status != EMBER_ZCL_STATUS_SUCCESS)
        {
            sCommandSuccess = false;

            CHECK_MESSAGE_LENGTH(1);
            uint8_t direction = chip::Encoding::Read8(message); // reportingRole
            ChipLogProgress(chipTool, "  direction: 0x%02x", direction);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
            ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);
        }
    }

    return false;
}

bool emberAfReadReportingConfigurationResponseCallback(chip::ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ReadReportingConfigurationResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    // struct readReportingConfigurationResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t direction = chip::Encoding::Read8(message); // reportingRole
        ChipLogProgress(chipTool, "  direction: 0x%02x", direction);

        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);

        if (direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t attributeType = chip::Encoding::Read8(message); // zclType
            ChipLogProgress(chipTool, "  attributeType: 0x%02x", attributeType);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t minimumReportingInterval = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(chipTool, "  minimumReportingInterval: %" PRIu16, minimumReportingInterval);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t maximumReportingInterval = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(chipTool, "  maximumReportingInterval: %" PRIu16, maximumReportingInterval);

            // FIXME: unk is not supported yet.
        }
        else
        {
            CHECK_MESSAGE_LENGTH(2);
            uint16_t timeout = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(chipTool, "  timeout: %" PRIu16, timeout);
        }
    }

    return false;
}

bool emberAfDiscoverAttributesResponseCallback(ClusterId clusterId, bool discoveryComplete, uint8_t * message, uint16_t messageLen,
                                               bool extended)
{
    ChipLogProgress(chipTool, "DiscoverAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(chipTool, "  extended: %d", extended);

    // struct discoverAttributesResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);

        CHECK_MESSAGE_LENGTH(1);
        uint8_t attributeType = chip::Encoding::Read8(message); // zclType
        ChipLogProgress(chipTool, "  attributeType: 0x%02x", attributeType);
    }

    return false;
}

bool emberAfDiscoverCommandsGeneratedResponseCallback(ClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                      CommandId * commandIds, uint16_t commandIdCount)
{
    ChipLogProgress(chipTool, "DiscoverCommandsGeneratedResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  manufacturerCode: 0x%04x", manufacturerCode);
    ChipLogProgress(chipTool, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(chipTool, "  commandIdCount: %" PRIu16, commandIdCount);

    for (uint16_t i = 0; i < commandIdCount; i++)
    {
        ChipLogProgress(chipTool, "  commandId: 0x%02x", commandIds++);
    }

    return false;
}

bool emberAfDiscoverCommandsReceivedResponseCallback(ClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                     CommandId * commandIds, uint16_t commandIdCount)
{
    ChipLogProgress(chipTool, "DiscoverCommandsReceivedResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  manufacturerCode: 0x%04x", manufacturerCode);
    ChipLogProgress(chipTool, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(chipTool, "  commandIdCount: %" PRIu16, commandIdCount);

    for (uint16_t i = 0; i < commandIdCount; i++)
    {
        ChipLogProgress(chipTool, "  commandId: 0x%02x", commandIds++);
    }

    return false;
}

bool emberAfDoorLockClusterClearAllPinsResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearAllPinsResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearAllRfidsResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearAllRfidsResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearHolidayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearPinResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearPinResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearRfidResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearWeekdayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterClearYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearYeardayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterGetHolidayScheduleResponseCallback(uint8_t scheduleId, uint8_t status, uint32_t localStartTime,
                                                              uint32_t localEndTime, uint8_t operatingModeDuringHoliday)
{
    ChipLogProgress(chipTool, "GetHolidayScheduleResponse:");
    ChipLogProgress(chipTool, "  scheduleId: %" PRIu8 "", scheduleId);
    LogStatus(status);
    ChipLogProgress(chipTool, "  localStartTime: %" PRIu32 "", localStartTime);
    ChipLogProgress(chipTool, "  localEndTime: %" PRIu32 "", localEndTime);
    ChipLogProgress(chipTool, "  operatingModeDuringHoliday: %" PRIu8 "", operatingModeDuringHoliday);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterGetLogRecordResponseCallback(uint16_t logEntryId, uint32_t timestamp, uint8_t eventType, uint8_t source,
                                                        uint8_t eventIdOrAlarmCode, uint16_t userId, uint8_t * pin)
{
    ChipLogProgress(chipTool, "GetLogRecordResponse:");
    ChipLogProgress(chipTool, "  logEntryId: %" PRIu16 "", logEntryId);
    ChipLogProgress(chipTool, "  timestamp: %" PRIu32 "", timestamp);
    ChipLogProgress(chipTool, "  eventType: %" PRIu8 "", eventType);
    ChipLogProgress(chipTool, "  source: %" PRIu8 "", source);
    ChipLogProgress(chipTool, "  eventIdOrAlarmCode: %" PRIu8 "", eventIdOrAlarmCode);
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  pin: %s", pin);

    return false;
}

bool emberAfDoorLockClusterGetPinResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * pin)
{
    ChipLogProgress(chipTool, "GetPinResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(chipTool, "  pin: %s", pin);

    return false;
}

bool emberAfDoorLockClusterGetRfidResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * rfid)
{
    ChipLogProgress(chipTool, "GetRfidResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(chipTool, "  rfid: %s", rfid);

    return false;
}

bool emberAfDoorLockClusterGetUserTypeResponseCallback(uint16_t userId, uint8_t userType)
{
    ChipLogProgress(chipTool, "GetUserTypeResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);

    return false;
}

bool emberAfDoorLockClusterGetWeekdayScheduleResponseCallback(uint8_t scheduleId, uint16_t userId, uint8_t status, uint8_t daysMask,
                                                              uint8_t startHour, uint8_t startMinute, uint8_t endHour,
                                                              uint8_t endMinute)
{
    ChipLogProgress(chipTool, "GetWeekdayScheduleResponse:");
    ChipLogProgress(chipTool, "  scheduleId: %" PRIu8 "", scheduleId);
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    LogStatus(status);
    ChipLogProgress(chipTool, "  daysMask: %" PRIu8 "", daysMask);
    ChipLogProgress(chipTool, "  startHour: %" PRIu8 "", startHour);
    ChipLogProgress(chipTool, "  startMinute: %" PRIu8 "", startMinute);
    ChipLogProgress(chipTool, "  endHour: %" PRIu8 "", endHour);
    ChipLogProgress(chipTool, "  endMinute: %" PRIu8 "", endMinute);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterGetYeardayScheduleResponseCallback(uint8_t scheduleId, uint16_t userId, uint8_t status,
                                                              uint32_t localStartTime, uint32_t localEndTime)
{
    ChipLogProgress(chipTool, "GetYeardayScheduleResponse:");
    ChipLogProgress(chipTool, "  scheduleId: %" PRIu8 "", scheduleId);
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    LogStatus(status);
    ChipLogProgress(chipTool, "  localStartTime: %" PRIu32 "", localStartTime);
    ChipLogProgress(chipTool, "  localEndTime: %" PRIu32 "", localEndTime);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterLockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "LockDoorResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterSetHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetHolidayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterSetRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetRfidResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterSetUserTypeResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetUserTypeResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterSetWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetWeekdayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterSetYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetYeardayScheduleResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterUnlockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "UnlockDoorResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfDoorLockClusterUnlockWithTimeoutResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "UnlockWithTimeoutResponse:");
    LogStatus(status);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfGroupsClusterAddGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "AddGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfGroupsClusterGetGroupMembershipResponseCallback(uint8_t capacity, uint8_t groupCount,
                                                            /* TYPE WARNING: array array defaults to */ uint8_t * groupList)
{
    ChipLogProgress(chipTool, "GetGroupMembershipResponse:");
    ChipLogProgress(chipTool, "  capacity: %" PRIu8 "", capacity);
    ChipLogProgress(chipTool, "  groupCount: %" PRIu8 "", groupCount);
    ChipLogProgress(chipTool, "  groupList: %p", groupList);

    return false;
}

bool emberAfGroupsClusterRemoveGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "RemoveGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfGroupsClusterViewGroupResponseCallback(uint8_t status, uint16_t groupId, uint8_t * groupName)
{
    ChipLogProgress(chipTool, "ViewGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  groupName: %s", groupName);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfIdentifyClusterIdentifyQueryResponseCallback(uint16_t timeout)
{
    ChipLogProgress(chipTool, "IdentifyQueryResponse:");
    ChipLogProgress(chipTool, "  timeout: %" PRIu16 "", timeout);

    return false;
}

bool emberAfScenesClusterAddSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "AddSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfScenesClusterGetSceneMembershipResponseCallback(uint8_t status, uint8_t capacity, uint16_t groupId, uint8_t sceneCount,
                                                            /* TYPE WARNING: array array defaults to */ uint8_t * sceneList)
{
    ChipLogProgress(chipTool, "GetSceneMembershipResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  capacity: %" PRIu8 "", capacity);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneCount: %" PRIu8 "", sceneCount);
    ChipLogProgress(chipTool, "  sceneList: %p", sceneList);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfScenesClusterRemoveAllScenesResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "RemoveAllScenesResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfScenesClusterRemoveSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "RemoveSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfScenesClusterStoreSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "StoreSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}

bool emberAfScenesClusterViewSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId, uint16_t transitionTime,
                                                   uint8_t * sceneName,
                                                   /* TYPE WARNING: array array defaults to */ uint8_t * extensionFieldSets)
{
    ChipLogProgress(chipTool, "ViewSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);
    ChipLogProgress(chipTool, "  transitionTime: %" PRIu16 "", transitionTime);
    ChipLogProgress(chipTool, "  sceneName: %s", sceneName);
    ChipLogProgress(chipTool, "  extensionFieldSets: %p", extensionFieldSets);

    sCommandSuccess = (status == EMBER_ZCL_STATUS_SUCCESS);
    return false;
}
