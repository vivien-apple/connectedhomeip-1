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
#include "Display.h"

#include "BluetoothWidget.h"

#include <platform/CHIPDeviceLayer.h>
#include <support/ErrorStr.h>
#include <support/logging/CHIPLogging.h>
#include <system/SystemPacketBuffer.h>

#include "esp_log.h"

#if CONFIG_HAVE_DISPLAY
extern BluetoothWidget bluetoothLED;
#endif // CONFIG_HAVE_DISPLAY

using namespace ::chip;
using namespace ::chip::Ble;
using namespace ::chip::DeviceLayer;

extern const char * TAG;

void GetStationIP(char * ip_buf, size_t ip_len)
{
    tcpip_adapter_ip_info_t ip;
    tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip);
    IPAddress::FromIPv4(ip.ip).ToString(ip_buf, ip_len);
    ESP_LOGE(TAG, "Got station ip %s", ip_buf);
}

void HandleBleMessageReceived(BLEEndPoint * endPoint, PacketBuffer * buffer)
{
    const size_t bufferLen = buffer->DataLength();
    char msg[bufferLen];
    msg[bufferLen] = 0;
    memcpy(msg, buffer->Start(), bufferLen);

    ChipLogProgress(Ble, "BLEEndPoint: Receive message: %s", msg);

    char gw_ip[INET6_ADDRSTRLEN];
    GetStationIP(gw_ip, sizeof(gw_ip));

    endPoint->Send(buffer);
}

void HandleBleConnectionClosed(BLEEndPoint * endPoint, BLE_ERROR err)
{
    ChipLogProgress(Ble, "BLEEndPoint: Connection closed (%s)", ErrorStr(err));

#if CONFIG_HAVE_DISPLAY
    bluetoothLED.Set(false);
#endif // CONFIG_HAVE_DISPLAY
}

void HandleBleNewConnection(BLEEndPoint * endPoint)
{
    ChipLogProgress(Ble, "BLEEndPoint: Connection opened");
    endPoint->OnMessageReceived  = HandleBleMessageReceived;
    endPoint->OnConnectionClosed = HandleBleConnectionClosed;

#if CONFIG_HAVE_DISPLAY
    bluetoothLED.Set(true);
#endif // CONFIG_HAVE_DISPLAY
}

void startBle()
{
    DeviceLayer::ConnectivityMgr().AddCHIPoBLEConnectionHandler(HandleBleNewConnection);
}
