/*
 *
 *    Copyright (c) 2021-2023 Project CHIP Authors
 *    All rights reserved.
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

#include <lib/core/CHIPConfig.h>

#include <app-common/zap-generated/cluster-objects.h>
#include <app/CommandHandlerInterface.h>
#include <app/clusters/diagnostic-logs-server/diagnostic-logs-provider-delegate.h>

namespace chip {
namespace app {
namespace Clusters {
namespace DiagnosticLogs {

// Spec mandated max file designator length
static constexpr uint8_t kMaxFileDesignatorLen = 32;

// Spec mandated max size of the log content field in the Response paylod
static constexpr uint16_t kMaxLogContentSize = 1024;

/// A reference implementation for DiagnosticLogs source.
class DiagnosticLogsServer
{
public:
    static DiagnosticLogsServer & Instance();

    /**
     * Set the default delegate of the diagnostic logs cluster for the specified endpoint
     *
     * @param endpoint ID of the endpoint
     *
     * @param delegate The log provider delegate at the endpoint
     */
    void SetLogProviderDelegate(EndpointId endpoint, LogProviderDelegate * delegate);

    /**
     * Handles the request to download diagnostic logs of type specified in the intent argument for protocol type ResponsePayload
     * This should return whatever fits in the logContent field of the RetrieveLogsResponse command
     *
     * @param commandHandler The command handler object from the RetrieveLogsRequest command
     *
     * @param path The command path from the RetrieveLogsRequest command
     *
     * @param intent The log type requested in the RetrieveLogsRequest command
     *
     */
    void HandleLogRequestForResponsePayload(CommandHandler * commandHandler, ConcreteCommandPath path, IntentEnum intent);

private:
    LogSessionHandle mLogSessionHandle;

    CommandHandler::Handle mAsyncCommandHandle;
    ConcreteCommandPath mRequestPath = ConcreteCommandPath(0, 0, 0);
    IntentEnum mIntent;

    static DiagnosticLogsServer sInstance;
};

} // namespace DiagnosticLogs
} // namespace Clusters
} // namespace app
} // namespace chip
