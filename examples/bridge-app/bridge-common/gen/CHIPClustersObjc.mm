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

#import <Foundation/Foundation.h>

#import "CHIPDevice.h"
#import "CHIPDevice_Internal.h"
#import "gen/CHIPClustersObjc.h"
#import "gen/ResponseCallbacks.h"

#include <controller/CHIPClusters.h>

using namespace ::chip;

class CHIPDefaultSuccessCallbackBridge : public Callback::Callback<DefaultSuccessCallback> {
public:
    CHIPDefaultSuccessCallbackBridge(DefaultSuccessHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DefaultSuccessCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDefaultSuccessCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDefaultSuccessCallbackBridge * callback = reinterpret_cast<CHIPDefaultSuccessCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler();
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    DefaultSuccessHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDefaultFailureCallbackBridge : public Callback::Callback<DefaultFailureCallback> {
public:
    CHIPDefaultFailureCallbackBridge(DefaultFailureHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DefaultFailureCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDefaultFailureCallbackBridge() {};

    static void CallbackFn(void * context, uint8_t status)
    {
        CHIPDefaultFailureCallbackBridge * callback = reinterpret_cast<CHIPDefaultFailureCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(status);
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    DefaultFailureHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPUnsupportedAttributeCallbackBridge : public Callback::Callback<DefaultSuccessCallback> {
public:
    CHIPUnsupportedAttributeCallbackBridge(DefaultSuccessHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DefaultSuccessCallback>(CallbackFn, this)
    {
    }

    ~CHIPUnsupportedAttributeCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPUnsupportedAttributeCallbackBridge * callback = reinterpret_cast<CHIPUnsupportedAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler();
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    DefaultSuccessHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPBooleanAttributeCallbackBridge : public Callback::Callback<BooleanAttributeCallback> {
public:
    CHIPBooleanAttributeCallbackBridge(BooleanAttributeHandler handler, dispatch_queue_t queue, bool keepAlive = false)
        : Callback::Callback<BooleanAttributeCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
        , mKeepAlive(keepAlive)
    {
    }

    ~CHIPBooleanAttributeCallbackBridge() {};

    static void CallbackFn(void * context, bool value)
    {
        CHIPBooleanAttributeCallbackBridge * callback = reinterpret_cast<CHIPBooleanAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(value);
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    BooleanAttributeHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt8uAttributeCallbackBridge : public Callback::Callback<Int8uAttributeCallback> {
public:
    CHIPInt8uAttributeCallbackBridge(Int8uAttributeHandler handler, dispatch_queue_t queue, bool keepAlive = false)
        : Callback::Callback<Int8uAttributeCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
        , mKeepAlive(keepAlive)
    {
    }

    ~CHIPInt8uAttributeCallbackBridge() {};

    static void CallbackFn(void * context, uint8_t value)
    {
        CHIPInt8uAttributeCallbackBridge * callback = reinterpret_cast<CHIPInt8uAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(value);
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    Int8uAttributeHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt8sAttributeCallbackBridge : public Callback::Callback<Int8sAttributeCallback> {
public:
    CHIPInt8sAttributeCallbackBridge(Int8sAttributeHandler handler, dispatch_queue_t queue, bool keepAlive = false)
        : Callback::Callback<Int8sAttributeCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
        , mKeepAlive(keepAlive)
    {
    }

    ~CHIPInt8sAttributeCallbackBridge() {};

    static void CallbackFn(void * context, int8_t value)
    {
        CHIPInt8sAttributeCallbackBridge * callback = reinterpret_cast<CHIPInt8sAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(value);
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    Int8sAttributeHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt16uAttributeCallbackBridge : public Callback::Callback<Int16uAttributeCallback> {
public:
    CHIPInt16uAttributeCallbackBridge(Int16uAttributeHandler handler, dispatch_queue_t queue, bool keepAlive = false)
        : Callback::Callback<Int16uAttributeCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
        , mKeepAlive(keepAlive)
    {
    }

    ~CHIPInt16uAttributeCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t value)
    {
        CHIPInt16uAttributeCallbackBridge * callback = reinterpret_cast<CHIPInt16uAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(value);
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    Int16uAttributeHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt16sAttributeCallbackBridge : public Callback::Callback<Int16sAttributeCallback> {
public:
    CHIPInt16sAttributeCallbackBridge(Int16sAttributeHandler handler, dispatch_queue_t queue, bool keepAlive = false)
        : Callback::Callback<Int16sAttributeCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
        , mKeepAlive(keepAlive)
    {
    }

    ~CHIPInt16sAttributeCallbackBridge() {};

    static void CallbackFn(void * context, int16_t value)
    {
        CHIPInt16sAttributeCallbackBridge * callback = reinterpret_cast<CHIPInt16sAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(value);
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    Int16sAttributeHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

@interface CHIPLevelControl ()

@property (readonly) Controller::LevelControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPLevelControl

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(EndpointId)endpoint queue:(dispatch_queue_t)queue
{
    CHIP_ERROR err = _cppCluster.Associate([device internalDevice], endpoint);

    if (err != CHIP_NO_ERROR) {
        return nil;
    }

    if (self = [super init]) {
        _callbackQueue = queue;
    }

    return self;
}

- (BOOL)move:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Move(onSuccess->Cancel(), onFailure->Cancel(), moveMode, rate, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToLevel:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                level:(uint8_t)level
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.MoveToLevel(onSuccess->Cancel(), onFailure->Cancel(), level, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToLevelWithOnOff:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       level:(uint8_t)level
              transitionTime:(uint16_t)transitionTime
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToLevelWithOnOff(onSuccess->Cancel(), onFailure->Cancel(), level, transitionTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveWithOnOff:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveWithOnOff(onSuccess->Cancel(), onFailure->Cancel(), moveMode, rate);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)step:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Step(
        onSuccess->Cancel(), onFailure->Cancel(), stepMode, stepSize, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stepWithOnOff:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepWithOnOff(onSuccess->Cancel(), onFailure->Cancel(), stepMode, stepSize, transitionTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stop:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Stop(onSuccess->Cancel(), onFailure->Cancel(), optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stopWithOnOff:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StopWithOnOff(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentLevel:(Int8uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentLevel(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentLevel:(DefaultSuccessHandler)onSuccessCallback
                  onFailureCallback:(DefaultFailureHandler)onFailureCallback
                   onReportCallback:(Int8uAttributeHandler)onReportCallback
                        minInterval:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                             change:(uint8_t)change
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentLevel(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeRemainingTime:(Int16uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeRemainingTime(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeOptions:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOptions(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeOptions:(DefaultSuccessHandler)onSuccessCallback
            onFailureCallback:(DefaultFailureHandler)onFailureCallback
                        value:(uint8_t)value
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeOptions(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeStartUpCurrentLevel:(Int8uAttributeHandler)onSuccessCallback
                       onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeStartUpCurrentLevel(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeStartUpCurrentLevel:(DefaultSuccessHandler)onSuccessCallback
                        onFailureCallback:(DefaultFailureHandler)onFailureCallback
                                    value:(uint8_t)value
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeStartUpCurrentLevel(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

@end

@interface CHIPOnOff ()

@property (readonly) Controller::OnOffCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPOnOff

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(EndpointId)endpoint queue:(dispatch_queue_t)queue
{
    CHIP_ERROR err = _cppCluster.Associate([device internalDevice], endpoint);

    if (err != CHIP_NO_ERROR) {
        return nil;
    }

    if (self = [super init]) {
        _callbackQueue = queue;
    }

    return self;
}

- (BOOL)off:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Off(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)offWithEffect:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             effectId:(uint8_t)effectId
        effectVariant:(uint8_t)effectVariant
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.OffWithEffect(onSuccess->Cancel(), onFailure->Cancel(), effectId, effectVariant);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)on:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.On(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)onWithRecallGlobalScene:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.OnWithRecallGlobalScene(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)onWithTimedOff:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
          onOffControl:(uint8_t)onOffControl
                onTime:(uint16_t)onTime
           offWaitTime:(uint16_t)offWaitTime
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.OnWithTimedOff(onSuccess->Cancel(), onFailure->Cancel(), onOffControl, onTime, offWaitTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)toggle:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Toggle(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeOnOff:(BooleanAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPBooleanAttributeCallbackBridge * onSuccess = new CHIPBooleanAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOnOff(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeOnOff:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
            onReportCallback:(BooleanAttributeHandler)onReportCallback
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIPBooleanAttributeCallbackBridge * onReport = new CHIPBooleanAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeOnOff(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeGlobalSceneControl:(BooleanAttributeHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPBooleanAttributeCallbackBridge * onSuccess = new CHIPBooleanAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeGlobalSceneControl(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeOnTime:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOnTime(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeOnTime:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       value:(uint16_t)value
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeOnTime(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeOffWaitTime:(Int16uAttributeHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOffWaitTime(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeOffWaitTime:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                            value:(uint16_t)value
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeOffWaitTime(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeStartUpOnOff:(Int8uAttributeHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeStartUpOnOff(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeStartUpOnOff:(DefaultSuccessHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
                             value:(uint8_t)value
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeStartUpOnOff(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(Int16uAttributeHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

@end
