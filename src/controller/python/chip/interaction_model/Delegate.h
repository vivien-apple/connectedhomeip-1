/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <type_traits>

#include <app/InteractionModelDelegate.h>
#include <controller/CHIPDeviceController.h>

namespace chip {
namespace python {
static constexpr ClusterStatus kUndefinedClusterStatus = 0xFF;
}
namespace Controller {

struct __attribute__((packed)) AttributePath
{
    chip::EndpointId endpointId;
    chip::ClusterId clusterId;
    chip::FieldId fieldId;
};

static_assert(std::is_same<chip::EndpointId, uint16_t>::value && std::is_same<chip::ClusterId, uint32_t>::value &&
                  std::is_same<chip::FieldId, uint32_t>::value,
              "Members in AttributePath does not match interaction_model/delegate.py");
static_assert(sizeof(AttributePath) == 2 + 4 + 4, "AttributePath might contain padding");

struct __attribute__((packed)) AttributeWriteStatus
{
    chip::NodeId nodeId;
    uint64_t appIdentifier;
    Protocols::InteractionModel::Status status;
    chip::EndpointId endpointId;
    chip::ClusterId clusterId;
    chip::FieldId fieldId;
};
static_assert(std::is_same<chip::EndpointId, uint16_t>::value && std::is_same<chip::ClusterId, uint32_t>::value &&
                  std::is_same<chip::FieldId, uint32_t>::value,
              "Members in AttributeWriteStatus does not match interaction_model/delegate.py");
static_assert(sizeof(AttributeWriteStatus) == 8 + 8 + 2 + 2 + 4 + 4, "Size of AttributeWriteStatus might contain padding");

} // namespace Controller
} // namespace chip
