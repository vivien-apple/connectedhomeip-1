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

#pragma once

#include <app/util/af-enums.h>
#include <inttypes.h>

// Global Response Callbacks
typedef void (*DefaultSuccessCallback)(void * context);
typedef void (*DefaultFailureCallback)(void * context, uint8_t status);
typedef void (*BooleanAttributeCallback)(void * context, bool value);
typedef void (*Int8uAttributeCallback)(void * context, uint8_t value);
typedef void (*Int8sAttributeCallback)(void * context, int8_t value);
typedef void (*Int16uAttributeCallback)(void * context, uint16_t value);
typedef void (*Int16sAttributeCallback)(void * context, int16_t value);
typedef void (*Int32uAttributeCallback)(void * context, uint32_t value);
typedef void (*Int32sAttributeCallback)(void * context, int32_t value);
typedef void (*Int64uAttributeCallback)(void * context, uint64_t value);
typedef void (*Int64sAttributeCallback)(void * context, int64_t value);
typedef void (*ReadReportingConfigurationReportedCallback)(void * context, uint16_t minInterval, uint16_t maxInterval);
typedef void (*ReadReportingConfigurationReceivedCallback)(void * context, uint16_t timeout);

// Cluster Specific Response Callbacks
