/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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
 *      Declaration of SetUp Code Parser, a class
 *      that implements parsing manual and QRCode for connecting
 *      to a CHIP Device.
 *
 */

#pragma once

#include <lib/core/CHIPError.h>
#include <lib/core/NodeId.h>
#include <lib/support/DLLUtil.h>
#include <protocols/secure_channel/RendezvousParameters.h>
#include <setup_payload/ManualSetupPayloadParser.h>
#include <setup_payload/QRCodeSetupPayloadParser.h>

#if CONFIG_DEVICE_LAYER
#include <platform/CHIPDeviceLayer.h>
#endif // CONFIG_DEVICE_LAYER

#if CONFIG_NETWORK_LAYER_BLE
#include <ble/BleLayer.h>
#endif // CONFIG_NETWORK_BLE

#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
#include <controller/DeviceDiscoveryDelegate.h>
#endif // CHIP_DEVICE_CONFIG_ENABLE_MDNS

namespace chip {
namespace Controller {

class DeviceCommissioner;

class DLL_EXPORT SetUpCodeParser
#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
    : public DeviceDiscoveryDelegate
#endif
{
public:
    SetUpCodeParser(DeviceCommissioner * commissioner) : mCommissioner(commissioner) {}
    virtual ~SetUpCodeParser() {}

    CHIP_ERROR PairDevice(chip::NodeId remoteId, const char * setUpCode);

private:
    CHIP_ERROR Connect(RendezvousInformationFlag rendezvousInformation, uint16_t discriminator, bool isShort);
    CHIP_ERROR StartConnectOverBle(uint16_t discriminator, bool isShort);
    CHIP_ERROR StopConnectOverBle();
    CHIP_ERROR StartConnectOverMdns(uint16_t discriminator, bool isShort);
    CHIP_ERROR StopConnectOverMdns();
    CHIP_ERROR StartConnectOverSoftAP(uint16_t discriminator, bool isShort);
    CHIP_ERROR StopConnectOverSoftAP();

    void OnDeviceDiscovered(RendezvousParameters & params);

#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
    /////////// DeviceDiscoveryDelegate Interface /////////
    void OnDiscoveredDevice(const chip::Mdns::DiscoveredNodeData & nodeData) override;
#endif // CHIP_DEVICE_CONFIG_ENABLE_MDNS

#if CONFIG_NETWORK_LAYER_BLE
    void OnDiscoveredDeviceOverBle(BLE_CONNECTION_OBJECT connObj);
    /////////// BLEConnectionDelegate Callbacks /////////
    static void OnDiscoveredDeviceOverBleSuccess(void * appState, BLE_CONNECTION_OBJECT connObj);
    static void OnDiscoveredDeviceOverBleError(void * appState, CHIP_ERROR err);
#endif // CONFIG_NETWORK_LAYER_BLE

    DeviceCommissioner * mCommissioner = nullptr;
    chip::NodeId mRemoteId;
    uint32_t mSetUpPINCode = 0;
};

} // namespace Controller
} // namespace chip
