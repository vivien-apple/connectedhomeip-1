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

#pragma once

#include "../common/NetworkCommand.h"

class EchoCommand : public NetworkCommand
{
public:
    EchoCommand(const char * commandName) : NetworkCommand(commandName) {}

    /////////// NetworkCommand Interface /////////
    uint16_t Encode(PacketBufferHandle & buffer, uint16_t bufferSize) override;
    bool Decode(uint8_t * msgBuf, uint16_t msgLen, uint8_t frameControl, uint8_t commandId) const override;
};
