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

#include "esp_log.h"
#include "BluetoothWidget.h"
#include "RendezvousDeviceCallbacks.h"
#include <platform/ConfigurationManager.h>
#include <support/CodeUtils.h>
#include <support/ErrorStr.h>
#include <support/logging/CHIPLogging.h>
#include <system/SystemPacketBuffer.h>

static const char * TAG = "rendezvous-devicecallbacks";

using namespace ::chip;

extern BluetoothWidget bluetoothLED;

RendezvousDeviceCallbacks * rendezvousCallbacks = nullptr;

extern CHIP_ERROR SetWiFiStationProvisioning(char * ssid, char * key);

RendezvousDeviceCallbacks::RendezvousDeviceCallbacks(Ble::BLEEndPoint * endPoint)
{
    uint32_t setupPINCode;
    CHIP_ERROR err = GetSetupPINCode(&setupPINCode);
    if (err == CHIP_NO_ERROR)
    {
        RendezvousParameters params = RendezvousParameters(Transport::PeerAddress::BLE(), endPoint, setupPINCode);
        mRendezvousSession = new RendezvousSession(params);
        mRendezvousSession->Init(this);
    }
}

CHIP_ERROR RendezvousDeviceCallbacks::Send(const char * msg)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    System::PacketBuffer * buffer;
    const size_t msgLen = strlen(msg);

    VerifyOrExit(mRendezvousSession, err = CHIP_ERROR_INCORRECT_STATE);

    buffer = System::PacketBuffer::NewWithAvailableSize(msgLen);
    memcpy(buffer->Start(), msg, msgLen);
    buffer->SetDataLength(msgLen);

    err = mRendezvousSession->SendMessage(buffer);

exit:
    return err;
}

CHIP_ERROR GetSetupPINCode(uint32_t * setupPINCode)
{
    CHIP_ERROR err = DeviceLayer::ConfigurationMgr().GetSetupPinCode(*setupPINCode);
    VerifyOrExit(err == CHIP_NO_ERROR, ESP_LOGE(TAG, "Couldn't get setupPINCode: %d", err));

exit:
    return err;
}


void RendezvousDeviceCallbacks::OnNewConnection(Ble::BLEEndPoint * endPoint)
{
    rendezvousCallbacks = new RendezvousDeviceCallbacks(endPoint);
}

void RendezvousDeviceCallbacks::OnRendezvousError(CHIP_ERROR err)
{
}

void RendezvousDeviceCallbacks::OnRendezvousConnectionOpened(CHIP_ERROR err)
{
    bluetoothLED.Set(true);
}

void RendezvousDeviceCallbacks::OnRendezvousConnectionClosed(CHIP_ERROR err)
{
    bluetoothLED.Set(false);
}

void RendezvousDeviceCallbacks::OnRendezvousMessageReceived(PacketBuffer * buffer)
{
    const size_t bufferLen = buffer->DataLength();
    char msg[bufferLen];
    msg[bufferLen] = 0;
    memcpy(msg, buffer->Start(), bufferLen);

    ChipLogProgress(Ble, "RendezvousDeviceCallbacks: Receive message: %s", msg);

    if ((bufferLen > 3) && (msg[0] == msg[1]) && (msg[0] == msg[bufferLen - 1]))
    {
        // WiFi credentials, of the form ‘::SSID:password:’, where ‘:’ can be any single ASCII character.
        msg[1]      = 0;
        char * ssid = strtok(&msg[2], msg);
        char * key  = strtok(NULL, msg);
        if (ssid && key)
        {
            ChipLogProgress(Ble, "RendezvousDeviceCallbacks: SSID: %s, key: %s", ssid, key);
            SetWiFiStationProvisioning(ssid, key);
        }
        else
        {
            ChipLogError(Ble, "RendezvousDeviceCallbacks: SSID: %p, key: %p", ssid, key);
        }
    }
    else
    {
        // Echo.
        mRendezvousSession->SendMessage(buffer);
    }
}

