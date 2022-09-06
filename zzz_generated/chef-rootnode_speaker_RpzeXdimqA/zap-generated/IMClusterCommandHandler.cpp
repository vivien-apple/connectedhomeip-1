/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

// THIS FILE IS GENERATED BY ZAP

#include <cinttypes>
#include <cstdint>

#include <app-common/zap-generated/af-structs.h>
#include <app-common/zap-generated/callback.h>
#include <app-common/zap-generated/cluster-objects.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app-common/zap-generated/ids/Commands.h>
#include <app/CommandHandler.h>
#include <app/InteractionModelEngine.h>
#include <app/util/util.h>
#include <lib/core/CHIPSafeCasts.h>
#include <lib/support/TypeTraits.h>

// Currently we need some work to keep compatible with ember lib.
#include <app/util/ember-compatibility-functions.h>

namespace chip {
namespace app {

namespace {
void MaybeDispatchServerError(CommandHandler * handler, const ConcreteCommandPath & path, CHIP_ERROR error)
{
    VerifyOrReturn(CHIP_NO_ERROR != error);

    if (error == CHIP_IM_GLOBAL_STATUS(UnsupportedCluster))
    {
        ChipLogError(Zcl, "Unknown cluster " ChipLogFormatMEI, ChipLogValueMEI(path.mClusterId));
    }
    else if (error == CHIP_IM_GLOBAL_STATUS(UnsupportedCommand))
    {
        // Unrecognized command ID, error status will apply.
        ChipLogError(Zcl, "Unknown command " ChipLogFormatMEI " for cluster " ChipLogFormatMEI, ChipLogValueMEI(path.mCommandId),
                     ChipLogValueMEI(path.mClusterId));
    }
    else
    {
        ChipLogProgress(Zcl, "Failed to dispatch command, Error=%" CHIP_ERROR_FORMAT, error.Format());
    }

    auto status = error.IsIMStatus() ? StatusIB(error).mStatus : Protocols::InteractionModel::Status::InvalidCommand;
    handler->AddStatus(path, status);
}
} // namespace

// Cluster specific command parsing

namespace Clusters {

namespace AdministratorCommissioning {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::OpenCommissioningWindow::Id: {
        Commands::OpenCommissioningWindow::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfAdministratorCommissioningClusterOpenCommissioningWindowCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::OpenBasicCommissioningWindow::Id: {
        Commands::OpenBasicCommissioningWindow::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfAdministratorCommissioningClusterOpenBasicCommissioningWindowCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::RevokeCommissioning::Id: {
        Commands::RevokeCommissioning::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfAdministratorCommissioningClusterRevokeCommissioningCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace AdministratorCommissioning

namespace DiagnosticLogs {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::RetrieveLogsRequest::Id: {
        Commands::RetrieveLogsRequest::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfDiagnosticLogsClusterRetrieveLogsRequestCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace DiagnosticLogs

namespace EthernetNetworkDiagnostics {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ResetCounts::Id: {
        Commands::ResetCounts::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfEthernetNetworkDiagnosticsClusterResetCountsCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace EthernetNetworkDiagnostics

namespace GeneralCommissioning {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ArmFailSafe::Id: {
        Commands::ArmFailSafe::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGeneralCommissioningClusterArmFailSafeCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::SetRegulatoryConfig::Id: {
        Commands::SetRegulatoryConfig::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGeneralCommissioningClusterSetRegulatoryConfigCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::CommissioningComplete::Id: {
        Commands::CommissioningComplete::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGeneralCommissioningClusterCommissioningCompleteCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace GeneralCommissioning

namespace GeneralDiagnostics {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::TestEventTrigger::Id: {
        Commands::TestEventTrigger::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGeneralDiagnosticsClusterTestEventTriggerCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace GeneralDiagnostics

namespace GroupKeyManagement {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::KeySetWrite::Id: {
        Commands::KeySetWrite::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupKeyManagementClusterKeySetWriteCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::KeySetRead::Id: {
        Commands::KeySetRead::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupKeyManagementClusterKeySetReadCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::KeySetRemove::Id: {
        Commands::KeySetRemove::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupKeyManagementClusterKeySetRemoveCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::KeySetReadAllIndices::Id: {
        Commands::KeySetReadAllIndices::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupKeyManagementClusterKeySetReadAllIndicesCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace GroupKeyManagement

namespace Groups {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::AddGroup::Id: {
        Commands::AddGroup::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterAddGroupCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::ViewGroup::Id: {
        Commands::ViewGroup::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterViewGroupCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::GetGroupMembership::Id: {
        Commands::GetGroupMembership::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterGetGroupMembershipCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::RemoveGroup::Id: {
        Commands::RemoveGroup::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterRemoveGroupCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::RemoveAllGroups::Id: {
        Commands::RemoveAllGroups::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterRemoveAllGroupsCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::AddGroupIfIdentifying::Id: {
        Commands::AddGroupIfIdentifying::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfGroupsClusterAddGroupIfIdentifyingCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace Groups

namespace Identify {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::Identify::Id: {
        Commands::Identify::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfIdentifyClusterIdentifyCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace Identify

namespace LevelControl {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::MoveToLevel::Id: {
        Commands::MoveToLevel::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterMoveToLevelCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::Move::Id: {
        Commands::Move::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterMoveCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::Step::Id: {
        Commands::Step::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterStepCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::Stop::Id: {
        Commands::Stop::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterStopCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::MoveToLevelWithOnOff::Id: {
        Commands::MoveToLevelWithOnOff::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterMoveToLevelWithOnOffCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::MoveWithOnOff::Id: {
        Commands::MoveWithOnOff::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterMoveWithOnOffCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::StepWithOnOff::Id: {
        Commands::StepWithOnOff::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterStepWithOnOffCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::StopWithOnOff::Id: {
        Commands::StopWithOnOff::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfLevelControlClusterStopWithOnOffCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace LevelControl

namespace NetworkCommissioning {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ScanNetworks::Id: {
        Commands::ScanNetworks::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterScanNetworksCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::AddOrUpdateWiFiNetwork::Id: {
        Commands::AddOrUpdateWiFiNetwork::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterAddOrUpdateWiFiNetworkCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::AddOrUpdateThreadNetwork::Id: {
        Commands::AddOrUpdateThreadNetwork::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterAddOrUpdateThreadNetworkCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::RemoveNetwork::Id: {
        Commands::RemoveNetwork::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterRemoveNetworkCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::ConnectNetwork::Id: {
        Commands::ConnectNetwork::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterConnectNetworkCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::ReorderNetwork::Id: {
        Commands::ReorderNetwork::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfNetworkCommissioningClusterReorderNetworkCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace NetworkCommissioning

namespace OtaSoftwareUpdateRequestor {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::AnnounceOtaProvider::Id: {
        Commands::AnnounceOtaProvider::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOtaSoftwareUpdateRequestorClusterAnnounceOtaProviderCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace OtaSoftwareUpdateRequestor

namespace OnOff {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::Off::Id: {
        Commands::Off::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOnOffClusterOffCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::On::Id: {
        Commands::On::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOnOffClusterOnCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::Toggle::Id: {
        Commands::Toggle::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOnOffClusterToggleCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace OnOff

namespace OperationalCredentials {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::AttestationRequest::Id: {
        Commands::AttestationRequest::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterAttestationRequestCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::CertificateChainRequest::Id: {
        Commands::CertificateChainRequest::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterCertificateChainRequestCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::CSRRequest::Id: {
        Commands::CSRRequest::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterCSRRequestCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::AddNOC::Id: {
        Commands::AddNOC::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterAddNOCCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::UpdateNOC::Id: {
        Commands::UpdateNOC::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterUpdateNOCCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::UpdateFabricLabel::Id: {
        Commands::UpdateFabricLabel::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterUpdateFabricLabelCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::RemoveFabric::Id: {
        Commands::RemoveFabric::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterRemoveFabricCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    case Commands::AddTrustedRootCertificate::Id: {
        Commands::AddTrustedRootCertificate::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfOperationalCredentialsClusterAddTrustedRootCertificateCallback(handler, path, data),
                            CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace OperationalCredentials

namespace SoftwareDiagnostics {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ResetWatermarks::Id: {
        Commands::ResetWatermarks::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfSoftwareDiagnosticsClusterResetWatermarksCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace SoftwareDiagnostics

namespace ThreadNetworkDiagnostics {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ResetCounts::Id: {
        Commands::ResetCounts::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfThreadNetworkDiagnosticsClusterResetCountsCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace ThreadNetworkDiagnostics

namespace WiFiNetworkDiagnostics {

CHIP_ERROR DispatchServerCommand(CommandHandler * handler, const ConcreteCommandPath & path, TLV::TLVReader & tlvData)
{
    switch (path.mCommandId)
    {
    case Commands::ResetCounts::Id: {
        Commands::ResetCounts::DecodableType data;
        ReturnErrorOnFailure(DataModel::Decode(tlvData, data));
        VerifyOrReturnError(emberAfWiFiNetworkDiagnosticsClusterResetCountsCallback(handler, path, data), CHIP_ERROR_INTERNAL);
        break;
    }
    default: {
        return CHIP_IM_GLOBAL_STATUS(UnsupportedCommand);
    }
    }
    return CHIP_NO_ERROR;
}

} // namespace WiFiNetworkDiagnostics

} // namespace Clusters

void DispatchSingleClusterCommand(const ConcreteCommandPath & aCommandPath, TLV::TLVReader & aReader, CommandHandler * apCommandObj)
{
    Compatibility::SetupEmberAfCommandHandler(apCommandObj, aCommandPath);

    CHIP_ERROR err = CHIP_NO_ERROR;
    switch (aCommandPath.mClusterId)
    {
    case Clusters::AdministratorCommissioning::Id:
        err = Clusters::AdministratorCommissioning::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::DiagnosticLogs::Id:
        err = Clusters::DiagnosticLogs::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::EthernetNetworkDiagnostics::Id:
        err = Clusters::EthernetNetworkDiagnostics::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::GeneralCommissioning::Id:
        err = Clusters::GeneralCommissioning::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::GeneralDiagnostics::Id:
        err = Clusters::GeneralDiagnostics::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::GroupKeyManagement::Id:
        err = Clusters::GroupKeyManagement::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::Groups::Id:
        err = Clusters::Groups::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::Identify::Id:
        err = Clusters::Identify::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::LevelControl::Id:
        err = Clusters::LevelControl::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::NetworkCommissioning::Id:
        err = Clusters::NetworkCommissioning::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::OtaSoftwareUpdateRequestor::Id:
        err = Clusters::OtaSoftwareUpdateRequestor::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::OnOff::Id:
        err = Clusters::OnOff::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::OperationalCredentials::Id:
        err = Clusters::OperationalCredentials::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::SoftwareDiagnostics::Id:
        err = Clusters::SoftwareDiagnostics::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::ThreadNetworkDiagnostics::Id:
        err = Clusters::ThreadNetworkDiagnostics::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    case Clusters::WiFiNetworkDiagnostics::Id:
        err = Clusters::WiFiNetworkDiagnostics::DispatchServerCommand(apCommandObj, aCommandPath, aReader);
        break;
    default:
        err = CHIP_IM_GLOBAL_STATUS(UnsupportedCluster);
        break;
    }
    MaybeDispatchServerError(apCommandObj, aCommandPath, err);

    Compatibility::ResetEmberAfObjects();
}

} // namespace app
} // namespace chip
