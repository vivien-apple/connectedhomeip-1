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

    if (mParams.IsBLE())
    {
#if CONFIG_DEVICE_LAYER && CONFIG_NETWORK_LAYER_BLE
        err = InitInternalBle(mParams.GetDiscriminator(), mParams.GetSetupPINCode());
#else
        err = CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
#endif // CONFIG_DEVICE_LAYER && CONFIG_NETWORK_LAYER_BLE
        SuccessOrExit(err);
    }

    mCallbacks = callbacks;

exit:
    return err;
}

#if CONFIG_DEVICE_LAYER && CONFIG_NETWORK_LAYER_BLE
CHIP_ERROR RendezvousSession::InitInternalBle(uint16_t discriminator, uint32_t setupPINCode)
{
    CHIP_ERROR err             = CHIP_NO_ERROR;
    Transport::BLE * transport = new Transport::BLE();
    err = transport->Init(Transport::BleConnectionParameters(this, DeviceLayer::ConnectivityMgr().GetBleLayer())
                              .SetDiscriminator(discriminator)
                              .SetSetupPINCode(setupPINCode));
    SuccessOrExit(err);

    mTransport = transport;
    mTransport->Retain();

exit:
    return err;
}
#endif

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
    Transport::PeerAddress peerAddress = Transport::PeerAddress::BLE();
    CHIP_ERROR err                     = mTransport->SendMessage(header, peerAddress, buffer);

    return err;
}

void RendezvousSession::OnBLEConnectionError(BLE_ERROR err) {}

void RendezvousSession::OnBLEConnectionComplete(BLE_ERROR err) {}

void RendezvousSession::OnBLEConnectionClosed(BLE_ERROR err) {}

void RendezvousSession::OnBLEPacketReceived(PacketBuffer * buffer) {}

} // namespace chip
