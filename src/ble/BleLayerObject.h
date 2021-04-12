/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2014-2017 Nest Labs, Inc.
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
 *    @file
 *      This file defines the interface that will be used by objects in BLE Layer.
 */

#pragma once

namespace chip {
namespace Ble {

class BleLayer;
class BleLayerDelegate;

class BleLayerObject
{
    friend class BleLayer;

public:
    // Public data members:
    BleLayer * mBle; ///< [READ-ONLY] Pointer to the BleLayer object that owns this object.
    BleLayerDelegate * mBleTransport;
    void * mAppState; ///< Generic pointer to app-specific data associated with the object.

protected:
    uint32_t mRefCount;

    void AddRef() { mRefCount++; }
    void Release();
};

} // namespace Ble
} // namespace chip
