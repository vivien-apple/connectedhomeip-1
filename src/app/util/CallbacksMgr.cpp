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
 *    This file contains impletations for the CallbacksMgr class. The object of this
 *    class will be used by Controller applications to interact with ZCL messages.
 *    This class provide mechanism to store callbacks for global message dispatching
 *    across the ZCL stack.
 */

#include "CallbacksMgr.h"

#include <core/CHIPCore.h>
#include <inttypes.h>
#include <support/CodeUtils.h>

namespace chip {
namespace app {

CHIP_ERROR CHIPCallbacksMgr::AddResponseCallback(NodeId nodeId, uint8_t sequenceNumber, Callback::Cancelable * onSuccessCallback,
                                                 Callback::Cancelable * onFailureCallback)
{
    // XXX mInfoScalar is a uint64_t which is not enough to store our discriminator (nodeId (uint64_t) + sequenceNumber (uint8_t))

    if (onSuccessCallback != nullptr)
    {
        onSuccessCallback->mInfoScalar = nodeId;
        mResponsesSuccess.Enqueue(onSuccessCallback);
    }

    if (onFailureCallback != nullptr)
    {
        onFailureCallback->mInfoScalar = nodeId;
        mResponsesFailure.Enqueue(onFailureCallback);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPCallbacksMgr::GetResponseCallback(NodeId nodeId, uint8_t sequenceNumber, Callback::Cancelable ** onSuccessCallback,
                                                 Callback::Cancelable ** onFailureCallback)
{
    Callback::Cancelable * ca;

    ca = &mResponsesSuccess;
    while (ca->mNext != &mResponsesSuccess)
    {
        if (ca->mNext != nullptr && ca->mNext->mInfoScalar == nodeId)
        {
            *onSuccessCallback = ca->mNext->Cancel();
            break;
        }

        ca = ca->mNext;
    }

    ca = &mResponsesFailure;
    while (ca->mNext != &mResponsesFailure)
    {
        if (ca->mNext != nullptr && ca->mNext->mInfoScalar == nodeId)
        {
            *onFailureCallback = ca->mNext->Cancel();
            break;
        }

        ca = ca->mNext;
    }

    if (*onSuccessCallback != nullptr && *onFailureCallback != nullptr)
    {
        return CHIP_NO_ERROR;
    }

    return CHIP_ERROR_KEY_NOT_FOUND;
}

CHIP_ERROR CHIPCallbacksMgr::AddReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId, AttributeId attributeId,
                                               Callback::Cancelable * onReportCallback)
{
    // XXX mInfoScalar is a uint64_t which is not enough to store our discriminator (nodeId (uint64_t) + endpointId (uint8_t) +
    // clusterId (uint16_t) + attributeId (uint16_t))

    if (onReportCallback != nullptr)
    {
        onReportCallback->mInfoScalar = nodeId;
        mReports.Enqueue(onReportCallback);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR CHIPCallbacksMgr::GetReportCallback(NodeId nodeId, EndpointId endpointId, ClusterId clusterId, AttributeId attributeId,
                                               Callback::Cancelable ** onReportCallback)
{
    Callback::Cancelable * ca = &mReports;
    while (ca->mNext != &mReports)
    {
        if (ca->mNext != nullptr && ca->mNext->mInfoScalar == nodeId)
        {
            *onReportCallback = ca->mNext;
            return CHIP_NO_ERROR;
        }

        ca = ca->mNext;
    }

    return CHIP_ERROR_KEY_NOT_FOUND;
}

} // namespace app
} // namespace chip
