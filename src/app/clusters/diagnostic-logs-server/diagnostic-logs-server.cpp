/**
 *
 *    Copyright (c) 2021-2023 Project CHIP Authors
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

#include <lib/core/CHIPConfig.h>

#include "diagnostic-logs-server.h"

#include <app-common/zap-generated/cluster-objects.h>
#include <app/CommandHandler.h>
#include <app/CommandHandlerInterface.h>
#include <app/ConcreteCommandPath.h>
#include <app/InteractionModelEngine.h>
#include <app/util/config.h>
#include <lib/support/ScopedBuffer.h>
#include <messaging/ExchangeContext.h>
#include <messaging/ExchangeMgr.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters::DiagnosticLogs;
using chip::Protocols::InteractionModel::Status;

#ifdef EMBER_AF_DIAGNOSTIC_LOGS_CLUSTER_SERVER_ENDPOINT_COUNT
static constexpr size_t kDiagnosticLogsLogProviderDelegateTableSize =
    EMBER_AF_DIAGNOSTIC_LOGS_CLUSTER_SERVER_ENDPOINT_COUNT + CHIP_DEVICE_CONFIG_DYNAMIC_ENDPOINT_COUNT;
static_assert(kDiagnosticLogsLogProviderDelegateTableSize < kEmberInvalidEndpointIndex,
              "DiagnosticLogs: log provider delegate table size error");

namespace {

LogProviderDelegate * gLogProviderDelegateTable[kDiagnosticLogsLogProviderDelegateTableSize] = { nullptr };

LogProviderDelegate * GetLogProviderDelegate(EndpointId endpoint)
{
    uint16_t ep = emberAfGetClusterServerEndpointIndex(endpoint, Id, EMBER_AF_DIAGNOSTIC_LOGS_CLUSTER_SERVER_ENDPOINT_COUNT);
    return (ep >= kDiagnosticLogsLogProviderDelegateTableSize ? nullptr : gLogProviderDelegateTable[ep]);
}

bool IsLogProviderDelegateNull(LogProviderDelegate * logProviderDelegate, EndpointId endpoint)
{
    if (logProviderDelegate == nullptr)
    {
        ChipLogProgress(Zcl, "Diagnosticlogs: no log provider delegate set for endpoint:%u", endpoint);
        return true;
    }
    return false;
}

} // anonymous namespace

DiagnosticLogsServer DiagnosticLogsServer::sInstance;

void DiagnosticLogsServer::SetLogProviderDelegate(EndpointId endpoint, LogProviderDelegate * logProviderDelegate)
{
    uint16_t ep =
        emberAfGetClusterServerEndpointIndex(endpoint, DiagnosticLogs::Id, EMBER_AF_DIAGNOSTIC_LOGS_CLUSTER_SERVER_ENDPOINT_COUNT);
    if (ep < kDiagnosticLogsLogProviderDelegateTableSize)
    {
        gLogProviderDelegateTable[ep] = logProviderDelegate;
    }
}

DiagnosticLogsServer & DiagnosticLogsServer::Instance()
{
    return sInstance;
}

void DiagnosticLogsServer::HandleLogRequestForResponsePayload(CommandHandler * commandHandler, ConcreteCommandPath path,
                                                              IntentEnum intent)
{
    Commands::RetrieveLogsResponse::Type response;
    mIntent = intent;

    EndpointId endpoint                       = path.mEndpointId;
    LogProviderDelegate * logProviderDelegate = GetLogProviderDelegate(endpoint);

    if (IsLogProviderDelegateNull(logProviderDelegate, endpoint))
    {
        response.status = StatusEnum::kNoLogs;
        commandHandler->AddResponse(path, response);
        return;
    }

    Platform::ScopedMemoryBuffer<uint8_t> buffer;

    if (!buffer.Alloc(kMaxLogContentSize))
    {
        ChipLogError(Zcl, "buffer not allocated");
        response.status = StatusEnum::kNoLogs;
        commandHandler->AddResponse(path, response);
        return;
    }

    mLogSessionHandle = logProviderDelegate->StartLogCollection(intent);

    if (mLogSessionHandle == kInvalidLogSessionHandle)
    {
        response.status = StatusEnum::kNoLogs;
        commandHandler->AddResponse(path, response);
        return;
    }

    MutableByteSpan mutableBuffer;

    mutableBuffer = MutableByteSpan(buffer.Get(), kMaxLogContentSize);

    bool isEOF = false;

    // Get the log chunk of size up to kMaxLogContentSize to send in the response payload.
    CHIP_ERROR err = logProviderDelegate->GetNextChunk(mLogSessionHandle, mutableBuffer, isEOF);

    if (err != CHIP_NO_ERROR)
    {
        response.status = StatusEnum::kNoLogs;
        commandHandler->AddResponse(path, response);
        return;
    }

    response.logContent = ByteSpan(mutableBuffer.data(), mutableBuffer.size());
    response.status     = StatusEnum::kSuccess;
    commandHandler->AddResponse(path, response);

    logProviderDelegate->EndLogCollection(mLogSessionHandle);
    mLogSessionHandle = kInvalidLogSessionHandle;
}

static void HandleRetrieveLogRequest(CommandHandler * commandObj, const ConcreteCommandPath & commandPath,
                                     TransferProtocolEnum protocol, IntentEnum intent, Optional<CharSpan> transferFileDesignator)
{

    if (protocol == TransferProtocolEnum::kResponsePayload)
    {
        DiagnosticLogsServer::Instance().HandleLogRequestForResponsePayload(commandObj, commandPath, intent);
    }
    else
    {
        commandObj->AddStatus(commandPath, Protocols::InteractionModel::Status::InvalidCommand);
    }
}

bool emberAfDiagnosticLogsClusterRetrieveLogsRequestCallback(CommandHandler * commandObj, const ConcreteCommandPath & commandPath,
                                                             const Commands::RetrieveLogsRequest::DecodableType & commandData)
{
    if (commandData.requestedProtocol == TransferProtocolEnum::kUnknownEnumValue ||
        commandData.intent == IntentEnum::kUnknownEnumValue)
    {
        commandObj->AddStatus(commandPath, Protocols::InteractionModel::Status::InvalidCommand);
        return true;
    }
    HandleRetrieveLogRequest(commandObj, commandPath, commandData.requestedProtocol, commandData.intent,
                             commandData.transferFileDesignator);
    return true;
}

void MatterDiagnosticLogsPluginServerInitCallback() {}
#endif // #ifdef EMBER_AF_DIAGNOSTIC_LOGS_CLUSTER_SERVER_ENDPOINT_COUNT
