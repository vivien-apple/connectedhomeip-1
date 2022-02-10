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

#include "CommissionerCommands.h"

constexpr uint16_t kPayloadMaxSize = 64;

CHIP_ERROR CommissionerCommands::PairWithQRCode(chip::NodeId nodeId, const chip::CharSpan payload)
{
    VerifyOrReturnError(payload.size > 0 && payload.size() < kPayloadMaxSize, CHIP_ERROR_INVALID_ARGUMENT);

    GetCurrentCommissioner().RegisterPairingDelegate(this);

    char qrCode[kPayloadMaxSize];
    memcpy(qrCode, payload.data(), payload.size());
    return GetCurrentCommissioner().PairDevice(nodeId, qrCode);
}

CHIP_ERROR CommissionerCommands::PairWithManualCode(chip::NodeId nodeId, const chip::CharSpan payload)
{
    VerifyOrReturnError(payload.size > 0 && payload.size() < kPayloadMaxSize, CHIP_ERROR_INVALID_ARGUMENT);

    GetCurrentCommissioner().RegisterPairingDelegate(this);

    char manualCode[kPayloadMaxSize];
    memcpy(manualCode, payload.data(), payload.size());
    return GetCurrentCommissioner().PairDevice(nodeId, manualCode);
}

void CommissionerCommands::OnStatusUpdate(DevicePairingDelegate::Status status)
{
    switch (status)
    {
    case DevicePairingDelegate::Status::SecurePairingSuccess:
        ChipLogProgress(chipTool, "Secure Pairing Success");
        break;
    case DevicePairingDelegate::Status::SecurePairingFailed:
        ChipLogError(chipTool, "Secure Pairing Failed");
        break;
    }
}

void CommissionerCommands::OnPairingComplete(CHIP_ERROR err)
{
    if (err == CHIP_NO_ERROR)
    {
        ChipLogProgress(chipTool, "Pairing Success");
    }
    else
    {
        ChipLogProgress(chipTool, "Pairing Failure: %s", ErrorStr(err));
    }

    if (err != CHIP_NO_ERROR)
    {
        // SetCommandExitStatus(err);
    }
}

void CommissionerCommands::OnPairingDeleted(CHIP_ERROR err)
{
    if (err == CHIP_NO_ERROR)
    {
        ChipLogProgress(chipTool, "Pairing Deleted Success");
    }
    else
    {
        ChipLogProgress(chipTool, "Pairing Deleted Failure: %s", ErrorStr(err));
    }

    // SetCommandExitStatus(err);
}

void CommissionerCommands::OnCommissioningComplete(chip::NodeId nodeId, CHIP_ERROR err)
{
    if (err == CHIP_NO_ERROR)
    {
        ChipLogProgress(chipTool, "Device commissioning completed with success");
    }
    else
    {
        ChipLogProgress(chipTool, "Device commissioning Failure: %s", ErrorStr(err));
    }

    // SetCommandExitStatus(err);
    ContinueOnChipMainThread();
}
