
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

// Enclosing macro to prevent multiple inclusion
#ifndef __ZAP_CALLBACK__
#define __ZAP_CALLBACK__

#include "af-structs.h"
#include "af-types.h"

/** @brief Cluster Init
 *
 * This function is called when a specific cluster is initialized. It gives the
 * application an opportunity to take care of cluster initialization procedures.
 * It is called exactly once for each endpoint where cluster is present.
 *
 * @param endpoint   Ver.: always
 * @param clusterId   Ver.: always
 */
void emberAfClusterInitCallback(uint8_t endpoint, EmberAfClusterId clusterId);

// Cluster Init Functions
void emberAfBarrierControlClusterInitCallback(uint8_t endpoint);
void emberAfBasicClusterInitCallback(uint8_t endpoint);
void emberAfColorControlClusterInitCallback(uint8_t endpoint);
void emberAfDoorLockClusterInitCallback(uint8_t endpoint);
void emberAfGroupsClusterInitCallback(uint8_t endpoint);
void emberAfIASZoneClusterInitCallback(uint8_t endpoint);
void emberAfIdentifyClusterInitCallback(uint8_t endpoint);
void emberAfLevelControlClusterInitCallback(uint8_t endpoint);
void emberAfOnOffClusterInitCallback(uint8_t endpoint);
void emberAfScenesClusterInitCallback(uint8_t endpoint);
void emberAfTemperatureMeasurementClusterInitCallback(uint8_t endpoint);

void emberAfBarrierControlClusterServerInitCallback(uint8_t endpoint);
void emberAfBasicClusterServerInitCallback(uint8_t endpoint);
void emberAfColorControlClusterServerInitCallback(uint8_t endpoint);
void emberAfDoorLockClusterServerInitCallback(uint8_t endpoint);
void emberAfGroupsClusterServerInitCallback(uint8_t endpoint);
void emberAfIASZoneClusterServerInitCallback(uint8_t endpoint);
void emberAfIdentifyClusterServerInitCallback(uint8_t endpoint);
void emberAfLevelControlClusterServerInitCallback(uint8_t endpoint);
void emberAfOnOffClusterServerInitCallback(uint8_t endpoint);
void emberAfScenesClusterServerInitCallback(uint8_t endpoint);
void emberAfTemperatureMeasurementClusterServerInitCallback(uint8_t endpoint);

void emberAfBarrierControlClusterServerTickCallback(uint8_t endpoint);
void emberAfBasicClusterServerTickCallback(uint8_t endpoint);
void emberAfColorControlClusterServerTickCallback(uint8_t endpoint);
void emberAfDoorLockClusterServerTickCallback(uint8_t endpoint);
void emberAfGroupsClusterServerTickCallback(uint8_t endpoint);
void emberAfIASZoneClusterServerTickCallback(uint8_t endpoint);
void emberAfIdentifyClusterServerTickCallback(uint8_t endpoint);
void emberAfLevelControlClusterServerTickCallback(uint8_t endpoint);
void emberAfOnOffClusterServerTickCallback(uint8_t endpoint);
void emberAfScenesClusterServerTickCallback(uint8_t endpoint);
void emberAfTemperatureMeasurementClusterServerTickCallback(uint8_t endpoint);

// Cluster Commands Callback

/**
 * @brief Barrier Control Cluster BarrierControlGoToPercent Command callback
 * @param percentOpen
 */

bool emberAfBarrierControlClusterBarrierControlGoToPercentCallback(uint8_t percentOpen);

/**
 * @brief Barrier Control Cluster BarrierControlStop Command callback
 */

bool emberAfBarrierControlClusterBarrierControlStopCallback();

/**
 * @brief Basic Cluster ResetToFactoryDefaults Command callback
 */

bool emberAfBasicClusterResetToFactoryDefaultsCallback();

/**
 * @brief Color Control Cluster MoveColor Command callback
 * @param rateX
 * @param rateY
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveColorCallback(int16_t rateX, int16_t rateY, uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveColorTemperature Command callback
 * @param moveMode
 * @param rate
 * @param colorTemperatureMinimum
 * @param colorTemperatureMaximum
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveColorTemperatureCallback(EmberAfHueMoveMode moveMode, uint16_t rate,
                                                            uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum,
                                                            uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveHue Command callback
 * @param moveMode
 * @param rate
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveHueCallback(EmberAfHueMoveMode moveMode, uint8_t rate, uint8_t optionsMask,
                                               uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveSaturation Command callback
 * @param moveMode
 * @param rate
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveSaturationCallback(EmberAfSaturationMoveMode moveMode, uint8_t rate, uint8_t optionsMask,
                                                      uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveToColor Command callback
 * @param colorX
 * @param colorY
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveToColorCallback(uint16_t colorX, uint16_t colorY, uint16_t transitionTime, uint8_t optionsMask,
                                                   uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveToColorTemperature Command callback
 * @param colorTemperature
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveToColorTemperatureCallback(uint16_t colorTemperature, uint16_t transitionTime,
                                                              uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveToHue Command callback
 * @param hue
 * @param direction
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveToHueCallback(uint8_t hue, EmberAfHueDirection direction, uint16_t transitionTime,
                                                 uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveToHueAndSaturation Command callback
 * @param hue
 * @param saturation
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveToHueAndSaturationCallback(uint8_t hue, uint8_t saturation, uint16_t transitionTime,
                                                              uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster MoveToSaturation Command callback
 * @param saturation
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterMoveToSaturationCallback(uint8_t saturation, uint16_t transitionTime, uint8_t optionsMask,
                                                        uint8_t optionsOverride);

/**
 * @brief Color Control Cluster StepColor Command callback
 * @param stepX
 * @param stepY
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterStepColorCallback(int16_t stepX, int16_t stepY, uint16_t transitionTime, uint8_t optionsMask,
                                                 uint8_t optionsOverride);

/**
 * @brief Color Control Cluster StepColorTemperature Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param colorTemperatureMinimum
 * @param colorTemperatureMaximum
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterStepColorTemperatureCallback(EmberAfHueStepMode stepMode, uint16_t stepSize, uint16_t transitionTime,
                                                            uint16_t colorTemperatureMinimum, uint16_t colorTemperatureMaximum,
                                                            uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster StepHue Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterStepHueCallback(EmberAfHueStepMode stepMode, uint8_t stepSize, uint8_t transitionTime,
                                               uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster StepSaturation Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterStepSaturationCallback(EmberAfSaturationStepMode stepMode, uint8_t stepSize, uint8_t transitionTime,
                                                      uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Color Control Cluster StopMoveStep Command callback
 * @param optionsMask
 * @param optionsOverride
 */

bool emberAfColorControlClusterStopMoveStepCallback(uint8_t optionsMask, uint8_t optionsOverride);

/**
 * @brief Door Lock Cluster ClearHolidaySchedule Command callback
 * @param scheduleId
 */

bool emberAfDoorLockClusterClearHolidayScheduleCallback(uint8_t scheduleId);

/**
 * @brief Door Lock Cluster ClearWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool emberAfDoorLockClusterClearWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId);

/**
 * @brief Door Lock Cluster ClearYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool emberAfDoorLockClusterClearYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId);

/**
 * @brief Door Lock Cluster GetHolidaySchedule Command callback
 * @param scheduleId
 */

bool emberAfDoorLockClusterGetHolidayScheduleCallback(uint8_t scheduleId);

/**
 * @brief Door Lock Cluster GetUserType Command callback
 * @param userId
 */

bool emberAfDoorLockClusterGetUserTypeCallback(uint16_t userId);

/**
 * @brief Door Lock Cluster GetWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool emberAfDoorLockClusterGetWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId);

/**
 * @brief Door Lock Cluster GetYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 */

bool emberAfDoorLockClusterGetYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId);

/**
 * @brief Door Lock Cluster LockDoor Command callback
 * @param pIN
 */

bool emberAfDoorLockClusterLockDoorCallback(uint8_t * PIN);

/**
 * @brief Door Lock Cluster SetHolidaySchedule Command callback
 * @param scheduleId
 * @param localStartTime
 * @param localEndTime
 * @param operatingModeDuringHoliday
 */

bool emberAfDoorLockClusterSetHolidayScheduleCallback(uint8_t scheduleId, uint32_t localStartTime, uint32_t localEndTime,
                                                      uint8_t operatingModeDuringHoliday);

/**
 * @brief Door Lock Cluster SetUserType Command callback
 * @param userId
 * @param userType
 */

bool emberAfDoorLockClusterSetUserTypeCallback(uint16_t userId, EmberAfDoorLockUserType userType);

/**
 * @brief Door Lock Cluster SetWeekdaySchedule Command callback
 * @param scheduleId
 * @param userId
 * @param daysMask
 * @param startHour
 * @param startMinute
 * @param endHour
 * @param endMinute
 */

bool emberAfDoorLockClusterSetWeekdayScheduleCallback(uint8_t scheduleId, uint16_t userId, uint8_t daysMask, uint8_t startHour,
                                                      uint8_t startMinute, uint8_t endHour, uint8_t endMinute);

/**
 * @brief Door Lock Cluster SetYeardaySchedule Command callback
 * @param scheduleId
 * @param userId
 * @param localStartTime
 * @param localEndTime
 */

bool emberAfDoorLockClusterSetYeardayScheduleCallback(uint8_t scheduleId, uint16_t userId, uint32_t localStartTime,
                                                      uint32_t localEndTime);

/**
 * @brief Door Lock Cluster UnlockDoor Command callback
 * @param pIN
 */

bool emberAfDoorLockClusterUnlockDoorCallback(uint8_t * PIN);

/**
 * @brief Door Lock Cluster UnlockWithTimeout Command callback
 * @param timeoutInSeconds
 * @param pin
 */

bool emberAfDoorLockClusterUnlockWithTimeoutCallback(uint16_t timeoutInSeconds, uint8_t * pin);

/**
 * @brief Groups Cluster AddGroup Command callback
 * @param groupId
 * @param groupName
 */

bool emberAfGroupsClusterAddGroupCallback(uint16_t groupId, uint8_t * groupName);

/**
 * @brief Groups Cluster AddGroupIfIdentifying Command callback
 * @param groupId
 * @param groupName
 */

bool emberAfGroupsClusterAddGroupIfIdentifyingCallback(uint16_t groupId, uint8_t * groupName);

/**
 * @brief Groups Cluster GetGroupMembership Command callback
 * @param groupCount
 * @param groupList
 */

bool emberAfGroupsClusterGetGroupMembershipCallback(uint8_t groupCount, uint16_t groupList);

/**
 * @brief Groups Cluster RemoveAllGroups Command callback
 */

bool emberAfGroupsClusterRemoveAllGroupsCallback();

/**
 * @brief Groups Cluster RemoveGroup Command callback
 * @param groupId
 */

bool emberAfGroupsClusterRemoveGroupCallback(uint16_t groupId);

/**
 * @brief Groups Cluster ViewGroup Command callback
 * @param groupId
 */

bool emberAfGroupsClusterViewGroupCallback(uint16_t groupId);

/**
 * @brief IAS Zone Cluster ZoneEnrollResponse Command callback
 * @param enrollResponseCode
 * @param zoneId
 */

bool emberAfIASZoneClusterZoneEnrollResponseCallback(EmberAfIasEnrollResponseCode enrollResponseCode, uint8_t zoneId);

/**
 * @brief Identify Cluster Identify Command callback
 * @param identifyTime
 */

bool emberAfIdentifyClusterIdentifyCallback(uint16_t identifyTime);

/**
 * @brief Identify Cluster IdentifyQuery Command callback
 */

bool emberAfIdentifyClusterIdentifyQueryCallback();

/**
 * @brief Level Control Cluster Move Command callback
 * @param moveMode
 * @param rate
 * @param optionMask
 * @param optionOverride
 */

bool emberAfLevelControlClusterMoveCallback(EmberAfMoveMode moveMode, uint8_t rate, uint8_t optionMask, uint8_t optionOverride);

/**
 * @brief Level Control Cluster MoveToLevel Command callback
 * @param level
 * @param transitionTime
 * @param optionMask
 * @param optionOverride
 */

bool emberAfLevelControlClusterMoveToLevelCallback(uint8_t level, uint16_t transitionTime, uint8_t optionMask,
                                                   uint8_t optionOverride);

/**
 * @brief Level Control Cluster MoveToLevelWithOnOff Command callback
 * @param level
 * @param transitionTime
 */

bool emberAfLevelControlClusterMoveToLevelWithOnOffCallback(uint8_t level, uint16_t transitionTime);

/**
 * @brief Level Control Cluster MoveWithOnOff Command callback
 * @param moveMode
 * @param rate
 */

bool emberAfLevelControlClusterMoveWithOnOffCallback(EmberAfMoveMode moveMode, uint8_t rate);

/**
 * @brief Level Control Cluster Step Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 * @param optionMask
 * @param optionOverride
 */

bool emberAfLevelControlClusterStepCallback(EmberAfStepMode stepMode, uint8_t stepSize, uint16_t transitionTime, uint8_t optionMask,
                                            uint8_t optionOverride);

/**
 * @brief Level Control Cluster StepWithOnOff Command callback
 * @param stepMode
 * @param stepSize
 * @param transitionTime
 */

bool emberAfLevelControlClusterStepWithOnOffCallback(EmberAfStepMode stepMode, uint8_t stepSize, uint16_t transitionTime);

/**
 * @brief Level Control Cluster Stop Command callback
 * @param optionMask
 * @param optionOverride
 */

bool emberAfLevelControlClusterStopCallback(uint8_t optionMask, uint8_t optionOverride);

/**
 * @brief Level Control Cluster StopWithOnOff Command callback
 */

bool emberAfLevelControlClusterStopWithOnOffCallback();

/**
 * @brief On/off Cluster Off Command callback
 */

bool emberAfOnOffClusterOffCallback();

/**
 * @brief On/off Cluster On Command callback
 */

bool emberAfOnOffClusterOnCallback();

/**
 * @brief On/off Cluster Toggle Command callback
 */

bool emberAfOnOffClusterToggleCallback();

/**
 * @brief Scenes Cluster AddScene Command callback
 * @param groupId
 * @param sceneId
 * @param transitionTime
 * @param sceneName
 * @param extensionFieldSets
 */

bool emberAfScenesClusterAddSceneCallback(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, uint8_t * sceneName,
                                          EmberAfSceneExtensionFieldSet extensionFieldSets);

/**
 * @brief Scenes Cluster GetSceneMembership Command callback
 * @param groupId
 */

bool emberAfScenesClusterGetSceneMembershipCallback(uint16_t groupId);

/**
 * @brief Scenes Cluster RecallScene Command callback
 * @param groupId
 * @param sceneId
 * @param transitionTime
 */

bool emberAfScenesClusterRecallSceneCallback(uint16_t groupId, uint8_t sceneId, uint16_t transitionTime);

/**
 * @brief Scenes Cluster RemoveAllScenes Command callback
 * @param groupId
 */

bool emberAfScenesClusterRemoveAllScenesCallback(uint16_t groupId);

/**
 * @brief Scenes Cluster RemoveScene Command callback
 * @param groupId
 * @param sceneId
 */

bool emberAfScenesClusterRemoveSceneCallback(uint16_t groupId, uint8_t sceneId);

/**
 * @brief Scenes Cluster StoreScene Command callback
 * @param groupId
 * @param sceneId
 */

bool emberAfScenesClusterStoreSceneCallback(uint16_t groupId, uint8_t sceneId);

/**
 * @brief Scenes Cluster ViewScene Command callback
 * @param groupId
 * @param sceneId
 */

bool emberAfScenesClusterViewSceneCallback(uint16_t groupId, uint8_t sceneId);

void emberAfPluginBarrierControlServerInitCallback();
void emberAfPluginBasicResetToFactoryDefaultsCallback(uint8_t endpointId);
void emberAfPluginColorControlServerComputePwmFromHsvCallback(uint8_t endpoint);
void emberAfPluginColorControlServerComputePwmFromTempCallback(uint8_t endpoint);
void emberAfPluginColorControlServerComputePwmFromXyCallback(uint8_t endpoint);
bool emberAfPluginDoorLockServerActivateDoorLockCallback(bool activate);
void emberAfPluginGroupsServerGetGroupNameCallback(uint8_t endpoint, uint16_t groupId, uint8_t * groupName);
bool emberAfPluginGroupsServerGroupNamesSupportedCallback(uint8_t endpoint);
void emberAfPluginGroupsServerSetGroupNameCallback(uint8_t endpoint, uint16_t groupId, uint8_t * groupName);
void emberAfPluginIasZoneClientZdoCallback(EmberNodeId emberNodeId, EmberApsFrame * apsFrame, uint8_t * message, uint16_t length);
void emberAfPluginIasZoneClientWriteAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
void emberAfPluginIasZoneClientReadAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
bool emberAfPluginIdentifyStartFeedbackCallback(uint8_t endpoint, uint16_t identifyTime);
bool emberAfPluginIdentifyStopFeedbackCallback(uint8_t endpoint);
void emberAfPluginLevelControlClusterServerPostInitCallback(CHIPEndpointId endpoint);
void emberAfPluginOnOffClusterServerPostInitCallback(CHIPEndpointId endpoint);
;
EmberAfStatus emberAfScenesClusterMakeInvalidCallback(uint8_t endpoint);
void emberAfScenesClusterRemoveScenesInGroupCallback(uint8_t endpoint, uint16_t groupId);
EmberAfStatus emberAfScenesClusterStoreCurrentSceneCallback(uint8_t endpoint, uint16_t groupId, uint8_t sceneId);
EmberAfStatus emberAfScenesClusterRecallSavedSceneCallback(uint8_t endpoint, uint16_t groupId, uint8_t sceneId);
uint8_t emberAfGetSourceRouteOverheadCallback(EmberNodeId destination);
bool emberAfClusterSecurityCustomCallback(EmberAfProfileId profileId, EmberAfClusterId clusterId, bool incoming, uint8_t commandId);
EmberStatus emberAfInterpanSendMessageCallback(EmberAfInterpanHeader * header, uint16_t messageLength, uint8_t * message);
bool emberAfPreCommandReceivedCallback(EmberAfClusterCommand * cmd);
void emberAfRegistrationAbortCallback();
bool emberAfDiscoverCommandsGeneratedResponseCallback(EmberAfClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                      uint8_t * commandIds, uint16_t commandIdCount);
bool emberAfDiscoverCommandsReceivedResponseCallback(EmberAfClusterId clusterId, uint16_t manufacturerCode, bool discoveryComplete,
                                                     uint8_t * commandIds, uint16_t commandIdCount);
bool emberAfDefaultResponseCallback(EmberAfClusterId clusterId, uint8_t commandId, EmberAfStatus status);
bool emberAfReportAttributesCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
bool emberAfReadAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
bool emberAfDiscoverAttributesResponseCallback(EmberAfClusterId clusterId, bool discoveryComplete, uint8_t * buffer,
                                               uint16_t bufLen, bool extended);
bool emberAfWriteAttributesResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
void emberAfPostAttributeChangeCallback(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attributeId, uint8_t mask,
                                        uint16_t manufacturerCode, uint8_t type, uint8_t size, uint8_t * value);
EmberAfStatus emberAfExternalAttributeReadCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                   EmberAfAttributeMetadata * attributeMetadata, uint16_t manufacturerCode,
                                                   uint8_t * buffer, uint16_t maxReadLength);
EmberAfStatus emberAfExternalAttributeWriteCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                    EmberAfAttributeMetadata * attributeMetadata, uint16_t manufacturerCode,
                                                    uint8_t * buffer);
bool emberAfAttributeReadAccessCallback(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode,
                                        uint16_t attributeId);
bool emberAfAttributeWriteAccessCallback(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode,
                                         uint16_t attributeId);
EmberAfStatus emberAfPreAttributeChangeCallback(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attributeId,
                                                uint8_t mask, uint16_t manufacturerCode, uint8_t type, uint8_t size,
                                                uint8_t * value);
EmberAfAttributeWritePermission emberAfAllowNetworkWriteAttributeCallback(uint8_t endpoint, EmberAfClusterId clusterId,
                                                                          EmberAfAttributeId attributeId, uint8_t mask,
                                                                          uint16_t manufacturerCode, uint8_t * value, uint8_t type);

void emberAfAddToCurrentAppTasksCallback(EmberAfApplicationTask tasks);
void emberAfRemoveFromCurrentAppTasksCallback(EmberAfApplicationTask tasks);
bool emberAfMessageSentCallback(EmberOutgoingMessageType type, uint16_t indexOrDestination, EmberApsFrame * apsFrame,
                                uint16_t msgLen, uint8_t * message, EmberStatus status);
void emberAfTrustCenterKeepaliveAbortCallback();
bool emberAfPreMessageSendCallback(EmberAfMessageStruct * messageStruct, EmberStatus * status);
bool emberAfGetEndpointInfoCallback(uint8_t endpoint, uint8_t * returnNetworkIndex, EmberAfEndpointInfoStruct * returnEndpointInfo);
uint32_t emberAfGetCurrentTimeCallback();
bool emberAfGroupsClusterEndpointInGroupCallback(uint8_t endpoint, uint16_t groupId);
bool emberAfStartMoveCallback();
bool emberAfConfigureReportingCommandCallback(const EmberAfClusterCommand * cmd);
bool emberAfReadReportingConfigurationCommandCallback(const EmberAfClusterCommand * cmd);
EmberStatus emberAfClearReportTableCallback(void);
bool emberAfConfigureReportingResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
bool emberAfReadReportingConfigurationResponseCallback(EmberAfClusterId clusterId, uint8_t * buffer, uint16_t bufLen);
void emberAfReportingAttributeChangeCallback(uint8_t endpoint, EmberAfClusterId clusterId, EmberAfAttributeId attributeId,
                                              uint8_t mask, uint16_t manufacturerCode, EmberAfAttributeType type, uint8_t * data);
void emberAfOnOffClusterLevelControlEffectCallback(uint8_t endpoint, bool newValue);
EmberAfStatus emberAfOnOffClusterSetValueCallback(uint8_t endpoint, uint8_t command, bool initiatedByLevelChange);
void emberAfDoorLockClusterServerAttributeChangedCallback(uint8_t endpoint, EmberAfAttributeId attributeId);
void emberAfIasZoneClusterClientInitCallback(uint8_t endpoint);
void emberAfIasZoneClusterServerInitCallback(uint8_t endpoint);
void emberAfIasZoneClusterServerMessageSentCallback(EmberOutgoingMessageType type, uint16_t indexOrDestination,
                                                    EmberApsFrame * apsFrame, uint16_t msgLen, uint8_t * message,
                                                    EmberStatus status);

EmberAfStatus emberAfIasZoneClusterServerPreAttributeChangedCallback(uint8_t endpoint, EmberAfAttributeId attributeId,
                                                                     EmberAfAttributeType attributeType, uint8_t size,
                                                                     uint8_t * value);
void emberAfIdentifyClusterServerAttributeChangedCallback(uint8_t endpoint, EmberAfAttributeId attributeId);

#endif //__ZAP_CALLBACK__
