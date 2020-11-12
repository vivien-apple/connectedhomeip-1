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
#ifndef SILABS_ZNET_CONFIG
#define SILABS_ZNET_CONFIG

#include "debug-printing-test.h"

/**** Included Header Section ****/

// Networks
#define EM_AF_GENERATED_NETWORK_TYPES                                                                                              \
    {                                                                                                                              \
        EM_AF_NETWORK_TYPE_ZIGBEE_PRO, /* Primary */                                                                               \
    }
#define EM_AF_GENERATED_ZIGBEE_PRO_NETWORKS                                                                                        \
    {                                                                                                                              \
        {                                                                                                                          \
            /* Primary */                                                                                                          \
            ZA_ROUTER,                                                                                                             \
            EMBER_AF_SECURITY_PROFILE_Z3,                                                                                          \
        },                                                                                                                         \
    }
#define EM_AF_GENERATED_NETWORK_STRINGS "Primary (pro)", /**** ZCL Section ****/
#define ZA_PROMPT "CHIPv1Clusters"
#define ZCL_USING_BASIC_CLUSTER_SERVER
#define ZCL_USING_IDENTIFY_CLUSTER_SERVER
#define ZCL_USING_GROUPS_CLUSTER_SERVER
#define ZCL_USING_SCENES_CLUSTER_SERVER
#define ZCL_USING_ON_OFF_CLUSTER_SERVER
#define ZCL_USING_ON_OFF_SWITCH_CONFIG_CLUSTER_SERVER
#define ZCL_USING_LEVEL_CONTROL_CLUSTER_SERVER
#define ZCL_USING_DOOR_LOCK_CLUSTER_SERVER
#define ZCL_USING_BARRIER_CONTROL_CLUSTER_SERVER
#define ZCL_USING_COLOR_CONTROL_CLUSTER_SERVER
#define ZCL_USING_TEMP_MEASUREMENT_CLUSTER_SERVER
#define ZCL_USING_IAS_ZONE_CLUSTER_SERVER
/**** Optional Attributes ****/
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_CURRENT_HUE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_CURRENT_SATURATION_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_REMAINING_TIME_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_TEMPERATURE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_MODE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_NUMBER_OF_PRIMARIES_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_1_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_1_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_1_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_2_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_2_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_2_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_3_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_3_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_3_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_4_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_4_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_4_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_5_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_5_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_5_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_6_X_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_6_Y_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_PRIMARY_6_INTENSITY_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_ENHANCED_CURRENT_HUE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_ENHANCED_COLOR_MODE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_LOOP_ACTIVE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_LOOP_DIRECTION_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_LOOP_TIME_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_LOOP_START_ENHANCED_HUE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_LOOP_STORED_ENHANCED_HUE_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_CAPABILITIES_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MIN_ATTRIBUTE
#define ZCL_USING_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_COLOR_TEMP_PHYSICAL_MAX_ATTRIBUTE
#define EMBER_AF_MANUFACTURER_CODE 0x1002
#define EMBER_AF_DEFAULT_RESPONSE_POLICY_ALWAYS

/**** Cluster endpoint counts ****/
#define EMBER_AF_BASIC_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_IDENTIFY_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_GROUPS_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_SCENES_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_ON_OFF_CLUSTER_SERVER_ENDPOINT_COUNT (2)
#define EMBER_AF_ON_OFF_SWITCH_CONFIG_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_LEVEL_CONTROL_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_DOOR_LOCK_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_BARRIER_CONTROL_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_COLOR_CONTROL_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_TEMP_MEASUREMENT_CLUSTER_SERVER_ENDPOINT_COUNT (1)
#define EMBER_AF_IAS_ZONE_CLUSTER_SERVER_ENDPOINT_COUNT (1)

/**** Cluster Endpoint Summaries ****/
#define EMBER_AF_MAX_SERVER_CLUSTER_COUNT (12)
#define EMBER_AF_MAX_CLIENT_CLUSTER_COUNT (0)
#define EMBER_AF_MAX_TOTAL_CLUSTER_COUNT (12)

/**** CLI Section ****/
#define EMBER_AF_GENERATE_CLI

/**** Security Section ****/
#define EMBER_AF_HAS_SECURITY_PROFILE_Z3

/**** Network Section ****/
#define EMBER_SUPPORTED_NETWORKS (1)
#define EMBER_AF_ZC_AND_ZR_DEVICE_COUNT (1)
#define EMBER_AF_NETWORK_INDEX_PRIMARY (0)
#define EMBER_AF_DEFAULT_NETWORK_INDEX EMBER_AF_NETWORK_INDEX_PRIMARY
#define EMBER_AF_HAS_ROUTER_NETWORK
#define EMBER_AF_HAS_RX_ON_WHEN_IDLE_NETWORK
#define EMBER_AF_TX_POWER_MODE EMBER_TX_POWER_MODE_USE_TOKEN

/**** Callback Section ****/
#define EMBER_CALLBACK_STACK_STATUS
#define EMBER_CALLBACK_SCENES_CLUSTER_SCENES_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_SCENES_CLUSTER_ADD_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_VIEW_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_ALL_SCENES
#define EMBER_CALLBACK_SCENES_CLUSTER_STORE_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_GET_SCENE_MEMBERSHIP
#define EMBER_CALLBACK_SCENES_CLUSTER_STORE_CURRENT_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_RECALL_SAVED_SCENE
#define EMBER_CALLBACK_SCENES_CLUSTER_CLEAR_SCENE_TABLE
#define EMBER_CALLBACK_SCENES_CLUSTER_SCENES_CLUSTER_MAKE_INVALID
#define EMBER_CALLBACK_SCENES_CLUSTER_REMOVE_SCENES_IN_GROUP
#define EMBER_CALLBACK_GROUPS_CLUSTER_GROUPS_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP
#define EMBER_CALLBACK_GROUPS_CLUSTER_VIEW_GROUP
#define EMBER_CALLBACK_GROUPS_CLUSTER_GET_GROUP_MEMBERSHIP
#define EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_GROUP
#define EMBER_CALLBACK_GROUPS_CLUSTER_REMOVE_ALL_GROUPS
#define EMBER_CALLBACK_GROUPS_CLUSTER_ADD_GROUP_IF_IDENTIFYING
#define EMBER_CALLBACK_GROUPS_CLUSTER_ENDPOINT_IN_GROUP
#define EMBER_CALLBACK_GROUPS_CLUSTER_CLEAR_GROUP_TABLE
#define EMBER_CALLBACK_CONFIGURE_REPORTING_COMMAND
#define EMBER_CALLBACK_READ_REPORTING_CONFIGURATION_COMMAND
#define EMBER_CALLBACK_CLEAR_REPORT_TABLE
#define EMBER_CALLBACK_REPORTING_ATTRIBUTE_CHANGE
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY
#define EMBER_CALLBACK_IDENTIFY_CLUSTER_IDENTIFY_QUERY
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_LEVEL_CONTROL_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_LEVEL_CONTROL_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_TO_LEVEL_WITH_ON_OFF
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_MOVE_WITH_ON_OFF
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STEP_WITH_ON_OFF
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP
#define EMBER_CALLBACK_LEVEL_CONTROL_CLUSTER_STOP_WITH_ON_OFF
#define EMBER_CALLBACK_ON_OFF_CLUSTER_ON_OFF_CLUSTER_LEVEL_CONTROL_EFFECT
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_COLOR_CONTROL_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STOP_MOVE_STEP
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_COLOR
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_COLOR
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_COLOR_TEMPERATURE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_COLOR_TEMPERATURE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_COLOR_TEMPERATURE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE_AND_SATURATION
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_HUE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_SATURATION
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_HUE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_MOVE_TO_SATURATION
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_HUE
#define EMBER_CALLBACK_COLOR_CONTROL_CLUSTER_STEP_SATURATION
#define EMBER_CALLBACK_TEMPERATURE_READING_COMPLETE
#define EMBER_CALLBACK_ON_OFF_CLUSTER_ON_OFF_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_ON_OFF_CLUSTER_OFF
#define EMBER_CALLBACK_ON_OFF_CLUSTER_ON
#define EMBER_CALLBACK_ON_OFF_CLUSTER_TOGGLE
#define EMBER_CALLBACK_ON_OFF_CLUSTER_ON_OFF_CLUSTER_SET_VALUE
#define EMBER_CALLBACK_BARRIER_CONTROL_CLUSTER_BARRIER_CONTROL_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_BARRIER_CONTROL_CLUSTER_BARRIER_CONTROL_GO_TO_PERCENT
#define EMBER_CALLBACK_BARRIER_CONTROL_CLUSTER_BARRIER_CONTROL_STOP
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_LOCK_DOOR
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_DOOR
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_PIN
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_PIN
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_PIN
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_ALL_PINS
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_WEEKDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_WEEKDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_WEEKDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_LOG_RECORD
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_USER_TYPE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_USER_TYPE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_YEARDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_YEARDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_YEARDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_HOLIDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_HOLIDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_HOLIDAY_SCHEDULE
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_SET_RFID
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_GET_RFID
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_RFID
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_CLEAR_ALL_RFIDS
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_DOOR_LOCK_CLUSTER_SERVER_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_DOOR_LOCK_CLUSTER_UNLOCK_WITH_TIMEOUT
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_PRE_ATTRIBUTE_CHANGED
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_ZONE_ENROLL_RESPONSE
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_INIT
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_TICK
#define EMBER_CALLBACK_IAS_ZONE_CLUSTER_IAS_ZONE_CLUSTER_SERVER_MESSAGE_SENT
#define EMBER_CALLBACK_BASIC_CLUSTER_RESET_TO_FACTORY_DEFAULTS
/**** Debug printing section ****/

// Global switch
#define EMBER_AF_PRINT_ENABLE
// Individual areas

#define EMBER_AF_SUPPORT_COMMAND_DISCOVERY

// Generated plugin macros

// Use this macro to check if Antenna Stub plugin is included
#define EMBER_AF_PLUGIN_ANTENNA_STUB

// Use this macro to check if Barrier Control Server Cluster plugin is included
#define EMBER_AF_PLUGIN_BARRIER_CONTROL_SERVER

// Use this macro to check if Basic Server Cluster plugin is included
#define EMBER_AF_PLUGIN_BASIC

// Use this macro to check if Binding Table Library plugin is included
#define EMBER_AF_PLUGIN_BINDING_TABLE_LIBRARY
// User options for plugin Binding Table Library
#define EMBER_BINDING_TABLE_SIZE 10

// Use this macro to check if CCM* Encryption plugin is included
#define EMBER_AF_PLUGIN_CCM_ENCRYPTION
// User options for plugin CCM* Encryption
#define EMBER_AF_PLUGIN_CCM_ENCRYPTION_SOFTWARE_CCM
#define USE_SOFTWARE_CCM

// Use this macro to check if Radio Coexistence Stub plugin is included
#define EMBER_AF_PLUGIN_COEXISTENCE_STUB

// Use this macro to check if Color Control Cluster Server plugin is included
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER
// User options for plugin Color Control Cluster Server
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_XY
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_TEMP
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_HSV
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_MIN_REPORT_INTERVAL 1
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_MAX_REPORT_INTERVAL 65535
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_COLOR_XY_CHANGE 1
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_COLOR_TEMP_CHANGE 1
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_HUE_CHANGE 1
#define EMBER_AF_PLUGIN_COLOR_CONTROL_SERVER_SATURATION_CHANGE 1

// Use this macro to check if Debug Basic Library plugin is included
#define EMBER_AF_PLUGIN_DEBUG_BASIC_LIBRARY

// Use this macro to check if Debug JTAG plugin is included
#define EMBER_AF_PLUGIN_DEBUG_JTAG

// Use this macro to check if Door Lock Server Cluster plugin is included
#define EMBER_AF_PLUGIN_DOOR_LOCK_SERVER

// Use this macro to check if Ember Minimal Printf plugin is included
#define EMBER_AF_PLUGIN_EMBER_MINIMAL_PRINTF

// Use this macro to check if Groups Server Cluster plugin is included
#define EMBER_AF_PLUGIN_GROUPS_SERVER

// Use this macro to check if HAL Library plugin is included
#define EMBER_AF_PLUGIN_HAL_LIBRARY

// Use this macro to check if IAS Zone Server plugin is included
#define EMBER_AF_PLUGIN_IAS_ZONE_SERVER
// User options for plugin IAS Zone Server
#define EMBER_AF_PLUGIN_IAS_ZONE_SERVER_ZONE_TYPE 541

// Use this macro to check if Identify Cluster plugin is included
#define EMBER_AF_PLUGIN_IDENTIFY

// Use this macro to check if Level Control Server Cluster plugin is included
#define EMBER_AF_PLUGIN_LEVEL_CONTROL
// User options for plugin Level Control Server Cluster
#define EMBER_AF_PLUGIN_LEVEL_CONTROL_MAXIMUM_LEVEL 255
#define EMBER_AF_PLUGIN_LEVEL_CONTROL_MINIMUM_LEVEL 0
#define EMBER_AF_PLUGIN_LEVEL_CONTROL_RATE 0

// Use this macro to check if mbed TLS plugin is included
#define EMBER_AF_PLUGIN_MBEDTLS
// User options for plugin mbed TLS
#define EMBER_AF_PLUGIN_MBEDTLS_CONF_DEVICE_ACCELERATION
#define EMBER_AF_PLUGIN_MBEDTLS_CONF_DEVICE_ACCELERATION_APP

// Use this macro to check if NVM3 Library plugin is included
#define EMBER_AF_PLUGIN_NVM3
// User options for plugin NVM3 Library
#define EMBER_AF_PLUGIN_NVM3_FLASH_PAGES 18
#define EMBER_AF_PLUGIN_NVM3_CACHE_SIZE 200
#define EMBER_AF_PLUGIN_NVM3_MAX_OBJECT_SIZE 254
#define EMBER_AF_PLUGIN_NVM3_USER_REPACK_HEADROOM 0

// Use this macro to check if On/Off Server Cluster plugin is included
#define EMBER_AF_PLUGIN_ON_OFF

// Use this macro to check if Packet Validate Library plugin is included
#define EMBER_AF_PLUGIN_PACKET_VALIDATE_LIBRARY

// Use this macro to check if RAIL Library plugin is included
#define EMBER_AF_PLUGIN_RAIL_LIBRARY
// User options for plugin RAIL Library
#define EMBER_AF_PLUGIN_RAIL_LIBRARY_RAILPHYDEF 1

// Use this macro to check if Reporting plugin is included
#define EMBER_AF_PLUGIN_REPORTING
// User options for plugin Reporting
#define EMBER_AF_PLUGIN_REPORTING_TABLE_SIZE 5
#define EMBER_AF_PLUGIN_REPORTING_ENABLE_GROUP_BOUND_REPORTS

// Use this macro to check if Scenes Server Cluster plugin is included
#define EMBER_AF_PLUGIN_SCENES
// User options for plugin Scenes Server Cluster
#define EMBER_AF_PLUGIN_SCENES_TABLE_SIZE 3

// Use this macro to check if Serial plugin is included
#define EMBER_AF_PLUGIN_SERIAL

// Use this macro to check if Simulated EEPROM version 2 to NVM3 Upgrade Stub plugin is included
#define EMBER_AF_PLUGIN_SIM_EEPROM2_TO_NVM3_UPGRADE_STUB

// Use this macro to check if Simple Main plugin is included
#define EMBER_AF_PLUGIN_SIMPLE_MAIN

// Use this macro to check if Strong Random plugin is included
#define EMBER_AF_PLUGIN_STRONG_RANDOM
// User options for plugin Strong Random
#define EMBER_AF_PLUGIN_STRONG_RANDOM_RADIO_PRNG
#define USE_RADIO_API_FOR_TRNG

// Use this macro to check if Temperature Measurement Server Cluster plugin is included
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER
// User options for plugin Temperature Measurement Server Cluster
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_MAX_MEASUREMENT_FREQUENCY_S 300
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_DEFAULT_REPORTABLE_TEMPERATURE_CHANGE_M_C 500
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_OVER_TEMPERATURE
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_OVER_TEMPERATURE_ASSERT_WARNING_THRESHOLD 55
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_OVER_TEMPERATURE_DEASSERT_WARNING_THRESHOLD 50
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_OVER_TEMPERATURE_ASSERT_CRITICAL_THRESHOLD 60
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_SERVER_OVER_TEMPERATURE_DEASSERT_CRITICAL_THRESHOLD 55

// Use this macro to check if Temperature Si7053 Stub plugin is included
#define EMBER_AF_PLUGIN_TEMPERATURE_SI7053_STUB

// Use this macro to check if ZCL Framework Core plugin is included
#define EMBER_AF_PLUGIN_ZCL_FRAMEWORK_CORE
// User options for plugin ZCL Framework Core
#define EMBER_AF_PLUGIN_ZCL_FRAMEWORK_CORE_CLI_ENABLED
#define ZA_CLI_FULL

// Use this macro to check if ZigBee PRO Stack Library plugin is included
#define EMBER_AF_PLUGIN_ZIGBEE_PRO_LIBRARY
// User options for plugin ZigBee PRO Stack Library
#define EMBER_MAX_END_DEVICE_CHILDREN 6
#define EMBER_PACKET_BUFFER_COUNT 75
#define EMBER_END_DEVICE_KEEP_ALIVE_SUPPORT_MODE EMBER_KEEP_ALIVE_SUPPORT_ALL
#define EMBER_END_DEVICE_POLL_TIMEOUT MINUTES_256
#define EMBER_END_DEVICE_POLL_TIMEOUT_SHIFT 6
#define EMBER_LINK_POWER_DELTA_INTERVAL 300
#define EMBER_APS_UNICAST_MESSAGE_COUNT 10
#define EMBER_BROADCAST_TABLE_SIZE 15
#define EMBER_NEIGHBOR_TABLE_SIZE 16

// Generated API headers

// API antenna from Antenna Stub plugin
#define EMBER_AF_API_ANTENNA                                                                                                       \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/base/hal/plugin/antenna/antenna.h"

// API coexistence from Radio Coexistence Stub plugin
#define EMBER_AF_API_COEXISTENCE                                                                                                   \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/radio/rail_lib/plugin/coexistence/protocol/"         \
    "ieee802154/coexistence-802154.h"

// API nvm3 from NVM3 Library plugin
#define EMBER_AF_API_NVM3                                                                                                          \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/base/hal/plugin/nvm3/nvm3-token.h"

// API rail-library from RAIL Library plugin
#define EMBER_AF_API_RAIL_LIBRARY                                                                                                  \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/radio/rail_lib/common/rail.h"

// API serial from Serial plugin
#define EMBER_AF_API_SERIAL                                                                                                        \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/base/hal/plugin/serial/serial.h"

// API temperature from Temperature Si7053 Stub plugin
#define EMBER_AF_API_TEMPERATURE                                                                                                   \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/platform/base/hal/plugin/temperature/temperature.h"

// API command-interpreter2 from ZCL Framework Core plugin
#define EMBER_AF_API_COMMAND_INTERPRETER2                                                                                          \
    "../../../../../Applications/Simplicity "                                                                                      \
    "Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v3.0/protocol/zigbee/app/util/serial/command-interpreter2.h"

// Custom macros
#ifdef TRANSITION_TIME_DS
#undef TRANSITION_TIME_DS
#endif
#define TRANSITION_TIME_DS 20

#ifdef FINDING_AND_BINDING_DELAY_MS
#undef FINDING_AND_BINDING_DELAY_MS
#endif
#define FINDING_AND_BINDING_DELAY_MS 3000

#endif // SILABS_ZNET_CONFIG
