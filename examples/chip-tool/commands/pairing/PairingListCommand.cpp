/*
 *   Copyright (c) 2021 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "PairingListCommand.h"

#include <lib/core/CHIPEncoding.h>
#include <lib/support/PersistentStorageMacros.h>
#include <lib/support/SafeInt.h>
#include <lib/support/Span.h>

CHIP_ERROR PairingListCommand::Run()
{
    ReturnLogErrorOnFailure(mStorage.Init());
    return PrintInformations();
}

CHIP_ERROR PairingListCommand::PrintInformations()
{
    uint64_t buffer[chip::Controller::kNumMaxPairedDevices];
    uint16_t bufferSize = sizeof(buffer);
    memset(buffer, 0, bufferSize);

    PERSISTENT_KEY_OP(static_cast<uint64_t>(0), chip::kPairedDeviceListKeyPrefix, key,
                      ReturnLogErrorOnFailure(mStorage.SyncGetKeyValue(key, buffer, bufferSize)));

    chip::SerializableU64Set<chip::Controller::kNumMaxPairedDevices> devices;
    devices.Deserialize(chip::ByteSpan((uint8_t *) buffer, bufferSize));

    uint16_t devicesCount = 0;
    while (buffer[devicesCount] != 0x0 && devicesCount < chip::Controller::kNumMaxPairedDevices)
    {
        devicesCount++;
    }

    if (devicesCount == 0)
    {
        ChipLogProgress(chipTool, "No paired devices.");
    }
    else
    {
        fprintf(stderr, "+---------------------------------------------------------------------------------------------+\n");
        fprintf(stderr, "|       NodeId       |                   Address                     | Port |    Interface    |\n");
        fprintf(stderr, "+---------------------------------------------------------------------------------------------+\n");
        for (uint16_t i = 0; i < devicesCount; i++)
        {
            ReturnLogErrorOnFailure(PrintDeviceInformations(buffer[i]));
        }
        fprintf(stderr, "+---------------------------------------------------------------------------------------------+\n");
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR PairingListCommand::PrintDeviceInformations(chip::NodeId deviceId)
{
    chip::Controller::SerializedDevice deviceInfo;
    uint16_t size = sizeof(deviceInfo.inner);

    PERSISTENT_KEY_OP(deviceId, chip::kPairedDeviceKeyPrefix, key,
                      ReturnLogErrorOnFailure(mStorage.SyncGetKeyValue(key, deviceInfo.inner, size)));
    VerifyOrReturnError(size <= sizeof(deviceInfo.inner), CHIP_ERROR_INVALID_DEVICE_DESCRIPTOR);

    chip::Controller::SerializableDevice serializable;
    constexpr size_t maxlen = BASE64_ENCODED_LEN(sizeof(serializable));
    const size_t len        = strnlen(chip::Uint8::to_const_char(&deviceInfo.inner[0]), maxlen);

    VerifyOrReturnError(len < sizeof(chip::Controller::SerializedDevice), CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(chip::CanCastTo<uint16_t>(len), CHIP_ERROR_INVALID_ARGUMENT);

    CHIP_ZERO_AT(serializable);
    const uint16_t deserializedLen = chip::Base64Decode(chip::Uint8::to_const_char(deviceInfo.inner), static_cast<uint16_t>(len),
                                                        chip::Uint8::to_uchar(reinterpret_cast<uint8_t *>(&serializable)));

    VerifyOrReturnError(deserializedLen > 0, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(deserializedLen <= sizeof(serializable), CHIP_ERROR_INVALID_ARGUMENT);

    const uint16_t port = chip::Encoding::LittleEndian::HostSwap16(serializable.mDevicePort);
    fprintf(stderr, "| 0x%-16" PRIx64 " | %-45s | %-5u| %-15s |\n", deviceId, serializable.mDeviceAddr, port,
            serializable.mInterfaceName);

    return CHIP_NO_ERROR;
}
