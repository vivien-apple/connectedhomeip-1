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

using namespace ::chip;

namespace {
constexpr uint8_t kZCLGlobalCmdFrameControlHeader  = 8;
constexpr uint8_t kZCLClusterCmdFrameControlHeader = 9;

bool isValidFrame(uint8_t frameControl)
{
    // Bit 3 of the frame control byte set means direction is server to client.
    return (frameControl == kZCLGlobalCmdFrameControlHeader || frameControl == kZCLClusterCmdFrameControlHeader);
}

bool isGlobalCommand(uint8_t frameControl)
{
    return (frameControl == kZCLGlobalCmdFrameControlHeader);
}
} // namespace

uint16_t ModelCommand::Encode(PacketBufferHandle & buffer, uint16_t bufferSize)
{
    ChipLogProgress(chipTool, "Endpoint id: '0x%02x', Cluster id: '0x%04x', Command id: '0x%02x'", mEndPointId, mClusterId,
                    mCommandId);

    return EncodeCommand(buffer, bufferSize, mEndPointId);
}

bool ModelCommand::Decode(uint8_t * msgBuf, uint16_t msgLen, uint8_t frameControl, uint8_t commandId) const
{
    if (!isValidFrame(frameControl))
    {
        ChipLogError(chipTool, "Unexpected frame control byte: 0x%02x", frameControl);
        return false;
    }

    return isGlobalCommand(frameControl) ? HandleGlobalResponse(commandId, msgBuf, msgLen)
                                         : HandleSpecificResponse(commandId, msgBuf, msgLen);
}
