/**
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

/**
 *
 *    Copyright (c) 2020 Silicon Labs
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
// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// Enclosing macro to prevent multiple inclusion
#ifndef __AF_GEN_EVENT__
#define __AF_GEN_EVENT__

// Code used to configure the cluster event mechanism
#define EMBER_AF_GENERATED_EVENT_CODE                                                                                              \
    EmberEventControl emberAfIdentifyClusterServerTickCallbackControl1;                                                            \
    EmberEventControl emberAfLevelControlClusterServerTickCallbackControl1;                                                        \
    EmberEventControl emberAfBarrierControlClusterServerTickCallbackControl1;                                                      \
    EmberEventControl emberAfIasZoneClusterServerTickCallbackControl1;                                                             \
    extern EmberEventControl emberAfPluginColorControlServerHueSatTransitionEventControl;                                          \
    extern EmberEventControl emberAfPluginColorControlServerTempTransitionEventControl;                                            \
    extern EmberEventControl emberAfPluginColorControlServerXyTransitionEventControl;                                              \
    extern EmberEventControl emberAfPluginDoorLockServerLockoutEventControl;                                                       \
    extern EmberEventControl emberAfPluginDoorLockServerRelockEventControl;                                                        \
    extern EmberEventControl emberAfPluginIasZoneClientStateMachineEventControl;                                                   \
    extern EmberEventControl emberAfPluginIasZoneServerManageQueueEventControl;                                                    \
    extern EmberEventControl emberAfPluginReportingTickEventControl;                                                               \
    extern EmberEventControl emberAfPluginTemperatureMeasurementServerReadEventControl;                                            \
    extern void emberAfPluginColorControlServerHueSatTransitionEventHandler(void);                                                 \
    extern void emberAfPluginColorControlServerTempTransitionEventHandler(void);                                                   \
    extern void emberAfPluginColorControlServerXyTransitionEventHandler(void);                                                     \
    extern void emberAfPluginDoorLockServerLockoutEventHandler(void);                                                              \
    extern void emberAfPluginDoorLockServerRelockEventHandler(void);                                                               \
    extern void emberAfPluginIasZoneClientStateMachineEventHandler(void);                                                          \
    extern void emberAfPluginIasZoneServerManageQueueEventHandler(void);                                                           \
    extern void emberAfPluginReportingTickEventHandler(void);                                                                      \
    extern void emberAfPluginTemperatureMeasurementServerReadEventHandler(void);                                                   \
    static void clusterTickWrapper(EmberEventControl * control, EmberAfTickFunction callback, chip::EndpointId endpoint)             \
    {                                                                                                                              \
        /* emberAfPushEndpointNetworkIndex(endpoint); */                                                                           \
        emberEventControlSetInactive(control);                                                                                     \
        (*callback)(endpoint);                                                                                                     \
        /* emberAfPopNetworkIndex(); */                                                                                            \
    }                                                                                                                              \
    void emberAfIdentifyClusterServerTickCallbackWrapperFunction1(void)                                                            \
    {                                                                                                                              \
        clusterTickWrapper(&emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallback, 1);        \
    }                                                                                                                              \
    void emberAfLevelControlClusterServerTickCallbackWrapperFunction1(void)                                                        \
    {                                                                                                                              \
        clusterTickWrapper(&emberAfLevelControlClusterServerTickCallbackControl1, emberAfLevelControlClusterServerTickCallback,    \
                           1);                                                                                                     \
    }                                                                                                                              \
    void emberAfBarrierControlClusterServerTickCallbackWrapperFunction1(void)                                                      \
    {                                                                                                                              \
        clusterTickWrapper(&emberAfBarrierControlClusterServerTickCallbackControl1,                                                \
                           emberAfBarrierControlClusterServerTickCallback, 1);                                                     \
    }                                                                                                                              \
    void emberAfIasZoneClusterServerTickCallbackWrapperFunction1(void)                                                             \
    {                                                                                                                              \
        clusterTickWrapper(&emberAfIasZoneClusterServerTickCallbackControl1, emberAfIasZoneClusterServerTickCallback, 1);          \
    }

// EmberEventData structs used to populate the EmberEventData table
#define EMBER_AF_GENERATED_EVENTS                                                                                                  \
    { &emberAfIdentifyClusterServerTickCallbackControl1, emberAfIdentifyClusterServerTickCallbackWrapperFunction1 },               \
        { &emberAfLevelControlClusterServerTickCallbackControl1, emberAfLevelControlClusterServerTickCallbackWrapperFunction1 },   \
        { &emberAfBarrierControlClusterServerTickCallbackControl1,                                                                 \
          emberAfBarrierControlClusterServerTickCallbackWrapperFunction1 },                                                        \
        { &emberAfIasZoneClusterServerTickCallbackControl1, emberAfIasZoneClusterServerTickCallbackWrapperFunction1 },             \
        { &emberAfPluginColorControlServerHueSatTransitionEventControl,                                                            \
          emberAfPluginColorControlServerHueSatTransitionEventHandler },                                                           \
        { &emberAfPluginColorControlServerTempTransitionEventControl, emberAfPluginColorControlServerTempTransitionEventHandler }, \
        { &emberAfPluginColorControlServerXyTransitionEventControl, emberAfPluginColorControlServerXyTransitionEventHandler },     \
        { &emberAfPluginDoorLockServerLockoutEventControl, emberAfPluginDoorLockServerLockoutEventHandler },                       \
        { &emberAfPluginDoorLockServerRelockEventControl, emberAfPluginDoorLockServerRelockEventHandler },                         \
        { &emberAfPluginIasZoneClientStateMachineEventControl, emberAfPluginIasZoneClientStateMachineEventHandler },               \
        { &emberAfPluginIasZoneServerManageQueueEventControl, emberAfPluginIasZoneServerManageQueueEventHandler },                 \
        { &emberAfPluginReportingTickEventControl, emberAfPluginReportingTickEventHandler },                                       \
        { &emberAfPluginTemperatureMeasurementServerReadEventControl, emberAfPluginTemperatureMeasurementServerReadEventHandler },

#define EMBER_AF_GENERATED_EVENT_STRINGS                                                                                           \
    "Identify Cluster Server EP 1", "Level Control Cluster Server EP 1", "Barrier Control Cluster Server EP 1",                    \
        "IAS Zone Cluster Server EP 1", "Color Control Cluster Server Plugin HueSatTransition",                                    \
        "Color Control Cluster Server Plugin TempTransition", "Color Control Cluster Server Plugin XyTransition",                  \
        "Door Lock Server Cluster Plugin Lockout", "Door Lock Server Cluster Plugin Relock",                                       \
        "IAS Zone Client Plugin StateMachine", "IAS Zone Server Plugin ManageQueue", "Reporting Plugin Tick",                      \
        "Temperature Measurement Server Cluster Plugin Read",

// The length of the event context table used to track and retrieve cluster events
#define EMBER_AF_EVENT_CONTEXT_LENGTH 4

// EmberAfEventContext structs used to populate the EmberAfEventContext table
#define EMBER_AF_GENERATED_EVENT_CONTEXT                                                                                           \
    { 0x1, 0x3, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIdentifyClusterServerTickCallbackControl1 },              \
        { 0x1, 0x8, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfLevelControlClusterServerTickCallbackControl1 },      \
        { 0x1, 0x103, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfBarrierControlClusterServerTickCallbackControl1 },  \
    {                                                                                                                              \
        0x1, 0x500, false, EMBER_AF_LONG_POLL, EMBER_AF_OK_TO_SLEEP, &emberAfIasZoneClusterServerTickCallbackControl1              \
    }

#endif // __AF_GEN_EVENT__
