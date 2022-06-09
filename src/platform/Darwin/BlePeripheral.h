/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#include <lib/core/CHIPError.h>
#include <platform/ConnectivityManager.h>

namespace chip {
namespace DeviceLayer {
namespace Internal {

class BlePeripheral
{
public:
    CHIP_ERROR Init();

    CHIP_ERROR SetAdvertisingEnabled(bool enabled);

    bool IsAdvertisingEnabled();

    bool IsAdvertising();

    CHIP_ERROR SetAdvertisingMode(ConnectivityManager::BLEAdvertisingMode mode);

    CHIP_ERROR GetDeviceName(char * buffer, size_t bufferSize);

    CHIP_ERROR SetDeviceName(const char * deviceName);
};

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip
