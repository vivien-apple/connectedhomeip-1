/*
 *   Copyright (c) 2021 Project CHIP Authors
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

#include "DiscoverCommand.h"

#include <commands/common/DeviceScanner.h>

CHIP_ERROR DiscoverCommand::RunCommand()
{
    return RunCommand(mNodeId, mFabricId);
}

CHIP_ERROR DiscoverStopCommand::RunCommand()
{
#if CHIP_DEVICE_LAYER_TARGET_DARWIN
    VerifyOrReturnError(IsInteractive(), CHIP_ERROR_INCORRECT_STATE);
    ReturnErrorOnFailure(GetDeviceScanner().Stop());

    SetCommandExitStatus(CHIP_NO_ERROR);
    return CHIP_NO_ERROR;
#else
    return CHIP_ERROR_NOT_IMPLEMENTED;
#endif // CHIP_DEVICE_LAYER_TARGET_DARWIN
}

CHIP_ERROR DiscoverListCommand::RunCommand()
{
#if CHIP_DEVICE_LAYER_TARGET_DARWIN
    VerifyOrReturnError(IsInteractive(), CHIP_ERROR_INCORRECT_STATE);
    GetDeviceScanner().Log();

    SetCommandExitStatus(CHIP_NO_ERROR);
    return CHIP_NO_ERROR;
#else
    return CHIP_ERROR_NOT_IMPLEMENTED;
#endif // CHIP_DEVICE_LAYER_TARGET_DARWIN
}
