
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

#ifndef SILABS_EMBER_AF_STRUCTS
#define SILABS_EMBER_AF_STRUCTS

#include "enums.h"
#include <stdint.h>

// Struct for BlockThreshold
typedef struct _BlockThreshold
{
    uint8_t blockThreshold;
    uint8_t priceControl;
    uint32_t blockPeriodStartTime;
    uint32_t blockPeriodDurationMinutes;
    uint8_t fuelType;
    uint32_t standingCharge;
} EmberAfBlockThreshold;

// Struct for BlockThresholdSubPayload
typedef struct _BlockThresholdSubPayload
{
    uint8_t tierNumberOfBlockThresholds;
    uint8_t * blockThreshold;
} EmberAfBlockThresholdSubPayload;

// Struct for ChatParticipant
typedef struct _ChatParticipant
{
    uint16_t uid;
    uint8_t * nickname;
} EmberAfChatParticipant;

// Struct for ChatRoom
typedef struct _ChatRoom
{
    uint16_t cid;
    uint8_t * name;
} EmberAfChatRoom;

// Struct for ConfigureReportingRecord
typedef struct _ConfigureReportingRecord
{
    uint8_t direction;
    uint16_t attributeId;
    uint8_t attributeType;
    uint16_t minimumReportingInterval;
    uint16_t maximumReportingInterval;
    uint8_t * reportableChangeLocation;
    uint16_t timeoutPeriod;
} EmberAfConfigureReportingRecord;

// Struct for ConfigureReportingStatusRecord
typedef struct _ConfigureReportingStatusRecord
{
    EmberAfStatus status;
    uint8_t direction;
    uint16_t attributeId;
} EmberAfConfigureReportingStatusRecord;

// Struct for DebtPayload
typedef struct _DebtPayload
{
    uint32_t collectionTime;
    uint32_t amountCollected;
    EmberAfRepaymentDebtType debtType;
    uint32_t outstandingDebt;
} EmberAfDebtPayload;

// Struct for DeviceInformationRecord
typedef struct _DeviceInformationRecord
{
    uint8_t * ieeeAddress;
    uint8_t endpointId;
    uint16_t profileId;
    uint16_t deviceId;
    uint8_t version;
    uint8_t groupIdCount;
    EmberAfDeviceInformationRecordSort sort;
} EmberAfDeviceInformationRecord;

// Struct for DiscoverAttributesInfoRecord
typedef struct _DiscoverAttributesInfoRecord
{
    uint16_t attributeId;
    uint8_t attributeType;
} EmberAfDiscoverAttributesInfoRecord;

// Struct for EndpointInformationRecord
typedef struct _EndpointInformationRecord
{
    uint16_t networkAddress;
    uint8_t endpointId;
    uint16_t profileId;
    uint16_t deviceId;
    uint8_t version;
} EmberAfEndpointInformationRecord;

// Struct for EventConfigurationPayload
typedef struct _EventConfigurationPayload
{
    uint16_t eventId;
    uint8_t eventConfiguration;
} EmberAfEventConfigurationPayload;

// Struct for EventLogPayload
typedef struct _EventLogPayload
{
    EmberAfEventLogId logId;
    uint16_t eventId;
    uint32_t eventTime;
    uint8_t * eventData;
} EmberAfEventLogPayload;

// Struct for ExtendedDiscoverAttributesInfoRecord
typedef struct _ExtendedDiscoverAttributesInfoRecord
{
    uint16_t attributeId;
    uint8_t attributeType;
    uint8_t attributeAccessControl;
} EmberAfExtendedDiscoverAttributesInfoRecord;

// Struct for GpPairingConfigurationGroupList
typedef struct _GpPairingConfigurationGroupList
{
    uint16_t SinkGroup;
    uint16_t Alias;
} EmberAfGpPairingConfigurationGroupList;

// Struct for GpTranslationTableUpdateTranslation
typedef struct _GpTranslationTableUpdateTranslation
{
    uint8_t index;
    uint8_t gpdCommandId;
    uint8_t endpoint;
    uint16_t profile;
    uint16_t cluster;
    uint8_t zigbeeCommandId;
    uint8_t * zigbeeCommandPayload;
    uint8_t * additionalInfoBlock;
} EmberAfGpTranslationTableUpdateTranslation;

// Struct for GroupInformationRecord
typedef struct _GroupInformationRecord
{
    uint16_t groupId;
    uint8_t groupType;
} EmberAfGroupInformationRecord;

// Struct for IasAceZoneStatusResult
typedef struct _IasAceZoneStatusResult
{
    uint8_t zoneId;
    uint16_t zoneStatus;
} EmberAfIasAceZoneStatusResult;

// Struct for NeighborInfo
typedef struct _NeighborInfo
{
    uint8_t * neighbor;
    int16_t x;
    int16_t y;
    int16_t z;
    int8_t rssi;
    uint8_t numberRssiMeasurements;
} EmberAfNeighborInfo;

// Struct for NodeInformation
typedef struct _NodeInformation
{
    uint16_t uid;
    uint16_t address;
    uint8_t endpoint;
    uint8_t * nickname;
} EmberAfNodeInformation;

// Struct for Notification
typedef struct _Notification
{
    uint16_t contentId;
    EmberAfStatus statusFeedback;
} EmberAfNotification;

// Struct for PowerProfileRecord
typedef struct _PowerProfileRecord
{
    uint8_t powerProfileId;
    uint8_t energyPhaseId;
    uint8_t powerProfileRemoteControl;
    uint8_t powerProfileState;
} EmberAfPowerProfileRecord;

// Struct for PriceMatrixSubPayload
typedef struct _PriceMatrixSubPayload
{
    uint8_t tierBlockId;
    uint32_t price;
} EmberAfPriceMatrixSubPayload;

// Struct for Protocol
typedef struct _Protocol
{
    uint16_t manufacturerCode;
    uint8_t protocolId;
} EmberAfProtocol;

// Struct for ReadAttributeStatusRecord
typedef struct _ReadAttributeStatusRecord
{
    uint16_t attributeId;
    EmberAfStatus status;
    uint8_t attributeType;
    uint8_t * attributeLocation;
} EmberAfReadAttributeStatusRecord;

// Struct for ReadReportingConfigurationAttributeRecord
typedef struct _ReadReportingConfigurationAttributeRecord
{
    uint8_t direction;
    uint16_t attributeId;
} EmberAfReadReportingConfigurationAttributeRecord;

// Struct for ReadReportingConfigurationRecord
typedef struct _ReadReportingConfigurationRecord
{
    EmberAfStatus status;
    uint8_t direction;
    uint16_t attributeId;
    uint8_t attributeType;
    uint16_t minimumReportingInterval;
    uint16_t maximumReportingInterval;
    uint8_t * reportableChangeLocation;
    uint16_t timeoutPeriod;
} EmberAfReadReportingConfigurationRecord;

// Struct for ReadStructuredAttributeRecord
typedef struct _ReadStructuredAttributeRecord
{
    uint16_t attributeId;
    uint8_t indicator;
    uint16_t indicies;
} EmberAfReadStructuredAttributeRecord;

// Struct for ReportAttributeRecord
typedef struct _ReportAttributeRecord
{
    uint16_t attributeId;
    uint8_t attributeType;
    uint8_t * attributeLocation;
} EmberAfReportAttributeRecord;

// Struct for SceneExtensionAttributeInfo
typedef struct _SceneExtensionAttributeInfo
{
    uint8_t attributeType;
    uint8_t * attributeLocation;
} EmberAfSceneExtensionAttributeInfo;

// Struct for SceneExtensionFieldSet
typedef struct _SceneExtensionFieldSet
{
    uint16_t clusterId;
    uint8_t length;
    uint8_t value;
} EmberAfSceneExtensionFieldSet;

// Struct for ScheduleEntry
typedef struct _ScheduleEntry
{
    uint16_t startTime;
    uint8_t activePriceTierOrFriendlyCreditEnable;
} EmberAfScheduleEntry;

// Struct for ScheduleEntryAuxilliaryLoadSwitchTimes
typedef struct _ScheduleEntryAuxilliaryLoadSwitchTimes
{
    uint16_t startTime;
    uint8_t auxiliaryLoadSwitchState;
} EmberAfScheduleEntryAuxilliaryLoadSwitchTimes;

// Struct for ScheduleEntryFriendlyCreditSwitchTimes
typedef struct _ScheduleEntryFriendlyCreditSwitchTimes
{
    uint16_t startTime;
    uint8_t friendlyCreditEnable;
} EmberAfScheduleEntryFriendlyCreditSwitchTimes;

// Struct for ScheduleEntryRateSwitchTimes
typedef struct _ScheduleEntryRateSwitchTimes
{
    uint16_t startTime;
    EmberAfPriceTier priceTier;
} EmberAfScheduleEntryRateSwitchTimes;

// Struct for ScheduledPhase
typedef struct _ScheduledPhase
{
    uint8_t energyPhaseId;
    uint16_t scheduledTime;
} EmberAfScheduledPhase;

// Struct for SeasonEntry
typedef struct _SeasonEntry
{
    uint32_t seasonStartDate;
    uint8_t weekIdRef;
} EmberAfSeasonEntry;

// Struct for SnapshotResponsePayload
typedef struct _SnapshotResponsePayload
{
    uint8_t snapshotScheduleId;
    EmberAfSnapshotScheduleConfirmation snapshotScheduleConfirmation;
} EmberAfSnapshotResponsePayload;

// Struct for SnapshotSchedulePayload
typedef struct _SnapshotSchedulePayload
{
    uint8_t snapshotScheduleId;
    uint32_t snapshotStartTime;
    uint32_t snapshotSchedule;
    EmberAfSnapshotPayloadType snapshotPayloadType;
    uint32_t snapshotCause;
} EmberAfSnapshotSchedulePayload;

// Struct for SpecialDay
typedef struct _SpecialDay
{
    uint32_t specialDayDate;
    uint8_t dayIdRef;
} EmberAfSpecialDay;

// Struct for TierLabelsPayload
typedef struct _TierLabelsPayload
{
    uint8_t tierId;
    uint8_t * tierLabel;
} EmberAfTierLabelsPayload;

// Struct for TopUpPayload
typedef struct _TopUpPayload
{
    uint8_t * topUpCode;
    int32_t topUpAmount;
    uint32_t topUpTime;
} EmberAfTopUpPayload;

// Struct for TransferredPhase
typedef struct _TransferredPhase
{
    uint8_t energyPhaseId;
    uint8_t macroPhaseId;
    uint16_t expectedDuration;
    uint16_t peakPower;
    uint16_t energy;
    uint16_t maxActivationDelay;
} EmberAfTransferredPhase;

// Struct for WriteAttributeRecord
typedef struct _WriteAttributeRecord
{
    uint16_t attributeId;
    uint8_t attributeType;
    uint8_t * attributeLocation;
} EmberAfWriteAttributeRecord;

// Struct for WriteAttributeStatusRecord
typedef struct _WriteAttributeStatusRecord
{
    EmberAfStatus status;
    uint16_t attributeId;
} EmberAfWriteAttributeStatusRecord;

// Struct for WriteStructuredAttributeRecord
typedef struct _WriteStructuredAttributeRecord
{
    uint16_t attributeId;
    uint8_t indicator;
    uint16_t indicies;
    uint8_t attributeType;
    uint8_t * attributeLocation;
} EmberAfWriteStructuredAttributeRecord;

// Struct for WriteStructuredAttributeStatusRecord
typedef struct _WriteStructuredAttributeStatusRecord
{
    EmberAfStatus status;
    uint16_t attributeId;
    uint8_t indicator;
    uint16_t indicies;
} EmberAfWriteStructuredAttributeStatusRecord;

// Struct for WwahBeaconSurvey
typedef struct _WwahBeaconSurvey
{
    uint16_t deviceShort;
    uint8_t rssi;
    uint8_t classificationMask;
} EmberAfWwahBeaconSurvey;

// Struct for WwahClusterStatusToUseTC
typedef struct _WwahClusterStatusToUseTC
{
    uint16_t clusterId;
    EmberAfStatus status;
} EmberAfWwahClusterStatusToUseTC;

#endif // SILABS_EMBER_AF_STRUCTS