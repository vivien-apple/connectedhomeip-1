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
 *      This file implements the CHIP Connection object that maintains a BLE connection.
 *
 */

#include <transport/BLE.h>

#include <support/CodeUtils.h>
#include <support/logging/CHIPLogging.h>
#include <transport/MessageHeader.h>

#include <inttypes.h>

namespace chip {
namespace Transport {

BLE::~BLE()
{
    if (mBleEndPoint)
    {
        // Ble endpoint is only non null if ble endpoint is initialized and connected
        mBleEndPoint->Close();
        mBleEndPoint = nullptr;
    }
}

CHIP_ERROR BLE::Init(BleConnectionParameters & params)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    VerifyOrExit(mState == State::kNotReady, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(params.HasEndPoint() || params.HasDiscriminator(), err = CHIP_ERROR_INVALID_ARGUMENT);

    mBleCallbacks = params.GetCallbackHandler();
    mBleLayer     = params.GetBleLayer();

    if (params.HasEndPoint())
    {
        err = InitInternal(params.GetEndPoint());
    }
    else if (params.HasDiscriminator())
    {
        VerifyOrExit(params.GetBleLayer(), err = CHIP_ERROR_INVALID_ARGUMENT);
        err = DelegateConnection(params.GetBleLayer(), params.GetDiscriminator());
    }
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(Inet, "Failed to initialize Ble transport: %s", ErrorStr(err));
        mBleCallbacks = nullptr;
        mBleLayer     = nullptr;
    }

    return err;
}

CHIP_ERROR BLE::InitInternal(Ble::BleLayer * bleLayer, BLE_CONNECTION_OBJECT connObj)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = bleLayer->NewBleEndPoint(&mBleEndPoint, connObj, kBleRole_Central, true);
    SuccessOrExit(err);

    // Initiate CHIP over BLE protocol connection.
    SetupEvents(mBleEndPoint);
    err = mBleEndPoint->StartConnect();
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        if (mBleEndPoint)
        {
            mBleEndPoint = nullptr;
        }
    }
    return err;
}

CHIP_ERROR BLE::InitInternal(Ble::BLEEndPoint * endPoint)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    mBleEndPoint = endPoint;
    SetupEvents(mBleEndPoint);
    // The endPoint is already connected, so manually trigger the ConnectionComplete callback.
    OnBleEndPointConnectionComplete(endPoint, err);

    return err;
}

void BLE::SetupEvents(Ble::BLEEndPoint * endPoint)
{
    endPoint->mAppState          = reinterpret_cast<void *>(this);
    endPoint->OnMessageReceived  = OnBleEndPointReceive;
    endPoint->OnConnectComplete  = OnBleEndPointConnectionComplete;
    endPoint->OnConnectionClosed = OnBleEndPointConnectionClosed;
}

CHIP_ERROR BLE::DelegateConnection(Ble::BleLayer * bleLayer, const uint16_t connDiscriminator)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    err = bleLayer->NewBleConnection(reinterpret_cast<void *>(this), connDiscriminator, OnBleConnectionComplete,
                                     OnBleConnectionError);
    SuccessOrExit(err);

exit:
    return err;
}

CHIP_ERROR BLE::SendMessage(const MessageHeader & header, const Transport::PeerAddress & address, System::PacketBuffer * msgBuf)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    VerifyOrExit(address.GetTransportType() == Type::kBle, err = CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrExit(mState == State::kInitialized, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mBleEndPoint != nullptr, err = CHIP_ERROR_INCORRECT_STATE);

    err    = mBleEndPoint->Send(msgBuf);
    msgBuf = nullptr;
    SuccessOrExit(err);

exit:
    if (msgBuf != NULL)
    {
        System::PacketBuffer::Free(msgBuf);
        msgBuf = NULL;
    }

    return err;
}

void BLE::OnBleConnectionComplete(void * appState, BLE_CONNECTION_OBJECT connObj)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    BLE * ble      = reinterpret_cast<BLE *>(appState);

    err = ble->InitInternal(ble->mBleLayer, connObj);
    SuccessOrExit(err);

exit:
    if (err != CHIP_NO_ERROR)
    {
        ble->OnBleConnectionError(appState, err);
    }
}

void BLE::OnBleConnectionError(void * appState, BLE_ERROR err)
{
    BLE * ble = reinterpret_cast<BLE *>(appState);

    if (ble->mBleCallbacks)
    {
        ble->mBleCallbacks->OnBLEConnectionError(err);
    }
}

void BLE::OnBleEndPointReceive(BLEEndPoint * endPoint, PacketBuffer * buffer)
{
    BLE * ble = reinterpret_cast<BLE *>(endPoint->mAppState);

    if (ble->mBleCallbacks)
    {
        ble->mBleCallbacks->OnBLEPacketReceived(buffer);
    }
}

void BLE::OnBleEndPointConnectionComplete(BLEEndPoint * endPoint, BLE_ERROR err)
{
    BLE * ble   = reinterpret_cast<BLE *>(endPoint->mAppState);
    ble->mState = State::kInitialized;

    if (ble->mBleCallbacks)
    {
        ble->mBleCallbacks->OnBLEConnectionComplete();
    }
}

void BLE::OnBleEndPointConnectionClosed(BLEEndPoint * endPoint, BLE_ERROR err)
{
    BLE * ble   = reinterpret_cast<BLE *>(endPoint->mAppState);
    ble->mState = State::kNotReady;

    if (ble->mBleCallbacks)
    {
        ble->mBleCallbacks->OnBLEConnectionClosed(err);
    }
}

} // namespace Transport
} // namespace chip
