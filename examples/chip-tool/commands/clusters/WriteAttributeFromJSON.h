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

#include <app-common/zap-generated/cluster-objects.h>

class JSONAttributeWriter
{
public:
    JSONAttributeWriter(ModelCommand * command) : mCommand(command) {}

    CHIP_ERROR WriteAttribute(chip::OperationalDeviceProxy * device, chip::EndpointId endpointId, chip::ClusterId clusterId,
                              chip::AttributeId attributeId, Json::Value & value);

private:
    ModelCommand * mCommand;
};

class WriteAttributeFromJSON : public ModelCommand
{
public:
    WriteAttributeFromJSON() : ModelCommand("write-by-id"), mWriter(this)
    {
        AddArgument("cluster-id", 0, UINT32_MAX, &mClusterId);
        AddArgument("attribute-id", 0, UINT32_MAX, &mAttributeId);
        AddArgument("attribute-value", &mJSON);
        ModelCommand::AddArguments();
    }

    WriteAttributeFromJSON(chip::ClusterId clusterId) : ModelCommand("write-by-id"), mClusterId(clusterId), mWriter(this)
    {
        AddArgument("attribute-id", 0, UINT32_MAX, &mAttributeId);
        AddArgument("attribute-value", &mJSON);
        ModelCommand::AddArguments();
    }

    WriteAttributeFromJSON(chip::ClusterId clusterId, const char * attributeName, chip::AttributeId attributeId) :
        ModelCommand("write"), mClusterId(clusterId), mAttributeId(attributeId), mWriter(this)
    {
        AddArgument("attr-name", attributeName);
        AddArgument("attribute-value", &mJSON);
        ModelCommand::AddArguments();
    }

    ~WriteAttributeFromJSON() {}

    CHIP_ERROR SendCommand(ChipDevice * device, chip::EndpointId endpointId) override
    {
        return mWriter.WriteAttribute(device, endpointId, mClusterId, mAttributeId, mJSON);
    }

private:
    chip::ClusterId mClusterId;
    chip::AttributeId mAttributeId;

    JSONAttributeWriter mWriter;
    Json::Value mJSON;
};
