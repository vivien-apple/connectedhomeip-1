/**
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

#import "CHIPDeviceStatusDelegateBridge.h"
#import <Foundation/Foundation.h>
#import <app/server/DataModelHandler.h>

CHIPDeviceStatusDelegateBridge::CHIPDeviceStatusDelegateBridge(chip::NodeId deviceId)
    : mDeviceId(deviceId)
{
}

CHIPDeviceStatusDelegateBridge::~CHIPDeviceStatusDelegateBridge() {}

void CHIPDeviceStatusDelegateBridge::OnMessage(chip::System::PacketBufferHandle message)
{
    NSLog(@"DeviceStatusDelegate received message from the device");
    HandleDataModelMessage(mDeviceId, std::move(message));
}

void CHIPDeviceStatusDelegateBridge::OnStatusChange() { NSLog(@"CHIPDeviceStatusDelegateBridge device status changed"); }
