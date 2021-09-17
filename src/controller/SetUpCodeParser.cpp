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
 *      Implementation of SetUp Code Parser, a class
 *      that implements parsing manual and QRCode for connecting
 *      to a CHIP Device.
 *
 */

#include <controller/SetUpCodeParser.h>

#include <controller/CHIPDeviceController.h>
#include <lib/mdns/Resolver.h>
#include <lib/support/CodeUtils.h>

namespace chip {
namespace Controller {

CHIP_ERROR SetUpCodeParser::PairDevice(NodeId remoteId, const char * setUpCode)
{
    SetupPayload payload;

    bool isQRCode = strncmp(setUpCode, kQRCodePrefix, strlen(kQRCodePrefix)) == 0;
    ReturnErrorOnFailure(isQRCode ? QRCodeSetupPayloadParser(setUpCode).populatePayload(payload)
                                  : ManualSetupPayloadParser(setUpCode).populatePayload(payload));

    mRemoteId     = remoteId;
    mSetUpPINCode = payload.setUpPINCode;

    return Connect(payload.rendezvousInformation, payload.discriminator, !isQRCode);
}

CHIP_ERROR SetUpCodeParser::Connect(RendezvousInformationFlag rendezvousInformation, uint16_t discriminator, bool isShort)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    bool isRunning = false;

    bool searchOverAll = rendezvousInformation == RendezvousInformationFlag::kNone;
    if (searchOverAll || rendezvousInformation == RendezvousInformationFlag::kBLE)
    {
        if (CHIP_NO_ERROR == (err = StartConnectOverBle(discriminator, isShort)))
        {
            isRunning = true;
        }
        VerifyOrReturnError(searchOverAll || CHIP_NO_ERROR == err, err);
    }

    if (searchOverAll || rendezvousInformation == RendezvousInformationFlag::kOnNetwork)
    {
        if (CHIP_NO_ERROR == (err = StartConnectOverMdns(discriminator, isShort)))
        {
            isRunning = true;
        }
        VerifyOrReturnError(searchOverAll || CHIP_NO_ERROR == err, err);
    }

    if (searchOverAll || rendezvousInformation == RendezvousInformationFlag::kSoftAP)
    {
        if (CHIP_NO_ERROR == (err = StartConnectOverSoftAP(discriminator, isShort)))
        {
            isRunning = true;
        }
        VerifyOrReturnError(searchOverAll || CHIP_NO_ERROR == err, err);
    }

    return isRunning ? CHIP_NO_ERROR : CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

CHIP_ERROR SetUpCodeParser::StartConnectOverBle(uint16_t discriminator, bool isShort)
{
#if CONFIG_NETWORK_LAYER_BLE
    Ble::BleLayer * bleLayer = DeviceLayer::ConnectivityMgr().GetBleLayer();
    VerifyOrReturnError(bleLayer != nullptr, CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE);
    return bleLayer->NewBleConnectionByDiscriminator(discriminator, this, OnDiscoveredDeviceOverBleSuccess,
                                                     OnDiscoveredDeviceOverBleError);
#else
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
#endif // CONFIG_NETWORK_LAYER_BLE
}

CHIP_ERROR SetUpCodeParser::StopConnectOverBle()
{
#if CONFIG_NETWORK_LAYER_BLE
    Ble::BleLayer * bleLayer = DeviceLayer::ConnectivityMgr().GetBleLayer();
    VerifyOrReturnError(bleLayer, CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE);
    return bleLayer->CancelBleIncompleteConnection();
#else
    return CHIP_NO_ERROR;
#endif // CONFIG_NETWORK_LAYER_BLE
}

CHIP_ERROR SetUpCodeParser::StartConnectOverMdns(uint16_t discriminator, bool isShort)
{
#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
    mCommissioner->RegisterDeviceDiscoveryDelegate(this);
    Mdns::DiscoveryFilter filter(isShort ? Mdns::DiscoveryFilterType::kShort : Mdns::DiscoveryFilterType::kLong, discriminator);
    return mCommissioner->DiscoverCommissionableNodes(filter);
#else
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
#endif // CHIP_DEVICE_CONFIG_ENABLE_MDNS
}

CHIP_ERROR SetUpCodeParser::StopConnectOverMdns()
{
#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
    mCommissioner->RegisterDeviceDiscoveryDelegate(nullptr);
#endif // CHIP_DEVICE_CONFIG_ENABLE_MDNS
    return CHIP_NO_ERROR;
}

CHIP_ERROR SetUpCodeParser::StartConnectOverSoftAP(uint16_t discriminator, bool isShort)
{
    return CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE;
}

CHIP_ERROR SetUpCodeParser::StopConnectOverSoftAP()
{
    return CHIP_NO_ERROR;
}

void SetUpCodeParser::OnDeviceDiscovered(RendezvousParameters & params)
{
    LogErrorOnFailure(mCommissioner->PairDevice(mRemoteId, params.SetSetupPINCode(mSetUpPINCode)));
}

#if CONFIG_NETWORK_LAYER_BLE
void SetUpCodeParser::OnDiscoveredDeviceOverBle(BLE_CONNECTION_OBJECT connObj)
{
    LogErrorOnFailure(StopConnectOverMdns());
    LogErrorOnFailure(StopConnectOverSoftAP());

    Transport::PeerAddress peerAddress = Transport::PeerAddress::BLE();
    RendezvousParameters params        = RendezvousParameters().SetPeerAddress(peerAddress).SetConnectionObject(connObj);
    OnDeviceDiscovered(params);
}

void SetUpCodeParser::OnDiscoveredDeviceOverBleSuccess(void * appState, BLE_CONNECTION_OBJECT connObj)
{
    (static_cast<SetUpCodeParser *>(appState))->OnDiscoveredDeviceOverBle(connObj);
}

void SetUpCodeParser::OnDiscoveredDeviceOverBleError(void * appState, CHIP_ERROR err)
{
    LogErrorOnFailure(err);
}
#endif // CONFIG_NETWORK_LAYER_BLE

#if CHIP_DEVICE_CONFIG_ENABLE_MDNS
void SetUpCodeParser::OnDiscoveredDevice(const Mdns::DiscoveredNodeData & nodeData)
{
    LogErrorOnFailure(StopConnectOverBle());
    LogErrorOnFailure(StopConnectOverMdns());
    LogErrorOnFailure(StopConnectOverSoftAP());

    Transport::PeerAddress peerAddress = Transport::PeerAddress::UDP(nodeData.ipAddress[0], nodeData.port, nodeData.interfaceId[0]);
    RendezvousParameters params        = RendezvousParameters().SetPeerAddress(peerAddress);
    OnDeviceDiscovered(params);
}
#endif // CHIP_DEVICE_CONFIG_ENABLE_MDNS

} // namespace Controller
} // namespace chip
