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

#include <transport/RendezvousSession.h>
#include <platform/CHIPDeviceLayer.h>

using namespace ::chip;

class RendezvousDeviceCallbacks : public RendezvousSessionCallback
{
public:
    RendezvousDeviceCallbacks(Ble::BLEEndPoint * endPoint);
    CHIP_ERROR Send(const char * msg);
    static void OnNewConnection(Ble::BLEEndPoint * endPoint);

private:
    RendezvousSession * mRendezvousSession;

    CHIP_ERROR GetSetupPINCode(uint32_t * setupPINCode);

    //////////// RendezvousSession callback Implementation ///////////////
    void OnRendezvousError(CHIP_ERROR err) override;
    void OnRendezvousConnectionOpened(CHIP_ERROR err) override;
    void OnRendezvousConnectionClosed(CHIP_ERROR err) override;
    void OnRendezvousMessageReceived(PacketBuffer * buffer) override;
};
