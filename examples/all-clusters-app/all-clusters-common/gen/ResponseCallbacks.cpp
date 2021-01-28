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
        ChipLogError(Zcl, "CHECK_MESSAGE_LENGTH expects a uint16_t value, got: %d", value);                                        \
        if (onFailureCallback != nullptr)                                                                                          \
        {                                                                                                                          \
            Callback::Callback<DefaultFailureCallback> * cb =                                                                      \
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);                                     \
            cb->mCall(cb->mContext, static_cast<uint8_t>(EMBER_ZCL_STATUS_INVALID_VALUE));                                         \
        }                                                                                                                          \
        return true;                                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    if (messageLen < value)                                                                                                        \
    {                                                                                                                              \
        ChipLogError(Zcl, "Unexpected response length: %d", messageLen);                                                           \
        if (onFailureCallback != nullptr)                                                                                          \
        {                                                                                                                          \
            Callback::Callback<DefaultFailureCallback> * cb =                                                                      \
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);                                     \
            cb->mCall(cb->mContext, static_cast<uint8_t>(EMBER_ZCL_STATUS_INVALID_VALUE));                                         \
        }                                                                                                                          \
        return true;                                                                                                               \
    }                                                                                                                              \
                                                                                                                                   \
    messageLen = static_cast<uint16_t>(messageLen - static_cast<uint16_t>(value));

#define GET_RESPONSE_CALLBACKS(name)                                                                                               \
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
            ChipLogDetail(Zcl, "%s: Missing success callback", name);                                                              \
        }                                                                                                                          \
                                                                                                                                   \
        if (onFailureCallback == nullptr)                                                                                          \
        {                                                                                                                          \
            ChipLogDetail(Zcl, "%s: Missing failure callback", name);                                                              \
        }                                                                                                                          \
                                                                                                                                   \
        return true;                                                                                                               \
    }

#define GET_REPORT_CALLBACK(name)                                                                                                  \
    Callback::Cancelable * onReportCallback = nullptr;                                                                             \
    CHIP_ERROR err = gCallbacks.GetReportCallback(sourceId, endpointId, clusterId, attributeId, &onReportCallback);                \
                                                                                                                                   \
    if (CHIP_NO_ERROR != err)                                                                                                      \
    {                                                                                                                              \
        if (onReportCallback == nullptr)                                                                                           \
        {                                                                                                                          \
            ChipLogDetail(Zcl, "%s: Missing report callback", name);                                                               \
        }                                                                                                                          \
                                                                                                                                   \
        return true;                                                                                                               \
    }

void LogStatus(uint8_t status)
{
    switch (status)
    {
    case EMBER_ZCL_STATUS_SUCCESS:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_SUCCESS (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_FAILURE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NOT_AUTHORIZED:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_NOT_AUTHORIZED (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_MALFORMED_COMMAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_MALFORMED_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_COMMAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUP_CLUSTER_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_GENERAL_COMMAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUP_GENERAL_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUP_MANUF_CLUSTER_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUP_MANUF_GENERAL_COMMAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUP_MANUF_GENERAL_COMMAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_FIELD:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INVALID_FIELD (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_VALUE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INVALID_VALUE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_READ_ONLY:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_READ_ONLY (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INSUFFICIENT_SPACE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INSUFFICIENT_SPACE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_DUPLICATE_EXISTS:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_DUPLICATE_EXISTS (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NOT_FOUND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_NOT_FOUND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNREPORTABLE_ATTRIBUTE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNREPORTABLE_ATTRIBUTE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_DATA_TYPE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INVALID_DATA_TYPE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_SELECTOR:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INVALID_SELECTOR (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_WRITE_ONLY:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_WRITE_ONLY (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INCONSISTENT_STARTUP_STATE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INCONSISTENT_STARTUP_STATE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_DEFINED_OUT_OF_BAND:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_DEFINED_OUT_Of_BAND (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_ACTION_DENIED:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_ACTION_DENIED (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_TIMEOUT:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_TIMEOUT (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_ABORT:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_ABORT (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_INVALID_IMAGE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_INVALID_IMAGE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_WAIT_FOR_DATA:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_WAIT_FOR_DATA (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_NO_IMAGE_AVAILABLE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_REQUIRE_MORE_IMAGE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_REQUIRE_MORE_IMAGE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_HARDWARE_FAILURE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_HARDWARE_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_SOFTWARE_FAILURE:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_SOFTWARE_FAILURE (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER (0x%02x)", status);
        break;
    case EMBER_ZCL_STATUS_LIMIT_REACHED:
        ChipLogProgress(Zcl, "  status: EMBER_ZCL_STATUS_LIMIT_REACHED (0x%02x)", status);
        break;
    default:
        ChipLogError(Zcl, "Unknow status: 0x%02x", status);
        break;
    }
}

// Singleton instance of the callbacks manager
app::CHIPCallbacksMgr & gCallbacks = app::CHIPCallbacksMgr::GetInstance();

bool emberAfDefaultResponseCallback(ClusterId clusterId, CommandId commandId, EmberAfStatus status)
{
    ChipLogProgress(Zcl, "DefaultResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(Zcl, "  CommandId: 0x%02x", commandId);
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("emberAfDefaultResponseCallback");
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
        cb->mCall(cb->mContext, static_cast<uint8_t>(status));
    }

    return true;
}

bool emberAfReadAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(Zcl, "ReadAttributesResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);

    GET_RESPONSE_CALLBACKS("emberAfReadAttributesResponseCallback");

    // struct readAttributeResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

        CHECK_MESSAGE_LENGTH(1);
        uint8_t status = chip::Encoding::Read8(message); // zclStatus
        LogStatus(status);

        if (status == EMBER_ZCL_STATUS_SUCCESS)
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t attributeType = chip::Encoding::Read8(message);
            ChipLogProgress(Zcl, "  attributeType: 0x%02x", attributeType);

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
                ChipLogError(Zcl, "attributeType 0x%02x is not supported", attributeType);
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
                ChipLogProgress(Zcl, "  value: 0x%02x", value);

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
                ChipLogProgress(Zcl, "  value: 0x%04x", value);

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
                ChipLogProgress(Zcl, "  value: 0x%08x", value);

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
                ChipLogProgress(Zcl, "  value: 0x%16x", value);

                Callback::Callback<Int64uAttributeCallback> * cb =
                    Callback::Callback<Int64uAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x10: // bool / Boolean
            {
                CHECK_MESSAGE_LENGTH(1);
                uint8_t value = chip::Encoding::Read8(message);
                ChipLogProgress(Zcl, "  value: %d", value);

                Callback::Callback<BooleanAttributeCallback> * cb =
                    Callback::Callback<BooleanAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x28: // int8 / Signed 8-bit integer
            {
                CHECK_MESSAGE_LENGTH(1);
                int8_t value = chip::CastToSigned(chip::Encoding::Read8(message));
                ChipLogProgress(Zcl, "  value: %" PRId8, value);

                Callback::Callback<Int8sAttributeCallback> * cb =
                    Callback::Callback<Int8sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x29: // int16 / Signed 16-bit integer
            {
                CHECK_MESSAGE_LENGTH(2);
                int16_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read16(message));
                ChipLogProgress(Zcl, "  value: %" PRId16, value);

                Callback::Callback<Int16sAttributeCallback> * cb =
                    Callback::Callback<Int16sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x2B: // int32 / Signed 32-bit integer
            {
                CHECK_MESSAGE_LENGTH(4);
                int32_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read32(message));
                ChipLogProgress(Zcl, "  value: %" PRId32, value);

                Callback::Callback<Int32sAttributeCallback> * cb =
                    Callback::Callback<Int32sAttributeCallback>::FromCancelable(onSuccessCallback);
                cb->mCall(cb->mContext, value);
                break;
            }

            case 0x2F: // int64 / Signed 64-bit integer
            {
                CHECK_MESSAGE_LENGTH(8);
                int64_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read64(message));
                ChipLogProgress(Zcl, "  value: %" PRId64, value);

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
            cb->mCall(cb->mContext, status);
        }

        // The current code is written matching the current API where there is a single attribute read
        // per read command. So if multiple attributes are read at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(Zcl, "Multiple attributes read at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfWriteAttributesResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(Zcl, "WriteAttributesResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);

    GET_RESPONSE_CALLBACKS("emberAfWriteAttributesResponseCallback");

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
            ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

            Callback::Callback<DefaultFailureCallback> * cb =
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
            cb->mCall(cb->mContext, status);
        }

        // The current code is written matching the current API where there is a single attribute written
        // per write command. So if multiple attributes are written at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(Zcl, "Multiple attributes written at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfConfigureReportingResponseCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(Zcl, "ConfigureReportingResponseCallback:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);

    GET_RESPONSE_CALLBACKS("emberAfConfigureReportingResponseCallback");

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
            ChipLogProgress(Zcl, "  direction: 0x%02x", direction);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
            ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

            Callback::Callback<DefaultFailureCallback> * cb =
                Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
            cb->mCall(cb->mContext, status);
        }

        // The current code is written matching the current API where there is a single attribute report
        // per configure command. So if multiple attributes are configured at the same time, something is wrong
        // somewhere.
        if (messageLen)
        {
            ChipLogError(Zcl, "Multiple attributes reports configured at the same time. Something went wrong.");
            break;
        }
    }

    return true;
}

bool emberAfReadReportingConfigurationResponseCallback(chip::ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(Zcl, "ReadReportingConfigurationResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);

    GET_RESPONSE_CALLBACKS("emberAfReadReportingConfigurationResponseCallback");

    // struct readReportingConfigurationResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(1);
        uint8_t direction = chip::Encoding::Read8(message); // reportingRole
        ChipLogProgress(Zcl, "  direction: 0x%02x", direction);

        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

        if (direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED)
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t attributeType = chip::Encoding::Read8(message); // zclType
            ChipLogProgress(Zcl, "  attributeType: 0x%02x", attributeType);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t minimumReportingInterval = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(Zcl, "  minimumReportingInterval: %" PRIu16, minimumReportingInterval);

            CHECK_MESSAGE_LENGTH(2);
            uint16_t maximumReportingInterval = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(Zcl, "  maximumReportingInterval: %" PRIu16, maximumReportingInterval);

            // FIXME: unk is not supported yet.

            Callback::Callback<ReadReportingConfigurationReportedCallback> * cb =
                Callback::Callback<ReadReportingConfigurationReportedCallback>::FromCancelable(onSuccessCallback);
            cb->mCall(cb->mContext, minimumReportingInterval, maximumReportingInterval);
        }
        else
        {
            CHECK_MESSAGE_LENGTH(2);
            uint16_t timeout = chip::Encoding::LittleEndian::Read16(message); // uint16
            ChipLogProgress(Zcl, "  timeout: %" PRIu16, timeout);

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
    ChipLogProgress(Zcl, "DiscoverAttributesResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(Zcl, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(Zcl, "  extended: %d", extended);

    GET_RESPONSE_CALLBACKS("emberAfDiscoverAttributesCallback");

    // struct discoverAttributesResponseRecord[]
    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

        CHECK_MESSAGE_LENGTH(1);
        uint8_t attributeType = chip::Encoding::Read8(message); // zclType
        ChipLogProgress(Zcl, "  attributeType: 0x%02x", attributeType);
    }

    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDiscoverCommandsGeneratedResponseCallback(ClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                      CommandId * commandIds, uint16_t commandIdCount)
{
    ChipLogProgress(Zcl, "DiscoverCommandsGeneratedResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(Zcl, "  manufacturerCode: 0x%04x", manufacturerCode);
    ChipLogProgress(Zcl, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(Zcl, "  commandIdCount: %" PRIu16, commandIdCount);

    for (uint16_t i = 0; i < commandIdCount; i++)
    {
        ChipLogProgress(Zcl, "  commandId: 0x%02x", commandIds++);
    }

    GET_RESPONSE_CALLBACKS("emberAfDiscoverCommandsGeneratedResponseCallback");
    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDiscoverCommandsReceivedResponseCallback(ClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                     CommandId * commandIds, uint16_t commandIdCount)
{
    ChipLogProgress(Zcl, "DiscoverCommandsReceivedResponse:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);
    ChipLogProgress(Zcl, "  manufacturerCode: 0x%04x", manufacturerCode);
    ChipLogProgress(Zcl, "  discoveryComplete: %d", discoveryComplete);
    ChipLogProgress(Zcl, "  commandIdCount: %" PRIu16, commandIdCount);

    for (uint16_t i = 0; i < commandIdCount; i++)
    {
        ChipLogProgress(Zcl, "  commandId: 0x%02x", commandIds++);
    }

    GET_RESPONSE_CALLBACKS("emberAfDiscoverCommandsGeneratedResponseCallback");
    Callback::Callback<DefaultSuccessCallback> * cb = Callback::Callback<DefaultSuccessCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfReportAttributesCallback(ClusterId clusterId, uint8_t * message, uint16_t messageLen)
{
    ChipLogProgress(Zcl, "emberAfReportAttributeCallback:");
    ChipLogProgress(Zcl, "  ClusterId: 0x%04x", clusterId);

    NodeId sourceId = emberAfCurrentCommand()->source;
    ChipLogProgress(Zcl, "  Source NodeId: %" PRIu64, sourceId);

    EndpointId endpointId = emberAfCurrentCommand()->apsFrame->sourceEndpoint;
    ChipLogProgress(Zcl, "  Source EndpointId: 0x%04x", endpointId);

    // TODO onFailureCallback is just here because of the CHECK_MESSAGE_LENGTH macro. It needs to be removed.
    Callback::Cancelable * onFailureCallback = nullptr;

    while (messageLen)
    {
        CHECK_MESSAGE_LENGTH(2);
        uint16_t attributeId = chip::Encoding::LittleEndian::Read16(message); // attribId
        ChipLogProgress(Zcl, "  attributeId: 0x%04x", attributeId);

        GET_REPORT_CALLBACK("emberAfReportAttributesCallback");

        CHECK_MESSAGE_LENGTH(1);
        uint8_t attributeType = chip::Encoding::Read8(message);
        ChipLogProgress(Zcl, "  attributeType: 0x%02x", attributeType);

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
            ChipLogError(Zcl, "attributeType 0x%02x is not supported", attributeType);
            return true;
        }

        case 0x08: // data8 / 8-bit data
        case 0x18: // map8 / 8-bit bitmap
        case 0x20: // uint8 / Unsigned  8-bit integer
        case 0x30: // enum8 / 8-bit enumeration
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t value = chip::Encoding::Read8(message);
            ChipLogProgress(Zcl, "  value: 0x%02x", value);

            Callback::Callback<Int8uAttributeCallback> * cb =
                Callback::Callback<Int8uAttributeCallback>::FromCancelable(onReportCallback);
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
            ChipLogProgress(Zcl, "  value: 0x%04x", value);

            Callback::Callback<Int16uAttributeCallback> * cb =
                Callback::Callback<Int16uAttributeCallback>::FromCancelable(onReportCallback);
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
            ChipLogProgress(Zcl, "  value: 0x%08x", value);

            Callback::Callback<Int32uAttributeCallback> * cb =
                Callback::Callback<Int32uAttributeCallback>::FromCancelable(onReportCallback);
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
            ChipLogProgress(Zcl, "  value: 0x%16x", value);

            Callback::Callback<Int64uAttributeCallback> * cb =
                Callback::Callback<Int64uAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }

        case 0x10: // bool / Boolean
        {
            CHECK_MESSAGE_LENGTH(1);
            uint8_t value = chip::Encoding::Read8(message);
            ChipLogProgress(Zcl, "  value: %d", value);

            Callback::Callback<BooleanAttributeCallback> * cb =
                Callback::Callback<BooleanAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }

        case 0x28: // int8 / Signed 8-bit integer
        {
            CHECK_MESSAGE_LENGTH(1);
            int8_t value = chip::CastToSigned(chip::Encoding::Read8(message));
            ChipLogProgress(Zcl, "  value: %" PRId8, value);

            Callback::Callback<Int8sAttributeCallback> * cb =
                Callback::Callback<Int8sAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }

        case 0x29: // int16 / Signed 16-bit integer
        {
            CHECK_MESSAGE_LENGTH(2);
            int16_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read16(message));
            ChipLogProgress(Zcl, "  value: %" PRId16, value);

            Callback::Callback<Int16sAttributeCallback> * cb =
                Callback::Callback<Int16sAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }

        case 0x2B: // int32 / Signed 32-bit integer
        {
            CHECK_MESSAGE_LENGTH(4);
            int32_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read32(message));
            ChipLogProgress(Zcl, "  value: %" PRId32, value);

            Callback::Callback<Int32sAttributeCallback> * cb =
                Callback::Callback<Int32sAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }

        case 0x2F: // int64 / Signed 64-bit integer
        {
            CHECK_MESSAGE_LENGTH(8);
            int64_t value = chip::CastToSigned(chip::Encoding::LittleEndian::Read64(message));
            ChipLogProgress(Zcl, "  value: %" PRId64, value);

            Callback::Callback<Int64sAttributeCallback> * cb =
                Callback::Callback<Int64sAttributeCallback>::FromCancelable(onReportCallback);
            cb->mCall(cb->mContext, value);
            break;
        }
        }
    }

    return true;
}
