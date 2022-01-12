/*
 *   Copyright (c) 2022 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "DiscoveryCommands.h"

CHIP_ERROR DiscoveryCommands::FindCommissionable()
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kNone, (uint64_t) 0);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionableByShortDiscriminator(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    uint64_t shortDiscriminator = static_cast<uint64_t>((value >> 8) & 0x0F);
    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kShortDiscriminator, shortDiscriminator);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionableByLongDiscriminator(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kLongDiscriminator, value);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionableByCommissioningMode()
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kCommissioningMode);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionableByVendorId(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kVendorId, value);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionableByDeviceType(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kDeviceType, value);
    return mDNSResolver->FindCommissionableNodes(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissioner()
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kCommissioner, 1);
    return mDNSResolver->FindCommissioners(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionerByVendorId(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kVendorId, value);
    return mDNSResolver->FindCommissioners(filter);
}

CHIP_ERROR DiscoveryCommands::FindCommissionerByDeviceType(uint64_t value)
{
    ReturnErrorOnFailure(SetupDiscoveryCommands());

    chip::Dnssd::DiscoveryFilter filter(chip::Dnssd::DiscoveryFilterType::kDeviceType, value);
    return mDNSResolver->FindCommissioners(filter);
}

CHIP_ERROR DiscoveryCommands::SetupDiscoveryCommands()
{
    ReturnErrorOnFailure(TearDownDiscoveryCommands());

    mDNSResolver = chip::Platform::New<chip::Dnssd::ResolverProxy>();
    ReturnErrorOnFailure(mDNSResolver->Init());
    mDNSResolver->SetResolverDelegate(this);
    return CHIP_NO_ERROR;
}

CHIP_ERROR DiscoveryCommands::TearDownDiscoveryCommands()
{
    VerifyOrReturnError(mDNSResolver != nullptr, CHIP_NO_ERROR);
    mDNSResolver->Shutdown();
    chip::Platform::Delete<chip::Dnssd::ResolverProxy>(mDNSResolver);
    mDNSResolver = nullptr;
    return CHIP_NO_ERROR;
}

void DiscoveryCommands::OnNodeDiscoveryComplete(const chip::Dnssd::DiscoveredNodeData & nodeData)
{
    // TODO: If multiple results are found for the same filter, then the test result depends
    //       on which result comes first. At the moment, the code assume that there is only
    //       a single match on the network, but if that's not enough, there may be a need
    //       to implement some sort of list that is built for a given duration before returning
    ReturnOnFailure(TearDownDiscoveryCommands());

    OnDiscoveryCommandsResults(nodeData);
}
