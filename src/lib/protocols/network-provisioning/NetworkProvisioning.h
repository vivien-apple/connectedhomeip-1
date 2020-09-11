/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2013-2017 Nest Labs, Inc.
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
 *      This file defines the Network Provisioning Profile, used
 *      to configure network interfaces.
 *
 *      The Network Provisioning Profile facilitates client-server
 *      operations such that the client (the controlling device) can
 *      trigger specific network functionality on the server (the device
 *      undergoing network provisioning).  These operations revolve around
 *      the steps necessary to provision the server device's network
 *      interfaces (such as 802.15.4/Thread and 802.11/Wi-Fi) provisioned
 *      such that the device may participate in those networks.  This includes
 *      scanning and specifying network names and security credentials.
 *
 */

#ifndef NETWORKPROVISIONING_H_
#define NETWORKPROVISIONING_H_

#include <core/CHIPCore.h>
#include <core/CHIPEncoding.h>
#include <core/CHIPTLV.h>
#include <message/CHIPServerBase.h>
#include <support/DLLUtil.h>

/**
 *   @namespace chip::Protocols::NetworkProvisioning
 *
 *   @brief
 *     This namespace includes all interfaces within Chip for the
 *     CHIP Network Provisioning profile, the first of the three
 *     CHIP provisioning profiles.
 *
 *     The interfaces define status codes, message types, data element
 *     tags, other constants, a server object, and a delegate object.
 *
 *     The Chip Network Provisioning Profile is focused on
 *     providing the data to get the network interfaces, such as
 *     802.15.4/Thread and 802.11/Wi-Fi, for a Chip device
 *     provisioned such that the device may participate in those
 *     networks.
 */

namespace chip {
namespace Protocols {
namespace NetworkProvisioning {

class NetworkProvisioningServer;

/**
 *  Network Provisioning Status Codes.
 */
enum
{
    kStatusCode_UnknownNetwork              = 1, /**< A provisioned network with the specified network ID was not found. */
    kStatusCode_TooManyNetworks             = 2, /**< The maximum number of provisioned networks has been reached. */
    kStatusCode_InvalidNetworkConfiguration = 3, /**< The specified network configuration is invalid. */
    kStatusCode_UnsupportedNetworkType      = 4, /**< The specified network type is unknown or unsupported. */
    kStatusCode_UnsupportedWiFiMode         = 5, /**< The specified WiFi mode is unsupported. */
    kStatusCode_UnsupportedWiFiRole         = 6, /**< The specified WiFi role is unsupported. */
    kStatusCode_UnsupportedWiFiSecurityType = 7, /**< The specified WiFi security type is unsupported. */
    kStatusCode_InvalidState      = 8, /**< The network provisioning operation could not be performed in the current state. */
    kStatusCode_TestNetworkFailed = 9, /**< The connectivity test of the specified network failed. */
                                       // XXX Placeholder for more detailed errors to come
    kStatusCode_NetworkConnectFailed         = 10, /**< An attempt to connect to the specified network failed. */
    kStatusCode_NoRouterAvailable            = 11, /**< An appropriate network router was not found. */
    kStatusCode_UnsupportedRegulatoryDomain  = 12, /**< The specified wireless regulatory domain is unsupported. */
    kStatusCode_UnsupportedOperatingLocation = 13, /**< The specified wireless operating location is unsupported. */
};

/**
 * Network Provisioning Message Types.
 */
enum
{
    kMsgType_ScanNetworks                        = 1,
    kMsgType_NetworkScanComplete                 = 2,
    kMsgType_AddNetwork                          = 3,
    kMsgType_AddNetworkComplete                  = 4,
    kMsgType_UpdateNetwork                       = 5,
    kMsgType_RemoveNetwork                       = 6,
    kMsgType_EnableNetwork                       = 7,
    kMsgType_DisableNetwork                      = 8,
    kMsgType_TestConnectivity                    = 9,
    kMsgType_SetRendezvousMode                   = 10,
    kMsgType_GetNetworks                         = 11,
    kMsgType_GetNetworksComplete                 = 12,
    kMsgType_GetLastResult                       = 13,
    kMsgType_AddNetworkV2                        = 14,
    kMsgType_SetWirelessRegulatoryConfig         = 15,
    kMsgType_GetWirelessRegulatoryConfig         = 16,
    kMgrType_GetWirelessRegulatoryConfigComplete = 17,
};

/**
 * @anchor NetworkProvisioningDataElementTags
 * Network Provisioning Data Element Tags.
 */
enum
{
    // Top-level Data Elements (profile-specific).
    kTag_Networks        = 1, /**< [ array ] An array of NetworkConfiguration structures. */
    kTag_EnabledNetworks = 2, /**< [ array ] An array of NetworkIds identifying the networks currently enabled on the device. */
    kTag_RendezvousMode  = 3, /**< [ uint ] A bit field indicating the currently active rendezvous mode. */

    // General-Purpose Data Elements (profile-specific).
    kTag_NetworkInformation = 32, /**< [ struct ] A structure containing information for a network. */
    kTag_NetworkId          = 33, /**< [ uint, 32-bit max ] An integer uniquely identifying a provisioned network. */
    kTag_NetworkType        = 34, /**< [ uint, 8-bit max ] An unsigned integer value identifying the type of a network. */
    kTag_WirelessSignalStrength =
        35, /**< [ int, 16-bit max ] An signed integer value giving the signal strength of a wireless network in dBm. */

    // WiFi Data Elements (Profile-specific).
    kTag_WiFiSSID = 64, /**< [ UTF-8 string ] A string containing a WiFi SSID. */
    kTag_WiFiMode = 65, /**< [ uint, 8-bit max ] An integer identify the mode of operation of the WiFi network. */
    kTag_WiFiRole = 66, /**< [ uint, 8-bit max ] An integer identify the role the device plays in the WiFi network. */
    kTag_WiFiSecurityType =
        67, /**< [ uint, 8-bit max ] An integer value identifying the type of security used by a WiFi network. */
    kTag_WiFiPreSharedKey = 68, /**< [ byte string ] A byte string containing the WiFi password/pre-shared key. */

    // Thread Data Elements (profile-specific).
    kTag_ThreadExtendedPANId = 80, /**< [ byte string ] The Thread extended PAN ID. */
    kTag_ThreadNetworkName   = 81, /**< [ UTF-8 string ] A UTF-8 string containing the name of the Thread network. */
    kTag_ThreadNetworkKey    = 82, /**< [ bytes string ] The Thread master network key. */
    kTag_ThreadMeshPrefix    = 83, /**< [ bytes string, exactly 8 bytes ] Thread mesh IPv6 /64 prefix (optional). */
    kTag_ThreadChannel       = 84, /**< [ uint, 8-bit max ] Thread channel number (optional). */
    kTag_ThreadPANId         = 85, /**< [ uint, 16-bit max ] Thread PAN ID (optional). */
    kTag_ThreadPSKc          = 86, /**< [ uint, 16-bit max ] Thread PSKc (optional). */

    // Wireless Regulatory Config Tags (context-specific)
    kTag_WirelessRegConfig_RegulatoryDomain = 1, /**< [ UTF-8 string, len 2 ] Wireless regulatory domain. */
    kTag_WirelessRegConfig_OperatingLocation =
        2, /**< [ uint enum, 8-bit max ] Operating location relevant to wireless regulatory rules. */
    kTag_WirelessRegConfig_SupportedRegulatoryDomains = 3, /**< [ array of string len 2 ] List of support regulatory domains. */
};

/**
 * Network Types.
 */
enum NetworkType
{
    kNetworkType_NotSpecified = -1,

    kNetworkType_WiFi   = 1,
    kNetworkType_Thread = 2
};

/**
 * WiFi Security Modes.
 */
enum WiFiSecurityType
{
    kWiFiSecurityType_NotSpecified = -1,

    kWiFiSecurityType_None                = 1,
    kWiFiSecurityType_WEP                 = 2,
    kWiFiSecurityType_WPAPersonal         = 3,
    kWiFiSecurityType_WPA2Personal        = 4,
    kWiFiSecurityType_WPA2MixedPersonal   = 5,
    kWiFiSecurityType_WPAEnterprise       = 6,
    kWiFiSecurityType_WPA2Enterprise      = 7,
    kWiFiSecurityType_WPA2MixedEnterprise = 8,
    kWiFiSecurityType_WPA3Personal        = 9,
    kWiFiSecurityType_WPA3MixedPersonal   = 10,
    kWiFiSecurityType_WPA3Enterprise      = 11,
    kWiFiSecurityType_WPA3MixedEnterprise = 12,
};

/**
 * WiFi Operating Modes.
 */
enum WiFiMode
{
    kWiFiMode_NotSpecified = -1,

    kWiFiMode_AdHoc   = 1,
    kWiFiMode_Managed = 2
};

/**
 * Device WiFi Role.
 */
enum WiFiRole
{
    kWiFiRole_NotSpecified = -1,

    kWiFiRole_Station     = 1,
    kWiFiRole_AccessPoint = 2
};

/**
 * Thread PAN Id.
 */
enum
{
    kThreadPANId_NotSpecified = UINT32_MAX
};

/**
 * Thread Channel.
 */
enum
{
    kThreadChannel_NotSpecified = UINT8_MAX
};

/**
 * Rendezvous Mode Flags.
 */
enum RendezvousModeFlags
{
    kRendezvousMode_EnableWiFiRendezvousNetwork = 0x0001,
    kRendezvousMode_EnableThreadRendezvous      = 0x0002
};

/**
 * Get Network Flags.
 */
enum GetNetworkFlags
{
    kGetNetwork_IncludeCredentials = 0x01
};

/**
 * Delegate class for implementing Network Provisioning operations.
 */
class NetworkProvisioningDelegate
{
public:
    NetworkProvisioningServer * Server;         /**< [READ ONLY] The server object to which this delegate is attached. */

   /**
     * Perform a network scan.
     *
     * @param[in] networkType   The technology (for example, WiFi or Thread) to scan.  @sa #NetworkType for valid types.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from performing a network scan.
     */
    virtual CHIP_ERROR HandleScanNetworks(uint8_t networkType) = 0;

    /**
     * Add a particular network.
     *
     * @param[in] networkInfoTLV    The network configuration encoded in TLV.  @sa @ref NetworkProvisioningDataElementTags for valid types.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from adding the network.
     */
    virtual CHIP_ERROR HandleAddNetwork(PacketBuffer *networkInfoTLV) = 0;

    /**
     * Update a network's configuration.
     *
     * @param[in] networkInfoTLV    The network configuration encoded in TLV.  @sa @ref NetworkProvisioningDataElementTags for valid types.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from updating the network.
     */
    virtual CHIP_ERROR HandleUpdateNetwork(PacketBuffer *networkInfoTLV) = 0;

    /**
     * Remove a configured network.
     *
     * @param[in] networkId     The ID of the network to remove.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from removing the network.
     */
    virtual CHIP_ERROR HandleRemoveNetwork(uint32_t networkId) = 0;

    /**
     * Get the configured networks.
     *
     * @param[in] flags     Flags to filter the retrieved networks.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from getting the configured networks.
     */
    virtual CHIP_ERROR HandleGetNetworks(uint8_t flags) = 0;

    /**
     * Enable the specified network.
     *
     * @param[in] networkId     The ID of the network to enable.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from enabling the network.
     */
    virtual CHIP_ERROR HandleEnableNetwork(uint32_t networkId) = 0;

    /**
     * Disable the specified network.
     *
     * @param[in] networkId     The ID of the network to disable.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from disabling the network.
     */
    virtual CHIP_ERROR HandleDisableNetwork(uint32_t networkId) = 0;

    /**
     * Test the connectivity of the specified network.
     *
     * @param[in] networkId     The ID of the network to test the connectivity of.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from testing connectivity.
     */
    virtual CHIP_ERROR HandleTestConnectivity(uint32_t networkId) = 0;

    /**
     * Set the rendezvous mode.
     *
     * @param[in] rendezvousMode    The rendezvous mode to use.  @sa #RendezvousModeFlags for valid modes.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from setting the rendezvous mode.
     */
    virtual CHIP_ERROR HandleSetRendezvousMode(uint16_t rendezvousMode) = 0;

    /**
     * Get wireless regulatory configuration information.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from fetching the requested information.
     */
    virtual CHIP_ERROR HandleGetWirelessRegulatoryConfig(void);

    /**
     * Set wireless regulatory configuration information.
     *
     * @param[in] regConfigTLV  A packet buffer containing the new wireless regulatory configuration
     *                          information encoded in TLV format.
     *
     * @retval #CHIP_NO_ERROR  On success.
     * @retval other            Other Chip or platform-specific error codes indicating that an error
     *                          occurred preventing the device from setting the requested information.
     */
    virtual CHIP_ERROR HandleSetWirelessRegulatoryConfig(PacketBuffer * regConfigTLV);

    /**
     * Called to determine if the device is currently paired to an account.
     */
    // TODO: make this pure virtual when product code provides appropriate implementations.
    virtual bool IsPairedToAccount() const;
};

/**
 * Server class for implementing the Network Provisioning profile.
 */
// TODO: Additional documentation detail required (i.e. expected class usage, number in the system, instantiation requirements,
// lifetime).
class DLL_EXPORT NetworkProvisioningServer : public ChipServerBase
{
public:
    NetworkProvisioningServer(void);

    CHIP_ERROR Init(ChipExchangeManager *exchangeMgr);
    CHIP_ERROR Shutdown(void);

    void SetDelegate(NetworkProvisioningDelegate *delegate);

    virtual CHIP_ERROR SendNetworkScanComplete(uint8_t resultCount, PacketBuffer *scanResultsTLV);
    virtual CHIP_ERROR SendAddNetworkComplete(uint32_t networkId);
    virtual CHIP_ERROR SendGetNetworksComplete(uint8_t resultCount, PacketBuffer *resultsTLV);
    virtual CHIP_ERROR SendGetWirelessRegulatoryConfigComplete(PacketBuffer *resultsTLV);
    virtual CHIP_ERROR SendSuccessResponse(void);
    virtual CHIP_ERROR SendStatusReport(uint32_t statusProfileId, uint16_t statusCode, CHIP_ERROR sysError = CHIP_NO_ERROR);

protected:
    ExchangeContext *mCurOp;
    NetworkProvisioningDelegate *mDelegate;
    struct
    {
        uint32_t StatusProfileId;
        uint16_t StatusCode;
        CHIP_ERROR SysError;
    } mLastOpResult;
    uint8_t mCurOpType;

private:
    static void HandleRequest(ExchangeContext *ec, const IPPacketInfo *pktInfo, const ChipMessageInfo *msgInfo, uint32_t profileId,
            uint8_t msgType, PacketBuffer *payload);
    CHIP_ERROR SendCompleteWithNetworkList(uint8_t msgType, int8_t resultCount, PacketBuffer *resultTLV);

    // Utility functions for managing registration with/notification from ChipFabricState about whether the
    // current security session is privileged to access network credential information.

    // Check if the session is marked as privileged to retrieve secret
    // credential information.
    bool SessionHasCredentialAccessPrivilege(uint16_t keyId, uint64_t peerNodeId) const;

    void GrantCredentialAccessPrivilege(uint16_t keyId, uint64_t peerNodeId);
    void ClearCredentialAccessPrivilege(void);
    static void HandleSessionEnd(uint16_t keyId, uint64_t peerNodeId, void *context);
    CHIP_ERROR RegisterSessionEndCallbackWithFabricState(void);

    NetworkProvisioningServer(const NetworkProvisioningServer&);   // not defined

    // Indicates the session that is privileged to
    // retrieve secret credential information.
    struct CredentialAccessSession
    {
        uint64_t PeerNodeId;
        uint16_t SessionKeyId;
    };
    CredentialAccessSession mCredentialAccessSession;

    chip::ChipFabricState::SessionEndCbCtxt mSessionEndCbCtxt;

};

} // namespace NetworkProvisioning
} // namespace Protocols
} // namespace chip

#endif /* NETWORKPROVISIONING_H_ */
