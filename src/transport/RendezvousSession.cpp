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
#include <support/CodeUtils.h>
#include <support/ErrorStr.h>

namespace chip {

RendezvousSession::RendezvousSession(Transport::Base * transport, RendezvousSessionCallbackHandler * callbacks) :
    mTransport(transport), mCallbacks(callbacks)
{
    mTransport->Retain();
}

RendezvousSession::~RendezvousSession()
{
    mTransport->Release();
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

} // namespace chip
