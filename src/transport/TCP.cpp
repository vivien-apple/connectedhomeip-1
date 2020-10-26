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
 *      This file implements the CHIP Connection object that maintains a TCP connection.
 *
 */

#include <support/CodeUtils.h>
#include <support/logging/CHIPLogging.h>
#include <transport/TCP.h>
#include <transport/raw/MessageHeader.h>

#include <inttypes.h>

using namespace chip::Inet;
using namespace chip::System;

namespace chip {
namespace Transport {

namespace {
constexpr int kListenBacklogSize = 2;
}

TCP::~TCP()
{
    if (mTCPEndPoint != nullptr)
    {
        mTCPEndPoint->Free();
        mTCPEndPoint = nullptr;
    }
}

CHIP_ERROR TCP::Init(RendezvousSessionDelegate * delegate, const RendezvousParameters & params)
{
    ChipLogProgress(chipTool, "%p: %s", this, __PRETTY_FUNCTION__);
    CHIP_ERROR err      = CHIP_NO_ERROR;
    InetLayer * inetLayer = params.GetInetLayer();

    VerifyOrExit(mState == State::kNotReady, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(inetLayer, err = CHIP_ERROR_INCORRECT_STATE);

    mDelegate = delegate;
    mParams = params;

#if INET_CONFIG_ENABLE_TCP_ENDPOINT
    if (params.IsController())
    {
        VerifyOrExit(params.HasIPAddress(), err = CHIP_ERROR_INCORRECT_STATE);

        err = inetLayer->NewTCPEndPoint(&mTCPEndPoint);
        SuccessOrExit(err);

        mTCPEndPoint->AppState             = reinterpret_cast<void *>(this);
        mTCPEndPoint->OnDataReceived       = OnTcpReceive;
        mTCPEndPoint->OnConnectComplete    = OnConnectionComplete;
        mTCPEndPoint->OnConnectionClosed   = OnConnectionClosed;
        mTCPEndPoint->OnConnectionReceived = OnConnectionReceived;
        mTCPEndPoint->OnAcceptError        = OnAcceptError;

        err = mTCPEndPoint->Connect(params.GetIPAddress(), CHIP_PORT);
        SuccessOrExit(err);
    }
    else
    {
        err = inetLayer->NewTCPEndPoint(&mTCPEndPoint);
        SuccessOrExit(err);

        err = mTCPEndPoint->Bind(kIPAddressType_IPv4, IPAddress::Any, CHIP_PORT);
        SuccessOrExit(err);

        mTCPEndPoint->AppState             = reinterpret_cast<void *>(this);
        mTCPEndPoint->OnDataReceived       = OnTcpReceive;
        mTCPEndPoint->OnConnectComplete    = OnConnectionComplete;
        mTCPEndPoint->OnConnectionClosed   = OnConnectionClosed;
        mTCPEndPoint->OnConnectionReceived = OnConnectionReceived;
        mTCPEndPoint->OnAcceptError        = OnAcceptError;

        err = mTCPEndPoint->Listen(kListenBacklogSize);
        SuccessOrExit(err);

    }
#else
    ExitNow(err = CHIP_SYSTEM_ERROR_NOT_SUPPORTED);
#endif

exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Inet, "Failed to initialize TCP transport: %s", ErrorStr(err));
        if (mTCPEndPoint)
        {
            mTCPEndPoint->Free();
            mTCPEndPoint = nullptr;
        }
    }
    return err;
}

CHIP_ERROR TCP::SendMessage(const PacketHeader & header, Header::Flags payloadFlags, const Transport::PeerAddress & address,
                            System::PacketBuffer * msgBuf)
{
    ChipLogProgress(chipTool, "%p: %s", this, __PRETTY_FUNCTION__);
    CHIP_ERROR err            = CHIP_NO_ERROR;
    const uint16_t headerSize = header.EncodeSizeBytes();
    uint16_t actualEncodedHeaderSize;

    VerifyOrExit(address.GetTransportType() == Type::kTcp, err = CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrExit(mState == State::kInitialized, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mTCPEndPoint != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(msgBuf->EnsureReservedSize(headerSize), err = CHIP_ERROR_NO_MEMORY);

    msgBuf->SetStart(msgBuf->Start() - headerSize);

    err = header.Encode(msgBuf->Start(), msgBuf->DataLength(), &actualEncodedHeaderSize, payloadFlags);
    SuccessOrExit(err);

    VerifyOrExit(headerSize == actualEncodedHeaderSize, err = CHIP_ERROR_INTERNAL);

    if (mParams.IsController())
    {
        err = mTCPEndPoint->Send(msgBuf);
    }
    else
    {
        VerifyOrExit(mRemoteTCPEndPoint != nullptr, err = CHIP_ERROR_INCORRECT_STATE);
        err = mRemoteTCPEndPoint->Send(msgBuf);
    }
    msgBuf = nullptr;
    SuccessOrExit(err);

exit:
    if (msgBuf != nullptr)
    {
        System::PacketBuffer::Free(msgBuf);
        msgBuf = nullptr;
    }
    return err;
}

void TCP::OnTcpReceive(Inet::TCPEndPoint * endPoint, System::PacketBuffer * buffer)
{
    TCP * tcp = reinterpret_cast<TCP *>(endPoint->AppState);
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mDelegate)
    {
        tcp->mDelegate->OnRendezvousMessageReceived(buffer);
    }
}

void TCP::OnConnectionComplete(Inet::TCPEndPoint * endPoint, INET_ERROR err)
{
    TCP * tcp   = reinterpret_cast<TCP *>(endPoint->AppState);
    tcp->mState = State::kInitialized;
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mDelegate)
    {
        if (err != INET_NO_ERROR)
        {
            tcp->mDelegate->OnRendezvousError(err);
        }
        else
        {
            tcp->mDelegate->OnRendezvousConnectionOpened();
        }
    }
}

void TCP::OnConnectionClosed(Inet::TCPEndPoint * endPoint, INET_ERROR err)
{
    TCP * tcp   = reinterpret_cast<TCP *>(endPoint->AppState);
    tcp->mState = State::kNotReady;
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mDelegate)
    {
        if (err != INET_NO_ERROR)
        {
            tcp->mDelegate->OnRendezvousError(err);
        }

    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);
        tcp->mDelegate->OnRendezvousConnectionClosed();
    }
}

void TCP::OnConnectionReceived(Inet::TCPEndPoint * listenEndPoint, Inet::TCPEndPoint * endPoint,
                               const Inet::IPAddress & peerAddress, uint16_t peerPort)
{
    TCP * tcp = reinterpret_cast<TCP *>(listenEndPoint->AppState);
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mState == State::kNotReady)
    {
        endPoint->AppState             = listenEndPoint->AppState;
        endPoint->OnDataReceived       = OnTcpReceive;
        endPoint->OnConnectComplete    = OnConnectionComplete;
        endPoint->OnConnectionClosed   = OnConnectionClosed;
        endPoint->OnConnectionReceived = OnConnectionReceived;
        endPoint->OnAcceptError        = OnAcceptError;
        endPoint->OnPeerClose          = OnPeerClosed;

        tcp->mRemoteTCPEndPoint = endPoint;
        tcp->mState             = State::kInitialized;
    }
    else
    {
        ChipLogError(Inet, "Insufficient connection space to accept new connections");
        endPoint->Free();
    }
}

void TCP::OnPeerClosed(Inet::TCPEndPoint * endPoint)
{
    TCP * tcp = reinterpret_cast<TCP *>(endPoint->AppState);
    tcp->mState = State::kNotReady;
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mDelegate)
    {
        tcp->mDelegate->OnRendezvousConnectionClosed();
    }
}

void TCP::OnAcceptError(Inet::TCPEndPoint * endPoint, INET_ERROR err)
{
    TCP * tcp = reinterpret_cast<TCP *>(endPoint->AppState);
    ChipLogProgress(chipTool, "%p: %s", tcp, __PRETTY_FUNCTION__);

    if (tcp->mDelegate)
    {
        tcp->mDelegate->OnRendezvousError(err);
    }
}

} // namespace Transport
} // namespace chip
