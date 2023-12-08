/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

#pragma once

namespace chip {
namespace app {
namespace Clusters {
namespace DiagnosticLogs {
namespace bdx {
// Spec mandated max file designator length
static constexpr uint8_t kMaxFileDesignatorLen = 32;

// Spec mandated max size of the log content field in the Response payload
static constexpr uint16_t kMaxLogContentSize = 1024;

} // namespace bdx
} // namespace DiagnosticLogs
} // namespace Clusters
} // namespace app
} // namespace chip
