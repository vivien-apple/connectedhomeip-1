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

#include "../../config/PersistentStorage.h"
#include "../common/CHIPCommand.h"
#include <app/chip-zcl-zpro-codec.h>
#include <lib/core/CHIPEncoding.h>

class ModelCommand : public CHIPCommand, public chip::app::ReadClient::Callback, public chip::app::WriteClient::Callback
{
public:
    using ChipDevice = ::chip::OperationalDeviceProxy;

    ModelCommand(const char * commandName) :
        CHIPCommand(commandName), mOnDeviceConnectedCallback(OnDeviceConnectedFn, this),
        mOnDeviceConnectionFailureCallback(OnDeviceConnectionFailureFn, this), mBufferedReadAdapter(*this)
    {}

    void AddArguments()
    {
        AddArgument("node-id", 0, UINT64_MAX, &mNodeId);
        AddArgument("endpoint-id", 0, 0xFFFF, &mEndPointId);
        AddArgument("timedInteractionTimeoutMs", 0, UINT16_MAX, &mTimedInteractionTimeoutMs);
    }

    /////////// CHIPCommand Interface /////////
    CHIP_ERROR RunCommand() override;
    chip::System::Clock::Timeout GetWaitDuration() const override { return chip::System::Clock::Seconds16(10); }

    virtual CHIP_ERROR SendCommand(ChipDevice * device, chip::EndpointId endPointId) = 0;

    /////////// WriteClient Callback Interface /////////
    void OnResponse(const chip::app::WriteClient * client, const chip::app::ConcreteAttributePath & path,
                    chip::app::StatusIB status) override
    {
        if (CHIP_NO_ERROR != status.ToChipError())
        {
            ChipLogError(chipTool, "Response Failure: %s", chip::ErrorStr(status.ToChipError()));
            SetCommandExitStatus(status.ToChipError());
            return;
        }
    }

    void OnError(const chip::app::WriteClient * client, const chip::app::StatusIB & status, CHIP_ERROR error) override
    {
        ChipLogProgress(chipTool, "Internal Error: %s", chip::ErrorStr(error));
        SetCommandExitStatus(error);
    }

    void OnDone(chip::app::WriteClient * client) override { SetCommandExitStatus(CHIP_NO_ERROR); }

    /////////// ReadClient Callback Interface /////////
    void OnEventData(const chip::app::ReadClient * client, const chip::app::EventHeader & eventHeader, chip::TLV::TLVReader * data,
                     const chip::app::StatusIB * status) override
    {
        if (status != nullptr && CHIP_NO_ERROR != status->ToChipError())
        {
            ChipLogError(chipTool, "Response Failure: %s", chip::ErrorStr(status->ToChipError()));
            SetCommandExitStatus(status->ToChipError());
            return;
        }

        if (data == nullptr)
        {
            ChipLogError(chipTool, "Response Failure: No Data");
            SetCommandExitStatus(CHIP_ERROR_INTERNAL);
            return;
        }

        CHIP_ERROR error = OnEventData(eventHeader, data);
        if (CHIP_NO_ERROR != error)
        {
            ChipLogError(chipTool, "Response Failure: Can not decode Data");
            SetCommandExitStatus(error);
            return;
        }
    }

    void OnAttributeData(const chip::app::ReadClient * client, const chip::app::ConcreteDataAttributePath & path,
                         chip::TLV::TLVReader * data, const chip::app::StatusIB & status) override
    {
        if (CHIP_NO_ERROR != status.ToChipError())
        {
            ChipLogError(chipTool, "Response Failure: %s", chip::ErrorStr(status.ToChipError()));
            SetCommandExitStatus(status.ToChipError());
            return;
        }

        if (data == nullptr)
        {
            ChipLogError(chipTool, "Response Failure: No Data");
            SetCommandExitStatus(CHIP_ERROR_INTERNAL);
            return;
        }

        CHIP_ERROR error = OnAttributeData(path, data);
        if (CHIP_NO_ERROR != error)
        {
            ChipLogError(chipTool, "Response Failure: Can not decode Data");
            SetCommandExitStatus(error);
            return;
        }
    }

    void OnError(const chip::app::ReadClient * client, CHIP_ERROR error) override
    {
        ChipLogProgress(chipTool, "Internal Error: %s", chip::ErrorStr(error));
        SetCommandExitStatus(error);
    }

    void OnDone(chip::app::ReadClient * client) override
    {
        readClient.reset();
        SetCommandExitStatus(CHIP_NO_ERROR);
    }

    void OnSubscriptionEstablished(const chip::app::ReadClient * client) override { OnAttributeSubscription(); }

    virtual CHIP_ERROR OnAttributeData(const chip::app::ConcreteDataAttributePath & path, chip::TLV::TLVReader * data)
    {
        return CHIP_ERROR_NOT_IMPLEMENTED;
    };
    virtual CHIP_ERROR OnEventData(const chip::app::EventHeader & header, chip::TLV::TLVReader * data)
    {
        return CHIP_ERROR_NOT_IMPLEMENTED;
    };
    virtual void OnAttributeSubscription(){};
    virtual void OnEventSubscription(){};

    CHIP_ERROR SubscribeAttribute(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId,
                                  chip::AttributeId attributeId, uint16_t minInterval, uint16_t maxInterval)
    {
        ChipLogProgress(chipTool, "Sending SubscribeAttribute to cluster " ChipLogFormatMEI " on endpoint %" PRIu16,
                        ChipLogValueMEI(clusterId), endpointId);
        return ReportAttribute(device, endpointId, clusterId, attributeId, chip::app::ReadClient::InteractionType::Subscribe,
                               minInterval, maxInterval);
    }

    CHIP_ERROR ReadAttribute(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId,
                             chip::AttributeId attributeId)
    {
        ChipLogProgress(chipTool, "Sending ReadAttribute to cluster " ChipLogFormatMEI " on endpoint %" PRIu16,
                        ChipLogValueMEI(clusterId), endpointId);
        return ReportAttribute(device, endpointId, clusterId, attributeId, chip::app::ReadClient::InteractionType::Read);
    }

    template <class T>
    CHIP_ERROR WriteAttribute(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId,
                              chip::AttributeId attributeId, const T & value)
    {
        ChipLogProgress(chipTool, "Sending WriteAttribute to cluster " ChipLogFormatMEI " on endpoint %" PRIu16,
                        ChipLogValueMEI(clusterId), endpointId);
        chip::app::AttributePathParams attributePathParams;
        if (!device->GetSecureSession().Value()->IsGroupSession())
        {
            attributePathParams.mEndpointId = endpointId;
        }
        attributePathParams.mClusterId   = clusterId;
        attributePathParams.mAttributeId = attributeId;

        chip::app::WriteClientHandle handle;
        ReturnErrorOnFailure(
            chip::app::InteractionModelEngine::GetInstance()->NewWriteClient(handle, this, mTimedInteractionTimeoutMs));
        ReturnErrorOnFailure(handle.EncodeAttributeWritePayload(attributePathParams, value));
        return handle.SendWriteRequest(device->GetSecureSession().Value());
    }

    CHIP_ERROR SubscribeEvent(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId, chip::EventId eventId,
                              uint16_t minInterval, uint16_t maxInterval)
    {
        ChipLogProgress(chipTool, "Sending SubscribeEvent to cluster " ChipLogFormatMEI " on endpoint %" PRIu16,
                        ChipLogValueMEI(clusterId), endpointId);
        return ReportEvent(device, endpointId, clusterId, eventId, chip::app::ReadClient::InteractionType::Subscribe, minInterval,
                           maxInterval);
    }

    CHIP_ERROR ReadEvent(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId, chip::EventId eventId)
    {
        ChipLogProgress(chipTool, "Sending ReadEvent to cluster " ChipLogFormatMEI " on endpoint %" PRIu16,
                        ChipLogValueMEI(clusterId), endpointId);
        return ReportEvent(device, endpointId, clusterId, eventId, chip::app::ReadClient::InteractionType::Read);
    }

    CHIP_ERROR ReportEvent(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId, chip::EventId eventId,
                           chip::app::ReadClient::InteractionType interactionType, uint16_t minInterval = 0,
                           uint16_t maxInterval = 0)
    {
        chip::app::EventPathParams eventPathParams[1];
        eventPathParams[0].mEndpointId = endpointId;
        eventPathParams[0].mClusterId  = clusterId;
        eventPathParams[0].mEventId    = eventId;

        chip::app::ReadPrepareParams readPrepareParams(device->GetSecureSession().Value());
        readPrepareParams.mpEventPathParamsList        = eventPathParams;
        readPrepareParams.mEventPathParamsListSize     = 1;
        readPrepareParams.mpAttributePathParamsList    = nullptr;
        readPrepareParams.mAttributePathParamsListSize = 0;

        if (interactionType == chip::app::ReadClient::InteractionType::Subscribe)
        {
            readPrepareParams.mMinIntervalFloorSeconds   = minInterval;
            readPrepareParams.mMaxIntervalCeilingSeconds = maxInterval;
        }

        readClient = std::make_unique<chip::app::ReadClient>(chip::app::InteractionModelEngine::GetInstance(),
                                                             device->GetExchangeManager(), mBufferedReadAdapter, interactionType);
        return readClient->SendRequest(readPrepareParams);
    }

    CHIP_ERROR ReportAttribute(ChipDevice * device, chip::EndpointId endpointId, chip::ClusterId clusterId,
                               chip::AttributeId attributeId, chip::app::ReadClient::InteractionType interactionType,
                               uint16_t minInterval = 0, uint16_t maxInterval = 0)
    {
        chip::app::AttributePathParams attributePathParams[1];
        attributePathParams[0].mEndpointId  = endpointId;
        attributePathParams[0].mClusterId   = clusterId;
        attributePathParams[0].mAttributeId = attributeId;

        chip::app::ReadPrepareParams readPrepareParams(device->GetSecureSession().Value());
        readPrepareParams.mpEventPathParamsList        = nullptr;
        readPrepareParams.mEventPathParamsListSize     = 0;
        readPrepareParams.mpAttributePathParamsList    = attributePathParams;
        readPrepareParams.mAttributePathParamsListSize = 1;

        if (interactionType == chip::app::ReadClient::InteractionType::Subscribe)
        {
            readPrepareParams.mMinIntervalFloorSeconds   = minInterval;
            readPrepareParams.mMaxIntervalCeilingSeconds = maxInterval;
        }

        readClient = std::make_unique<chip::app::ReadClient>(chip::app::InteractionModelEngine::GetInstance(),
                                                             device->GetExchangeManager(), mBufferedReadAdapter, interactionType);
        return readClient->SendRequest(readPrepareParams);
    }

protected:
    chip::Optional<uint16_t> mTimedInteractionTimeoutMs;

private:
    chip::NodeId mNodeId;
    chip::EndpointId mEndPointId;

    static void OnDeviceConnectedFn(void * context, ChipDevice * device);
    static void OnDeviceConnectionFailureFn(void * context, PeerId peerId, CHIP_ERROR error);

    chip::Callback::Callback<chip::OnDeviceConnected> mOnDeviceConnectedCallback;
    chip::Callback::Callback<chip::OnDeviceConnectionFailure> mOnDeviceConnectionFailureCallback;

    std::unique_ptr<chip::app::ReadClient> readClient;
    chip::app::BufferedReadCallback mBufferedReadAdapter;
};
