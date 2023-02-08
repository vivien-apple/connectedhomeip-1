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

#include "AppMain.h"
#include <app-common/zap-generated/callback.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/CommandHandler.h>
#include <app/clusters/identify-server/identify-server.h>
#include <app/clusters/network-commissioning/network-commissioning.h>
#include <app/util/af.h>
#include <platform/Linux/NetworkCommissioningDriver.h>

using namespace chip;
using namespace chip::app;
// using namespace chip::app::Clusters;

#if CHIP_DEVICE_CONFIG_ENABLE_WPA
namespace {
DeviceLayer::NetworkCommissioning::LinuxWiFiDriver sLinuxWiFiDriver;
Clusters::NetworkCommissioning::Instance sWiFiNetworkCommissioningInstance(0, &sLinuxWiFiDriver);
} // namespace
#endif

bool emberAfBasicClusterMfgSpecificPingCallback(chip::app::CommandHandler * commandObj)
{
    emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
    return true;
}

void OnIdentifyStart(Identify *)
{
    ChipLogProgress(Zcl, "OnIdentifyStart");
}

void OnIdentifyStop(Identify *)
{
    ChipLogProgress(Zcl, "OnIdentifyStop");
}

void OnTriggerEffect(Identify * identify)
{
    switch (identify->mCurrentEffectIdentifier)
    {
    case Clusters::Identify::IdentifyEffectIdentifier::kBlink:
        ChipLogProgress(Zcl, "IdentifyEffectIdentifier::kBlink");
        break;
    case Clusters::Identify::IdentifyEffectIdentifier::kBreathe:
        ChipLogProgress(Zcl, "IdentifyEffectIdentifier::kBreathe");
        break;
    case Clusters::Identify::IdentifyEffectIdentifier::kOkay:
        ChipLogProgress(Zcl, "IdentifyEffectIdentifier::kOkay");
        break;
    case Clusters::Identify::IdentifyEffectIdentifier::kChannelChange:
        ChipLogProgress(Zcl, "IdentifyEffectIdentifier::kChannelChange");
        break;
    default:
        ChipLogProgress(Zcl, "No identifier effect");
        return;
    }
}

static Clusters::Identify::Identify gIdentify0 = {
    chip::EndpointId{ 0 }, OnIdentifyStart, OnIdentifyStop, Clusters::Identify::IdentifyIdentifyType::kVisibleLED, OnTriggerEffect,
};

static Clusters::Identify::Identify gIdentify1 = {
    chip::EndpointId{ 1 }, OnIdentifyStart, OnIdentifyStop, Clusters::Identify::IdentifyIdentifyType::kVisibleLED, OnTriggerEffect,
};

void ApplicationInit()
{
#if CHIP_DEVICE_CONFIG_ENABLE_WPA
    sWiFiNetworkCommissioningInstance.Init();
#endif
}

int main(int argc, char * argv[])
{
    VerifyOrDie(ChipLinuxAppInit(argc, argv) == 0);
    ChipLinuxAppMainLoop();
    return 0;
}
