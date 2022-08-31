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

/**
 *    @file
 *      This file declares an implementation of System::Layer using select().
 */

#pragma once

#include <lib/support/ObjectLifeCycle.h>
#include <system/SystemLayer.h>
#include <system/SystemTimer.h>

namespace chip {
namespace System {

class LayerImplDispatch : public LayerSockets
{
public:
    LayerImplDispatch() = default;
    ~LayerImplDispatch() override { VerifyOrDie(mLayerState.Destroy()); }

    // Layer overrides.
    CHIP_ERROR Init() override;
    void Shutdown() override;
    bool IsInitialized() const override { return mLayerState.IsInitialized(); }
    CHIP_ERROR StartTimer(Clock::Timeout delay, TimerCompleteCallback onComplete, void * appState) override;
    void CancelTimer(TimerCompleteCallback onComplete, void * appState) override;
    CHIP_ERROR ScheduleWork(TimerCompleteCallback onComplete, void * appState) override;

    // LayerSocket overrides.
    CHIP_ERROR StartWatchingSocket(int fd, SocketWatchToken * tokenOut) override;
    CHIP_ERROR SetCallback(SocketWatchToken token, SocketWatchCallback callback, intptr_t data) override;
    CHIP_ERROR RequestCallbackOnPendingRead(SocketWatchToken token) override;
    CHIP_ERROR RequestCallbackOnPendingWrite(SocketWatchToken token) override;
    CHIP_ERROR ClearCallbackOnPendingRead(SocketWatchToken token) override;
    CHIP_ERROR ClearCallbackOnPendingWrite(SocketWatchToken token) override;
    CHIP_ERROR StopWatchingSocket(SocketWatchToken * tokenInOut) override;
    SocketWatchToken InvalidSocketWatchToken() override { return reinterpret_cast<SocketWatchToken>(nullptr); }

    void SetDispatchQueue(dispatch_queue_t dispatchQueue) override { mDispatchQueue = dispatchQueue; };
    dispatch_queue_t GetDispatchQueue() override { return mDispatchQueue; };
    void HandleTimerComplete(TimerList::Node * timer);

protected:
    static void MaybeClearDispatchSource(dispatch_source_t source);

    static constexpr int kSocketWatchMax = (INET_CONFIG_ENABLE_TCP_ENDPOINT ? INET_CONFIG_NUM_TCP_ENDPOINTS : 0) +
        (INET_CONFIG_ENABLE_UDP_ENDPOINT ? INET_CONFIG_NUM_UDP_ENDPOINTS : 0);

    struct SocketWatch
    {
        void Clear();
        int mFD;
        SocketEvents mPendingIO;
        SocketWatchCallback mCallback;
        dispatch_source_t mRdSource;
        dispatch_source_t mWrSource;
        intptr_t mCallbackData;
    };
    SocketWatch mSocketWatchPool[kSocketWatchMax];

    TimerPool<TimerList::Node> mTimerPool;
    TimerList mTimerList;
    ObjectLifeCycle mLayerState;
    dispatch_queue_t mDispatchQueue = nullptr;
};

using LayerImpl = LayerImplDispatch;

} // namespace System
} // namespace chip
