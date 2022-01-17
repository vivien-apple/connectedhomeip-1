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

class ReadAttribute : public ModelCommand
{
public:
    ReadAttribute(chip::ClusterId clusterId, const char * attributeName, chip::AttributeId attributeId) :
        ModelCommand("read"), mClusterId(clusterId), mAttributeId(attributeId)
    {
        AddArgument("attr-name", attributeName);
        ModelCommand::AddArguments();
    }

    ~ReadAttribute() {}

    CHIP_ERROR SendCommand(ChipDevice * device, chip::EndpointId endpointId) override
    {
        return ModelCommand::ReadAttribute(device, endpointId, mClusterId, mAttributeId);
    }

private:
    chip::ClusterId mClusterId;
    chip::AttributeId mAttributeId;
};
