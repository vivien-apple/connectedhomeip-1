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

class ReportAttribute : public ModelCommand
{
public:
    ReportAttribute(chip::ClusterId clusterId, const char * attributeName, chip::AttributeId attributeId) :
        ModelCommand("report"), mClusterId(clusterId), mAttributeId(attributeId)
    {
        AddArgument("attr-name", attributeName);
        AddArgument("min-interval", 0, UINT16_MAX, &mMinInterval);
        AddArgument("max-interval", 0, UINT16_MAX, &mMaxInterval);
        AddArgument("wait", 0, 1, &mWait);
        ModelCommand::AddArguments();
    }

    ~ReportAttribute() {}

    CHIP_ERROR SendCommand(ChipDevice * device, chip::EndpointId endpointId) override
    {
        return ModelCommand::SubscribeAttribute(device, endpointId, mClusterId, mAttributeId, mMinInterval, mMaxInterval);
    }

    chip::System::Clock::Timeout GetWaitDuration() const override
    {
        return chip::System::Clock::Seconds16(mWait ? UINT16_MAX : 10);
    }

    void OnAttributeSubscription() override
    {
        if (!mWait)
        {
            SetCommandExitStatus(CHIP_NO_ERROR);
        }
    }

private:
    chip::ClusterId mClusterId;
    chip::AttributeId mAttributeId;

    uint16_t mMinInterval;
    uint16_t mMaxInterval;
    bool mWait;
};
