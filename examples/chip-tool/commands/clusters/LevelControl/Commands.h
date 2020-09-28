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

#ifndef __CHIPTOOL_LEVELCONTROL_COMMANDS_H__
#define __CHIPTOOL_LEVELCONTROL_COMMANDS_H__

#include "../../common/ModelCommand.h"

class MoveToLevel : public ModelCommand
{
public:
    MoveToLevel(const uint16_t clusterId) : ModelCommand("move-to-level", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t level           = 50;
        uint16_t transitionTime = 100;
        uint8_t optionMask      = 0;
        uint8_t optionOverride  = 0;
        return encodeMoveToLevelCommand(buffer->Start(), bufferSize, endPointId, level, transitionTime, optionMask, optionOverride);
    }
};

class Move : public ModelCommand
{
public:
    Move(const uint16_t clusterId) : ModelCommand("move", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t moveMode       = 4;
        uint8_t rate           = 50;
        uint8_t optionMask     = 0;
        uint8_t optionOverride = 0;
        return encodeMoveCommand(buffer->Start(), bufferSize, endPointId, moveMode, rate, optionMask, optionOverride);
    }
};

class Step : public ModelCommand
{
public:
    Step(const uint16_t clusterId) : ModelCommand("step", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t stepMode        = 4;
        uint8_t stepSize        = 50;
        uint16_t transitionTime = 100;
        uint8_t optionMask      = 0;
        uint8_t optionOverride  = 0;
        return encodeStepCommand(buffer->Start(), bufferSize, endPointId, stepMode, stepSize, transitionTime, optionMask,
                                 optionOverride);
    }
};

class Stop : public ModelCommand
{
public:
    Stop(const uint16_t clusterId) : ModelCommand("stop", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t optionMask     = 0;
        uint8_t optionOverride = 0;
        return encodeStopCommand(buffer->Start(), bufferSize, endPointId, optionMask, optionOverride);
    }
};

class MoveToLevelWithOnOff : public ModelCommand
{
public:
    MoveToLevelWithOnOff(const uint16_t clusterId) : ModelCommand("move-to-level-with-onoff", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t level           = 50;
        uint16_t transitionTime = 100;
        return encodeMoveToLevelWithOnOffCommand(buffer->Start(), bufferSize, endPointId, level, transitionTime);
    }
};

class MoveWithOnOff : public ModelCommand
{
public:
    MoveWithOnOff(const uint16_t clusterId) : ModelCommand("move-with-onoff", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t moveMode = 4;
        uint8_t moveRate = 50;
        return encodeMoveWithOnOffCommand(buffer->Start(), bufferSize, endPointId, moveMode, moveRate);
    }
};

class StepWithOnOff : public ModelCommand
{
public:
    StepWithOnOff(const uint16_t clusterId) : ModelCommand("step-with-onoff", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        uint8_t stepMode        = 4;
        uint8_t stepSize        = 50;
        uint16_t transitionTime = 100;
        return encodeStepWithOnOffCommand(buffer->Start(), bufferSize, endPointId, stepMode, stepSize, transitionTime);
    }
};

class StopWithOnOff : public ModelCommand
{
public:
    StopWithOnOff(const uint16_t clusterId) : ModelCommand("stop-with-onoff", clusterId) {}

    size_t EncodeCommand(PacketBuffer * buffer, size_t bufferSize, uint16_t endPointId) override
    {
        return encodeStopWithOnOffCommand(buffer->Start(), bufferSize, endPointId);
    }
};

void registerClusterLevelControl(Commands & commands)
{
    const uint16_t clusterId = 0x0008;

    commands.Register(make_unique<MoveToLevel>(clusterId));
    commands.Register(make_unique<Move>(clusterId));
    commands.Register(make_unique<Step>(clusterId));
    commands.Register(make_unique<Stop>(clusterId));
    commands.Register(make_unique<MoveToLevelWithOnOff>(clusterId));
    commands.Register(make_unique<MoveWithOnOff>(clusterId));
    commands.Register(make_unique<StepWithOnOff>(clusterId));
    commands.Register(make_unique<StopWithOnOff>(clusterId));
}

#endif // __CHIPTOOL_LEVELCONTROL_COMMANDS_H__
