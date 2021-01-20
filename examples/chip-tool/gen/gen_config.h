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

// User options for plugin Binding Table Library
#define EMBER_BINDING_TABLE_SIZE 10

/**** Network Section ****/
#define EMBER_SUPPORTED_NETWORKS (1)

#define EMBER_APS_UNICAST_MESSAGE_COUNT 10

/**** Cluster endpoint counts ****/
#define EMBER_AF_BARRIER_CONTROL_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_BASIC_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_COLOR_CONTROL_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_DOOR_LOCK_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_GROUPS_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_IDENTIFY_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_LEVEL_CONTROL_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_ON_OFF_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_SCENES_CLUSTER_CLIENT_ENDPOINT_COUNT (1)
#define EMBER_AF_TEMP_MEASUREMENT_CLUSTER_CLIENT_ENDPOINT_COUNT (1)

/**** Cluster Plugins ****/

// Use this macro to check if the client side of the Barrier Control cluster is included
#define ZCL_USING_BARRIER_CONTROL_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_BARRIER_CONTROL_CLIENT

// Use this macro to check if the client side of the Basic cluster is included
#define ZCL_USING_BASIC_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_BASIC_CLIENT

// Use this macro to check if the client side of the Color Control cluster is included
#define ZCL_USING_COLOR_CONTROL_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_COLOR_CONTROL_CLIENT

// Use this macro to check if the client side of the Door Lock cluster is included
#define ZCL_USING_DOOR_LOCK_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_DOOR_LOCK_CLIENT

// Use this macro to check if the client side of the Groups cluster is included
#define ZCL_USING_GROUPS_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_GROUPS_CLIENT

// Use this macro to check if the client side of the Identify cluster is included
#define ZCL_USING_IDENTIFY_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_IDENTIFY_CLIENT

// Use this macro to check if the client side of the Level Control cluster is included
#define ZCL_USING_LEVEL_CONTROL_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_LEVEL_CONTROL_CLIENT

// Use this macro to check if the client side of the On/off cluster is included
#define ZCL_USING_ON_OFF_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_ON_OFF_CLIENT

// Use this macro to check if the client side of the Scenes cluster is included
#define ZCL_USING_SCENES_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_SCENES_CLIENT

// Use this macro to check if the client side of the Temperature Measurement cluster is included
#define ZCL_USING_TEMP_MEASUREMENT_CLUSTER_CLIENT
#define EMBER_AF_PLUGIN_TEMPERATURE_MEASUREMENT_CLIENT