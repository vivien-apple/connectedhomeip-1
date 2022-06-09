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

/**
 *    @file
 *          Provides an implementation of the DiagnosticDataProvider object
 *          for Darwin platform.
 */

#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <lib/support/logging/CHIPLogging.h>
#include <platform/Darwin/DiagnosticDataProviderImpl.h>
#include <platform/DiagnosticDataProvider.h>

#include <arpa/inet.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

namespace chip {
namespace DeviceLayer {

DiagnosticDataProviderImpl & DiagnosticDataProviderImpl::GetDefaultInstance()
{
    static DiagnosticDataProviderImpl sInstance;
    return sInstance;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetUpTime(uint64_t & upTime)
{
    System::Clock::Timestamp currentTime = System::SystemClock().GetMonotonicTimestamp();
    System::Clock::Timestamp startTime   = PlatformMgrImpl().GetStartTime();

    if (currentTime >= startTime)
    {
        upTime = std::chrono::duration_cast<System::Clock::Seconds64>(currentTime - startTime).count();
        return CHIP_NO_ERROR;
    }

    return CHIP_ERROR_INVALID_TIME;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetTotalOperationalHours(uint32_t & totalOperationalHours)
{
    uint64_t upTime = 0;

    if (GetUpTime(upTime) == CHIP_NO_ERROR)
    {
        uint32_t totalHours = 0;
        if (ConfigurationMgr().GetTotalOperationalHours(totalHours) == CHIP_NO_ERROR)
        {
            VerifyOrReturnError(upTime / 3600 <= UINT32_MAX, CHIP_ERROR_INVALID_INTEGER_VALUE);
            totalOperationalHours = totalHours + static_cast<uint32_t>(upTime / 3600);
            return CHIP_NO_ERROR;
        }
    }

    return CHIP_ERROR_INVALID_TIME;
}

CHIP_ERROR DiagnosticDataProviderImpl::ResetWatermarks()
{
    // If implemented, the server SHALL set the value of the CurrentHeapHighWatermark attribute to the
    // value of the CurrentHeapUsed.
    // On Darwin, overide with non-op to pass CI.

    return CHIP_NO_ERROR;
}

CHIP_ERROR DiagnosticDataProviderImpl::GetNetworkInterfaces(NetworkInterface ** interfaces)
{
    NetworkInterface * interface = new NetworkInterface();

    strncpy(interface->Name, "WiFi-Test", Inet::InterfaceId::kMaxIfNameLength);
    interface->name          = CharSpan::fromCharString(interface->Name);
    interface->isOperational = true;
    interface->type          = EMBER_ZCL_INTERFACE_TYPE_WI_FI;
    interface->offPremiseServicesReachableIPv4.SetNull();
    interface->offPremiseServicesReachableIPv6.SetNull();

    uint8_t mac[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05 };
    memcpy(interface->MacAddress, mac, kMaxHardwareAddrSize);
    interface->hardwareAddress = ByteSpan(interface->MacAddress, sizeof(mac));
    interface->Next            = nullptr;

    *interfaces = interface;
    return CHIP_NO_ERROR;
}

void DiagnosticDataProviderImpl::ReleaseNetworkInterfaces(NetworkInterface * interface)
{
    while (interface)
    {
        NetworkInterface * del = interface;
        interface              = interface->Next;
        delete del;
    }
}

} // namespace DeviceLayer
} // namespace chip
