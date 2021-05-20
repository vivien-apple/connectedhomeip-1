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
 *    This file contains implementations for the CallbacksMgr class. The object of this
 *    class will be used by Controller applications to interact with ZCL messages.
 *    This class provide mechanism to store callbacks for global message dispatching
 *    across the ZCL stack.
 */

#include "CHIPDeviceCallbacksMgr.h"

#include <core/CHIPCore.h>
#include <inttypes.h>

namespace {

} // namespace

namespace chip {
namespace app {

CHIP_ERROR CHIPDeviceCallbacksMgr::AddResponseCallback(NodeId nodeId, uint8_t sequenceNumber,
                                                       Callback::Cancelable * onSuccessCallback,
                                                       Callback::Cancelable * onFailureCallback)
{
    VerifyOrReturnError(onSuccessCallback != nullptr, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(onFailureCallback != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    ResponseCallbackInfo info{ nodeId, sequenceNumber };

    // If some callbacks have already been registered for the same ResponseCallbackInfo, it usually means that the response
    // has not been received for a previous command with the same sequenceNumber. Cancel the previously registered callbacks.
    mResponsesSuccess.CancelCallback(info);
    mResponsesFailure.CancelCallback(info);

#if 0
    onSuccessCallback->mInfoPtr = CHIPPlatformMemoryAlloc(sizeof(info));
    if (onSuccessCallback->mInfoPtr == nullptr)
    {
        return CHIP_ERROR_NO_MEMORY;
    }

    onFailureCallback->mInfoPtr = CHIPPlatformMemoryAlloc(sizeof(info));
    if (onFailureCallback->mInfoPtr == nullptr)
    {
        CHIPPlatformMemoryFree(onSuccessCallback->mInfoPtr);
        return CHIP_ERROR_NO_MEMORY;
    }
#endif

    /* TODO CHECK ERROR HERE */ mResponsesSuccess.Enqueue(onSuccessCallback, info);
    /* TODO CHECK ERROR HERE */ mResponsesFailure.Enqueue(onFailureCallback, info);
    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPDeviceCallbacksMgr::CancelResponseCallback(NodeId nodeId, uint8_t sequenceNumber)
{
    ResponseCallbackInfo info{ nodeId, sequenceNumber };
    mResponsesSuccess.CancelCallback(info);
    mResponsesFailure.CancelCallback(info);
    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPDeviceCallbacksMgr::GetResponseCallback(NodeId nodeId, uint8_t sequenceNumber,
                                                       Callback::Cancelable ** onSuccessCallback,
                                                       Callback::Cancelable ** onFailureCallback)
{
    ResponseCallbackInfo info{ nodeId, sequenceNumber };

    ReturnErrorOnFailure(mResponsesSuccess.GetCallback(info, onSuccessCallback));
    mResponsesSuccess.CancelCallback(info);

    // TODO: WARNING: This leaks the callback if the above failed
    ReturnErrorOnFailure(mResponsesFailure.GetCallback(info, onFailureCallback));
    mResponsesFailure.CancelCallback(info);

    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPDeviceCallbacksMgr::AddReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId,
                                                     AttributeId attributeId, Callback::Cancelable * onReportCallback)
{
    VerifyOrReturnError(onReportCallback != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    ReportCallbackInfo info{ nodeId, endpointId, clusterId, attributeId };

    // If a callback has already been registered for the same ReportCallbackInfo, let's cancel it.
    mReports.CancelCallback(info);

    /* TODO CHECK ERROR HERE */ mReports.Enqueue(onReportCallback, info);
    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPDeviceCallbacksMgr::GetReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId,
                                                     AttributeId attributeId, Callback::Cancelable ** onReportCallback)
{
    ReportCallbackInfo info{ nodeId, endpointId, clusterId, attributeId };

    ReturnErrorOnFailure(mReports.GetCallback(info, onReportCallback));

    return CHIP_NO_ERROR;
}

} // namespace app
} // namespace chip
