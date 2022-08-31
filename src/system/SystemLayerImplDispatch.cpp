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
 *      This file implements Layer using libdispatch.
 */

#include <lib/support/CodeUtils.h>
#include <lib/support/TimeUtils.h>
#include <platform/LockTracker.h>
#include <system/SystemFaultInjection.h>
#include <system/SystemLayer.h>
#include <system/SystemLayerImplDispatch.h>

namespace chip {
namespace System {

CHIP_ERROR LayerImplDispatch::Init()
{
    VerifyOrReturnError(mLayerState.SetInitializing(), CHIP_ERROR_INCORRECT_STATE);

    for (auto & w : mSocketWatchPool)
    {
        w.Clear();
    }

    VerifyOrReturnError(mLayerState.SetInitialized(), CHIP_ERROR_INCORRECT_STATE);
    return CHIP_NO_ERROR;
}

void LayerImplDispatch::Shutdown()
{
    VerifyOrReturn(mLayerState.SetShuttingDown());

    TimerList::Node * timer;
    while ((timer = mTimerList.PopEarliest()) != nullptr)
    {
        MaybeClearDispatchSource(timer->mTimerSource);
        timer->mTimerSource = nullptr;
    }
    mTimerPool.ReleaseAll();

    for (auto & w : mSocketWatchPool)
    {
        w.Clear();
    }

    mLayerState.ResetFromShuttingDown(); // Return to uninitialized state to permit re-initialization.
}

CHIP_ERROR LayerImplDispatch::StartTimer(Clock::Timeout delay, TimerCompleteCallback onComplete, void * appState)
{
    VerifyOrReturnError(mLayerState.IsInitialized(), CHIP_ERROR_INCORRECT_STATE);

    CHIP_SYSTEM_FAULT_INJECT(FaultInjection::kFault_TimeoutImmediate, delay = System::Clock::kZero);

    CancelTimer(onComplete, appState);

    TimerList::Node * timer = mTimerPool.Create(*this, SystemClock().GetMonotonicTimestamp() + delay, onComplete, appState);
    VerifyOrReturnError(timer != nullptr, CHIP_ERROR_NO_MEMORY);

    dispatch_queue_t dispatchQueue = GetDispatchQueue();
    VerifyOrReturnError(dispatchQueue != nullptr, CHIP_ERROR_INCORRECT_STATE);

    (void) mTimerList.Add(timer);
    dispatch_source_t timerSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, DISPATCH_TIMER_STRICT, dispatchQueue);
    if (timerSource == nullptr)
    {
        chipDie();
    }

    timer->mTimerSource = timerSource;
    dispatch_source_set_timer(
        timerSource, dispatch_walltime(nullptr, static_cast<int64_t>(Clock::Milliseconds64(delay).count() * NSEC_PER_MSEC)),
        DISPATCH_TIME_FOREVER, 2 * NSEC_PER_MSEC);
    dispatch_source_set_event_handler(timerSource, ^{
        MaybeClearDispatchSource(timerSource);
        timer->mTimerSource = nullptr;

        this->HandleTimerComplete(timer);
    });
    dispatch_resume(timerSource);

    return CHIP_NO_ERROR;
}

void LayerImplDispatch::CancelTimer(TimerCompleteCallback onComplete, void * appState)
{
    VerifyOrReturn(mLayerState.IsInitialized());

    TimerList::Node * timer = mTimerList.Remove(onComplete, appState);
    VerifyOrReturn(timer != nullptr);

    MaybeClearDispatchSource(timer->mTimerSource);
    timer->mTimerSource = nullptr;

    mTimerPool.Release(timer);
}

CHIP_ERROR LayerImplDispatch::ScheduleWork(TimerCompleteCallback onComplete, void * appState)
{
    VerifyOrReturnError(mLayerState.IsInitialized(), CHIP_ERROR_INCORRECT_STATE);

    dispatch_queue_t dispatchQueue = GetDispatchQueue();
    VerifyOrReturnError(dispatchQueue != nullptr, CHIP_ERROR_INCORRECT_STATE);

    dispatch_async(dispatchQueue, ^{
        onComplete(this, appState);
    });

    return CHIP_NO_ERROR;
}

void LayerImplDispatch::HandleTimerComplete(TimerList::Node * timer)
{
    mTimerList.Remove(timer);
    mTimerPool.Invoke(timer);
}

CHIP_ERROR LayerImplDispatch::StartWatchingSocket(int fd, SocketWatchToken * tokenOut)
{
    // Find a free slot.
    SocketWatch * watch = nullptr;
    for (auto & w : mSocketWatchPool)
    {
        if (w.mFD == fd)
        {
            // Duplicate registration is an error.
            return CHIP_ERROR_INVALID_ARGUMENT;
        }
        if ((w.mFD == kInvalidFd) && (watch == nullptr))
        {
            watch = &w;
        }
    }
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_ENDPOINT_POOL_FULL);

    watch->mFD = fd;

    *tokenOut = reinterpret_cast<SocketWatchToken>(watch);
    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::SetCallback(SocketWatchToken token, SocketWatchCallback callback, intptr_t data)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(token);
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    watch->mCallback     = callback;
    watch->mCallbackData = data;
    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::RequestCallbackOnPendingRead(SocketWatchToken token)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(token);
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    watch->mPendingIO.Set(SocketEventFlags::kRead);

    if (watch->mRdSource == nullptr)
    {
        // First time requesting callback for read events: install a dispatch source
        dispatch_queue_t dispatchQueue = GetDispatchQueue();
        VerifyOrReturnError(dispatchQueue != nullptr, CHIP_ERROR_INCORRECT_STATE);

        watch->mRdSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_READ, static_cast<uintptr_t>(watch->mFD), 0, dispatchQueue);
        ReturnErrorCodeIf(watch->mRdSource == nullptr, CHIP_ERROR_NO_MEMORY);
        dispatch_source_set_event_handler(watch->mRdSource, ^{
            if (watch->mPendingIO.Has(SocketEventFlags::kRead) && watch->mCallback != nullptr)
            {
                SocketEvents events;
                events.Set(SocketEventFlags::kRead);
                watch->mCallback(events, watch->mCallbackData);
            }
        });
        // only now we are sure the source exists and can become active
        dispatch_activate(watch->mRdSource);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::RequestCallbackOnPendingWrite(SocketWatchToken token)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(token);
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    watch->mPendingIO.Set(SocketEventFlags::kWrite);

    if (watch->mWrSource == nullptr)
    {
        // First time requesting callback for read events: install a dispatch source
        dispatch_queue_t dispatchQueue = GetDispatchQueue();
        VerifyOrReturnError(dispatchQueue != nullptr, CHIP_ERROR_INCORRECT_STATE);

        watch->mWrSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_WRITE, static_cast<uintptr_t>(watch->mFD), 0, dispatchQueue);
        ReturnErrorCodeIf(watch->mWrSource == nullptr, CHIP_ERROR_NO_MEMORY);
        dispatch_source_set_event_handler(watch->mWrSource, ^{
            if (watch->mPendingIO.Has(SocketEventFlags::kWrite) && watch->mCallback != nullptr)
            {
                SocketEvents events;
                events.Set(SocketEventFlags::kWrite);
                watch->mCallback(events, watch->mCallbackData);
            }
        });
        // only now we are sure the source exists and can become active
        watch->mPendingIO.Set(SocketEventFlags::kWrite);
        dispatch_activate(watch->mWrSource);
    }

    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::ClearCallbackOnPendingRead(SocketWatchToken token)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(token);
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    watch->mPendingIO.Clear(SocketEventFlags::kRead);

    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::ClearCallbackOnPendingWrite(SocketWatchToken token)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(token);
    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);

    watch->mPendingIO.Clear(SocketEventFlags::kWrite);

    return CHIP_NO_ERROR;
}

CHIP_ERROR LayerImplDispatch::StopWatchingSocket(SocketWatchToken * tokenInOut)
{
    SocketWatch * watch = reinterpret_cast<SocketWatch *>(*tokenInOut);
    *tokenInOut         = InvalidSocketWatchToken();

    VerifyOrReturnError(watch != nullptr, CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(watch->mFD >= 0, CHIP_ERROR_INCORRECT_STATE);

    watch->Clear();

    return CHIP_NO_ERROR;
}

void LayerImplDispatch::SocketWatch::Clear()
{
    mFD = kInvalidFd;
    mPendingIO.ClearAll();
    mCallback     = nullptr;
    mCallbackData = 0;

    MaybeClearDispatchSource(mRdSource);
    MaybeClearDispatchSource(mWrSource);

    mRdSource = nullptr;
    mWrSource = nullptr;
}

void LayerImplDispatch::MaybeClearDispatchSource(dispatch_source_t source)
{
    if (source)
    {
        dispatch_source_cancel(source);
        dispatch_release(source);
    }
}

} // namespace System
} // namespace chip
