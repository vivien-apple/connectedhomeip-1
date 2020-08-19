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

#ifndef __TRANSPORT_RENDEZVOUSSESSION_H__
#define __TRANSPORT_RENDEZVOUSSESSION_H__

#include <core/CHIPCore.h>
#include <transport/BLE.h>
#include <transport/Base.h>

namespace chip {

class RendezvousParameters
{
public:
    explicit RendezvousParameters(const Transport::PeerAddress & peerAddress, uint16_t discriminator, uint32_t setupPINCode) :
        mPeerAddress(peerAddress), mDiscriminator(discriminator), mSetupPINCode(setupPINCode)
    {}

#if CONFIG_NETWORK_LAYER_BLE
    explicit RendezvousParameters(const Transport::PeerAddress & peerAddress, Ble::BLEEndPoint * endPoint, uint32_t setupPINCode) :
        mPeerAddress(peerAddress), mEndPoint(endPoint), mSetupPINCode(setupPINCode)
    {}
#endif // CONFIG_NETWORK_LAYER_BLE

    bool IsUDP() const { return mPeerAddress.GetTransportType() == Transport::Type::kUdp; };
    bool IsBLE() const { return mPeerAddress.GetTransportType() == Transport::Type::kBle; };

    const Transport::PeerAddress GetPeerAddress() const { return mPeerAddress; };

    bool HasDiscriminator() const { return mDiscriminator != 0; };
    uint16_t GetDiscriminator() const { return mDiscriminator; };

    uint32_t GetSetupPINCode() const { return mSetupPINCode; };

#if CONFIG_NETWORK_LAYER_BLE
    bool HasEndPoint() const { return mEndPoint != nullptr; };
    Ble::BLEEndPoint * GetEndPoint() const { return mEndPoint; };
#endif // CONFIG_NETWORK_LAYER_BLE

private:
    Transport::PeerAddress mPeerAddress;
#if CONFIG_NETWORK_LAYER_BLE
    Ble::BLEEndPoint * mEndPoint = nullptr;
#endif // CONFIG_NETWORK_LAYER_BLE

    uint16_t mDiscriminator = 0; ///< the target peripheral discriminator
    uint32_t mSetupPINCode  = 0; ///< the target peripheral setup PIN Code
};

class RendezvousSessionCallback
{
public:
    virtual ~RendezvousSessionCallback() {}

    virtual void OnRendezvousConnectionOpened()                             = 0;
    virtual void OnRendezvousConnectionClosed(CHIP_ERROR err)               = 0;
    virtual void OnRendezvousMessageReceived(System::PacketBuffer * buffer) = 0;
    virtual void OnRendezvousError(CHIP_ERROR err)                          = 0;
};

class RendezvousSession :
#if CONFIG_NETWORK_LAYER_BLE
    public Transport::BLECallbackHandler
#endif // CONFIG_NETWORK_LAYER_BLE
{
public:
    explicit RendezvousSession(const RendezvousParameters & params) : mParams(params) {}

    CHIP_ERROR Init(RendezvousSessionCallback * callbacks);
    virtual ~RendezvousSession();
    CHIP_ERROR SendMessage(System::PacketBuffer * buffer);

#if CONFIG_NETWORK_LAYER_BLE
    //////////// BLECallbackHandler Implementation ///////////////
    void OnBLEConnectionError(BLE_ERROR err) override;
    void OnBLEConnectionComplete() override;
    void OnBLEConnectionClosed(BLE_ERROR err) override;
    void OnBLEPacketReceived(System::PacketBuffer * buffer) override;
#endif // CONFIG_NETWORK_LAYER_BLE

private:
#if CONFIG_NETWORK_LAYER_BLE
    CHIP_ERROR InitInternalBle(Transport::BleConnectionParameters & params);
#endif // CONFIG_NETWORK_LAYER_BLE

    const RendezvousParameters mParams;
    Transport::Base * mTransport           = nullptr;
    RendezvousSessionCallback * mCallbacks = nullptr; ///< transport events
};

} // namespace chip
#endif // __TRANSPORT_RENDEZVOUSSESSION_H__
