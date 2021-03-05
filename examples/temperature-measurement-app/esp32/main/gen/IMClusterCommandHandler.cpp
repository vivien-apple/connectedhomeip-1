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

#include <cinttypes>
#include <cstdint>

#include "af-structs.h"
#include "call-command-handler.h"
#include "callback.h"
#include "cluster-id.h"
#include "command-id.h"
#include "util.h"

#include <app/InteractionModelEngine.h>

// Currently we need some work to keep compatible with ember lib.
#include <util/ember-compatibility-functions.h>

namespace chip {
namespace app {

// Cluster specific command parsing

namespace clusters {

} // namespace clusters

void DispatchSingleClusterCommand(chip::ClusterId aClusterId, chip::CommandId aCommandId, chip::EndpointId aEndPointId,
                                  chip::TLV::TLVReader & aReader, Command * apCommandObj)
{
    ChipLogDetail(Zcl, "Received Cluster Command: Cluster=%" PRIx16 " Command=%" PRIx8 " Endpoint=%" PRIx8, aClusterId, aCommandId,
                  aEndPointId);
    Compatibility::SetupEmberAfObjects(apCommandObj, aClusterId, aCommandId, aEndPointId);
    switch (aClusterId)
    {
    default:
        // Unrecognized cluster ID, error status will apply.
        // TODO: Encode response for Cluster not found
        ChipLogError(Zcl, "Unknown cluster %" PRIx16, aClusterId);
        break;
    }
    Compatibility::ResetEmberAfObjects();
}

} // namespace app
} // namespace chip
