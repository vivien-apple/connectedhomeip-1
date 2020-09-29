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
 * @file EchoDeviceCallbacks.cpp
 *
 * Implements all the callbacks to the application from the CHIP Stack
 *
 **/

#include "EchoDeviceCallbacks.h"
#include "RendezvousDeviceDelegate.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_netif.h"
#include <platform/CHIPDeviceLayer.h>
#include <support/CodeUtils.h>

#include "LEDWidget.h"
#include "WiFiWidget.h"
#include <inet/IPAddress.h>

extern "C" {
#include "gen/attribute-id.h"
#include "gen/cluster-id.h"
} // extern "C"

static const char * TAG = "echo-devicecallbacks";
using namespace ::chip::Inet;
using namespace ::chip::DeviceLayer;

// In wifi-echo.cpp
extern LEDWidget statusLED1;
extern LEDWidget statusLED2;
extern WiFiWidget wifiLED;
extern RendezvousDeviceDelegate * rendezvousDelegate;

void EchoDeviceCallbacks::DeviceEventCallback(const ChipDeviceEvent * event, intptr_t arg)
{
    if (event->Type == DeviceEventType::kInternetConnectivityChange)
    {
        ESP_LOGI(TAG, "Current free heap: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
        if (event->InternetConnectivityChange.IPv4 == kConnectivity_Established)
        {
            esp_netif_ip_info_t ipInfo;
            if (esp_netif_get_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"), &ipInfo) == ESP_OK)
            {
                char ipAddrStr[INET_ADDRSTRLEN];
                esp_ip4addr_ntoa(&ipInfo.ip, ipAddrStr, sizeof(ipAddrStr));
                ESP_LOGI(TAG, "Server ready at: %s:%d", ipAddrStr, CHIP_PORT);

                // Since the commissioner device does not yet have a mechanism to discover the IP address
                // of the peripheral, the following code send it over the current Rendezvous session.
                if (rendezvousDelegate != NULL)
                {
                    rendezvousDelegate->Send(ipAddrStr);
                }
            }
            wifiLED.Set(true);
        }
        else if (event->InternetConnectivityChange.IPv4 == kConnectivity_Lost)
        {
            ESP_LOGE(TAG, "Lost IPv4 connectivity...");
            wifiLED.Set(false);
        }
        if (event->InternetConnectivityChange.IPv6 == kConnectivity_Established)
        {
            ESP_LOGI(TAG, "IPv6 Server ready...");
        }
        else if (event->InternetConnectivityChange.IPv6 == kConnectivity_Lost)
        {
            ESP_LOGE(TAG, "Lost IPv6 connectivity...");
        }
    }
    if (event->Type == DeviceEventType::kSessionEstablished && event->SessionEstablished.IsCommissioner)
    {
        ESP_LOGI(TAG, "Commissioner detected!");
    }
}

void OnOffPostAttributeChangeCallback(uint8_t endpoint, uint16_t attributeId, uint8_t * value)
{
    ESP_LOGI(TAG, "endpoint: '0x%02x', attribute ID: '0x%04x', value: %d", endpoint, attributeId, *value);

    if (attributeId != ZCL_ON_OFF_ATTRIBUTE_ID)
    {
        ESP_LOGI(TAG, "Unknown attribute ID: %d", attributeId);
        return;
    }

    // At this point we can assume that value points to a bool value.
    if (endpoint == 1)
    {
        statusLED1.Set(*value);
    }
    else if (endpoint == 2)
    {
        statusLED2.Set(*value);
    }
    else
    {
        ESP_LOGE(TAG, "Unexpected endpoint id: %d", endpoint);
    }
}

TimerHandle_t identifyTimer;
void IdentifyTimerCallback(TimerHandle_t handle)
{
    statusLED1.Animate();

    // Get remaining timer count.
    uint32_t timerCount = (uint32_t) pvTimerGetTimerID(handle);

    // Decrement the timer count.
    timerCount--;
    vTimerSetTimerID(handle, (void *) timerCount);

    // If the timer count reaches 0, just stop the timer.
    if (timerCount == 0)
    {
        xTimerStop(handle, 0);
    }
}

void IdentifyPostAttributeChangeCallback(uint8_t endpoint, uint16_t attributeId, uint8_t * value)
{
    ESP_LOGI(TAG, "endpoint: '0x%02x', attribute ID: '0x%04x', value: %d", endpoint, attributeId, *value);

    if (attributeId != ZCL_IDENTIFY_TIME_ATTRIBUTE_ID)
    {
        ESP_LOGI(TAG, "Unknown attribute ID: %d", attributeId);
        return;
    }

    // Only endpoint 1 supports the Identify cluster
    if (endpoint == 1)
    {
        statusLED1.Blink(500);

        // timerCount represents the number of callback execution before the we stopped the timer.
        // value is expressed in seconds and the timer is fired every 250ms, so just multiply value by 4.
        // Also, we want timerCount to be odd number, so the ligth state ends in the same state it starts.
        uint32_t timerCount = (*value) * 4;

        identifyTimer = xTimerCreate("IdentifyTimer", pdMS_TO_TICKS(250), pdTRUE, (void *) timerCount, &IdentifyTimerCallback);
        if (xTimerStart(identifyTimer, 10) != pdPASS)
        {
            ESP_LOGE(TAG, "Identify timer start error");
        }
    }
    else
    {
        ESP_LOGE(TAG, "Unexpected endpoint id: %d", endpoint);
    }
}

void EchoDeviceCallbacks::PostAttributeChangeCallback(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attributeId,
                                                      uint8_t mask, uint16_t manufacturerCode, uint8_t type, uint8_t size,
                                                      uint8_t * value)
{
    ESP_LOGI(TAG, "PostAttributeChangeCallback for cluster ID: '0x%04x'", clusterId);

    switch (clusterId)
    {
    case ZCL_ON_OFF_CLUSTER_ID:
        OnOffPostAttributeChangeCallback(endpoint, attributeId, value);
        break;

    case ZCL_IDENTIFY_CLUSTER_ID:
        IdentifyPostAttributeChangeCallback(endpoint, attributeId, value);
        break;

    default:
        ESP_LOGI(TAG, "Unhandled cluster ID: %d", clusterId);
        break;
    }

    ESP_LOGI(TAG, "Current free heap: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}
