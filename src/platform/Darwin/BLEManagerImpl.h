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

/**
 *    @file
 *          Provides an implementation of the BLEManager singleton object
 *          for the Darwin platforms.
 */

#pragma once

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE

namespace chip {
namespace DeviceLayer {
namespace Internal {

using namespace chip::Ble;

/**
 * Concrete implementation of the BLEManagerImpl singleton object for the Darwin platforms.
 */
class BLEManagerImpl final : public BLEManager, private BleLayer
{
    // Allow the BLEManager interface class to delegate method calls to
    // the implementation methods provided by this class.
    friend BLEManager;

public:
    CHIP_ERROR ConfigureBle(uint32_t aNodeId, bool aIsCentral) { return CHIP_NO_ERROR; }

private:
    // ===== Members that implement the BLEManager internal interface.

    CHIP_ERROR _Init(void);
    CHIP_ERROR _Shutdown() { return CHIP_NO_ERROR; }
    CHIPoBLEServiceMode _GetCHIPoBLEServiceMode(void);
    CHIP_ERROR _SetCHIPoBLEServiceMode(CHIPoBLEServiceMode val);
    bool _IsAdvertisingEnabled(void);
    CHIP_ERROR _SetAdvertisingEnabled(bool val);
    bool _IsAdvertising(void);
    CHIP_ERROR _SetAdvertisingMode(BLEAdvertisingMode mode);
    CHIP_ERROR _GetDeviceName(char * buf, size_t bufSize);
    CHIP_ERROR _SetDeviceName(const char * deviceName);
    uint16_t _NumConnections(void);
    void _OnPlatformEvent(const ChipDeviceEvent * event);
    BleLayer * _GetBleLayer(void);

    // ===== Members for internal use by the following friends.

    friend BLEManager & BLEMgr(void);
    friend BLEManagerImpl & BLEMgrImpl(void);

    static BLEManagerImpl sInstance;

    CHIPoBLEServiceMode mServiceMode;
    bool mIsCentral = false;

    enum
    {
        kMaxDeviceNameLength = 20
    };

    char mDeviceName[kMaxDeviceNameLength + 1];

    enum class Flags : uint16_t
    {
        kAsyncInitCompleted        = 0x0001, /**< One-time asynchronous initialization actions have been performed. */
        kDarwinBLELayerInitialized = 0x0002, /**< The Darwin layer has been initialized. */
        kAppRegistered             = 0x0004, /**< The CHIPoBLE application has been registered with the Bluez layer. */
        kAdvertisingConfigured     = 0x0008, /**< CHIPoBLE advertising has been configured in the Bluez layer. */
        kAdvertising               = 0x0010, /**< The system is currently CHIPoBLE advertising. */
        kControlOpInProgress       = 0x0020, /**< An async control operation has been issued to the ESP BLE layer. */
        kAdvertisingEnabled        = 0x0040, /**< The application has enabled CHIPoBLE advertising. */
        kFastAdvertisingEnabled    = 0x0080, /**< The application has enabled fast advertising. */
        kUseCustomDeviceName       = 0x0100, /**< The application has configured a custom BLE device name. */
        kAdvertisingRefreshNeeded  = 0x0200, /**< The advertising configuration/state in BLE layer needs to be updated. */
    };

    BitFlags<Flags> mFlags;

    void DriveBLEState();
    static void DriveBLEState(intptr_t arg);
};

/**
 * Returns a reference to the public interface of the BLEManager singleton object.
 *
 * Internal components should use this to access features of the BLEManager object
 * that are common to all platforms.
 */
inline BLEManager & BLEMgr(void)
{
    return BLEManagerImpl::sInstance;
}

/**
 * Returns the platform-specific implementation of the BLEManager singleton object.
 *
 * Internal components can use this to gain access to features of the BLEManager
 * that are specific to the Darwin platforms.
 */
inline BLEManagerImpl & BLEMgrImpl(void)
{
    return BLEManagerImpl::sInstance;
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip

#endif // CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
