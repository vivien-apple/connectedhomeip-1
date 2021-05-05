/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

// Prevent multiple inclusion
#pragma once

// Default values for the attributes longer than a pointer,
// in a form of a binary blob
// Separate block is generated for big-endian and little-endian cases.
#if BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 0, Cluster: Basic (server), big-endian */                                                                     \
                                                                                                                                   \
        /* 0 - VendorName, */                                                                                                      \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                \
                                                                                                                                   \
            /* 32 - ProductName, */                                                                                                \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                          \
                                                                                                                                   \
            /* 64 - UserLabel, */                                                                                                  \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                          \
                                                                                                                                   \
            /* 96 - Location, */                                                                                                   \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                        \
                                                                                                                                   \
            /* 112 - HardwareVersionString, */                                                                                     \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                              \
                                                                                                                                   \
            /* 176 - SoftwareVersion, */                                                                                           \
            0x00, 0x00, 0x00, 0x00,                                                                                                \
                                                                                                                                   \
            /* 180 - SoftwareVersionString, */                                                                                     \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                              \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: General Commissioning (server), big-endian */                                                 \
                                                                                                                                   \
            /* 244 - FabricId, */                                                                                                  \
            1, 'o', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                            \
                                                                                                                                   \
            /* 252 - Breadcrumb, */                                                                                                \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                        \
    }

#else // !BIGENDIAN_CPU
#define GENERATED_DEFAULTS                                                                                                         \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 0, Cluster: Basic (server), little-endian */                                                                  \
                                                                                                                                   \
        /* 0 - VendorName, */                                                                                                      \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                \
                                                                                                                                   \
            /* 32 - ProductName, */                                                                                                \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                          \
                                                                                                                                   \
            /* 64 - UserLabel, */                                                                                                  \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                          \
                                                                                                                                   \
            /* 96 - Location, */                                                                                                   \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                        \
                                                                                                                                   \
            /* 112 - HardwareVersionString, */                                                                                     \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                              \
                                                                                                                                   \
            /* 176 - SoftwareVersion, */                                                                                           \
            0x00, 0x00, 0x00, 0x00,                                                                                                \
                                                                                                                                   \
            /* 180 - SoftwareVersionString, */                                                                                     \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,      \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                              \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: General Commissioning (server), little-endian */                                              \
                                                                                                                                   \
            /* 244 - FabricId, */                                                                                                  \
            1, 'o', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                            \
                                                                                                                                   \
            /* 252 - Breadcrumb, */                                                                                                \
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,                                                                        \
    }

#endif // BIGENDIAN_CPU

#define GENERATED_DEFAULTS_COUNT (9)

#define ZAP_TYPE(type) ZCL_##type##_ATTRIBUTE_TYPE
#define ZAP_LONG_DEFAULTS_INDEX(index)                                                                                             \
    {                                                                                                                              \
        (uint8_t *) (&generatedDefaults[index])                                                                                    \
    }
#define ZAP_MIN_MAX_DEFAULTS_INDEX(index)                                                                                          \
    {                                                                                                                              \
        (uint8_t *) (&minMaxDefault[index])                                                                                        \
    }
#define ZAP_EMPTY_DEFAULT()                                                                                                        \
    {                                                                                                                              \
        (uint8_t *) 0                                                                                                              \
    }
#define ZAP_SIMPLE_DEFAULT(x)                                                                                                      \
    {                                                                                                                              \
        (uint8_t *) x                                                                                                              \
    }

// This is an array of EmberAfAttributeMinMaxValue structures.
#define GENERATED_MIN_MAX_DEFAULT_COUNT 0
#define GENERATED_MIN_MAX_DEFAULTS                                                                                                 \
    {                                                                                                                              \
    }

#define ZAP_ATTRIBUTE_MASK(mask) ATTRIBUTE_MASK_##mask
// This is an array of EmberAfAttributeMetadata structures.
#define GENERATED_ATTRIBUTE_COUNT 20
#define GENERATED_ATTRIBUTES                                                                                                       \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 0, Cluster: On/off (server) */                                                                                \
        { 0x0000, ZAP_TYPE(BOOLEAN), 1, 0, ZAP_SIMPLE_DEFAULT(0x00) }, /* on/off */                                                \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(2) }, /* cluster revision */                                      \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Level Control (server) */                                                                     \
            { 0x0000, ZAP_TYPE(INT8U), 1, 0, ZAP_SIMPLE_DEFAULT(0x00) }, /* current level */                                       \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(3) },   /* cluster revision */                                    \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Basic (server) */                                                                             \
            { 0x0000, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_EMPTY_DEFAULT() }, /* InteractionModelVersion */     \
            { 0x0001, ZAP_TYPE(CHAR_STRING), 32, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_LONG_DEFAULTS_INDEX(0) },  /* VendorName */    \
            { 0x0002, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_EMPTY_DEFAULT() },               /* VendorID */      \
            { 0x0003, ZAP_TYPE(CHAR_STRING), 32, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_LONG_DEFAULTS_INDEX(32) }, /* ProductName */   \
            { 0x0004, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_EMPTY_DEFAULT() },               /* ProductID */     \
            { 0x0005, ZAP_TYPE(CHAR_STRING), 32, ZAP_ATTRIBUTE_MASK(SINGLETON) | ZAP_ATTRIBUTE_MASK(WRITABLE),                     \
              ZAP_LONG_DEFAULTS_INDEX(64) }, /* UserLabel */                                                                       \
            { 0x0006, ZAP_TYPE(CHAR_STRING), 16, ZAP_ATTRIBUTE_MASK(SINGLETON) | ZAP_ATTRIBUTE_MASK(WRITABLE),                     \
              ZAP_LONG_DEFAULTS_INDEX(96) },                                                          /* Location */               \
            { 0x0007, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_SIMPLE_DEFAULT(0x00) }, /* HardwareVersion */        \
            { 0x0008, ZAP_TYPE(CHAR_STRING), 64, ZAP_ATTRIBUTE_MASK(SINGLETON),                                                    \
              ZAP_LONG_DEFAULTS_INDEX(112) }, /* HardwareVersionString */                                                          \
            { 0x0009, ZAP_TYPE(INT32U), 4, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_LONG_DEFAULTS_INDEX(176) }, /* SoftwareVersion */    \
            { 0x000A, ZAP_TYPE(CHAR_STRING), 64, ZAP_ATTRIBUTE_MASK(SINGLETON),                                                    \
              ZAP_LONG_DEFAULTS_INDEX(180) },                                                      /* SoftwareVersionString */     \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, ZAP_ATTRIBUTE_MASK(SINGLETON), ZAP_SIMPLE_DEFAULT(3) }, /* cluster revision */          \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: General Commissioning (server) */                                                             \
            { 0x0000, ZAP_TYPE(OCTET_STRING), 8, 0, ZAP_LONG_DEFAULTS_INDEX(244) },                      /* FabricId */            \
            { 0x0001, ZAP_TYPE(INT64U), 8, ZAP_ATTRIBUTE_MASK(WRITABLE), ZAP_LONG_DEFAULTS_INDEX(252) }, /* Breadcrumb */          \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0001) },                              /* cluster revision */    \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Network Commissioning (server) */                                                             \
            { 0xFFFD, ZAP_TYPE(INT16U), 2, 0, ZAP_SIMPLE_DEFAULT(0x0001) }, /* cluster revision */                                 \
    }

// This is an array of EmberAfCluster structures.
#define ZAP_ATTRIBUTE_INDEX(index) ((EmberAfAttributeMetadata *) (&generatedAttributes[index]))

// Cluster function static arrays
#define GENERATED_FUNCTION_ARRAYS                                                                                                  \
    const EmberAfGenericClusterFunction chipFuncArrayOnOffServer[] = {                                                             \
        (EmberAfGenericClusterFunction) emberAfOnOffClusterServerInitCallback,                                                     \
    };                                                                                                                             \
    const EmberAfGenericClusterFunction chipFuncArrayLevelControlServer[] = {                                                      \
        (EmberAfGenericClusterFunction) emberAfLevelControlClusterServerInitCallback,                                              \
    };                                                                                                                             \
    const EmberAfGenericClusterFunction chipFuncArrayBasicServer[] = {                                                             \
        (EmberAfGenericClusterFunction) emberAfBasicClusterServerInitCallback,                                                     \
    };

#define ZAP_CLUSTER_MASK(mask) CLUSTER_MASK_##mask
#define GENERATED_CLUSTER_COUNT 5
#define GENERATED_CLUSTERS                                                                                                         \
    {                                                                                                                              \
        {                                                                                                                          \
            0x0006,                                                                                                                \
            ZAP_ATTRIBUTE_INDEX(0),                                                                                                \
            2,                                                                                                                     \
            3,                                                                                                                     \
            ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION),                                                            \
            chipFuncArrayOnOffServer                                                                                               \
        }, /* Endpoint: 0, Cluster: On/off (server) */                                                                             \
            { 0x0008,                                                                                                              \
              ZAP_ATTRIBUTE_INDEX(2),                                                                                              \
              2,                                                                                                                   \
              3,                                                                                                                   \
              ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION),                                                          \
              chipFuncArrayLevelControlServer }, /* Endpoint: 0, Cluster: Level Control (server) */                                \
            { 0x0028,                                                                                                              \
              ZAP_ATTRIBUTE_INDEX(4),                                                                                              \
              12,                                                                                                                  \
              254,                                                                                                                 \
              ZAP_CLUSTER_MASK(SERVER) | ZAP_CLUSTER_MASK(INIT_FUNCTION),                                                          \
              chipFuncArrayBasicServer }, /* Endpoint: 0, Cluster: Basic (server) */                                               \
            {                                                                                                                      \
                0x0030, ZAP_ATTRIBUTE_INDEX(16), 3, 18, ZAP_CLUSTER_MASK(SERVER), NULL                                             \
            }, /* Endpoint: 0, Cluster: General Commissioning (server) */                                                          \
            {                                                                                                                      \
                0x0031, ZAP_ATTRIBUTE_INDEX(19), 1, 2, ZAP_CLUSTER_MASK(SERVER), NULL                                              \
            }, /* Endpoint: 0, Cluster: Network Commissioning (server) */                                                          \
    }

#define ZAP_CLUSTER_INDEX(index) ((EmberAfCluster *) (&generatedClusters[index]))

// This is an array of EmberAfEndpointType structures.
#define GENERATED_ENDPOINT_TYPES                                                                                                   \
    {                                                                                                                              \
        { ZAP_CLUSTER_INDEX(0), 5, 280 },                                                                                          \
    }

// Largest attribute size is needed for various buffers
#define ATTRIBUTE_LARGEST (65)

// Total size of singleton attributes
#define ATTRIBUTE_SINGLETONS_SIZE (254)

// Total size of attribute storage
#define ATTRIBUTE_MAX_SIZE (280)

// Number of fixed endpoints
#define FIXED_ENDPOINT_COUNT (1)

// Array of endpoints that are supported, the data inside
// the array is the endpoint number.
#define FIXED_ENDPOINT_ARRAY                                                                                                       \
    {                                                                                                                              \
        0x0000                                                                                                                     \
    }

// Array of profile ids
#define FIXED_PROFILE_IDS                                                                                                          \
    {                                                                                                                              \
        0x0104                                                                                                                     \
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
#define EMBER_AF_GENERATED_COMMAND_COUNT (37)
#define GENERATED_COMMANDS                                                                                                         \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 0, Cluster: On/off (server) */                                                                                \
        { 0x0006, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) },     /* Off */                                                         \
            { 0x0006, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* On */                                                          \
            { 0x0006, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Toggle */                                                      \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Level Control (server) */                                                                     \
            { 0x0008, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* MoveToLevel */                                                 \
            { 0x0008, 0x01, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Move */                                                        \
            { 0x0008, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Step */                                                        \
            { 0x0008, 0x03, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* Stop */                                                        \
            { 0x0008, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* MoveToLevelWithOnOff */                                        \
            { 0x0008, 0x05, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* MoveWithOnOff */                                               \
            { 0x0008, 0x06, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* StepWithOnOff */                                               \
            { 0x0008, 0x07, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* StopWithOnOff */                                               \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Basic (server) */                                                                             \
            { 0x0028, 0x00, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* StartUp */                                                     \
            { 0x0028, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* ShutDown */                                                    \
            { 0x0028, 0x02, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* Leave */                                                       \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: General Commissioning (server) */                                                             \
            { 0x0030, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* ArmFailSafe */                                                 \
            { 0x0030, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* ArmFailSafeResponse */                                         \
            { 0x0030, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* SetRegulatoryConfig */                                         \
            { 0x0030, 0x03, ZAP_COMMAND_MASK(OUTGOING_SERVER) }, /* SetRegulatoryConfigResponse */                                 \
            { 0x0030, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* CommissioningComplete */                                       \
            { 0x0030, 0x05, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* CommissioningCompleteResponse */                               \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Network Commissioning (server) */                                                             \
            { 0x0031, 0x00, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* ScanNetworks */                                                \
            { 0x0031, 0x01, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* ScanNetworksResponse */                                        \
            { 0x0031, 0x02, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* AddWiFiNetwork */                                              \
            { 0x0031, 0x03, ZAP_COMMAND_MASK(OUTGOING_SERVER) }, /* AddWiFiNetworkResponse */                                      \
            { 0x0031, 0x04, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* UpdateWiFiNetwork */                                           \
            { 0x0031, 0x05, ZAP_COMMAND_MASK(OUTGOING_SERVER) }, /* UpdateWiFiNetworkResponse */                                   \
            { 0x0031, 0x06, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* AddThreadNetwork */                                            \
            { 0x0031, 0x07, ZAP_COMMAND_MASK(OUTGOING_SERVER) }, /* AddThreadNetworkResponse */                                    \
            { 0x0031, 0x08, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* UpdateThreadNetwork */                                         \
            { 0x0031, 0x09, ZAP_COMMAND_MASK(OUTGOING_SERVER) }, /* UpdateThreadNetworkResponse */                                 \
            { 0x0031, 0x0A, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* RemoveNetwork */                                               \
            { 0x0031, 0x0B, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* RemoveNetworkResponse */                                       \
            { 0x0031, 0x0C, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* EnableNetwork */                                               \
            { 0x0031, 0x0D, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* EnableNetworkResponse */                                       \
            { 0x0031, 0x0E, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* DisableNetwork */                                              \
            { 0x0031, 0x0F, ZAP_COMMAND_MASK(INCOMING_CLIENT) }, /* DisableNetworkResponse */                                      \
            { 0x0031, 0x10, ZAP_COMMAND_MASK(INCOMING_SERVER) }, /* GetLastNetworkCommissioningResult */                           \
    }

// Array of EmberAfManufacturerCodeEntry structures for commands.
#define GENERATED_COMMAND_MANUFACTURER_CODE_COUNT (0)
#define GENERATED_COMMAND_MANUFACTURER_CODES                                                                                       \
    {                                                                                                                              \
        {                                                                                                                          \
            0x00, 0x00                                                                                                             \
        }                                                                                                                          \
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

// User options for plugin Reporting
#define EMBER_AF_PLUGIN_REPORTING_TABLE_SIZE (2)
#define EMBER_AF_PLUGIN_REPORTING_ENABLE_GROUP_BOUND_REPORTS

#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE (2)
#define EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS                                                                               \
    {                                                                                                                              \
                                                                                                                                   \
        /* Endpoint: 0, Cluster: On/off (server) */                                                                                \
        {                                                                                                                          \
            ZAP_REPORT_DIRECTION(REPORTED), 0x0000, 0x0006, 0x0000, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }          \
        }, /* on/off */                                                                                                            \
                                                                                                                                   \
            /* Endpoint: 0, Cluster: Level Control (server) */                                                                     \
            {                                                                                                                      \
                ZAP_REPORT_DIRECTION(REPORTED), 0x0000, 0x0008, 0x0000, ZAP_CLUSTER_MASK(SERVER), 0x0000, { { 0, 65344, 0 } }      \
            }, /* current level */                                                                                                 \
    }
