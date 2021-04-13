/*
 *   Copyright (c) 2020 Project CHIP Authors
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

#include "ModelCommand.h"

#include <inttypes.h>

using namespace ::chip;

namespace {
constexpr uint16_t kWaitDurationInSeconds = 10;
} // namespace

CHIP_ERROR ModelCommand::Run(PersistentStorage & storage, NodeId localId, NodeId remoteId)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = mCommissioner.SetUdpListenPort(storage.GetListenPort());
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(Controller, "Init failure! Commissioner: %s", ErrorStr(err)));

    err = mCommissioner.Init(localId, &storage);
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(Controller, "Init failure! Commissioner: %s", ErrorStr(err)));

    err = mCommissioner.ServiceEvents();
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(Controller, "Init failure! Run Loop: %s", ErrorStr(err)));

    err = mCommissioner.GetDevice(remoteId, &mDevice);
    VerifyOrExit(err == CHIP_NO_ERROR, ChipLogError(chipTool, "Init failure! No pairing for device: %" PRIu64, localId));

    mRemoteId = remoteId;
    err       = UpdateNetworkAddress(remoteId, 0);

    UpdateWaitForResponse(true);
    WaitForResponse(kWaitDurationInSeconds);

    VerifyOrExit(GetCommandExitStatus(), err = CHIP_ERROR_INTERNAL);

exit:
    mCommissioner.ServiceEventSignal();
    mCommissioner.Shutdown();
    return err;
}

CHIP_ERROR ModelCommand::UpdateNetworkAddress(NodeId remoteId, uint64_t fabricId)
{
    ReturnErrorOnFailure(mAddressUpdater.Init(&mCommissioner, this));
    ReturnErrorOnFailure(Mdns::Resolver::Instance().SetResolverDelegate(&mAddressUpdater));
    return Mdns::Resolver::Instance().ResolveNodeId(remoteId, fabricId, Inet::kIPAddressType_Any);
}

void ModelCommand::OnAddressUpdateComplete(NodeId nodeId, CHIP_ERROR err)
{
    if (CHIP_NO_ERROR != err)
    {
        ChipLogError(chipTool, "Failed to update the device address: %s", ErrorStr(err));
        SetCommandExitStatus(false);
        return;
    }

    err = mCommissioner.GetDevice(mRemoteId, &mDevice);
    if (CHIP_NO_ERROR != err)
    {
        ChipLogError(chipTool, "Failed to retrieve the device: %" PRIu64, mRemoteId);
        SetCommandExitStatus(false);
        return;
    }

    err = SendCommand(mDevice, mEndPointId);
    if (CHIP_NO_ERROR != err)
    {
        ChipLogError(chipTool, "Failed to send message: %s", ErrorStr(err));
        SetCommandExitStatus(false);
        return;
    }
}
