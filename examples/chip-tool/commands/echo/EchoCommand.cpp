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

#include "EchoCommand.h"

using namespace ::chip;

namespace {
static const char PAYLOAD[] = "Message from Standalone CHIP echo client!";

bool IsIdenticalMessage(uint8_t * msgBuf, uint16_t msgLen)
{
    return (msgLen + 1 == sizeof PAYLOAD) && (memcmp(msgBuf, PAYLOAD, msgLen) == 0);
}
} // namespace

uint16_t EchoCommand::Encode(PacketBufferHandle & buffer, uint16_t bufferSize)
{
    uint16_t payloadLen = 0;

    if (strlen(PAYLOAD) > bufferSize)
    {
        ChipLogError(chipTool, "PAYLOAD length too big for PacketBuffer (> bufferSize)");
    }
    else
    {
        payloadLen = static_cast<uint16_t>(strlen(PAYLOAD));
        memcpy(buffer->Start(), PAYLOAD, payloadLen);
    }

    return payloadLen;
}

bool EchoCommand::Decode(uint8_t * msgBuf, uint16_t msgLen, uint8_t frameControl, uint8_t commandId) const
{
    bool success = IsIdenticalMessage(msgBuf, msgLen);

    if (!success)
    {
        ChipLogError(chipTool, "Echo: Error \nSend: %s \nRecv: %.*s", PAYLOAD, msgLen, msgBuf);
    }

    return success;
}
