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
 *    @file
 *      This file defines the CHIP Connection object that maintains a BLE connection.
 *
 */

#ifndef __TRANSPORT_BLE_H__
#define __TRANSPORT_BLE_H__

#include <ble/BleConfig.h>

#if CONFIG_NETWORK_LAYER_BLE

#include <utility>

#include <ble/BleError.h>
#include <ble/BleLayer.h>
#include <core/CHIPCore.h>
#include <transport/Base.h>

namespace chip {
namespace Transport {

class BLECallbackHandler;

/** Defines connections parameters for setting up a BLE transport */
class BleConnectionParameters
{
public:
    explicit BleConnectionParameters(BLECallbackHandler * callbacks) : mCallbackHandler(callbacks) {}

    BleConnectionParameters(const BleConnectionParameters &) = default;
    BleConnectionParameters(BleConnectionParameters &&)      = default;

    BLECallbackHandler * GetCallbackHandler() { return mCallbackHandler; }

    bool HasBleLayer() const { return mLayer != nullptr; };
    Ble::BleLayer * GetBleLayer() { return mLayer; }
    BleConnectionParameters & SetBleLayer(Ble::BleLayer * bleLayer)
    {
        mLayer = bleLayer;

        return *this;
    }

    bool HasDiscriminator() const { return mDiscriminator != 0; };
    uint16_t GetDiscriminator() const { return mDiscriminator; };
    BleConnectionParameters & SetDiscriminator(const uint16_t discriminator)
    {
        mDiscriminator = discriminator;

        return *this;
    }

    bool HasEndPoint() const { return mEndPoint != nullptr; };
    Ble::BLEEndPoint * GetEndPoint() const { return mEndPoint; };
    BleConnectionParameters & SetEndPoint(Ble::BLEEndPoint * endPoint)
    {
        mEndPoint = endPoint;

        return *this;
    }

private:
    BLECallbackHandler * mCallbackHandler = nullptr;
    Ble::BleLayer * mLayer                = nullptr; ///< Associated ble layer
    Ble::BLEEndPoint * mEndPoint          = nullptr; ///< the target peripheral opened BLEEndPoint
    uint16_t mDiscriminator               = 0;       ///< the target peripheral discriminator
};

/** Implements a transport using BLE.
 *
 *  TODO: BLE transport currently does NOT receive messages as defined
 *        in the Transport::Base (i.e. no header is parsed and processed) and
 *        instead received packets are sent raw via BLE Handler callbacks.
 */
class DLL_EXPORT BLE : public Base
{
    /**
     *  The State of the BLE connection
     *
     */
    enum class State
    {
        kNotReady    = 0, /**< State before initialization. */
        kInitialized = 1, /**< State after class is connected and ready. */
    };

public:
    virtual ~BLE();

    /**
     * Initialize a BLE transport to a given peripheral or a given device name.
     *
     * @param params        BLE configuration parameters for this transport
     */
    CHIP_ERROR Init(BleConnectionParameters & params);

    CHIP_ERROR SendMessage(const MessageHeader & header, const Transport::PeerAddress & address,
                           System::PacketBuffer * msgBuf) override;

    bool CanSendToPeer(const Transport::PeerAddress & address) override
    {
        return (mState == State::kInitialized) && (address.GetTransportType() == Type::kBle);
    }

private:
    CHIP_ERROR InitInternal(Ble::BleLayer * bleLayer, BLE_CONNECTION_OBJECT connObj);
    CHIP_ERROR InitInternal(Ble::BLEEndPoint * endPoint);
    CHIP_ERROR DelegateConnection(Ble::BleLayer * bleLayer, const uint16_t connDiscriminator);
    void SetupEvents(Ble::BLEEndPoint * endPoint);

    // Those functions are BLEConnectionDelegate callbacks used when the connection
    // parameters used a name instead of a BLE_CONNECTION_OBJECT.
    static void OnBleConnectionComplete(void * appState, BLE_CONNECTION_OBJECT connObj);
    static void OnBleConnectionError(void * appState, BLE_ERROR err);

    // Those functions are BLEEndPoint callbacks
    static void OnBleEndPointReceive(BLEEndPoint * endPoint, PacketBuffer * buffer);
    static void OnBleEndPointConnectionComplete(BLEEndPoint * endPoint, BLE_ERROR err);
    static void OnBleEndPointConnectionClosed(BLEEndPoint * endPoint, BLE_ERROR err);

    Ble::BleLayer * mBleLayer          = nullptr;          ///< Associated ble layer
    BLEEndPoint * mBleEndPoint         = nullptr;          ///< BLE endpoint used by the transport
    State mState                       = State::kNotReady; ///< State of the BLE transport
    BLECallbackHandler * mBleCallbacks = nullptr;          ///< BLE events
};

/** Defines callbacks that are BLE specific, beyond standard
 *  'transport' layer base callbacks for message receive
 */
class BLECallbackHandler
{
public:
    virtual ~BLECallbackHandler() {}

    virtual void OnBLEConnectionError(BLE_ERROR err)        = 0;
    virtual void OnBLEConnectionComplete()                  = 0;
    virtual void OnBLEConnectionClosed(BLE_ERROR err)       = 0;
    virtual void OnBLEPacketReceived(PacketBuffer * buffer) = 0;
};

} // namespace Transport
} // namespace chip

#endif // CONFIG_NETWORK_LAYER_BLE

#endif // __TRANSPORT_BLE_H__
