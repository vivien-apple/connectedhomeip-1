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
#include <app/util/CallbacksMgr.h>
#include <app/util/af.h>
#include <app/util/basic-types.h>
#include <core/CHIPEncoding.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>

using namespace ::chip;

#define CHECK_MESSAGE_LENGTH(value)                                                                                                \
    if (!chip::CanCastTo<uint16_t>(value))                                                                                         \
    {                                                                                                                              \
        ChipLogError(chipTool, "CHECK_MESSAGE_LENGTH expects a uint16_t value, got: %d", value);                                   \
        Callback::Callback<DefaultFailureCallback> * cb =                                                                          \
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);                                         \
        cb->mCall(cb->mContext, EMBER_ZCL_STATUS_INVALID_VALUE);                                                                   \
        return true;                                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    if (messageLen < value)                                                                                                        \
    {                                                                                                                              \
        ChipLogError(chipTool, "Unexpected response length: %d", messageLen);                                                      \
        Callback::Callback<DefaultFailureCallback> * cb =                                                                          \
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);                                         \
        cb->mCall(cb->mContext, EMBER_ZCL_STATUS_INVALID_VALUE);                                                                   \
        return true;                                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    messageLen = static_cast<uint16_t>(messageLen - static_cast<uint16_t>(value));

#define GET_CALLBACKS(name)                                                                                                        \
    Callback::Cancelable * onSuccessCallback = nullptr;                                                                            \
    Callback::Cancelable * onFailureCallback = nullptr;                                                                            \
    NodeId sourceId                          = emberAfCurrentCommand()->source;                                                    \
    uint8_t sequenceNumber                   = emberAfCurrentCommand()->seqNum;                                                    \
    CHIP_ERROR err = gCallbacks.GetResponseCallback(sourceId, sequenceNumber, &onSuccessCallback, &onFailureCallback);             \
                                                                                                                                   \
    if (CHIP_NO_ERROR != err)                                                                                                      \
    {                                                                                                                              \
        if (onSuccessCallback == nullptr)                                                                                          \
        {                                                                                                                          \
            ChipLogDetail(chipTool, "%s: Missing success callback", name);                                                         \
        }                                                                                                                          \
                                                                                                                                   \
        if (onFailureCallback == nullptr)                                                                                          \
        {                                                                                                                          \
            ChipLogDetail(chipTool, "%s: Missing failure callback", name);                                                         \
        }                                                                                                                          \
                                                                                                                                   \
        return true;                                                                                                               \
    }

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

// Singleton instance of the callbacks manager
app::CHIPCallbacksMgr & gCallbacks = app::CHIPCallbacksMgr::GetInstance();

bool emberAfDefaultResponseCallback(ClusterId clusterId, CommandId commandId, EmberAfStatus status)
{
    ChipLogProgress(chipTool, "DefaultResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  CommandId: 0x%02x", commandId);
    LogStatus(status);

    GET_CALLBACKS("emberAfDefaultResponseCallback");
    if (status == EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultSuccessCallback> * cb =
            Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
        cb->mCall(cb->mContext);
    }
    else
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
    }

    return true;
}

bool emberAfReadAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ReadAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    GET_CALLBACKS("emberAfReadAttributesResponseCallback");

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
            CHECK_MESSAGE_LENGTH(1);
            uint8_t attributeType = chip::Encoding::Read8(message);
            ChipLogProgress(chipTool, "  attributeType: 0x%02x", attributeType);

            switch (attributeType)
            {
            case 0x00: // nodata / No data
            case 0x0A: // data24 / 24-bit data
            case 0x0C: // data40 / 40-bit data
            case 0x0D: // data48 / 48-bit data
            case 0x0E: // data56 / 56-bit data
            case 0x1A: // map24 / 24-bit bitmap
            case 0x1C: // map40 / 40-bit bitmap
            case 0x1D: // map48 / 48-bit bitmap
            case 0x1E: // map56 / 56-bit bitmap
            case 0x22: // uint24 / Unsigned 24-bit integer
            case 0x24: // uint40 / Unsigned 40-bit integer
            case 0x25: // uint48 / Unsigned 48-bit integer
            case 0x26: // uint56 / Unsigned 56-bit integer
            case 0x2A: // int24 / Signed 24-bit integer
            case 0x2C: // int40 / Signed 40-bit integer
            case 0x2D: // int48 / Signed 48-bit integer
            case 0x2E: // int56 / Signed 56-bit integer
            case 0x38: // semi / Semi-precision
            case 0x39: // single / Single precision
            case 0x3A: // double / Double precision
            case 0x41: // octstr / Octet string
            case 0x42: // string / Character string
            case 0x43: // octstr16 / Long octet string
            case 0x44: // string16 / Long character string
            case 0x48: // array / Array
            case 0x49: // struct / Structure
            case 0x50: // set / Set
            case 0x51: // bag / Bag
            case 0xE0: // ToD / Time of day
            {
                ChipLogError(chipTool, "attributeType 0x%02x is not supported", attributeType);
                Callback::Callback<DefaultFailureCallback> * cb =
                    Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
                cb->mCall(cb->mContext, EMBER_ZCL_STATUS_INVALID_VALUE);
                return true;
            }

            case 0x08: // data8 / 8-bit data
            case 0x18: // map8 / 8-bit bitmap
            case 0x20: // uint8 / Unsigned  8-bit integer
            case 0x30: // enum8 / 8-bit enumeration
            {
                CHECK_MESSAGE_LENGTH(1);
                uint8_t value = chip::Encoding::Read8(message);
                ChipLogProgress(chipTool, "  value: 0x%02x", value);

                Callback::Callback<Int8uAttributeCallback> * cb =
                    Callback::Callback<Int8uAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x09: // data16 / 16-bit data
            case 0x19: // map16 / 16-bit bitmap
            case 0x21: // uint16 / Unsigned 16-bit integer
            case 0x31: // enum16 / 16-bit enumeration
            case 0xE8: // clusterId / Cluster ID
            case 0xE9: // attribId / Attribute ID
            case 0xEA: // bacOID / BACnet OID
            case 0xF1: // key128 / 128-bit security key
            case 0xFF: // unk / Unknown
            {
                CHECK_MESSAGE_LENGTH(2);
                uint16_t value = chip::Encoding::LittleEndian::Read16(message);
                ChipLogProgress(chipTool, "  value: 0x%04x", value);

                Callback::Callback<Int16uAttributeCallback> * cb =
                    Callback::Callback<Int16uAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x0B: // data32 / 32-bit data
            case 0x1B: // map32 / 32-bit bitmap
            case 0x23: // uint32 / Unsigned 32-bit integer
            case 0xE1: // date / Date
            case 0xE2: // UTC / UTCTime
            {
                CHECK_MESSAGE_LENGTH(4);
                uint32_t value = chip::Encoding::LittleEndian::Read32(message);
                ChipLogProgress(chipTool, "  value: 0x%08x", value);

                Callback::Callback<Int32uAttributeCallback> * cb =
                    Callback::Callback<Int32uAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x0F: // data64 / 64-bit data
            case 0x1F: // map64 / 64-bit bitmap
            case 0x27: // uint64 / Unsigned 64-bit integer
            case 0xF0: // EUI64 / IEEE address
            {
                CHECK_MESSAGE_LENGTH(8);
                uint64_t value = chip::Encoding::LittleEndian::Read64(message);
                ChipLogProgress(chipTool, "  value: 0x%16x", value);

                Callback::Callback<Int64uAttributeCallback> * cb =
                    Callback::Callback<Int64uAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x10: // bool / Boolean
            {
                CHECK_MESSAGE_LENGTH(1);
                uint8_t value = chip::Encoding::Read8(message);
                ChipLogProgress(chipTool, "  value: %d", value);

                Callback::Callback<BooleanAttributeCallback> * cb =
                    Callback::Callback<BooleanAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x28: // int8 / Signed 8-bit integer
            {
                CHECK_MESSAGE_LENGTH(1);
                int8_t value = chip::CastToSigned(chip::Encoding::Read8(message));
                ChipLogProgress(chipTool, "  value: %" PRId8, value);

                Callback::Callback<Int8sAttributeCallback> * cb =
                    Callback::Callback<Int8sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x29: // int16 / Signed 16-bit integer
            {
                CHECK_MESSAGE_LENGTH(2);
                int16_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read16(message));
                ChipLogProgress(chipTool, "  value: %" PRId16, value);

                Callback::Callback<Int16sAttributeCallback> * cb =
                    Callback::Callback<Int16sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x2B: // int32 / Signed 32-bit integer
            {
                CHECK_MESSAGE_LENGTH(4);
                int32_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read32(message));
                ChipLogProgress(chipTool, "  value: %" PRId32, value);

                Callback::Callback<Int32sAttributeCallback> * cb =
                    Callback::Callback<Int32sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x2F: // int64 / Signed 64-bit integer
            {
                CHECK_MESSAGE_LENGTH(8);
                int64_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read64(message));
                ChipLogProgress(chipTool, "  value: %" PRId64, value);

                Callback::Callback<Int64sAttributeCallback> * cb =
                    Callback::Callback<Int64sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }
            }
        }
        else
        {
            Callback::Callback<DefaultFailureCallback> * cb =
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
            cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        }

        // The current code is written matching the current API where there is a single attribute read
        // per read command. So if multiple attributes are read at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(chipTool, "Multiple attributes read at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfWriteAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "WriteAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    GET_CALLBACKS("emberAfWriteAttributesResponseCallback");

    // struct writeAttributeResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status == EMBER_ZCL_STATUS_SUCCESS)
        {
            Callback::Callback<DefaultSuccessCallback> * cb =
                Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
            cb->mCall(cb->mContext);
        }
        else
        {
            CHECK_MESSAGE_LENGTH(2);
            uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
            ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);

            Callback::Callback<DefaultFailureCallback> * cb =
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
            cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        }

        // The current code is written matching the current API where there is a single attribute written
        // per write command. So if multiple attributes are written at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(chipTool, "Multiple attributes written at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfConfigureReportingResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ConfigureReportingResponseCallback:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    GET_CALLBACKS("emberAfConfigureReportingResponseCallback");

    // struct configureReportingResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status == EMBER_ZCL_STATUS_SUCCESS)
        {
            Callback::Callback<DefaultSuccessCallback> * cb =
                Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
            cb->mCall(cb->mContext);
        }
        else
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t direction = chip::Encoding::Read8(message); // reportingRole
            ChipLogProgress(chipTool, "  direction: 0x%02x", direction);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
            ChipLogProgress(chipTool, "  attributeId: 0x%04x", attributeId);

            Callback::Callback<DefaultFailureCallback> * cb =
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
            cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        }

        // The current code is written matching the current API where there is a single attribute report
        // per configure command. So if multiple attributes are configured at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(chipTool, "Multiple attributes reports configured at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfReadReportingConfigurationResponseCallback(chip::ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(chipTool, "ReadReportingConfigurationResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);

    GET_CALLBACKS("emberAfReadReportingConfigurationResponseCallback");

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

            Callback::Callback<ReadReportingConfigurationReportedCallback> * cb =
                Callback::Callback<ReadReportingConfigurationReportedCallback>::FromCancelable(onSuccessCallback);
            cb->mCall(cb->mContext, minimumReportingInterval, maximumReportingInterval);
        }
        else
        {
            CHECK_MESSAGE_LENGTH(2);
            uint16_t timeout = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(chipTool, "  timeout: %" PRIu16, timeout);

            Callback::Callback<ReadReportingConfigurationReceivedCallback> * cb =
                Callback::Callback<ReadReportingConfigurationReceivedCallback>::FromCancelable(onSuccessCallback);
            cb->mCall(cb->mContext, timeout);
        }
    }

    return true;
}

bool emberAfDiscoverAttributesResponseCallback(ClusterId clusterId, bool discoveryComplete, uint8_t * message, uint16_t messageLen,
                                               bool extended)
{
    ChipLogProgress(chipTool, "DiscoverAttributesResponse:");
    ChipLogProgress(chipTool, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(chipTool, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(chipTool, "  extended: %d", extended);

    GET_CALLBACKS("emberAfDiscoverAttributesCallback");

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

    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
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

    GET_CALLBACKS("emberAfDiscoverCommandsGeneratedResponseCallback");
    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
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

    GET_CALLBACKS("emberAfDiscoverCommandsGeneratedResponseCallback");
    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearAllPinsResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearAllPinsResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearAllPinsResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearAllPinsResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearAllPinsResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearAllRfidsResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearAllRfidsResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearAllRfidsResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearHolidayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearPinResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearPinResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearPinResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearRfidResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearRfidResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearWeekdayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "ClearYeardayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterClearYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
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

    GET_CALLBACKS("DoorLockClusterGetHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, scheduleId, localStartTime, localEndTime, operatingModeDuringHoliday);
    return true;
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

    GET_CALLBACKS("DoorLockClusterGetLogRecordResponseCallback");

    Callback::Callback<DoorLockClusterGetLogRecordResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetLogRecordResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, logEntryId, timestamp, eventType, source, eventIdOrAlarmCode, userId, pin);
    return true;
}

bool emberAfDoorLockClusterGetPinResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * pin)
{
    ChipLogProgress(chipTool, "GetPinResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(chipTool, "  pin: %s", pin);

    GET_CALLBACKS("DoorLockClusterGetPinResponseCallback");

    Callback::Callback<DoorLockClusterGetPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userStatus, userType, pin);
    return true;
}

bool emberAfDoorLockClusterGetRfidResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * rfid)
{
    ChipLogProgress(chipTool, "GetRfidResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(chipTool, "  rfid: %s", rfid);

    GET_CALLBACKS("DoorLockClusterGetRfidResponseCallback");

    Callback::Callback<DoorLockClusterGetRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userStatus, userType, rfid);
    return true;
}

bool emberAfDoorLockClusterGetUserTypeResponseCallback(uint16_t userId, uint8_t userType)
{
    ChipLogProgress(chipTool, "GetUserTypeResponse:");
    ChipLogProgress(chipTool, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(chipTool, "  userType: %" PRIu8 "", userType);

    GET_CALLBACKS("DoorLockClusterGetUserTypeResponseCallback");

    Callback::Callback<DoorLockClusterGetUserTypeResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetUserTypeResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userType);
    return true;
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

    GET_CALLBACKS("DoorLockClusterGetWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, scheduleId, userId, daysMask, startHour, startMinute, endHour, endMinute);
    return true;
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

    GET_CALLBACKS("DoorLockClusterGetYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, scheduleId, userId, localStartTime, localEndTime);
    return true;
}

bool emberAfDoorLockClusterLockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "LockDoorResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterLockDoorResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterLockDoorResponseCallback> * cb =
        Callback::Callback<DoorLockClusterLockDoorResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetHolidayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetPinResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetPinResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetPinResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetRfidResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetRfidResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetUserTypeResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetUserTypeResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetUserTypeResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetUserTypeResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetUserTypeResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetWeekdayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "SetYeardayScheduleResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterSetYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterUnlockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "UnlockDoorResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterUnlockDoorResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterUnlockDoorResponseCallback> * cb =
        Callback::Callback<DoorLockClusterUnlockDoorResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterUnlockWithTimeoutResponseCallback(uint8_t status)
{
    ChipLogProgress(chipTool, "UnlockWithTimeoutResponse:");
    LogStatus(status);

    GET_CALLBACKS("DoorLockClusterUnlockWithTimeoutResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback> * cb =
        Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfGroupsClusterAddGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "AddGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    GET_CALLBACKS("GroupsClusterAddGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<GroupsClusterAddGroupResponseCallback> * cb =
        Callback::Callback<GroupsClusterAddGroupResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId);
    return true;
}

bool emberAfGroupsClusterGetGroupMembershipResponseCallback(uint8_t capacity, uint8_t groupCount,
                                                            /* TYPE WARNING: array array defaults to */ uint8_t * groupList)
{
    ChipLogProgress(chipTool, "GetGroupMembershipResponse:");
    ChipLogProgress(chipTool, "  capacity: %" PRIu8 "", capacity);
    ChipLogProgress(chipTool, "  groupCount: %" PRIu8 "", groupCount);
    ChipLogProgress(chipTool, "  groupList: %p", groupList);

    GET_CALLBACKS("GroupsClusterGetGroupMembershipResponseCallback");

    Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback> * cb =
        Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, capacity, groupCount, groupList);
    return true;
}

bool emberAfGroupsClusterRemoveGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "RemoveGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    GET_CALLBACKS("GroupsClusterRemoveGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<GroupsClusterRemoveGroupResponseCallback> * cb =
        Callback::Callback<GroupsClusterRemoveGroupResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId);
    return true;
}

bool emberAfGroupsClusterViewGroupResponseCallback(uint8_t status, uint16_t groupId, uint8_t * groupName)
{
    ChipLogProgress(chipTool, "ViewGroupResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  groupName: %s", groupName);

    GET_CALLBACKS("GroupsClusterViewGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<GroupsClusterViewGroupResponseCallback> * cb =
        Callback::Callback<GroupsClusterViewGroupResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, groupName);
    return true;
}

bool emberAfIdentifyClusterIdentifyQueryResponseCallback(uint16_t timeout)
{
    ChipLogProgress(chipTool, "IdentifyQueryResponse:");
    ChipLogProgress(chipTool, "  timeout: %" PRIu16 "", timeout);

    GET_CALLBACKS("IdentifyClusterIdentifyQueryResponseCallback");

    Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback> * cb =
        Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, timeout);
    return true;
}

bool emberAfScenesClusterAddSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "AddSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    GET_CALLBACKS("ScenesClusterAddSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterAddSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterAddSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId);
    return true;
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

    GET_CALLBACKS("ScenesClusterGetSceneMembershipResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback> * cb =
        Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, capacity, groupId, sceneCount, sceneList);
    return true;
}

bool emberAfScenesClusterRemoveAllScenesResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(chipTool, "RemoveAllScenesResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);

    GET_CALLBACKS("ScenesClusterRemoveAllScenesResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback> * cb =
        Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId);
    return true;
}

bool emberAfScenesClusterRemoveSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "RemoveSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    GET_CALLBACKS("ScenesClusterRemoveSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterRemoveSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterRemoveSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId);
    return true;
}

bool emberAfScenesClusterStoreSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(chipTool, "StoreSceneResponse:");
    LogStatus(status);
    ChipLogProgress(chipTool, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(chipTool, "  sceneId: %" PRIu8 "", sceneId);

    GET_CALLBACKS("ScenesClusterStoreSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterStoreSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterStoreSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId);
    return true;
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

    GET_CALLBACKS("ScenesClusterViewSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, static_cast<EmberAfStatus>(status));
        return true;
    }

    Callback::Callback<ScenesClusterViewSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterViewSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId, transitionTime, sceneName, extensionFieldSets);
    return true;
}
