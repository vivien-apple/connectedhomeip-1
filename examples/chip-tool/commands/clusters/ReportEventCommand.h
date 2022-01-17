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

#pragma once

#include "ModelCommand.h"

class ReportEvent : public ModelCommand
{
public:
    ReportEvent() : ModelCommand("report-event-by-id")
    {
        AddArgument("cluster-id", 0, UINT32_MAX, &mClusterId);
        AddArgument("event-id", 0, UINT32_MAX, &mEventId);
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("wait", 0, 1, &mWait);
        ModelCommand::AddArguments();
    }

    ReportEvent(chip::ClusterId clusterId) : ModelCommand("report-event-by-id"), mClusterId(clusterId)
    {
        AddArgument("event-id", 0, UINT32_MAX, &mEventId);
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("wait", 0, 1, &mWait);
        ModelCommand::AddArguments();
    }
    ReportEvent(chip::ClusterId clusterId, const char * eventName, chip::EventId eventId) :
        ModelCommand("report-event"), mClusterId(clusterId), mEventId(eventId)
    {
        AddArgument("attr-name", eventName);
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("wait", 0, 1, &mWait);
        ModelCommand::AddArguments();
    }

    ~ReportEvent() {}

    CHIP_ERROR SendCommand(ChipDevice * device, chip::EndpointId endpointId) override
    {
        return ModelCommand::SubscribeEvent(device, endpointId, mClusterId, mEventId, mMinInterval, mMaxInterval);
    }

    chip::System::Clock::Timeout GetWaitDuration() const override
    {
        return chip::System::Clock::Seconds16(mWait ? UINT16_MAX : 10);
    }

    void OnEventSubscription() override
    {
        if (!mWait)
        {
            SetCommandExitStatus(CHIP_NO_ERROR);
        }
    }

private:
    chip::ClusterId mClusterId;
    chip::EventId mEventId;

    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    bool mWait;
};
