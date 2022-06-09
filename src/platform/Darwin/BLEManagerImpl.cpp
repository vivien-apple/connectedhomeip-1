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

namespace {
static BlePeripheral gPeripheral;
} // namespace

BLEManagerImpl BLEManagerImpl::sInstance;

CHIP_ERROR BLEManagerImpl::ConfigureBle(uint32_t nodeId, bool isCentral)
{
    mIsCentral = isCentral;
    return CHIP_NO_ERROR;
}

CHIP_ERROR BLEManagerImpl::_Init()
{
    ChipLogDetail(DeviceLayer, "%s", __FUNCTION__);

    // Initialize the Chip BleLayer.
    BleApplicationDelegateImpl * appDelegate   = new BleApplicationDelegateImpl();
    BleConnectionDelegateImpl * connDelegate   = new BleConnectionDelegateImpl();
    BlePlatformDelegateImpl * platformDelegate = new BlePlatformDelegateImpl();
    ReturnErrorOnFailure(BleLayer::Init(platformDelegate, connDelegate, appDelegate, &SystemLayer()));

    if (mIsCentral)
    {
        ReturnErrorOnFailure(_SetCHIPoBLEServiceMode(ConnectivityManager::kCHIPoBLEServiceMode_Disabled));
    }
    else
    {
        ReturnErrorOnFailure(_SetCHIPoBLEServiceMode(ConnectivityManager::kCHIPoBLEServiceMode_Enabled));

        bool shouldStartAdvertising = CHIP_DEVICE_CONFIG_CHIPOBLE_ENABLE_ADVERTISING_AUTOSTART;
#if CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        if (shouldStartAdvertising && ConfigurationMgr().IsFullyProvisioned())
        {
            shouldStartAdvertising = false;
        }

#endif // CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        ReturnErrorOnFailure(_SetAdvertisingEnabled(shouldStartAdvertising));
    }

    return CHIP_NO_ERROR;
}

ConnectivityManager::CHIPoBLEServiceMode BLEManagerImpl::_GetCHIPoBLEServiceMode(void)
{
    return mServiceMode;
}

CHIP_ERROR BLEManagerImpl::_SetCHIPoBLEServiceMode(ConnectivityManager::CHIPoBLEServiceMode val)
{
    ReturnErrorCodeIf(val == ConnectivityManager::kCHIPoBLEServiceMode_NotSupported, CHIP_ERROR_INVALID_ARGUMENT);
    ReturnErrorCodeIf(mServiceMode != ConnectivityManager::kCHIPoBLEServiceMode_NotSupported, CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE);

    if (val == ConnectivityManager::kCHIPoBLEServiceMode_Enabled)
    {
        ReturnErrorOnFailure(gPeripheral.Init());
    }

    mServiceMode = val;
    return CHIP_NO_ERROR;
}

bool BLEManagerImpl::_IsAdvertisingEnabled(void)
{
    return gPeripheral.IsAdvertisingEnabled();
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingEnabled(bool val)
{
    return gPeripheral.SetAdvertisingEnabled(val);
}

CHIP_ERROR BLEManagerImpl::_SetAdvertisingMode(BLEAdvertisingMode mode)
{
    return gPeripheral.SetAdvertisingMode(mode);
}

bool BLEManagerImpl::_IsAdvertising(void)
{
    return gPeripheral.IsAdvertising();
}

CHIP_ERROR BLEManagerImpl::_GetDeviceName(char * buffer, size_t bufferSize)
{
    return gPeripheral.GetDeviceName(buffer, bufferSize);
}

CHIP_ERROR BLEManagerImpl::_SetDeviceName(const char * deviceName)
{
    return gPeripheral.SetDeviceName(deviceName);
}

BleLayer * BLEManagerImpl::_GetBleLayer()
{
    return this;
}

uint16_t BLEManagerImpl::_NumConnections(void)
{
    return mHasConnection ? 1 : 0;
}

void BLEManagerImpl::_OnPlatformEvent(const ChipDeviceEvent * event)
{
    auto svcId           = &CHIP_BLE_SVC_ID;
    const ChipBleUUID C1 = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F, 0x9D, 0x11 } };
    const ChipBleUUID C2 = { { 0x18, 0xEE, 0x2E, 0xF5, 0x26, 0x3D, 0x45, 0x59, 0x95, 0x9F, 0x4F, 0x9C, 0x42, 0x9F, 0x9D, 0x12 } };

    switch (event->Type)
    {
    case DeviceEventType::kCHIPoBLESubscribe:
        HandleSubscribeReceived(event->CHIPoBLESubscribe.ConId, svcId, &C2);
        mHasConnection = true;
        {
            ChipDeviceEvent evt;
            evt.Type = DeviceEventType::kCHIPoBLEConnectionEstablished;
            PlatformMgr().PostEventOrDie(&evt);
        }
        break;

    case DeviceEventType::kCHIPoBLEUnsubscribe:
        HandleUnsubscribeReceived(event->CHIPoBLEUnsubscribe.ConId, svcId, &C2);
        mHasConnection = false;
        {
            ChipDeviceEvent evt;
            evt.Type = DeviceEventType::kCHIPoBLEConnectionClosed;
            PlatformMgr().PostEventOrDie(&evt);
        }
        break;

    case DeviceEventType::kCHIPoBLEIndicateConfirm:
        HandleIndicationConfirmation(event->CHIPoBLEIndicateConfirm.ConId, svcId, &C2);
        break;

    case DeviceEventType::kCHIPoBLEWriteReceived:
        HandleWriteReceived(event->CHIPoBLEWriteReceived.ConId, svcId, &C1,
                            PacketBufferHandle::Adopt(event->CHIPoBLEWriteReceived.Data));
        break;

    case DeviceEventType::kCHIPoBLEAdvertisingChange:
        ChipLogError(Ble, "DeviceEventType::kCHIPoBLEAdvertisingChange");
        break;

    case DeviceEventType::kCHIPoBLEConnectionError:
        HandleConnectionError(event->CHIPoBLEConnectionError.ConId, event->CHIPoBLEConnectionError.Reason);
        break;

    case DeviceEventType::kServiceProvisioningChange:
    case DeviceEventType::kAccountPairingChange:
        ChipLogError(Ble, "Service provisoning or account pairing change...");
#if CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        // If CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED is enabled, and there is a change to the
        // device's provisioning state, then automatically disable CHIPoBLE advertising if the device
        // is now fully provisioned.
        if (ConfigurationMgr().IsFullyProvisioned())
        {
            _SetAdvertisingEnabled(false);
            ChipLogProgress(DeviceLayer, "CHIPoBLE advertising disabled because device is fully provisioned");
        }
#endif // CHIP_DEVICE_CONFIG_CHIPOBLE_DISABLE_ADVERTISING_WHEN_PROVISIONED
        break;
    default:
        // Not interested in the other events.
        break;
    }
}

} // namespace Internal
} // namespace DeviceLayer
} // namespace chip

#endif // CHIP_DEVICE_CONFIG_ENABLE_CHIPOBLE
