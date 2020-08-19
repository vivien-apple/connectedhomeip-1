/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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

#include "RendezvousSession.h"

#if CONFIG_DEVICE_LAYER
#include <platform/CHIPDeviceLayer.h>
#endif

#include <support/CodeUtils.h>
#include <support/ErrorStr.h>

namespace chip {

CHIP_ERROR RendezvousSession::Init(RendezvousSessionCallback * callbacks)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    VerifyOrExit(callbacks != nullptr, err = CHIP_ERROR_INCORRECT_STATE);

    mCallbacks = callbacks;

    if (mParams.IsBLE())
    {
#if CONFIG_NETWORK_LAYER_BLE
        Transport::BleConnectionParameters params = Transport::BleConnectionParameters(this);

        if (mParams.HasDiscriminator())
        {
#if CONFIG_DEVICE_LAYER
            params.SetBleLayer(DeviceLayer::ConnectivityMgr().GetBleLayer());
#endif // CONFIG_DEVICE_LAYER
            params.SetDiscriminator(mParams.GetDiscriminator());
        }
        else if (mParams.HasEndPoint())
        {
            params.SetEndPoint(mParams.GetEndPoint());
        }

        err = InitInternalBle(params);
#else
        err = CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
#endif // CONFIG_NETWORK_LAYER_BLE
        SuccessOrExit(err);
    }

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(Inet, "Failed to initialize RendezvousSession: %s", ErrorStr(err));
        mCallbacks = nullptr;
    }

    return err;
}

#if CONFIG_NETWORK_LAYER_BLE
CHIP_ERROR RendezvousSession::InitInternalBle(Transport::BleConnectionParameters & params)
{
    CHIP_ERROR err             = CHIP_NO_ERROR;
    Transport::BLE * transport = new Transport::BLE();

    err = transport->Init(params);
    SuccessOrExit(err);

    mTransport = transport;
    mTransport->Retain();
    transport->Release();

exit:
    return err;
}
#endif // CONFIG_NETWORK_LAYER_BLE

RendezvousSession::~RendezvousSession()
{
    if (mTransport)
    {
        mTransport->Release();
        mTransport = nullptr;
    }

    mCallbacks = nullptr;
}

CHIP_ERROR RendezvousSession::SendMessage(System::PacketBuffer * buffer)
{
    // Rendezvous does not use a MessageHeader, but the Transport::Base API expects one, so
    // let build an empty one for now.
    MessageHeader header;
    CHIP_ERROR err = mTransport->SendMessage(header, mParams.GetPeerAddress(), buffer);

    return err;
}

#if CONFIG_NETWORK_LAYER_BLE
void RendezvousSession::OnBLEConnectionError(BLE_ERROR err)
{
    mCallbacks->OnRendezvousError(err);
}

void RendezvousSession::OnBLEConnectionComplete()
{
    mCallbacks->OnRendezvousConnectionOpened();
}

void RendezvousSession::OnBLEConnectionClosed(BLE_ERROR err)
{
    mCallbacks->OnRendezvousConnectionClosed(err);
}

void RendezvousSession::OnBLEPacketReceived(PacketBuffer * buffer)
{
    mCallbacks->OnRendezvousMessageReceived(buffer);
}
#endif // CONFIG_NETWORK_LAYER_BLE

} // namespace chip
