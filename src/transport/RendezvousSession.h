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

#include <system/SystemPacketBuffer.h>
#include <transport/Base.h>

namespace chip {

class RendezvousSessionCallbackHandler
{
public:
    virtual ~RendezvousSessionCallbackHandler() {}

    virtual void OnConnectionOpened(CHIP_ERROR err)               = 0;
    virtual void OnConnectionClosed(CHIP_ERROR err)               = 0;
    virtual void OnMessageReceived(System::PacketBuffer * buffer) = 0;
    virtual void OnError(CHIP_ERROR err)                          = 0;
};

class RendezvousSession
{
public:
    RendezvousSession(Transport::Base * transport, RendezvousSessionCallbackHandler * callbacks);
    virtual ~RendezvousSession();

private:
    Transport::Base * mTransport                  = nullptr;
    RendezvousSessionCallbackHandler * mCallbacks = nullptr; ///< transport events
};

} // namespace chip
#endif // __TRANSPORT_RENDEZVOUSSESSION_H__
