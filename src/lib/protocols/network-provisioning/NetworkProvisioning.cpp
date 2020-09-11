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
 *      This file implements the Chip Network Provisioning Profile, used
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
#include "NetworkProvisioning.h"

#include <Chip/Support/CodeUtils.h>
#include <protocols/CHIPProtocols.h>
#include <protocols/common/CommonProtocol.h>

namespace chip {
namespace Protocols {
namespace NetworkProvisioning {

using namespace ::chip::Encoding;
using namespace ::chip::TLV;

NetworkProvisioningServer::NetworkProvisioningServer()
{
    FabricState = NULL;
    ExchangeMgr = NULL;
    mCurOp = NULL;
    mDelegate = NULL;
}

/**
 * Initialize the Network Provisioning Server state and register to receive
 * Network Provisioning messages.
 *
 * @param[in] exchangeMgr   A pointer to the system Chip Exchange Manager.
 *
 * @retval #CHIP_ERROR_TOO_MANY_UNSOLICITED_MESSAGE_HANDLERS   If too many message handlers have
 *                                                              already been registered.
 * @retval #CHIP_NO_ERROR                                      On success.
 */
CHIP_ERROR NetworkProvisioningServer::Init(ChipExchangeManager *exchangeMgr)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    ExchangeMgr = exchangeMgr;
    FabricState = exchangeMgr->FabricState;
    mCurOp = NULL;
    mDelegate = NULL;
    mLastOpResult.StatusProfileId = kChipProtocol_Common;
    mLastOpResult.StatusCode = Common::kStatus_Success;
    mLastOpResult.SysError = CHIP_NO_ERROR;
    memset(&mCredentialAccessSession, 0, sizeof(mCredentialAccessSession));

    // Register to receive unsolicited Network Provisioning messages from the exchange manager.
    err =
        ExchangeMgr->RegisterUnsolicitedMessageHandler(kChipProtocol_NetworkProvisioning, HandleRequest, this);
    SuccessOrExit(err);

    err = RegisterSessionEndCallbackWithFabricState();

exit:

    return err;
}
/**
 * Shutdown the Network Provisioning Server.
 *
 * @retval #CHIP_NO_ERROR  On success.
 */
// TODO: Additional documentation detail required (i.e. how this function impacts object lifecycle).
CHIP_ERROR NetworkProvisioningServer::Shutdown()
{
    ExchangeMgr = NULL;
    FabricState = NULL;
    mCurOp = NULL;
    mDelegate = NULL;

    return CHIP_NO_ERROR;
}

/**
 * Set the delegate to process Network Provisioning Server events.
 *
 * @param[in] delegate  A pointer to the Network Provisioning Delegate.
 */
void NetworkProvisioningServer::SetDelegate(NetworkProvisioningDelegate *delegate)
{
    mDelegate = delegate;
    mDelegate->Server = this;
}

/**
 * Send a Network Scan Complete response message containing the results of the scan.
 *
 * @param[in]   resultCount     The number of scan results.
 * @param[in]   scanResultsTLV  The scan results.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE     If the Network Provisioning Server is not initialized correctly.
 * @retval #CHIP_ERROR_BUFFER_TOO_SMALL    If the results buffer is not large enough.
 * @retval #CHIP_NO_ERROR                  On success.
 * @retval other                            Other Chip or platform-specific error codes indicating that an error
 *                                          occurred preventing the device from sending the Scan Complete response.
 */
CHIP_ERROR NetworkProvisioningServer::SendNetworkScanComplete(uint8_t resultCount, PacketBuffer *scanResultsTLV)
{
    return SendCompleteWithNetworkList(kMsgType_NetworkScanComplete, resultCount, scanResultsTLV);
}

/**
 * Send a Get Networks Complete message containing the previously scanned networks.
 *
 * @param[in]   resultCount     The number of scan results.
 * @param[in]   scanResultsTLV  The scan results.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE     If the Network Provisioning Server is not initialized correctly.
 * @retval #CHIP_ERROR_BUFFER_TOO_SMALL    If the results buffer is not large enough.
 * @retval #CHIP_NO_ERROR                  On success.
 * @retval other                            Other Chip or platform-specific error codes indicating that an error
 *                                          occurred preventing the device from sending the Get Networks Complete message.
 */
CHIP_ERROR NetworkProvisioningServer::SendGetNetworksComplete(uint8_t resultCount, PacketBuffer *scanResultsTLV)
{
    return SendCompleteWithNetworkList(kMsgType_GetNetworksComplete, resultCount, scanResultsTLV);
}

CHIP_ERROR NetworkProvisioningServer::SendCompleteWithNetworkList(uint8_t msgType, int8_t resultCount, PacketBuffer *resultTLV)
{
    CHIP_ERROR err;
    uint8_t *p;

    VerifyOrExit(mDelegate != NULL, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mCurOp != NULL, err = CHIP_ERROR_INCORRECT_STATE);

    if (!resultTLV->EnsureReservedSize(CHIP_SYSTEM_CONFIG_HEADER_RESERVE_SIZE + 1))
        ExitNow(err = CHIP_ERROR_BUFFER_TOO_SMALL);

    p = resultTLV->Start() - 1;
    resultTLV->SetStart(p);

    *p = resultCount;

    err = mCurOp->SendMessage(kChipProtocol_NetworkProvisioning, msgType, resultTLV, 0);
    resultTLV = NULL;

    mLastOpResult.StatusProfileId = kChipProtocol_Common;
    mLastOpResult.StatusCode = Common::kStatus_Success;
    mLastOpResult.SysError = CHIP_NO_ERROR;

exit:
    if (mCurOp != NULL)
    {
        mCurOp->Close();
        mCurOp = NULL;
    }
    if (resultTLV != NULL)
        PacketBuffer::Free(resultTLV);
    return err;
}

/**
 * Send an Add Network Complete message if the network was successfully added.
 *
 * @param[in]   networkId   The ID of the added network.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE     If the Network Provisioning Server is not initialized correctly.
 * @retval #CHIP_ERROR_NO_MEMORY           On failure to allocate an PacketBuffer.
 * @retval #CHIP_NO_ERROR                  On success.
 * @retval other                            Other Chip or platform-specific error codes indicating that an error
 *                                          occurred preventing the device from sending the Add Network Complete message.
 */
CHIP_ERROR NetworkProvisioningServer::SendAddNetworkComplete(uint32_t networkId)
{
    CHIP_ERROR     err;
    PacketBuffer*   respBuf = NULL;
    uint8_t*        p;
    uint8_t         respLen = 4;

    VerifyOrExit(mDelegate != NULL, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mCurOp != NULL, err = CHIP_ERROR_INCORRECT_STATE);

    // Authorize the current session for privileged access to secret
    // credential information.
    if (mCurOp->EncryptionType != kChipEncryptionType_None &&
        ChipKeyId::IsSessionKey(mCurOp->KeyId))
    {
        GrantCredentialAccessPrivilege(mCurOp->KeyId, mCurOp->PeerNodeId);
    }

    respBuf = PacketBuffer::NewWithAvailableSize(respLen);
    VerifyOrExit(respBuf != NULL, err = CHIP_ERROR_NO_MEMORY);

    p = respBuf->Start();
    LittleEndian::Write32(p, networkId);
    respBuf->SetDataLength(respLen);

    err = mCurOp->SendMessage(kChipProtocol_NetworkProvisioning, kMsgType_AddNetworkComplete, respBuf, 0);
    respBuf = NULL;

    mLastOpResult.StatusProfileId = kChipProtocol_Common;
    mLastOpResult.StatusCode = Common::kStatus_Success;
    mLastOpResult.SysError = CHIP_NO_ERROR;

exit:
    if (mCurOp != NULL)
    {
        mCurOp->Close();
        mCurOp = NULL;
    }
    if (respBuf != NULL)
        PacketBuffer::Free(respBuf);
    return err;
}

/**
 * Send a GetWirelessRegulatoryConfigComplete message to the peer.
 *
 * @param[in]   resultsTLV   A packet buffer containing the wireless regulatory configuration information
 *                           to be returned.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE     If the Network Provisioning Server is not initialized correctly.
 * @retval #CHIP_ERROR_NO_MEMORY           On failure to allocate an PacketBuffer.
 * @retval #CHIP_NO_ERROR                  On success.
 * @retval other                            Other Chip or platform-specific error codes indicating that an error
 *                                          occurred preventing the device from sending the Add Network Complete message.
 */
CHIP_ERROR NetworkProvisioningServer::SendGetWirelessRegulatoryConfigComplete(PacketBuffer *resultsTLV)
{
    CHIP_ERROR err;

    VerifyOrExit(mDelegate != NULL, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mCurOp != NULL, err = CHIP_ERROR_INCORRECT_STATE);

    err = mCurOp->SendMessage(kChipProtocol_NetworkProvisioning, kMgrType_GetWirelessRegulatoryConfigComplete, resultsTLV, 0);
    resultsTLV = NULL;

    mLastOpResult.StatusProfileId = kChipProtocol_Common;
    mLastOpResult.StatusCode = Common::kStatus_Success;
    mLastOpResult.SysError = CHIP_NO_ERROR;

exit:
    if (mCurOp != NULL)
    {
        mCurOp->Close();
        mCurOp = NULL;
    }
    PacketBuffer::Free(resultsTLV);
    return err;
}

/**
 * Send a success response to a Network Provisioning request.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE If there is no request being processed.
 * @retval #CHIP_NO_ERROR              On success.
 * @retval other                        Other Chip or platform-specific error codes indicating that an error
 *                                      occurred preventing the device from sending the success response.
 */
CHIP_ERROR NetworkProvisioningServer::SendSuccessResponse()
{
    return SendStatusReport(kChipProtocol_Common, Common::kStatus_Success);
}

/**
 * Send a status report response to a request.
 *
 * @param[in]   statusProfileId     The Chip profile ID this status report pertains to.
 * @param[in]   statusCode          The status code to be included in this response.
 * @param[in]   sysError            The system error code to be included in this response.
 *
 * @retval #CHIP_ERROR_INCORRECT_STATE If there is no request being processed.
 * @retval #CHIP_NO_ERROR              On success.
 * @retval other                        Other Chip or platform-specific error codes indicating that an error
 *                                      occurred preventing the device from sending the status report.
 */
CHIP_ERROR NetworkProvisioningServer::SendStatusReport(uint32_t statusProfileId, uint16_t statusCode, CHIP_ERROR sysError)
{
    CHIP_ERROR err;

    VerifyOrExit(mDelegate != NULL, err = CHIP_ERROR_INCORRECT_STATE);
    VerifyOrExit(mCurOp != NULL, err = CHIP_ERROR_INCORRECT_STATE);

    err = ChipServerBase::SendStatusReport(mCurOp, statusProfileId, statusCode, sysError);

    mLastOpResult.StatusProfileId = statusProfileId;
    mLastOpResult.StatusCode = statusCode;
    mLastOpResult.SysError = sysError;

exit:

    if (mCurOp != NULL)
    {
        mCurOp->Close();
        mCurOp = NULL;
    }

    return err;
}

/**
 * Indicates if the session with the given node id and the session key id is
 * authorized to retrieve secret credential information.
 *
 * @return Returns 'true' if the given peer is privileged, else
 * 'false'.
 */

bool NetworkProvisioningServer::SessionHasCredentialAccessPrivilege(uint16_t keyId, uint64_t peerNodeId) const
{
    return (peerNodeId == mCredentialAccessSession.PeerNodeId &&
            keyId == mCredentialAccessSession.SessionKeyId);
}

void NetworkProvisioningServer::GrantCredentialAccessPrivilege(uint16_t keyId, uint64_t peerNodeId)
{
    mCredentialAccessSession.PeerNodeId = peerNodeId;
    mCredentialAccessSession.SessionKeyId = keyId;
}

void NetworkProvisioningServer::ClearCredentialAccessPrivilege(void)
{
    memset(&mCredentialAccessSession, 0, sizeof(mCredentialAccessSession));
}

void NetworkProvisioningServer::HandleSessionEnd(uint16_t keyId, uint64_t peerNodeId, void *context)
{
    NetworkProvisioningServer *server = static_cast<NetworkProvisioningServer *>(context);

    // Clear the privileged session when notified of its removal by FabricState
    if (server->SessionHasCredentialAccessPrivilege(keyId, peerNodeId))
    {
        server->ClearCredentialAccessPrivilege();
    }
}

CHIP_ERROR NetworkProvisioningServer::RegisterSessionEndCallbackWithFabricState(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    mSessionEndCbCtxt.OnSessionRemoved = HandleSessionEnd;
    mSessionEndCbCtxt.context = this;
    mSessionEndCbCtxt.next = NULL;

    err = FabricState->RegisterSessionEndCallback(&mSessionEndCbCtxt);

    return err;
}

void NetworkProvisioningServer::HandleRequest(ExchangeContext *ec, const IPPacketInfo *pktInfo, const ChipMessageInfo *msgInfo, uint32_t profileId,
        uint8_t msgType, PacketBuffer *payload)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    NetworkProvisioningServer *server = (NetworkProvisioningServer *) ec->AppState;
    NetworkProvisioningDelegate *delegate = server->mDelegate;
    uint32_t networkId;
    uint16_t rendezvousMode;
    uint8_t networkType;
    uint8_t flags;
    uint16_t dataLen;
    const uint8_t *p;

    // Fail messages for the wrong profile. This shouldn't happen, but better safe than sorry.
    if (profileId != kChipProtocol_NetworkProvisioning)
    {
        ChipServerBase::SendStatusReport(ec, kChipProtocol_Common, Common::kStatus_BadRequest, CHIP_NO_ERROR);
        ec->Close();
        ExitNow();
    }

    // Call on the delegate to enforce message-level access control.  If policy dictates the message should NOT
    // be processed, then simply end the exchange and return.  If an error response was warranted, the appropriate
    // response will have been sent within EnforceAccessControl().
    if (!server->EnforceAccessControl(ec, profileId, msgType, msgInfo, server->mDelegate))
    {
        ec->Close();
        ExitNow();
    }

    // Disallow simultaneous requests.
    if (server->mCurOp != NULL)
    {
        ChipServerBase::SendStatusReport(ec, kChipProtocol_Common, Common::kStatus_Busy, CHIP_NO_ERROR);
        ec->Close();
        ExitNow();
    }

    // Record that we have a request in process.
    server->mCurOp = ec;
    server->mCurOpType = msgType;

    dataLen = payload->DataLength();
    p = payload->Start();

    // Decode and dispatch the message.
    switch (msgType)
    {
    case kMsgType_ScanNetworks:
        VerifyOrExit(dataLen >= 1, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        networkType = Get8(p);
        PacketBuffer::Free(payload);
        payload = NULL;
        err = delegate->HandleScanNetworks(networkType);
        break;

#if CHIP_CONFIG_SUPPORT_LEGACY_ADD_NETWORK_MESSAGE
    case kMsgType_AddNetwork:
#endif
    case kMsgType_AddNetworkV2:
        VerifyOrExit(dataLen >= 1, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        err = delegate->HandleAddNetwork(payload);
        payload = NULL;
        break;

    case kMsgType_UpdateNetwork:
        VerifyOrExit(dataLen >= 1, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        err = delegate->HandleUpdateNetwork(payload);
        payload = NULL;
        break;

    case kMsgType_RemoveNetwork:
    case kMsgType_EnableNetwork:
    case kMsgType_DisableNetwork:
    case kMsgType_TestConnectivity:
        VerifyOrExit(dataLen >= 4, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        networkId = LittleEndian::Read32(p);
        PacketBuffer::Free(payload);
        payload = NULL;
        if (msgType == kMsgType_RemoveNetwork)
            err = delegate->HandleRemoveNetwork(networkId);
        else if (msgType == kMsgType_EnableNetwork)
            err = delegate->HandleEnableNetwork(networkId);
        else if (msgType == kMsgType_DisableNetwork)
            err = delegate->HandleDisableNetwork(networkId);
        else if (msgType == kMsgType_TestConnectivity)
            err = delegate->HandleTestConnectivity(networkId);
        break;

    case kMsgType_GetNetworks:
        VerifyOrExit(dataLen >= 1, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        flags = *p;
        PacketBuffer::Free(payload);
        payload = NULL;

#if CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV

        // According to Chip Device Access Control Policy,
        // When servicing a GetNetworks message from a peer that has authenticated using PASE/PairingCode,
        // a device in an unpaired state must reject the message with an access denied error if the peer has
        // set the IncludeCredentials flag and the current session is not privileged to retrieve secret
        // credentials.
        if (msgInfo->PeerAuthMode == kChipAuthMode_PASE_PairingCode && !delegate->IsPairedToAccount()
                && (flags & kGetNetwork_IncludeCredentials) != 0
                && !server->SessionHasCredentialAccessPrivilege(msgInfo->KeyId, msgInfo->SourceNodeId))
        {
            server->SendStatusReport(kChipProtocol_Common, Common::kStatus_AccessDenied);
            break;
        }
#endif // CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV

        err = delegate->HandleGetNetworks(flags);
        break;

    case kMsgType_SetRendezvousMode:
        VerifyOrExit(dataLen >= 2, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        rendezvousMode = LittleEndian::Read16(p);

        PacketBuffer::Free(payload);
        payload = NULL;

#if CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV

        // Per device access control policy, when servicing a SetRendezvousMode message from a peer that has authenticated using
        // PASE/PairingCode, a device in a paired state should reject a SetRendezvousMode message with an access denied error if
        // the requested mode is not 0--i.e. if the peer requests to *enable* any rendezvous mode.
        if (rendezvousMode != 0 && msgInfo->PeerAuthMode == kChipAuthMode_PASE_PairingCode && delegate->IsPairedToAccount())
        {
            server->SendStatusReport(kChipProtocol_Common, Common::kStatus_AccessDenied);
            break;
        }

#endif // CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV

        err = delegate->HandleSetRendezvousMode(rendezvousMode);
        break;

    case kMsgType_GetLastResult:
        err = server->SendStatusReport(server->mLastOpResult.StatusProfileId, server->mLastOpResult.StatusCode, server->mLastOpResult.SysError);
        break;

    case kMsgType_GetWirelessRegulatoryConfig:
        err = delegate->HandleGetWirelessRegulatoryConfig();
        break;

    case kMsgType_SetWirelessRegulatoryConfig:
        VerifyOrExit(dataLen >= 1, err = CHIP_ERROR_INVALID_MESSAGE_LENGTH);
        err = delegate->HandleSetWirelessRegulatoryConfig(payload);
        payload = NULL;
        break;

    default:
        server->SendStatusReport(kChipProtocol_Common, Common::kStatus_UnsupportedMessage);
        break;
    }

exit:

    if (err != CHIP_NO_ERROR && server->mCurOp != NULL)
    {
        uint16_t statusCode =
                (err == CHIP_ERROR_INVALID_MESSAGE_LENGTH) ? Common::kStatus_BadRequest : Common::kStatus_InternalError;
        server->SendStatusReport(kChipProtocol_Common, statusCode, err);
    }

    if (payload != NULL)
        PacketBuffer::Free(payload);
}

CHIP_ERROR NetworkProvisioningDelegate::HandleGetWirelessRegulatoryConfig(void)
{
    Server->SendStatusReport(kChipProtocol_Common, Common::kStatus_UnsupportedMessage);
    return CHIP_NO_ERROR;
}

CHIP_ERROR NetworkProvisioningDelegate::HandleSetWirelessRegulatoryConfig(PacketBuffer * regConfigTLV)
{
    PacketBuffer::Free(regConfigTLV);
    Server->SendStatusReport(kChipProtocol_Common, Common::kStatus_UnsupportedMessage);
    return CHIP_NO_ERROR;
}

void NetworkProvisioningDelegate::EnforceAccessControl(ExchangeContext *ec, uint32_t msgProfileId, uint8_t msgType,
        const ChipMessageInfo *msgInfo, AccessControlResult& result)
{
    // If the result has not already been determined by a subclass...
    if (result == kAccessControlResult_NotDetermined)
    {
        switch (msgType)
        {
        case kMsgType_ScanNetworks:
#if CHIP_CONFIG_SUPPORT_LEGACY_ADD_NETWORK_MESSAGE
        case kMsgType_AddNetwork:
#endif
        case kMsgType_AddNetworkV2:
        case kMsgType_UpdateNetwork:
        case kMsgType_RemoveNetwork:
        case kMsgType_EnableNetwork:
        case kMsgType_DisableNetwork:
        case kMsgType_TestConnectivity:
        case kMsgType_GetNetworks:
        case kMsgType_GetWirelessRegulatoryConfig:
        case kMsgType_SetWirelessRegulatoryConfig:
        case kMsgType_GetLastResult:
#if CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV
            if (msgInfo->PeerAuthMode == kChipAuthMode_CASE_AccessToken ||
                (msgInfo->PeerAuthMode == kChipAuthMode_PASE_PairingCode && !IsPairedToAccount()))
#endif // CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV
            {
                result = kAccessControlResult_Accepted;
            }
            break;
        case kMsgType_SetRendezvousMode:
#if CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV
            if (msgInfo->PeerAuthMode == kChipAuthMode_CASE_AccessToken ||
                msgInfo->PeerAuthMode == kChipAuthMode_PASE_PairingCode)
#endif // CHIP_CONFIG_REQUIRE_AUTH_NETWORK_PROV
            {
                result = kAccessControlResult_Accepted;
            }
            break;

        default:
            ChipServerBase::SendStatusReport(ec, kChipProtocol_Common, Common::kStatus_UnsupportedMessage, CHIP_NO_ERROR);
            result = kAccessControlResult_Rejected_RespSent;
            break;
        }
    }

    // Call up to the base class.
    ChipServerDelegateBase::EnforceAccessControl(ec, msgProfileId, msgType, msgInfo, result);
}

// TODO: eliminate this method when device code provides appropriate implementations.
bool NetworkProvisioningDelegate::IsPairedToAccount() const
{
    return false;
}

} // namespace NetworkProvisioning
} // namespace Protocols
} // namespace chip
