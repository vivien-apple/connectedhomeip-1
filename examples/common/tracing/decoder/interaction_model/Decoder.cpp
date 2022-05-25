/*
 *   Copyright (c) 2022 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "Decoder.h"
#include "DecoderCustomLog.h"

#include <app/MessageDef/InvokeRequestMessage.h>
#include <app/MessageDef/InvokeResponseMessage.h>
#include <app/MessageDef/ReadRequestMessage.h>
#include <app/MessageDef/ReportDataMessage.h>
#include <app/MessageDef/StatusResponseMessage.h>
#include <app/MessageDef/SubscribeRequestMessage.h>
#include <app/MessageDef/SubscribeResponseMessage.h>
#include <app/MessageDef/TimedRequestMessage.h>
#include <app/MessageDef/WriteRequestMessage.h>
#include <app/MessageDef/WriteResponseMessage.h>

namespace {
constexpr const char * kProtocolName = "Interaction Model";

constexpr const char * kUnknown               = "Unknown";
constexpr const char * kStatusResponse        = "Status Response";
constexpr const char * kReadRequest           = "Read Request";
constexpr const char * kSubscribeRequest      = "Subscribe Request";
constexpr const char * kSubscribeResponse     = "Subscribe Response";
constexpr const char * kReportData            = "Report Data";
constexpr const char * kWriteRequest          = "Write Request";
constexpr const char * kWriteResponse         = "Write Response";
constexpr const char * kInvokeCommandRequest  = "InvokeCommandRequest";
constexpr const char * kInvokeCommandResponse = "InvokeCommandResponse";
constexpr const char * kTimedRequest          = "Timed Request";

} // namespace

using MessageType = chip::Protocols::InteractionModel::MsgType;

namespace chip {
namespace trace {
namespace interaction_model {

CHIP_ERROR DecodeStatusResponse(TLV::TLVReader & reader);
CHIP_ERROR DecodeReadRequest(TLV::TLVReader & reader);
CHIP_ERROR DecodeSubscribeRequest(TLV::TLVReader & reader);
CHIP_ERROR DecodeSubscribeResponse(TLV::TLVReader & reader);
CHIP_ERROR DecodeReportData(TLV::TLVReader & reader);
CHIP_ERROR DecodeWriteRequest(TLV::TLVReader & reader);
CHIP_ERROR DecodeWriteResponse(TLV::TLVReader & reader);
CHIP_ERROR DecodeInvokeCommandRequest(TLV::TLVReader & reader);
CHIP_ERROR DecodeInvokeCommandResponse(TLV::TLVReader & reader);
CHIP_ERROR DecodeTimedRequest(TLV::TLVReader & reader);

const char * ToProtocolName()
{
    return kProtocolName;
}

const char * ToProtocolMessageTypeName(uint8_t protocolCode)
{
    switch (protocolCode)
    {
    case to_underlying(MessageType::StatusResponse):
        return kStatusResponse;
    case to_underlying(MessageType::ReadRequest):
        return kReadRequest;
    case to_underlying(MessageType::SubscribeRequest):
        return kSubscribeRequest;
    case to_underlying(MessageType::SubscribeResponse):
        return kSubscribeResponse;
    case to_underlying(MessageType::ReportData):
        return kReportData;
    case to_underlying(MessageType::WriteRequest):
        return kWriteRequest;
    case to_underlying(MessageType::WriteResponse):
        return kWriteResponse;
    case to_underlying(MessageType::InvokeCommandRequest):
        return kInvokeCommandRequest;
    case to_underlying(MessageType::InvokeCommandResponse):
        return kInvokeCommandResponse;
    case to_underlying(MessageType::TimedRequest):
        return kTimedRequest;
    default:
        return kUnknown;
    }
}

CHIP_ERROR LogAsProtocolMessage(uint8_t protocolCode, const uint8_t * data, size_t len)
{
    TLV::TLVReader reader;
    reader.Init(data, len);

    switch (protocolCode)
    {
    case to_underlying(MessageType::StatusResponse):
        return DecodeStatusResponse(reader);
    case to_underlying(MessageType::ReadRequest):
        return DecodeReadRequest(reader);
    case to_underlying(MessageType::SubscribeRequest):
        return DecodeSubscribeRequest(reader);
    case to_underlying(MessageType::SubscribeResponse):
        return DecodeSubscribeResponse(reader);
    case to_underlying(MessageType::ReportData):
        return DecodeReportData(reader);
    case to_underlying(MessageType::WriteRequest):
        return DecodeWriteRequest(reader);
    case to_underlying(MessageType::WriteResponse):
        return DecodeWriteResponse(reader);
    case to_underlying(MessageType::InvokeCommandRequest):
        return DecodeInvokeCommandRequest(reader);
    case to_underlying(MessageType::InvokeCommandResponse):
        return DecodeInvokeCommandResponse(reader);
    case to_underlying(MessageType::TimedRequest):
        return DecodeTimedRequest(reader);
    default:
        return CHIP_ERROR_NOT_IMPLEMENTED;
    }
}

CHIP_ERROR DecodeStatusResponse(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::InvokeRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeReadRequest(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::ReadRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeSubscribeRequest(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::SubscribeRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeSubscribeResponse(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::SubscribeResponseMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeReportData(TLV::TLVReader & reader)
{
    ReturnErrorOnFailure(MaybeDecodeNestedReadResponse(reader.GetReadPoint(), reader.GetTotalLength()));

#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::ReportDataMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeWriteRequest(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::WriteRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeWriteResponse(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::WriteResponseMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeInvokeCommandRequest(TLV::TLVReader & reader)
{
    ReturnErrorOnFailure(MaybeDecodeNestedCommandRequest(reader.GetReadPoint(), reader.GetTotalLength()));

#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::InvokeRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeInvokeCommandResponse(TLV::TLVReader & reader)
{
    ReturnErrorOnFailure(MaybeDecodeNestedCommandResponse(reader.GetReadPoint(), reader.GetTotalLength()));

#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::InvokeResponseMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

CHIP_ERROR DecodeTimedRequest(TLV::TLVReader & reader)
{
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
    app::TimedRequestMessage::Parser parser;
    ReturnErrorOnFailure(parser.Init(reader));
    return parser.CheckSchemaValidity();
#else
    return CHIP_NO_ERROR;
#endif
}

} // namespace interaction_model
} // namespace trace
} // namespace chip
