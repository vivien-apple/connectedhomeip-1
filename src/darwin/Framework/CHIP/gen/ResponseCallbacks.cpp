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

bool emberAfDoorLockClusterClearAllPinsResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearAllPinsResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearAllPinsResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearAllPinsResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearAllPinsResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearAllRfidsResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearAllRfidsResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearAllRfidsResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearHolidayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearPinResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearPinResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearPinResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearRfidResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearRfidResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearWeekdayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterClearYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "ClearYeardayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterClearYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "GetHolidayScheduleResponse:");
    ChipLogProgress(Zcl, "  scheduleId: %" PRIu8 "", scheduleId);
    LogStatus(status);
    ChipLogProgress(Zcl, "  localStartTime: %" PRIu32 "", localStartTime);
    ChipLogProgress(Zcl, "  localEndTime: %" PRIu32 "", localEndTime);
    ChipLogProgress(Zcl, "  operatingModeDuringHoliday: %" PRIu8 "", operatingModeDuringHoliday);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "GetLogRecordResponse:");
    ChipLogProgress(Zcl, "  logEntryId: %" PRIu16 "", logEntryId);
    ChipLogProgress(Zcl, "  timestamp: %" PRIu32 "", timestamp);
    ChipLogProgress(Zcl, "  eventType: %" PRIu8 "", eventType);
    ChipLogProgress(Zcl, "  source: %" PRIu8 "", source);
    ChipLogProgress(Zcl, "  eventIdOrAlarmCode: %" PRIu8 "", eventIdOrAlarmCode);
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(Zcl, "  pin: %s", pin);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetLogRecordResponseCallback");

    Callback::Callback<DoorLockClusterGetLogRecordResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetLogRecordResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, logEntryId, timestamp, eventType, source, eventIdOrAlarmCode, userId, pin);
    return true;
}

bool emberAfDoorLockClusterGetPinResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * pin)
{
    ChipLogProgress(Zcl, "GetPinResponse:");
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(Zcl, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(Zcl, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(Zcl, "  pin: %s", pin);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetPinResponseCallback");

    Callback::Callback<DoorLockClusterGetPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userStatus, userType, pin);
    return true;
}

bool emberAfDoorLockClusterGetRfidResponseCallback(uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * rfid)
{
    ChipLogProgress(Zcl, "GetRfidResponse:");
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(Zcl, "  userStatus: %" PRIu8 "", userStatus);
    ChipLogProgress(Zcl, "  userType: %" PRIu8 "", userType);
    ChipLogProgress(Zcl, "  rfid: %s", rfid);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetRfidResponseCallback");

    Callback::Callback<DoorLockClusterGetRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userStatus, userType, rfid);
    return true;
}

bool emberAfDoorLockClusterGetUserTypeResponseCallback(uint16_t userId, uint8_t userType)
{
    ChipLogProgress(Zcl, "GetUserTypeResponse:");
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    ChipLogProgress(Zcl, "  userType: %" PRIu8 "", userType);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetUserTypeResponseCallback");

    Callback::Callback<DoorLockClusterGetUserTypeResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetUserTypeResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, userId, userType);
    return true;
}

bool emberAfDoorLockClusterGetWeekdayScheduleResponseCallback(uint8_t scheduleId, uint16_t userId, uint8_t status, uint8_t daysMask,
                                                              uint8_t startHour, uint8_t startMinute, uint8_t endHour,
                                                              uint8_t endMinute)
{
    ChipLogProgress(Zcl, "GetWeekdayScheduleResponse:");
    ChipLogProgress(Zcl, "  scheduleId: %" PRIu8 "", scheduleId);
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    LogStatus(status);
    ChipLogProgress(Zcl, "  daysMask: %" PRIu8 "", daysMask);
    ChipLogProgress(Zcl, "  startHour: %" PRIu8 "", startHour);
    ChipLogProgress(Zcl, "  startMinute: %" PRIu8 "", startMinute);
    ChipLogProgress(Zcl, "  endHour: %" PRIu8 "", endHour);
    ChipLogProgress(Zcl, "  endMinute: %" PRIu8 "", endMinute);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "GetYeardayScheduleResponse:");
    ChipLogProgress(Zcl, "  scheduleId: %" PRIu8 "", scheduleId);
    ChipLogProgress(Zcl, "  userId: %" PRIu16 "", userId);
    LogStatus(status);
    ChipLogProgress(Zcl, "  localStartTime: %" PRIu32 "", localStartTime);
    ChipLogProgress(Zcl, "  localEndTime: %" PRIu32 "", localEndTime);

    GET_RESPONSE_CALLBACKS("DoorLockClusterGetYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, scheduleId, userId, localStartTime, localEndTime);
    return true;
}

bool emberAfDoorLockClusterLockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "LockDoorResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterLockDoorResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterLockDoorResponseCallback> * cb =
        Callback::Callback<DoorLockClusterLockDoorResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetHolidayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetHolidayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetHolidayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetPinResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetPinResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetPinResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetPinResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetPinResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetRfidResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetRfidResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetRfidResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetRfidResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetRfidResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetUserTypeResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetUserTypeResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetUserTypeResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetUserTypeResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetUserTypeResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetWeekdayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetWeekdayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetWeekdayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterSetYeardayScheduleResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "SetYeardayScheduleResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterSetYeardayScheduleResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback> * cb =
        Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterUnlockDoorResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "UnlockDoorResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterUnlockDoorResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterUnlockDoorResponseCallback> * cb =
        Callback::Callback<DoorLockClusterUnlockDoorResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfDoorLockClusterUnlockWithTimeoutResponseCallback(uint8_t status)
{
    ChipLogProgress(Zcl, "UnlockWithTimeoutResponse:");
    LogStatus(status);

    GET_RESPONSE_CALLBACKS("DoorLockClusterUnlockWithTimeoutResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback> * cb =
        Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext);
    return true;
}

bool emberAfGroupsClusterAddGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(Zcl, "AddGroupResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);

    GET_RESPONSE_CALLBACKS("GroupsClusterAddGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "GetGroupMembershipResponse:");
    ChipLogProgress(Zcl, "  capacity: %" PRIu8 "", capacity);
    ChipLogProgress(Zcl, "  groupCount: %" PRIu8 "", groupCount);
    ChipLogProgress(Zcl, "  groupList: %p", groupList);

    GET_RESPONSE_CALLBACKS("GroupsClusterGetGroupMembershipResponseCallback");

    Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback> * cb =
        Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, capacity, groupCount, groupList);
    return true;
}

bool emberAfGroupsClusterRemoveGroupResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(Zcl, "RemoveGroupResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);

    GET_RESPONSE_CALLBACKS("GroupsClusterRemoveGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<GroupsClusterRemoveGroupResponseCallback> * cb =
        Callback::Callback<GroupsClusterRemoveGroupResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId);
    return true;
}

bool emberAfGroupsClusterViewGroupResponseCallback(uint8_t status, uint16_t groupId, uint8_t * groupName)
{
    ChipLogProgress(Zcl, "ViewGroupResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  groupName: %s", groupName);

    GET_RESPONSE_CALLBACKS("GroupsClusterViewGroupResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<GroupsClusterViewGroupResponseCallback> * cb =
        Callback::Callback<GroupsClusterViewGroupResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, groupName);
    return true;
}

bool emberAfIdentifyClusterIdentifyQueryResponseCallback(uint16_t timeout)
{
    ChipLogProgress(Zcl, "IdentifyQueryResponse:");
    ChipLogProgress(Zcl, "  timeout: %" PRIu16 "", timeout);

    GET_RESPONSE_CALLBACKS("IdentifyClusterIdentifyQueryResponseCallback");

    Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback> * cb =
        Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, timeout);
    return true;
}

bool emberAfScenesClusterAddSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(Zcl, "AddSceneResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  sceneId: %" PRIu8 "", sceneId);

    GET_RESPONSE_CALLBACKS("ScenesClusterAddSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "GetSceneMembershipResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  capacity: %" PRIu8 "", capacity);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  sceneCount: %" PRIu8 "", sceneCount);
    ChipLogProgress(Zcl, "  sceneList: %p", sceneList);

    GET_RESPONSE_CALLBACKS("ScenesClusterGetSceneMembershipResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback> * cb =
        Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, capacity, groupId, sceneCount, sceneList);
    return true;
}

bool emberAfScenesClusterRemoveAllScenesResponseCallback(uint8_t status, uint16_t groupId)
{
    ChipLogProgress(Zcl, "RemoveAllScenesResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);

    GET_RESPONSE_CALLBACKS("ScenesClusterRemoveAllScenesResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback> * cb =
        Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId);
    return true;
}

bool emberAfScenesClusterRemoveSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(Zcl, "RemoveSceneResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  sceneId: %" PRIu8 "", sceneId);

    GET_RESPONSE_CALLBACKS("ScenesClusterRemoveSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<ScenesClusterRemoveSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterRemoveSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId);
    return true;
}

bool emberAfScenesClusterStoreSceneResponseCallback(uint8_t status, uint16_t groupId, uint8_t sceneId)
{
    ChipLogProgress(Zcl, "StoreSceneResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  sceneId: %" PRIu8 "", sceneId);

    GET_RESPONSE_CALLBACKS("ScenesClusterStoreSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
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
    ChipLogProgress(Zcl, "ViewSceneResponse:");
    LogStatus(status);
    ChipLogProgress(Zcl, "  groupId: %" PRIu16 "", groupId);
    ChipLogProgress(Zcl, "  sceneId: %" PRIu8 "", sceneId);
    ChipLogProgress(Zcl, "  transitionTime: %" PRIu16 "", transitionTime);
    ChipLogProgress(Zcl, "  sceneName: %s", sceneName);
    ChipLogProgress(Zcl, "  extensionFieldSets: %p", extensionFieldSets);

    GET_RESPONSE_CALLBACKS("ScenesClusterViewSceneResponseCallback");

    if (status != EMBER_ZCL_STATUS_SUCCESS)
    {
        Callback::Callback<DefaultFailureCallback> * cb =
            Callback::Callback<DefaultFailureCallback>::FromCancelable(onFailureCallback);
        cb->mCall(cb->mContext, status);
        return true;
    }

    Callback::Callback<ScenesClusterViewSceneResponseCallback> * cb =
        Callback::Callback<ScenesClusterViewSceneResponseCallback>::FromCancelable(onSuccessCallback);
    cb->mCall(cb->mContext, groupId, sceneId, transitionTime, sceneName, extensionFieldSets);
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
