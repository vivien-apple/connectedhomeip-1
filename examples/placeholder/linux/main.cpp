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

#include "AppMain.h"

#include <lib/support/CodeUtils.h>

#include "MatterCallbacks.h"

int main(int argc, char * argv[])
{
    VerifyOrDie(ChipLinuxAppInit(argc, argv) == 0);

    // XXX Need to pass a parameter instead of an hardcoded string.
    auto command = GetTestCommand("Test_FOO");
    chip::DeviceLayer::PlatformMgr().AddEventHandler(OnPlatformEvent, reinterpret_cast<intptr_t>(command.get()));

    ChipLinuxAppMainLoop();

    return 0;
}
