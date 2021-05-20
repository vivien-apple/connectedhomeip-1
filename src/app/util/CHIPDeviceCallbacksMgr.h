/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
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

/**
 * @file
 *    This file contains definitions for the CallbacksMgr class. The object of this
 *    class will be used by Controller applications to interact with ZCL messages.
 *    This class provide mechanism to store callbacks for global message dispatching
 *    across the ZCL stack.
 */

#pragma once

#include <app/util/basic-types.h>
#include <core/CHIPCallback.h>
#include <core/CHIPError.h>
#include <support/CHIPPlatformMemory.h>
#include <support/DLLUtil.h>

namespace chip {
namespace app {

struct ResponseCallbackInfo
{
    chip::NodeId nodeId;
    uint8_t sequenceNumber;

    explicit ResponseCallbackInfo(chip::NodeId nodeId, uint8_t sequenceNumber):
      nodeId(nodeId), sequenceNumber(sequenceNumber) {}

    bool operator==(ResponseCallbackInfo const & other) { return nodeId == other.nodeId && sequenceNumber == other.sequenceNumber; }
};

struct ReportCallbackInfo
{
    chip::NodeId nodeId;
    chip::EndpointId endpointId;
    chip::ClusterId clusterId;
    chip::AttributeId attributeId;

    explicit ReportCallbackInfo(chip::NodeId nodeId,
      chip::EndpointId endpointId,
      chip::ClusterId clusterId,
      chip::AttributeId attributeId):
      nodeId(nodeId), endpointId(endpointId), clusterId(clusterId), attributeId(attributeId) {}

    bool operator==(ReportCallbackInfo const & other)
    {
        return nodeId == other.nodeId && endpointId == other.endpointId && clusterId == other.clusterId &&
            attributeId == other.attributeId;
    }
};

template<typename T>
class CHIPDeviceCallbackDeque : protected Callback::CallbackDeque
{
public:
    // TODO: add destructor to clean up everything
    CHIPDeviceCallbackDeque() {}

    ~CHIPDeviceCallbackDeque()
    {
        // TODO: Clean-up whatever is remaining, freeing the mInfoPtr
    }

    CHIP_ERROR Enqueue(Cancelable * ca, const T & info)
    {
        ca->mInfoPtr = CHIPPlatformMemoryAlloc(sizeof(info));
        if (ca->mInfoPtr == nullptr)
        {
            return CHIP_ERROR_NO_MEMORY;
        }

        memcpy(ca->mInfoPtr, &info, sizeof(info));

        Callback::CallbackDeque::Enqueue(ca);
    }

    CHIP_ERROR CancelCallback(const T & info)
    {
        Callback::Cancelable * ca = nullptr;
        CHIP_ERROR err            = GetCallback(info, &ca);
        if (CHIP_NO_ERROR == err)
        {
            ca->Cancel();
            CHIPPlatformMemoryFree(ca->mInfoPtr);
            queue.Dequeue(ca);
        }

        return err;
    }

    template <typename T>
    CHIP_ERROR GetCallback(const T & info, Callback::Cancelable ** callback) const
    {
        auto * beginning_entry = this;

        Callback::Cancelable * ca = this;
        while (ca != nullptr && ca->mNext != beginning)
        {
            if (*reinterpret_cast<T *>(ca->mNext->mInfoPtr) == info)
            {
                *callback = ca->mNext;
                return CHIP_NO_ERROR;
            }

            ca = ca->mNext;
        }

        return CHIP_ERROR_KEY_NOT_FOUND;
    }
};

class DLL_EXPORT CHIPDeviceCallbacksMgr
{
public:
    CHIPDeviceCallbacksMgr(const CHIPDeviceCallbacksMgr &)  = delete;
    CHIPDeviceCallbacksMgr(const CHIPDeviceCallbacksMgr &&) = delete;
    CHIPDeviceCallbacksMgr & operator=(const CHIPDeviceCallbacksMgr &) = delete;

    static CHIPDeviceCallbacksMgr & GetInstance()
    {
        static CHIPDeviceCallbacksMgr instance;
        return instance;
    }

    CHIP_ERROR AddResponseCallback(NodeId nodeId, uint8_t sequenceNumber, Callback::Cancelable * onSuccessCallback,
                                   Callback::Cancelable * onFailureCallback);
    CHIP_ERROR CancelResponseCallback(NodeId nodeId, uint8_t sequenceNumber);
    CHIP_ERROR GetResponseCallback(NodeId nodeId, uint8_t sequenceNumber, Callback::Cancelable ** onSuccessCallback,
                                   Callback::Cancelable ** onFailureCallback);

    CHIP_ERROR AddReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId, AttributeId attributeId,
                                 Callback::Cancelable * onReportCallback);
    CHIP_ERROR GetReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId, AttributeId attributeId,
                                 Callback::Cancelable ** onReportCallback);

private:
    CHIPDeviceCallbacksMgr() {}

    CHIPDeviceCallbackDeque<ResponseCallbackInfo> mResponsesSuccess;
    CHIPDeviceCallbackDeque<ResponseCallbackInfo> mResponsesFailure;
    CHIPDeviceCallbackDeque<ReportCallbackInfo> mReports;
};

} // namespace app
} // namespace chip
