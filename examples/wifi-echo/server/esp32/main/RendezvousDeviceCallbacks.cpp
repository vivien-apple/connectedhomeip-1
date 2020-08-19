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

#include "RendezvousDeviceCallbacks.h"
#include "BluetoothWidget.h"
#include "esp_log.h"
#include <platform/ConfigurationManager.h>
#include <support/CodeUtils.h>
#include <support/ErrorStr.h>
#include <support/logging/CHIPLogging.h>
#include <system/SystemPacketBuffer.h>

static const char * TAG = "rendezvous-devicecallbacks";
extern BluetoothWidget bluetoothLED;
extern CHIP_ERROR SetWiFiStationProvisioning(char * ssid, char * key);

using namespace ::chip;

RendezvousDeviceCallbacks * rendezvousCallbacks = nullptr;

CHIP_ERROR RendezvousDeviceCallbacks::Init(Ble::BLEEndPoint * endPoint)
{
    CHIP_ERROR err;

    uint32_t setupPINCode;
    err = DeviceLayer::ConfigurationMgr().GetSetupPinCode(setupPINCode);
    SuccessOrExit(err);

    mRendezvousSession = new RendezvousSession(RendezvousParameters(Transport::PeerAddress::BLE(), endPoint, setupPINCode));
    err                = mRendezvousSession->Init(this);
    SuccessOrExit(err);

exit:
    return err;
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

void RendezvousDeviceCallbacks::OnNewConnection(Ble::BLEEndPoint * endPoint)
{
    ESP_LOGI(TAG, "OnRendezvousDeviceCallbacks::OnNewConnection");

    rendezvousCallbacks = new RendezvousDeviceCallbacks();
    CHIP_ERROR err      = rendezvousCallbacks->Init(endPoint);
    if (err != CHIP_NO_ERROR)
    {
        ESP_LOGI(TAG, "RendezvousDeviceCallbacks init failed: %s", ErrorStr(err));
    }
}

void RendezvousDeviceCallbacks::OnRendezvousError(CHIP_ERROR err)
{
    ESP_LOGI(TAG, "OnRendezvousError: %s", ErrorStr(err));
}

void RendezvousDeviceCallbacks::OnRendezvousConnectionOpened()
{
    ESP_LOGI(TAG, "OnRendezvousConnectionOpened");
    bluetoothLED.Set(true);
}

void RendezvousDeviceCallbacks::OnRendezvousConnectionClosed(CHIP_ERROR err)
{
    ESP_LOGI(TAG, "OnRendezvousConnectionClosed");
    bluetoothLED.Set(false);
}

void RendezvousDeviceCallbacks::OnRendezvousMessageReceived(PacketBuffer * buffer)
{
    ESP_LOGI(TAG, "OnRendezvousMessageReceived");

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
