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

#include "TestCommand.h"

CHIP_ERROR TestCommand::RunCommand()
{
    if (mPICSFilePath.HasValue())
    {
        PICS.SetValue(PICSBooleanReader::Read(mPICSFilePath.Value()));
    }

    NextTest();

    return CHIP_NO_ERROR;
}

CHIP_ERROR TestCommand::WaitForCommissionee()
{
    return CurrentCommissioner().GetConnectedDevice(mNodeId, &mOnDeviceConnectedCallback, &mOnDeviceConnectionFailureCallback);
}

void TestCommand::OnDeviceConnectedFn(void * context, chip::OperationalDeviceProxy * device)
{
    ChipLogProgress(chipTool, " **** Test Setup: Device Connected\n");
    auto * command = static_cast<TestCommand *>(context);
    VerifyOrReturn(command != nullptr, ChipLogError(chipTool, "Device connected, but cannot run the test, as the context is null"));
    command->mDevices[command->GetIdentity()] = device;

    command->NextTest();
}

void TestCommand::OnDeviceConnectionFailureFn(void * context, PeerId peerId, CHIP_ERROR error)
{
    ChipLogProgress(chipTool, " **** Test Setup: Device Connection Failure [deviceId=%" PRIu64 ". Error %" CHIP_ERROR_FORMAT "\n]",
                    peerId.GetNodeId(), error.Format());
    auto * command = static_cast<TestCommand *>(context);
    VerifyOrReturn(command != nullptr, ChipLogError(chipTool, "Test command context is null"));
    command->SetCommandExitStatus(error);
}

void TestCommand::OnWaitForMsFn(chip::System::Layer * systemLayer, void * context)
{
    auto * command = static_cast<TestCommand *>(context);
    command->NextTest();
}

CHIP_ERROR TestCommand::Wait(chip::System::Clock::Timeout duration)
{
    return chip::DeviceLayer::SystemLayer().StartTimer(duration, OnWaitForMsFn, this);
}

CHIP_ERROR TestCommand::Log(const char * message)
{
    ChipLogDetail(chipTool, "%s", message);
    ReturnErrorOnFailure(ContinueOnChipMainThread());
    return CHIP_NO_ERROR;
}

CHIP_ERROR TestCommand::UserPrompt(const char * message)
{
    ChipLogDetail(chipTool, "USER_PROMPT: %s", message);
    ReturnErrorOnFailure(ContinueOnChipMainThread());
    return CHIP_NO_ERROR;
}

void TestCommand::Exit(std::string message)
{
    ChipLogError(chipTool, " ***** Test Failure: %s\n", message.c_str());
    SetCommandExitStatus(CHIP_ERROR_INTERNAL);
}

void TestCommand::ThrowFailureResponse()
{
    Exit("Expecting success response but got a failure response");
}

void TestCommand::ThrowSuccessResponse()
{
    Exit("Expecting failure response but got a success response");
}

bool TestCommand::ShouldSkip(const char * expression)
{
    // If there is no PICS configuration file, considers that nothing should be skipped.
    if (!PICS.HasValue())
    {
        return false;
    }

    std::map<std::string, bool> pics(PICS.Value());
    bool shouldSkip = !PICSBooleanExpressionParser::Eval(expression, pics);
    if (shouldSkip)
    {
        ChipLogProgress(chipTool, " **** Skipping: %s == false\n", expression);
        ContinueOnChipMainThread();
    }
    return shouldSkip;
}
