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

@interface CHIPBarrierControl ()

@property (readonly) Controller::BarrierControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBarrierControl

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

- (BOOL)barrierControlGoToPercent:(DefaultSuccessHandler)onSuccessCallback
                onFailureCallback:(DefaultFailureHandler)onFailureCallback
                      percentOpen:(uint8_t)percentOpen
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

    CHIP_ERROR err = self.cppCluster.BarrierControlGoToPercent(onSuccess->Cancel(), onFailure->Cancel(), percentOpen);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)barrierControlStop:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.BarrierControlStop(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierMovingState:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierMovingState(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierSafetyStatus:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierSafetyStatus(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierCapabilities:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierCapabilities(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierPosition:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierPosition(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPBasic ()

@property (readonly) Controller::BasicCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBasic

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

- (BOOL)mfgSpecificPing:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.MfgSpecificPing(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)resetToFactoryDefaults:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ResetToFactoryDefaults(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZclVersion:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeZclVersion(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePowerSource:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePowerSource(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPBinding ()

@property (readonly) Controller::BindingCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBinding

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

- (BOOL)bind:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               nodeId:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId
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

    CHIP_ERROR err = self.cppCluster.Bind(onSuccess->Cancel(), onFailure->Cancel(), nodeId, groupId, endpointId, clusterId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)unbind:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               nodeId:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId
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

    CHIP_ERROR err = self.cppCluster.Unbind(onSuccess->Cancel(), onFailure->Cancel(), nodeId, groupId, endpointId, clusterId);
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

@interface CHIPColorControl ()

@property (readonly) Controller::ColorControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPColorControl

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

- (BOOL)moveColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                rateX:(int16_t)rateX
                rateY:(int16_t)rateY
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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
        = self.cppCluster.MoveColor(onSuccess->Cancel(), onFailure->Cancel(), rateX, rateY, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveColorTemperature:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    moveMode:(uint8_t)moveMode
                        rate:(uint16_t)rate
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveColorTemperature(onSuccess->Cancel(), onFailure->Cancel(), moveMode, rate,
        colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             moveMode:(uint8_t)moveMode
                 rate:(uint8_t)rate
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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
        = self.cppCluster.MoveHue(onSuccess->Cancel(), onFailure->Cancel(), moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveSaturation:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
              moveMode:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
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
        = self.cppCluster.MoveSaturation(onSuccess->Cancel(), onFailure->Cancel(), moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               colorX:(uint16_t)colorX
               colorY:(uint16_t)colorY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveToColor(
        onSuccess->Cancel(), onFailure->Cancel(), colorX, colorY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToColorTemperature:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
              colorTemperature:(uint16_t)colorTemperature
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveToColorTemperature(
        onSuccess->Cancel(), onFailure->Cancel(), colorTemperature, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  hue:(uint8_t)hue
            direction:(uint8_t)direction
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveToHue(
        onSuccess->Cancel(), onFailure->Cancel(), hue, direction, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToHueAndSaturation:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
                           hue:(uint8_t)hue
                    saturation:(uint8_t)saturation
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveToHueAndSaturation(
        onSuccess->Cancel(), onFailure->Cancel(), hue, saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)moveToSaturation:(DefaultSuccessHandler)onSuccessCallback
       onFailureCallback:(DefaultFailureHandler)onFailureCallback
              saturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.MoveToSaturation(
        onSuccess->Cancel(), onFailure->Cancel(), saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stepColor:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                stepX:(int16_t)stepX
                stepY:(int16_t)stepY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.StepColor(
        onSuccess->Cancel(), onFailure->Cancel(), stepX, stepY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stepColorTemperature:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    stepMode:(uint8_t)stepMode
                    stepSize:(uint16_t)stepSize
              transitionTime:(uint16_t)transitionTime
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.StepColorTemperature(onSuccess->Cancel(), onFailure->Cancel(), stepMode, stepSize,
        transitionTime, colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stepHue:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint8_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.StepHue(
        onSuccess->Cancel(), onFailure->Cancel(), stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stepSaturation:(DefaultSuccessHandler)onSuccessCallback
     onFailureCallback:(DefaultFailureHandler)onFailureCallback
              stepMode:(uint8_t)stepMode
              stepSize:(uint8_t)stepSize
        transitionTime:(uint8_t)transitionTime
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.StepSaturation(
        onSuccess->Cancel(), onFailure->Cancel(), stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)stopMoveStep:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
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

    CHIP_ERROR err = self.cppCluster.StopMoveStep(onSuccess->Cancel(), onFailure->Cancel(), optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentHue:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentHue(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentHue:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentHue(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentSaturation:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentSaturation(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentSaturation:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentSaturation(
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

- (BOOL)readAttributeCurrentX:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentX(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentX:(DefaultSuccessHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback
               onReportCallback:(Int16uAttributeHandler)onReportCallback
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change
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

    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentX(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentY:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentY(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentY:(DefaultSuccessHandler)onSuccessCallback
              onFailureCallback:(DefaultFailureHandler)onFailureCallback
               onReportCallback:(Int16uAttributeHandler)onReportCallback
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change
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

    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentY(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeDriftCompensation:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeDriftCompensation(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCompensationText:(UnsupportedAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPUnsupportedAttributeCallbackBridge * onSuccess
        = new CHIPUnsupportedAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCompensationText(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTemperature:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTemperature(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeColorTemperature:(DefaultSuccessHandler)onSuccessCallback
                      onFailureCallback:(DefaultFailureHandler)onFailureCallback
                       onReportCallback:(Int16uAttributeHandler)onReportCallback
                            minInterval:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                                 change:(uint16_t)change
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

    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeColorTemperature(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorMode:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorMode(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorControlOptions:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorControlOptions(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorControlOptions:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorControlOptions(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNumberOfPrimaries:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeNumberOfPrimaries(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6X:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6X(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6Y:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Y(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6Intensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Intensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeWhitePointX:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointX(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeWhitePointX:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointX(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeWhitePointY:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointY(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeWhitePointY:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointY(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRX:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRX(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRX:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRX(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRY:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRY(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRY:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRY(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRIntensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRIntensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRIntensity:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRIntensity(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGX:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGX(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGX:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGX(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGY:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGY(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGY:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGY(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGIntensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGIntensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGIntensity:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGIntensity(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBX:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBX(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBX:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBX(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBY:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBY(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBY:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBY(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBIntensity:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBIntensity(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBIntensity:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBIntensity(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeEnhancedCurrentHue:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedCurrentHue(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeEnhancedColorMode:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedColorMode(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopActive:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopActive(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopDirection:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopDirection(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopTime:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopTime(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorCapabilities:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorCapabilities(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTempPhysicalMin:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMin(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTempPhysicalMax:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMax(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCoupleColorTempToLevelMinMireds:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCoupleColorTempToLevelMinMireds(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeStartUpColorTemperatureMireds:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeStartUpColorTemperatureMireds(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeStartUpColorTemperatureMireds:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeStartUpColorTemperatureMireds(onSuccess->Cancel(), onFailure->Cancel(), value);
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

@interface CHIPDoorLock ()

@property (readonly) Controller::DoorLockCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPDoorLock

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

- (BOOL)clearAllPins:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ClearAllPins(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearAllRfids:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ClearAllRfids(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId
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

    CHIP_ERROR err = self.cppCluster.ClearHolidaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.ClearPin(onSuccess->Cancel(), onFailure->Cancel(), userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.ClearRfid(onSuccess->Cancel(), onFailure->Cancel(), userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId
                      userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.ClearWeekdaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)clearYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
           onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  scheduleId:(uint8_t)scheduleId
                      userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.ClearYeardaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
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

    CHIP_ERROR err = self.cppCluster.GetHolidaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getLogRecord:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
             logIndex:(uint16_t)logIndex
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

    CHIP_ERROR err = self.cppCluster.GetLogRecord(onSuccess->Cancel(), onFailure->Cancel(), logIndex);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.GetPin(onSuccess->Cancel(), onFailure->Cancel(), userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.GetRfid(onSuccess->Cancel(), onFailure->Cancel(), userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getUserType:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.GetUserType(onSuccess->Cancel(), onFailure->Cancel(), userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.GetWeekdaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
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

    CHIP_ERROR err = self.cppCluster.GetYeardaySchedule(onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)lockDoor:(DoorLockClusterLockDoorResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  pin:(char *)pin
{
    CHIPDoorLockClusterLockDoorResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterLockDoorResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.LockDoor(onSuccess->Cancel(), onFailure->Cancel(), pin);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setHolidaySchedule:(DefaultSuccessHandler)onSuccessCallback
             onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    scheduleId:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday
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

    CHIP_ERROR err = self.cppCluster.SetHolidaySchedule(
        onSuccess->Cancel(), onFailure->Cancel(), scheduleId, localStartTime, localEndTime, operatingModeDuringHoliday);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setPin:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                  pin:(char *)pin
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

    CHIP_ERROR err = self.cppCluster.SetPin(onSuccess->Cancel(), onFailure->Cancel(), userId, userStatus, userType, pin);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setRfid:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                   id:(char *)id
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

    CHIP_ERROR err = self.cppCluster.SetRfid(onSuccess->Cancel(), onFailure->Cancel(), userId, userStatus, userType, id);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setUserType:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
               userId:(uint16_t)userId
             userType:(uint8_t)userType
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

    CHIP_ERROR err = self.cppCluster.SetUserType(onSuccess->Cancel(), onFailure->Cancel(), userId, userType);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setWeekdaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
                  daysMask:(uint8_t)daysMask
                 startHour:(uint8_t)startHour
               startMinute:(uint8_t)startMinute
                   endHour:(uint8_t)endHour
                 endMinute:(uint8_t)endMinute
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

    CHIP_ERROR err = self.cppCluster.SetWeekdaySchedule(
        onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId, daysMask, startHour, startMinute, endHour, endMinute);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)setYeardaySchedule:(DefaultSuccessHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime
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

    CHIP_ERROR err = self.cppCluster.SetYeardaySchedule(
        onSuccess->Cancel(), onFailure->Cancel(), scheduleId, userId, localStartTime, localEndTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)unlockDoor:(DoorLockClusterUnlockDoorResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
                  pin:(char *)pin
{
    CHIPDoorLockClusterUnlockDoorResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterUnlockDoorResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.UnlockDoor(onSuccess->Cancel(), onFailure->Cancel(), pin);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)unlockWithTimeout:(DefaultSuccessHandler)onSuccessCallback
        onFailureCallback:(DefaultFailureHandler)onFailureCallback
         timeoutInSeconds:(uint16_t)timeoutInSeconds
                      pin:(char *)pin
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

    CHIP_ERROR err = self.cppCluster.UnlockWithTimeout(onSuccess->Cancel(), onFailure->Cancel(), timeoutInSeconds, pin);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeLockState:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockState(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeLockState:(DefaultSuccessHandler)onSuccessCallback
               onFailureCallback:(DefaultFailureHandler)onFailureCallback
                onReportCallback:(Int8uAttributeHandler)onReportCallback
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

    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeLockState(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeLockType:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockType(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeActuatorEnabled:(BooleanAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeActuatorEnabled(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPGroups ()

@property (readonly) Controller::GroupsCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPGroups

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

- (BOOL)addGroup:(GroupsClusterAddGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
            groupName:(char *)groupName
{
    CHIPGroupsClusterAddGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterAddGroupResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddGroup(onSuccess->Cancel(), onFailure->Cancel(), groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)addGroupIfIdentifying:(DefaultSuccessHandler)onSuccessCallback
            onFailureCallback:(DefaultFailureHandler)onFailureCallback
                      groupId:(uint16_t)groupId
                    groupName:(char *)groupName
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

    CHIP_ERROR err = self.cppCluster.AddGroupIfIdentifying(onSuccess->Cancel(), onFailure->Cancel(), groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getGroupMembership:(GroupsClusterGetGroupMembershipResponseHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                groupCount:(uint8_t)groupCount
                 groupList:(uint16_t)groupList
{
    CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetGroupMembership(onSuccess->Cancel(), onFailure->Cancel(), groupCount, groupList);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)removeAllGroups:(DefaultSuccessHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.RemoveAllGroups(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)removeGroup:(GroupsClusterRemoveGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
{
    CHIPGroupsClusterRemoveGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterRemoveGroupResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveGroup(onSuccess->Cancel(), onFailure->Cancel(), groupId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)viewGroup:(GroupsClusterViewGroupResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
{
    CHIPGroupsClusterViewGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterViewGroupResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewGroup(onSuccess->Cancel(), onFailure->Cancel(), groupId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNameSupport:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPIasZone ()

@property (readonly) Controller::IasZoneCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPIasZone

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

- (BOOL)readAttributeZoneState:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneState(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneType:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneType(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneStatus:(Int16uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneStatus(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeIasCieAddress:(Int64uAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt64uAttributeCallbackBridge * onSuccess = new CHIPInt64uAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeIasCieAddress(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeIasCieAddress:(DefaultSuccessHandler)onSuccessCallback
                  onFailureCallback:(DefaultFailureHandler)onFailureCallback
                              value:(uint64_t)value
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeIasCieAddress(onSuccess->Cancel(), onFailure->Cancel(), value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneId:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneId(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPIdentify ()

@property (readonly) Controller::IdentifyCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPIdentify

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

- (BOOL)identify:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
         identifyTime:(uint16_t)identifyTime
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

    CHIP_ERROR err = self.cppCluster.Identify(onSuccess->Cancel(), onFailure->Cancel(), identifyTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)identifyQuery:(IdentifyClusterIdentifyQueryResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge * onSuccess
        = new CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.IdentifyQuery(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeIdentifyTime:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeIdentifyTime(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeIdentifyTime:(DefaultSuccessHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.WriteAttributeIdentifyTime(onSuccess->Cancel(), onFailure->Cancel(), value);
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

@interface CHIPScenes ()

@property (readonly) Controller::ScenesCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPScenes

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

- (BOOL)addScene:(ScenesClusterAddSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
       transitionTime:(uint16_t)transitionTime
            sceneName:(char *)sceneName
            clusterId:(uint16_t)clusterId
               length:(uint8_t)length
                value:(uint8_t)value
{
    CHIPScenesClusterAddSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterAddSceneResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddScene(
        onSuccess->Cancel(), onFailure->Cancel(), groupId, sceneId, transitionTime, sceneName, clusterId, length, value);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)getSceneMembership:(ScenesClusterGetSceneMembershipResponseHandler)onSuccessCallback
         onFailureCallback:(DefaultFailureHandler)onFailureCallback
                   groupId:(uint16_t)groupId
{
    CHIPScenesClusterGetSceneMembershipResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterGetSceneMembershipResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetSceneMembership(onSuccess->Cancel(), onFailure->Cancel(), groupId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)recallScene:(DefaultSuccessHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
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

    CHIP_ERROR err = self.cppCluster.RecallScene(onSuccess->Cancel(), onFailure->Cancel(), groupId, sceneId, transitionTime);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)removeAllScenes:(ScenesClusterRemoveAllScenesResponseHandler)onSuccessCallback
      onFailureCallback:(DefaultFailureHandler)onFailureCallback
                groupId:(uint16_t)groupId
{
    CHIPScenesClusterRemoveAllScenesResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterRemoveAllScenesResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveAllScenes(onSuccess->Cancel(), onFailure->Cancel(), groupId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)removeScene:(ScenesClusterRemoveSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
{
    CHIPScenesClusterRemoveSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterRemoveSceneResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveScene(onSuccess->Cancel(), onFailure->Cancel(), groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)storeScene:(ScenesClusterStoreSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
{
    CHIPScenesClusterStoreSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterStoreSceneResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StoreScene(onSuccess->Cancel(), onFailure->Cancel(), groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}
- (BOOL)viewScene:(ScenesClusterViewSceneResponseHandler)onSuccessCallback
    onFailureCallback:(DefaultFailureHandler)onFailureCallback
              groupId:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
{
    CHIPScenesClusterViewSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterViewSceneResponseCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewScene(onSuccess->Cancel(), onFailure->Cancel(), groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeSceneCount:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneCount(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentScene:(Int8uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentScene(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentGroup:(Int16uAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentGroup(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeSceneValid:(BooleanAttributeHandler)onSuccessCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneValid(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNameSupport:(Int8uAttributeHandler)onSuccessCallback onFailureCallback:(DefaultFailureHandler)onFailureCallback
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

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(onSuccess->Cancel(), onFailure->Cancel());
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

@interface CHIPTemperatureMeasurement ()

@property (readonly) Controller::TemperatureMeasurementCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPTemperatureMeasurement

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

- (BOOL)readAttributeMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                 onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMeasuredValue(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeMeasuredValue:(DefaultSuccessHandler)onSuccessCallback
                   onFailureCallback:(DefaultFailureHandler)onFailureCallback
                    onReportCallback:(Int16sAttributeHandler)onReportCallback
                         minInterval:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                              change:(int16_t)change
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

    CHIPInt16sAttributeCallbackBridge * onReport = new CHIPInt16sAttributeCallbackBridge(onReportCallback, _callbackQueue, true);
    if (!onReport) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeMeasuredValue(
        onSuccess->Cancel(), onFailure->Cancel(), onReport->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        delete onReport;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeMinMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMinMeasuredValue(onSuccess->Cancel(), onFailure->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeMaxMeasuredValue:(Int16sAttributeHandler)onSuccessCallback
                    onFailureCallback:(DefaultFailureHandler)onFailureCallback
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(onSuccessCallback, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(onFailureCallback, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMaxMeasuredValue(onSuccess->Cancel(), onFailure->Cancel());
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
