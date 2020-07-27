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
#include <support/logging/CHIPLogging.h>
#include <system/SystemPacketBuffer.h>

using namespace ::chip;

BluetoothWidget * RendezvousSession::mVirtualLed;

Ble::BLEEndPoint * RendezvousSession::mEndPoint = nullptr;

RendezvousSession::RendezvousSession(BluetoothWidget * virtualLed)
{
    mVirtualLed = virtualLed;
    mVirtualLed->Init();
#if CONFIG_HAVE_DISPLAY
#endif

    DeviceLayer::ConnectivityMgr().AddCHIPoBLEConnectionHandler(HandleConnectionOpened);
}

CHIP_ERROR RendezvousSession::Send(const char * msg)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    System::PacketBuffer * buffer;
    const size_t msgLen = strlen(msg);

    VerifyOrExit(mEndPoint, err = CHIP_ERROR_INCORRECT_STATE);

    buffer = System::PacketBuffer::NewWithAvailableSize(msgLen);
    memcpy(buffer->Start(), msg, msgLen);
    buffer->SetDataLength(msgLen);

    err = mEndPoint->Send(buffer);

exit:
    return err;
}

void RendezvousSession::HandleConnectionOpened(Ble::BLEEndPoint * endPoint)
{
    ChipLogProgress(Ble, "RendezvousSession: Connection opened");

    mEndPoint                     = endPoint;
    mEndPoint->OnMessageReceived  = HandleMessageReceived;
    mEndPoint->OnConnectionClosed = HandleConnectionClosed;
    mVirtualLed->Set(true);
}

void RendezvousSession::HandleConnectionClosed(Ble::BLEEndPoint * endPoint, BLE_ERROR err)
{
    ChipLogProgress(Ble, "RendezvousSession: Connection closed (%s)", ErrorStr(err));

    mEndPoint = nullptr;
    mVirtualLed->Set(false);
}

void RendezvousSession::HandleMessageReceived(Ble::BLEEndPoint * endPoint, PacketBuffer * buffer)
{
    const size_t bufferLen = buffer->DataLength();
    char msg[bufferLen];
    msg[bufferLen] = 0;
    memcpy(msg, buffer->Start(), bufferLen);

    ChipLogProgress(Ble, "RendezvousSession: Receive message: %s", msg);

    mEndPoint->Send(buffer);
}
