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
