/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2018 Nest Labs, Inc.
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
 *          for Darwin platforms.
 */
#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <ble/CHIPBleServiceData.h>
#include <lib/support/logging/CHIPLogging.h>
#include <platform/CommissionableDataProvider.h>
#include <platform/Darwin/BleApplicationDelegate.h>
#include <platform/Darwin/BleConnectionDelegate.h>
#include <platform/Darwin/BlePeripheral.h>
#include <platform/Darwin/BlePlatformDelegate.h>

#include <new>

#if CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE

using namespace ::chip;
using namespace ::chip::Ble;

namespace chip {
namespace DeviceLayer {
namespace Internal {

BlePeripheral peripheral;

BLEManagerImpl BLEManagerImpl::sInstance;

CHIP_ERROR BLEManagerImpl::_Init()
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    // Initialize the Chip BleLayer.
    BleApplicationDelegateImpl * appDelegate   = new BleApplicationDelegateImpl();
    BleConnectionDelegateImpl * connDelegate   = new BleConnectionDelegateImpl();
    BlePlatformDelegateImpl * platformDelegate = new BlePlatformDelegateImpl();
    ReturnErrorOnFailure(BleLayer::Init(platformDelegate, connDelegate, appDelegate, &SystemLayer()));

    mFlags.ClearAll();
    mFlags.Set(Flags::kAdvertisingEnabled, CHIP_DEVICE_CONFIG_CHIPOBLE_ENABLE_ADVERTISING_AUTOSTART && !mIsCentral);
    mFlags.Set(Flags::kFastAdvertisingEnabled, true);

    memset(mDeviceName, 0, sizeof(mDeviceName));

    mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Enabled;

    PlatformMgr().ScheduleWork(DriveBLEState, 0);

    return CHIP_NO_ERROR;
}

ConnectivityManager::CHIPoBLEServiceMode BLEManagerImpl::_GetCHIPoBLEServiceMode(void)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    return mServiceMode;
}

CHIP_ERROR BLEManagerImpl::_SetCHIPoBLEServiceMode(ConnectivityManager::CHIPoBLEServiceMode val)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    ReturnErrorCodeIf(val == ConnectivityManager::kCHIPoBLEServiceMode_NotSupported, CHIP_ERROR_INVALID_ARGUMENT);
    ReturnErrorCodeIf(mServiceMode != ConnectivityManager::kCHIPoBLEServiceMode_NotSupported, CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE);
    if (val != mServiceMode)
    {
        mServiceMode = val;
        PlatformMgr().ScheduleWork(DriveBLEState, 0);
    }

    return CHIP_NO_ERROR;
}

bool BLEManagerImpl::_IsAdvertisingEnabled(void)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    return mFlags.Has(Flags::kAdvertisingEnabled);
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingEnabled(bool val)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    if (val != mFlags.Has(Flags::kAdvertisingEnabled))
    {
        mFlags.Set(Flags::kAdvertisingEnabled, val);
    }

    PlatformMgr().ScheduleWork(DriveBLEState, 0);
    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingMode(BLEAdvertisingMode mode)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    switch (mode)
    {
    case BLEAdvertisingMode::kFastAdvertising:
        mFlags.Set(Flags::kFastAdvertisingEnabled, true);
        mFlags.Set(Flags::kAdvertisingRefreshNeeded);
        break;
    case BLEAdvertisingMode::kSlowAdvertising:
        mFlags.Set(Flags::kFastAdvertisingEnabled, false);
        break;
    default:
        return CHIP_ERROR_INVALID_ARGUMENT;
    }

    mFlags.Set(Flags::kAdvertisingRefreshNeeded);
    PlatformMgr().ScheduleWork(DriveBLEState, 0);
    return CHIP_NO_ERROR;
}

bool BLEManagerImpl::_IsAdvertising(void)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    return mFlags.Has(Flags::kAdvertising);
}

CHIP_ERROR BLEManagerImpl::_GetDeviceName(char * buf, size_t bufSize)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    ReturnErrorCodeIf(strlen(mDeviceName) >= bufSize, CHIP_ERROR_BUFFER_TOO_SMALL);

    strcpy(buf, mDeviceName);

    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_SetDeviceName(const char * deviceName)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);
    ReturnErrorCodeIf(mServiceMode != ConnectivityManager::kCHIPoBLEServiceMode_NotSupported, CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE);
    if (deviceName != nullptr && deviceName[0] != 0)
    {
        ReturnErrorCodeIf(strlen(deviceName) >= kMaxDeviceNameLength, CHIP_ERROR_INVALID_ARGUMENT);
        strcpy(mDeviceName, deviceName);

        mFlags.Set(Flags::kUseCustomDeviceName);
    }
    else
    {
        uint16_t discriminator;
        ReturnErrorOnFailure(GetCommissionableDataProvider()->GetSetupDiscriminator(discriminator));
        snprintf(mDeviceName, sizeof(mDeviceName), "%s%04u", CHIP_DEVICE_CONFIG_BLE_DEVICE_NAME_PREFIX, discriminator);

        mDeviceName[kMaxDeviceNameLength] = 0;
        mFlags.Clear(Flags::kUseCustomDeviceName);
    }

    return CHIP_NO_ERROR;
}

BleLayer * BLEManagerImpl::_GetBleLayer()
{
    return this;
}

uint16_t BLEManagerImpl::_NumConnections(void)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);
    return 0;
}

void BLEManagerImpl::_OnPlatformEvent(const ChipDeviceEvent * event)
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);
}

void BLEManagerImpl::DriveBLEState()
{
    if (mIsCentral)
    {
        return;
    }

    CHIP_ERROR err = CHIP_NO_ERROR;

    if (!mFlags.Has(Flags::kAsyncInitCompleted))
    {
        mFlags.Set(Flags::kAsyncInitCompleted);

        // If CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED is enabled,
        // disable CHIPoBLE advertising if the device is fully provisioned.
#if CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        if (ConfigurationMgr().IsFullyProvisioned())
        {
            mFlags.Clear(Flags::kAdvertisingEnabled);
            ChipLogProgress(DeviceLayer, "CHIPoBLE advertising disabled because device is fully provisioned");
        }
#endif // CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        ExitNow();
    }

    // If there's already a control operation in progress, wait until it completes.
    VerifyOrExit(!mFlags.Has(Flags::kControlOpInProgress), /* */);

    if (mServiceMode == ConnectivityManager::kCHIPoBLEServiceMode_Enabled && !mFlags.Has(Flags::kDarwinBLELayerInitialized))
    {
        uint16_t discriminator;
        err = GetCommissionableDataProvider()->GetSetupDiscriminator(discriminator);
        SuccessOrExit(err);

        err = peripheral.Init(GetBleLayer(), nullptr, discriminator);
        SuccessOrExit(err);
        mFlags.Set(Flags::kDarwinBLELayerInitialized);
    }

    // If the application has enabled CHIPoBLE and BLE advertising...
    if (mServiceMode == ConnectivityManager::kCHIPoBLEServiceMode_Enabled && mFlags.Has(Flags::kAdvertisingEnabled))
    {
        // Start/re-start advertising if not already advertising, or if the advertising state of the
        // Bluez BLE layer needs to be refreshed.
        if (!mFlags.Has(Flags::kAdvertising) || mFlags.Has(Flags::kAdvertisingRefreshNeeded))
        {
            mFlags.Clear(Flags::kAdvertisingRefreshNeeded);

            // Configure advertising data if it hasn't been done yet.  This is an asynchronous step which
            // must complete before advertising can be started.  When that happens, this method will
            // be called again, and execution will proceed to the code below.
            if (!mFlags.Has(Flags::kAdvertisingConfigured))
            {
                err = peripheral.UpdateAdvertising();
                ExitNow();
            }

            // Start advertising.  This is also an asynchronous step.
            err = peripheral.StartAdvertising();
            SuccessOrExit(err);

            sInstance.mFlags.Set(Flags::kAdvertising);
            ExitNow();
        }
    }
    // Otherwise stop advertising if needed...
    else
    {
        if (mFlags.Has(Flags::kAdvertising))
        {
            err = peripheral.StopAdvertising();
            SuccessOrExit(err);
            mFlags.Set(Flags::kControlOpInProgress);

            ExitNow();
        }
    }
exit:
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "Disabling CHIPoBLE service due to error: %s", ErrorStr(err));
        mServiceMode = ConnectivityManager::kCHIPoBLEServiceMode_Disabled;
    }
}

void BLEManagerImpl::DriveBLEState(intptr_t arg)
{
    sInstance.DriveBLEState();
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip

#endif // CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
