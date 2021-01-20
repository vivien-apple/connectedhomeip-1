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

// Prevent multiple inclusion
#pragma once

// Default values for the attributes longer than a pointer,
// in a form of a binary blob
// Separate block is generated for big-endian and little-endian cases.
#if BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
    }

#else // !BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
    }

#endif // BIGENDIAN_CPU

#define GENERATED_DEFAULTS_COUNT (0)

#define ZAP_TYPE(type) ZCL_##type##_ATTRIBUTE_TYPE
#define ZAP_LONG_DEFAULTS_INDEX(index)                                                                                             \
    {                                                                                                                              \
        (uint8_t *) (&generatedDefaults[index])                                                                                    \
    }
#define ZAP_MIN_MAX_DEFAULTS_INDEX(index)                                                                                          \
    {                                                                                                                              \
        (uint8_t *) (&minMaxDefault[index])                                                                                        \
    }

// This is an array of EmberAfAttributeMinMaxValue structures.
#define GENERATED_MIN_MAX_DEFAULT_COUNT 0
#define GENERATED_MIN_MAX_DEFAULTS                                                                                                 \
    {                                                                                                                              \
    }

#define ZAP_ATTRIBUTE_MASK(mask) ATTRIBUTE_MASK_##mask
// This is an array of EmberAfAttributeMetadata structures.
#define GENERATED_ATTRIBUTE_COUNT 10
#define GENERATED_ATTRIBUTES                                                                                                       \
    {                                                                                                                              \
        { 0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 } }, /* Basic (client): cluster revision */     \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 2 }                                         \
            }, /* Identify (client): cluster revision */                                                                           \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Groups (client): cluster revision */                                                                             \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Scenes (client): cluster revision */                                                                             \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 2 }                                         \
            }, /* On/off (client): cluster revision */                                                                             \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Level Control (client): cluster revision */                                                                      \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Door Lock (client): cluster revision */                                                                          \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 0x0001 }                                    \
            }, /* Barrier Control (client): cluster revision */                                                                    \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Color Control (client): cluster revision */                                                                      \
            {                                                                                                                      \
                0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(CLIENT), { (uint8_t *) 3 }                                         \
            }, /* Temperature Measurement (client): cluster revision */                                                            \
    }

// This is an array of EmberAfCluster structures.
#define ZAP_ATTRIBUTE_INDEX(index) ((EmberAfAttributeMetadata *) (&generatedAttributes[index]))

// Cluster function static arrays
#define GENERATED_FUNCTION_ARRAYS

#define ZAP_CLUSTER_MASK(mask) CLUSTER_MASK_##mask
#define GENERATED_CLUSTER_COUNT 10
#define GENERATED_CLUSTERS                                                                                                         \
    {                                                                                                                              \
        { 0x0000, ZAP_ATTRIBUTE_INDEX(0), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL }, /* Endpoint: 1, Cluster: Basic (client) */       \
            {                                                                                                                      \
                0x0003, ZAP_ATTRIBUTE_INDEX(1), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Identify (client) */                                                                       \
            { 0x0004, ZAP_ATTRIBUTE_INDEX(2), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL }, /* Endpoint: 1, Cluster: Groups (client) */  \
            { 0x0005, ZAP_ATTRIBUTE_INDEX(3), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL }, /* Endpoint: 1, Cluster: Scenes (client) */  \
            { 0x0006, ZAP_ATTRIBUTE_INDEX(4), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL }, /* Endpoint: 1, Cluster: On/off (client) */  \
            {                                                                                                                      \
                0x0008, ZAP_ATTRIBUTE_INDEX(5), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Level Control (client) */                                                                  \
            {                                                                                                                      \
                0x0101, ZAP_ATTRIBUTE_INDEX(6), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Door Lock (client) */                                                                      \
            {                                                                                                                      \
                0x0103, ZAP_ATTRIBUTE_INDEX(7), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Barrier Control (client) */                                                                \
            {                                                                                                                      \
                0x0300, ZAP_ATTRIBUTE_INDEX(8), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Color Control (client) */                                                                  \
            {                                                                                                                      \
                0x0402, ZAP_ATTRIBUTE_INDEX(9), 1, 2, ZAP_CLUSTER_MASK(CLIENT), NULL                                               \
            }, /* Endpoint: 1, Cluster: Temperature Measurement (client) */                                                        \
    }

#define ZAP_CLUSTER_INDEX(index) ((EmberAfCluster *) (&generatedClusters[index]))

// This is an array of EmberAfEndpointType structures.
#define GENERATED_ENDPOINT_TYPES                                                                                                   \
    {                                                                                                                              \
        { ZAP_CLUSTER_INDEX(0), 10, 20 },                                                                                          \
    }

// Largest attribute size is needed for various buffers
#define ATTRIBUTE_LARGEST (2)

// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (0)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE (20)

// Number of fixed endpoints
#define FIXED_ENDPOINT_COUNT (1)

// Array of endpoints that are supported, the data inside
// the array is the endpoint number.
#define FIXED_ENDPOINT_ARRAY                                                                                                       \
    {                                                                                                                              \
        0x0001                                                                                                                     \
    }

// Array of profile ids
#define FIXED_PROFILE_IDS                                                                                                          \
    {                                                                                                                              \
        0x0103                                                                                                                     \
    }

// Array of device ids
#define FIXED_DEVICE_IDS                                                                                                           \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of device versions
#define FIXED_DEVICE_VERSIONS                                                                                                      \
    {                                                                                                                              \
        1                                                                                                                          \
    }

// Array of endpoint types supported on each endpoint
#define FIXED_ENDPOINT_TYPES                                                                                                       \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of networks supported on each endpoint
#define FIXED_NETWORKS                                                                                                             \
    {                                                                                                                              \
        0                                                                                                                          \
    }

// Array of EmberAfCommandMetadata structs.
#define ZAP_COMMAND_MASK(mask) COMMAND_MASK_##mask
#define EMBER_AF_GENERATED_COMMAND_COUNT (102)
#define GENERATED_COMMANDS                                                                                                         \
    {                                                                                                                              \
        { 0x0000, 0x00,                                                                                                            \
          ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Basic (client): MfgSpecificPing */           \
            {                                                                                                                      \
                0x0000, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            },                                                   /* Basic (client): ResetToFactoryDefaults */                      \
            { 0x0003, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Identify (client): Identify */                                 \
            { 0x0003, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Identify (client): IdentifyQueryResponse */                    \
            { 0x0003, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Identify (client): IdentifyQuery */                            \
            { 0x0004, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): AddGroup */                                   \
            { 0x0004, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Groups (client): AddGroupResponse */                           \
            { 0x0004, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): ViewGroup */                                  \
            { 0x0004, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Groups (client): ViewGroupResponse */                          \
            { 0x0004, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): GetGroupMembership */                         \
            { 0x0004, 0x02, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Groups (client): GetGroupMembershipResponse */                 \
            { 0x0004, 0x03, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): RemoveGroup */                                \
            { 0x0004, 0x03, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Groups (client): RemoveGroupResponse */                        \
            { 0x0004, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): RemoveAllGroups */                            \
            { 0x0004, 0x05, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Groups (client): AddGroupIfIdentifying */                      \
            { 0x0005, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): AddScene */                                   \
            { 0x0005, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): AddSceneResponse */                           \
            { 0x0005, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): ViewScene */                                  \
            { 0x0005, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): ViewSceneResponse */                          \
            { 0x0005, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): RemoveScene */                                \
            { 0x0005, 0x02, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): RemoveSceneResponse */                        \
            { 0x0005, 0x03, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): RemoveAllScenes */                            \
            { 0x0005, 0x03, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): RemoveAllScenesResponse */                    \
            { 0x0005, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): StoreScene */                                 \
            { 0x0005, 0x04, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): StoreSceneResponse */                         \
            { 0x0005, 0x05, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): RecallScene */                                \
            { 0x0005, 0x06, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Scenes (client): GetSceneMembership */                         \
            { 0x0005, 0x06, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Scenes (client): GetSceneMembershipResponse */                 \
            { 0x0006, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* On/off (client): Off */                                        \
            { 0x0006, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* On/off (client): On */                                         \
            { 0x0006, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* On/off (client): Toggle */                                     \
            { 0x0008, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): MoveToLevel */                         \
            { 0x0008, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): Move */                                \
            { 0x0008, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): Step */                                \
            { 0x0008, 0x03, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): Stop */                                \
            { 0x0008, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): MoveToLevelWithOnOff */                \
            { 0x0008, 0x05, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): MoveWithOnOff */                       \
            { 0x0008, 0x06, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): StepWithOnOff */                       \
            { 0x0008, 0x07, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Level Control (client): StopWithOnOff */                       \
            { 0x0101, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Door Lock (client): LockDoor */                                \
            { 0x0101, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Door Lock (client): LockDoorResponse */                        \
            { 0x0101, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Door Lock (client): UnlockDoor */                              \
            { 0x0101, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Door Lock (client): UnlockDoorResponse */                      \
            { 0x0101, 0x03,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): UnlockWithTimeout */ \
            {                                                                                                                      \
                0x0101, 0x03, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): UnlockWithTimeoutResponse */                                                                 \
            { 0x0101, 0x04,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetLogRecord */      \
            {                                                                                                                      \
                0x0101, 0x04, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetLogRecordResponse */                                                                      \
            { 0x0101, 0x05,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): SetPin */            \
            { 0x0101, 0x06,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetPin */            \
            { 0x0101, 0x06,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetPinResponse */    \
            { 0x0101, 0x07,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearPin */          \
            { 0x0101, 0x07,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearPinResponse */  \
            { 0x0101, 0x08,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearAllPins */      \
            {                                                                                                                      \
                0x0101, 0x08, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            },                   /* Door Lock (client): ClearAllPinsResponse */                                                    \
            { 0x0101, 0x09, 0 }, /* Door Lock (client): SetUserStatusResponse */                                                   \
            { 0x0101, 0x0A, 0 }, /* Door Lock (client): GetUserStatusResponse */                                                   \
            {                                                                                                                      \
                0x0101, 0x0B, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetWeekdaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x0B, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetWeekdayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x0C, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetWeekdaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x0C, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetWeekdayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x0D, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearWeekdaySchedule */                                                                      \
            {                                                                                                                      \
                0x0101, 0x0D, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearWeekdayScheduleResponse */                                                              \
            {                                                                                                                      \
                0x0101, 0x0E, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetYeardaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x0E, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetYeardayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x0F, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetYeardaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x0F, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetYeardayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x10, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearYeardaySchedule */                                                                      \
            {                                                                                                                      \
                0x0101, 0x10, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearYeardayScheduleResponse */                                                              \
            {                                                                                                                      \
                0x0101, 0x11, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetHolidaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x11, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetHolidayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x12, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetHolidaySchedule */                                                                        \
            {                                                                                                                      \
                0x0101, 0x12, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetHolidayScheduleResponse */                                                                \
            {                                                                                                                      \
                0x0101, 0x13, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearHolidaySchedule */                                                                      \
            {                                                                                                                      \
                0x0101, 0x13, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): ClearHolidayScheduleResponse */                                                              \
            { 0x0101, 0x14,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): SetUserType */       \
            {                                                                                                                      \
                0x0101, 0x14, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): SetUserTypeResponse */                                                                       \
            { 0x0101, 0x15,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetUserType */       \
            {                                                                                                                      \
                0x0101, 0x15, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Door Lock (client): GetUserTypeResponse */                                                                       \
            { 0x0101, 0x16,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): SetRfid */           \
            { 0x0101, 0x16,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): SetRfidResponse */   \
            { 0x0101, 0x17,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetRfid */           \
            { 0x0101, 0x17,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): GetRfidResponse */   \
            { 0x0101, 0x18,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearRfid */         \
            { 0x0101, 0x18,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearRfidResponse */ \
            { 0x0101, 0x19,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Door Lock (client): ClearAllRfids */     \
            {                                                                                                                      \
                0x0101, 0x19, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            },                                                   /* Door Lock (client): ClearAllRfidsResponse */                   \
            { 0x0103, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Barrier Control (client): BarrierControlGoToPercent */         \
            { 0x0103, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Barrier Control (client): BarrierControlStop */                \
            { 0x0300, 0x00,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Color Control (client): MoveToHue */     \
            { 0x0300, 0x01,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Color Control (client): MoveHue */       \
            { 0x0300, 0x02,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Color Control (client): StepHue */       \
            {                                                                                                                      \
                0x0300, 0x03, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): MoveToSaturation */                                                                      \
            {                                                                                                                      \
                0x0300, 0x04, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): MoveSaturation */                                                                        \
            {                                                                                                                      \
                0x0300, 0x05, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): StepSaturation */                                                                        \
            {                                                                                                                      \
                0x0300, 0x06, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            },                                                   /* Color Control (client): MoveToHueAndSaturation */              \
            { 0x0300, 0x07, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Color Control (client): MoveToColor */                         \
            { 0x0300, 0x08, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Color Control (client): MoveColor */                           \
            { 0x0300, 0x09, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Color Control (client): StepColor */                           \
            {                                                                                                                      \
                0x0300, 0x0A, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): MoveToColorTemperature */                                                                \
            { 0x0300, 0x47,                                                                                                        \
              ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT) }, /* Color Control (client): StopMoveStep */  \
            {                                                                                                                      \
                0x0300, 0x4B, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): MoveColorTemperature */                                                                  \
            {                                                                                                                      \
                0x0300, 0x4C, ZAP_COMMAND_MASK(INCOMING_CLIENT) | ZAP_COMMAND_MASK(OUTGOING_CLIENT)                                \
            }, /* Color Control (client): StepColorTemperature */                                                                  \
    }

// Array of EmberAfManufacturerCodeEntry structures for commands.
#define GENERATED_COMMAND_MANUFACTURER_CODE_COUNT (1)
#define GENERATED_COMMAND_MANUFACTURER_CODES                                                                                       \
    {                                                                                                                              \
        { 0, 0x1002 },                                                                                                             \
    }

// This is an array of EmberAfManufacturerCodeEntry structures for clusters.
#define GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_CLUSTER_MANUFACTURER_CODES                                                                                       \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
    }

// This is an array of EmberAfManufacturerCodeEntry structures for attributes.
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_ATTRIBUTE_MANUFACTURER_CODES                                                                                     \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
    }

// Array of EmberAfPluginReportingEntry structures.
#define ZRD(x) EMBER_ZCL_REPORTING_DIRECTION_##x
#define ZAP_REPORT_DIRECTION(x) ZRD(x)

#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE (0)
#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS                                                                               \
    {                                                                                                                              \
    }
