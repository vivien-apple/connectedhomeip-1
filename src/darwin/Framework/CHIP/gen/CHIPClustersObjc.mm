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
    CHIPDefaultSuccessCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
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
                callback->mHandler(nil, nil);
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDefaultFailureCallbackBridge : public Callback::Callback<DefaultFailureCallback> {
public:
    CHIPDefaultFailureCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
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
                NSError * error = [NSError errorWithDomain:@"ZCL" code:status userInfo:@ { NSLocalizedDescriptionKey : @"" }];
                callback->mHandler(error, nil);
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPUnsupportedAttributeCallbackBridge : public Callback::Callback<DefaultSuccessCallback> {
public:
    CHIPUnsupportedAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DefaultSuccessCallback>(CallbackFn, this)
    {
    }

    ~CHIPUnsupportedAttributeCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPUnsupportedAttributeCallbackBridge * callback = reinterpret_cast<CHIPUnsupportedAttributeCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                NSError * error = [NSError errorWithDomain:@"ZCL"
                                                      code:0
                                                  userInfo:@ { NSLocalizedDescriptionKey : @"Unsuported attribute type" }];
                callback->mHandler(error, nil);
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPBooleanAttributeCallbackBridge : public Callback::Callback<BooleanAttributeCallback> {
public:
    CHIPBooleanAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue, bool keepAlive = false)
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
                callback->mHandler(nil, @ { @"value" : [NSNumber numberWithBool:value] });
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt8uAttributeCallbackBridge : public Callback::Callback<Int8uAttributeCallback> {
public:
    CHIPInt8uAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue, bool keepAlive = false)
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
                callback->mHandler(nil, @ { @"value" : [NSNumber numberWithUnsignedChar:value] });
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt8sAttributeCallbackBridge : public Callback::Callback<Int8sAttributeCallback> {
public:
    CHIPInt8sAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue, bool keepAlive = false)
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
                callback->mHandler(nil, @ { @"value" : [NSNumber numberWithChar:value] });
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt16uAttributeCallbackBridge : public Callback::Callback<Int16uAttributeCallback> {
public:
    CHIPInt16uAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue, bool keepAlive = false)
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
                callback->mHandler(nil, @ { @"value" : [NSNumber numberWithUnsignedShort:value] });
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPInt16sAttributeCallbackBridge : public Callback::Callback<Int16sAttributeCallback> {
public:
    CHIPInt16sAttributeCallbackBridge(ResponseHandler handler, dispatch_queue_t queue, bool keepAlive = false)
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
                callback->mHandler(nil, @ { @"value" : [NSNumber numberWithShort:value] });
                if (!callback->mKeepAlive) {
                    callback->Cancel();
                    delete callback;
                }
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
    bool mKeepAlive;
};

class CHIPDoorLockClusterClearAllPinsResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterClearAllPinsResponseCallback> {
public:
    CHIPDoorLockClusterClearAllPinsResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearAllPinsResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearAllPinsResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearAllPinsResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearAllPinsResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback> {
public:
    CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearAllRfidsResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearHolidayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearPinResponseCallbackBridge : public Callback::Callback<DoorLockClusterClearPinResponseCallback> {
public:
    CHIPDoorLockClusterClearPinResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearPinResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearPinResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearPinResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearPinResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearRfidResponseCallbackBridge : public Callback::Callback<DoorLockClusterClearRfidResponseCallback> {
public:
    CHIPDoorLockClusterClearRfidResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearRfidResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearRfidResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearRfidResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearRfidResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearWeekdayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterClearYeardayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetHolidayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge() {};

    static void CallbackFn(
        void * context, uint8_t scheduleId, uint32_t localStartTime, uint32_t localEndTime, uint8_t operatingModeDuringHoliday)
    {
        CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"scheduleId" : [NSNumber numberWithUnsignedChar:scheduleId],
                    @"localStartTime" : [NSNumber numberWithUnsignedLong:localStartTime],
                    @"localEndTime" : [NSNumber numberWithUnsignedLong:localEndTime],
                    @"operatingModeDuringHoliday" : [NSNumber numberWithUnsignedChar:operatingModeDuringHoliday],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetLogRecordResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterGetLogRecordResponseCallback> {
public:
    CHIPDoorLockClusterGetLogRecordResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetLogRecordResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetLogRecordResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t logEntryId, uint32_t timestamp, uint8_t eventType, uint8_t source,
        uint8_t eventIdOrAlarmCode, uint16_t userId, uint8_t * pin)
    {
        CHIPDoorLockClusterGetLogRecordResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetLogRecordResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"logEntryId" : [NSNumber numberWithUnsignedShort:logEntryId],
                    @"timestamp" : [NSNumber numberWithUnsignedLong:timestamp],
                    @"eventType" : [NSNumber numberWithUnsignedChar:eventType],
                    @"source" : [NSNumber numberWithUnsignedChar:source],
                    @"eventIdOrAlarmCode" : [NSNumber numberWithUnsignedChar:eventIdOrAlarmCode],
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"pin" : [NSString stringWithFormat:@"%s", pin],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetPinResponseCallbackBridge : public Callback::Callback<DoorLockClusterGetPinResponseCallback> {
public:
    CHIPDoorLockClusterGetPinResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetPinResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetPinResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * pin)
    {
        CHIPDoorLockClusterGetPinResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetPinResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"userStatus" : [NSNumber numberWithUnsignedChar:userStatus],
                    @"userType" : [NSNumber numberWithUnsignedChar:userType],
                    @"pin" : [NSString stringWithFormat:@"%s", pin],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetRfidResponseCallbackBridge : public Callback::Callback<DoorLockClusterGetRfidResponseCallback> {
public:
    CHIPDoorLockClusterGetRfidResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetRfidResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetRfidResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t userId, uint8_t userStatus, uint8_t userType, uint8_t * rfid)
    {
        CHIPDoorLockClusterGetRfidResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetRfidResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"userStatus" : [NSNumber numberWithUnsignedChar:userStatus],
                    @"userType" : [NSNumber numberWithUnsignedChar:userType],
                    @"rfid" : [NSString stringWithFormat:@"%s", rfid],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetUserTypeResponseCallbackBridge : public Callback::Callback<DoorLockClusterGetUserTypeResponseCallback> {
public:
    CHIPDoorLockClusterGetUserTypeResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetUserTypeResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetUserTypeResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t userId, uint8_t userType)
    {
        CHIPDoorLockClusterGetUserTypeResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetUserTypeResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"userType" : [NSNumber numberWithUnsignedChar:userType],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetWeekdayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint8_t scheduleId, uint16_t userId, uint8_t daysMask, uint8_t startHour,
        uint8_t startMinute, uint8_t endHour, uint8_t endMinute)
    {
        CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"scheduleId" : [NSNumber numberWithUnsignedChar:scheduleId],
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"daysMask" : [NSNumber numberWithUnsignedChar:daysMask],
                    @"startHour" : [NSNumber numberWithUnsignedChar:startHour],
                    @"startMinute" : [NSNumber numberWithUnsignedChar:startMinute],
                    @"endHour" : [NSNumber numberWithUnsignedChar:endHour],
                    @"endMinute" : [NSNumber numberWithUnsignedChar:endMinute],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterGetYeardayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint8_t scheduleId, uint16_t userId, uint32_t localStartTime, uint32_t localEndTime)
    {
        CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"scheduleId" : [NSNumber numberWithUnsignedChar:scheduleId],
                    @"userId" : [NSNumber numberWithUnsignedShort:userId],
                    @"localStartTime" : [NSNumber numberWithUnsignedLong:localStartTime],
                    @"localEndTime" : [NSNumber numberWithUnsignedLong:localEndTime],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterLockDoorResponseCallbackBridge : public Callback::Callback<DoorLockClusterLockDoorResponseCallback> {
public:
    CHIPDoorLockClusterLockDoorResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterLockDoorResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterLockDoorResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterLockDoorResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterLockDoorResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetHolidayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetPinResponseCallbackBridge : public Callback::Callback<DoorLockClusterSetPinResponseCallback> {
public:
    CHIPDoorLockClusterSetPinResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetPinResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetPinResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetPinResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetPinResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetRfidResponseCallbackBridge : public Callback::Callback<DoorLockClusterSetRfidResponseCallback> {
public:
    CHIPDoorLockClusterSetRfidResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetRfidResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetRfidResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetRfidResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetRfidResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetUserTypeResponseCallbackBridge : public Callback::Callback<DoorLockClusterSetUserTypeResponseCallback> {
public:
    CHIPDoorLockClusterSetUserTypeResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetUserTypeResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetUserTypeResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetUserTypeResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetUserTypeResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetWeekdayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback> {
public:
    CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterSetYeardayScheduleResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterUnlockDoorResponseCallbackBridge : public Callback::Callback<DoorLockClusterUnlockDoorResponseCallback> {
public:
    CHIPDoorLockClusterUnlockDoorResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterUnlockDoorResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterUnlockDoorResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterUnlockDoorResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterUnlockDoorResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge
    : public Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback> {
public:
    CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<DoorLockClusterUnlockWithTimeoutResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge() {};

    static void CallbackFn(void * context)
    {
        CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge * callback
            = reinterpret_cast<CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {});
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPGroupsClusterAddGroupResponseCallbackBridge : public Callback::Callback<GroupsClusterAddGroupResponseCallback> {
public:
    CHIPGroupsClusterAddGroupResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<GroupsClusterAddGroupResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPGroupsClusterAddGroupResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId)
    {
        CHIPGroupsClusterAddGroupResponseCallbackBridge * callback
            = reinterpret_cast<CHIPGroupsClusterAddGroupResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge
    : public Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback> {
public:
    CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<GroupsClusterGetGroupMembershipResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge() {};

    static void CallbackFn(
        void * context, uint8_t capacity, uint8_t groupCount, /* TYPE WARNING: array array defaults to */ uint8_t * groupList)
    {
        CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge * callback
            = reinterpret_cast<CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"capacity" : [NSNumber numberWithUnsignedChar:capacity],
                    @"groupCount" : [NSNumber numberWithUnsignedChar:groupCount],
                    // groupList: /* TYPE WARNING: array array defaults to */ uint8_t *
                    // Conversion from this type to Objc is not properly implemented yet
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPGroupsClusterRemoveGroupResponseCallbackBridge : public Callback::Callback<GroupsClusterRemoveGroupResponseCallback> {
public:
    CHIPGroupsClusterRemoveGroupResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<GroupsClusterRemoveGroupResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPGroupsClusterRemoveGroupResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId)
    {
        CHIPGroupsClusterRemoveGroupResponseCallbackBridge * callback
            = reinterpret_cast<CHIPGroupsClusterRemoveGroupResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPGroupsClusterViewGroupResponseCallbackBridge : public Callback::Callback<GroupsClusterViewGroupResponseCallback> {
public:
    CHIPGroupsClusterViewGroupResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<GroupsClusterViewGroupResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPGroupsClusterViewGroupResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId, uint8_t * groupName)
    {
        CHIPGroupsClusterViewGroupResponseCallbackBridge * callback
            = reinterpret_cast<CHIPGroupsClusterViewGroupResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"groupName" : [NSString stringWithFormat:@"%s", groupName],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge
    : public Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback> {
public:
    CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<IdentifyClusterIdentifyQueryResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t timeout)
    {
        CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge * callback
            = reinterpret_cast<CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"timeout" : [NSNumber numberWithUnsignedShort:timeout],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterAddSceneResponseCallbackBridge : public Callback::Callback<ScenesClusterAddSceneResponseCallback> {
public:
    CHIPScenesClusterAddSceneResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterAddSceneResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterAddSceneResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId, uint8_t sceneId)
    {
        CHIPScenesClusterAddSceneResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterAddSceneResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"sceneId" : [NSNumber numberWithUnsignedChar:sceneId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterGetSceneMembershipResponseCallbackBridge
    : public Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback> {
public:
    CHIPScenesClusterGetSceneMembershipResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterGetSceneMembershipResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterGetSceneMembershipResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint8_t capacity, uint16_t groupId, uint8_t sceneCount,
        /* TYPE WARNING: array array defaults to */ uint8_t * sceneList)
    {
        CHIPScenesClusterGetSceneMembershipResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterGetSceneMembershipResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"capacity" : [NSNumber numberWithUnsignedChar:capacity],
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"sceneCount" : [NSNumber numberWithUnsignedChar:sceneCount],
                    // sceneList: /* TYPE WARNING: array array defaults to */ uint8_t *
                    // Conversion from this type to Objc is not properly implemented yet
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterRemoveAllScenesResponseCallbackBridge
    : public Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback> {
public:
    CHIPScenesClusterRemoveAllScenesResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterRemoveAllScenesResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterRemoveAllScenesResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId)
    {
        CHIPScenesClusterRemoveAllScenesResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterRemoveAllScenesResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterRemoveSceneResponseCallbackBridge : public Callback::Callback<ScenesClusterRemoveSceneResponseCallback> {
public:
    CHIPScenesClusterRemoveSceneResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterRemoveSceneResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterRemoveSceneResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId, uint8_t sceneId)
    {
        CHIPScenesClusterRemoveSceneResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterRemoveSceneResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"sceneId" : [NSNumber numberWithUnsignedChar:sceneId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterStoreSceneResponseCallbackBridge : public Callback::Callback<ScenesClusterStoreSceneResponseCallback> {
public:
    CHIPScenesClusterStoreSceneResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterStoreSceneResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterStoreSceneResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId, uint8_t sceneId)
    {
        CHIPScenesClusterStoreSceneResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterStoreSceneResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"sceneId" : [NSNumber numberWithUnsignedChar:sceneId],
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
};

class CHIPScenesClusterViewSceneResponseCallbackBridge : public Callback::Callback<ScenesClusterViewSceneResponseCallback> {
public:
    CHIPScenesClusterViewSceneResponseCallbackBridge(ResponseHandler handler, dispatch_queue_t queue)
        : Callback::Callback<ScenesClusterViewSceneResponseCallback>(CallbackFn, this)
        , mHandler(handler)
        , mQueue(queue)
    {
    }

    ~CHIPScenesClusterViewSceneResponseCallbackBridge() {};

    static void CallbackFn(void * context, uint16_t groupId, uint8_t sceneId, uint16_t transitionTime, uint8_t * sceneName,
        /* TYPE WARNING: array array defaults to */ uint8_t * extensionFieldSets)
    {
        CHIPScenesClusterViewSceneResponseCallbackBridge * callback
            = reinterpret_cast<CHIPScenesClusterViewSceneResponseCallbackBridge *>(context);
        if (callback && callback->mQueue) {
            dispatch_async(callback->mQueue, ^{
                callback->mHandler(nil, @ {
                    @"groupId" : [NSNumber numberWithUnsignedShort:groupId],
                    @"sceneId" : [NSNumber numberWithUnsignedChar:sceneId],
                    @"transitionTime" : [NSNumber numberWithUnsignedShort:transitionTime],
                    @"sceneName" : [NSString stringWithFormat:@"%s", sceneName],
                    // extensionFieldSets: /* TYPE WARNING: array array defaults to */ uint8_t *
                    // Conversion from this type to Objc is not properly implemented yet
                });
                callback->Cancel();
                delete callback;
            });
        }
    };

private:
    ResponseHandler mHandler;
    dispatch_queue_t mQueue;
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

- (BOOL)barrierControlGoToPercent:(uint8_t)percentOpen completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)barrierControlStop:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeBarrierMovingState:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeBarrierSafetyStatus:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeBarrierCapabilities:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeBarrierPosition:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)mfgSpecificPing:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)resetToFactoryDefaults:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeZclVersion:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePowerSource:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)bind:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)unbind:(uint64_t)nodeId
              groupId:(uint16_t)groupId
           endpointId:(uint8_t)endpointId
            clusterId:(uint16_t)clusterId
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)moveColor:(int16_t)rateX
                rateY:(int16_t)rateY
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveColorTemperature:(uint8_t)moveMode
                        rate:(uint16_t)rate
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
           completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveHue:(uint8_t)moveMode
                 rate:(uint8_t)rate
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveSaturation:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
     completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToColor:(uint16_t)colorX
               colorY:(uint16_t)colorY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToColorTemperature:(uint16_t)colorTemperature
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
             completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToHue:(uint8_t)hue
            direction:(uint8_t)direction
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToHueAndSaturation:(uint8_t)hue
                    saturation:(uint8_t)saturation
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
             completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToSaturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride
       completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stepColor:(int16_t)stepX
                stepY:(int16_t)stepY
       transitionTime:(uint16_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stepColorTemperature:(uint8_t)stepMode
                    stepSize:(uint16_t)stepSize
              transitionTime:(uint16_t)transitionTime
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
           completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stepHue:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint8_t)transitionTime
          optionsMask:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stepSaturation:(uint8_t)stepMode
              stepSize:(uint8_t)stepSize
        transitionTime:(uint8_t)transitionTime
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
     completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stopMoveStep:(uint8_t)optionsMask
      optionsOverride:(uint8_t)optionsOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCurrentHue:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeCurrentHue:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                              change:(uint8_t)change
                   completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ConfigureAttributeCurrentHue(onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentHue:(ResponseHandler)reportHandler
{
    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentHue(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeCurrentSaturation:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeCurrentSaturation:(uint16_t)minInterval
                                maxInterval:(uint16_t)maxInterval
                                     change:(uint8_t)change
                          completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ConfigureAttributeCurrentSaturation(
        onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentSaturation:(ResponseHandler)reportHandler
{
    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentSaturation(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeRemainingTime:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCurrentX:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeCurrentX:(uint16_t)minInterval
                       maxInterval:(uint16_t)maxInterval
                            change:(uint16_t)change
                 completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ConfigureAttributeCurrentX(onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentX:(ResponseHandler)reportHandler
{
    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentX(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeCurrentY:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeCurrentY:(uint16_t)minInterval
                       maxInterval:(uint16_t)maxInterval
                            change:(uint16_t)change
                 completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ConfigureAttributeCurrentY(onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentY:(ResponseHandler)reportHandler
{
    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentY(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeDriftCompensation:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCompensationText:(ResponseHandler)completionHandler
{
    CHIPUnsupportedAttributeCallbackBridge * onSuccess
        = new CHIPUnsupportedAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorTemperature:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeColorTemperature:(uint16_t)minInterval
                               maxInterval:(uint16_t)maxInterval
                                    change:(uint16_t)change
                         completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ConfigureAttributeColorTemperature(
        onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeColorTemperature:(ResponseHandler)reportHandler
{
    CHIPInt16uAttributeCallbackBridge * onReport = new CHIPInt16uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeColorTemperature(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeColorMode:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorControlOptions:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorControlOptions:(uint8_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeNumberOfPrimaries:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary1X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary1Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary1Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary2X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary2Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary2Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary3X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary3Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary3Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary4X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary4Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary4Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary5X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary5Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary5Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary6X:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary6Y:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributePrimary6Intensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeWhitePointX:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeWhitePointX:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeWhitePointY:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeWhitePointY:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointRX:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointRX:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointRY:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointRY:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointRIntensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointRIntensity:(uint8_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointGX:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointGX:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointGY:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointGY:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointGIntensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointGIntensity:(uint8_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointBX:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointBX:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointBY:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointBY:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorPointBIntensity:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeColorPointBIntensity:(uint8_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeEnhancedCurrentHue:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeEnhancedColorMode:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorLoopActive:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorLoopDirection:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorLoopTime:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorCapabilities:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorTempPhysicalMin:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeColorTempPhysicalMax:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCoupleColorTempToLevelMinMireds:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeStartUpColorTemperatureMireds:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeStartUpColorTemperatureMireds:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)clearAllPins:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearAllPinsResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearAllPinsResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearAllRfids:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearAllRfidsResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearHolidaySchedule:(uint8_t)scheduleId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearHolidayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearPin:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearPinResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearPinResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearRfid:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearRfidResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearRfidResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearWeekdaySchedule:(uint8_t)scheduleId userId:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearWeekdayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)clearYeardaySchedule:(uint8_t)scheduleId userId:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterClearYeardayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getHolidaySchedule:(uint8_t)scheduleId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetHolidayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getLogRecord:(uint16_t)logIndex completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetLogRecordResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetLogRecordResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getPin:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetPinResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetPinResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getRfid:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetRfidResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetRfidResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getUserType:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetUserTypeResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetUserTypeResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getWeekdaySchedule:(uint8_t)scheduleId userId:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetWeekdayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getYeardaySchedule:(uint8_t)scheduleId userId:(uint16_t)userId completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterGetYeardayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)lockDoor:(char *)pin completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterLockDoorResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterLockDoorResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setHolidaySchedule:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday
             completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetHolidayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setPin:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                  pin:(char *)pin
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetPinResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetPinResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setRfid:(uint16_t)userId
           userStatus:(uint8_t)userStatus
             userType:(uint8_t)userType
                   id:(char *)id
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetRfidResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetRfidResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setUserType:(uint16_t)userId userType:(uint8_t)userType completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetUserTypeResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetUserTypeResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setWeekdaySchedule:(uint8_t)scheduleId
                    userId:(uint16_t)userId
                  daysMask:(uint8_t)daysMask
                 startHour:(uint8_t)startHour
               startMinute:(uint8_t)startMinute
                   endHour:(uint8_t)endHour
                 endMinute:(uint8_t)endMinute
         completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetWeekdayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)setYeardaySchedule:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime
         completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterSetYeardayScheduleResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)unlockDoor:(char *)pin completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterUnlockDoorResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterUnlockDoorResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)unlockWithTimeout:(uint16_t)timeoutInSeconds pin:(char *)pin completionHandler:(ResponseHandler)completionHandler
{
    CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge * onSuccess
        = new CHIPDoorLockClusterUnlockWithTimeoutResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeLockState:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeLockState:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                  completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ConfigureAttributeLockState(onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeLockState:(ResponseHandler)reportHandler
{
    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeLockState(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeLockType:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeActuatorEnabled:(ResponseHandler)completionHandler
{
    CHIPBooleanAttributeCallbackBridge * onSuccess = new CHIPBooleanAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)addGroup:(uint16_t)groupId groupName:(char *)groupName completionHandler:(ResponseHandler)completionHandler
{
    CHIPGroupsClusterAddGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterAddGroupResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)addGroupIfIdentifying:(uint16_t)groupId groupName:(char *)groupName completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getGroupMembership:(uint8_t)groupCount groupList:(uint16_t)groupList completionHandler:(ResponseHandler)completionHandler
{
    CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterGetGroupMembershipResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)removeAllGroups:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)removeGroup:(uint16_t)groupId completionHandler:(ResponseHandler)completionHandler
{
    CHIPGroupsClusterRemoveGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterRemoveGroupResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)viewGroup:(uint16_t)groupId completionHandler:(ResponseHandler)completionHandler
{
    CHIPGroupsClusterViewGroupResponseCallbackBridge * onSuccess
        = new CHIPGroupsClusterViewGroupResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeNameSupport:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)identify:(uint16_t)identifyTime completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)identifyQuery:(ResponseHandler)completionHandler
{
    CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge * onSuccess
        = new CHIPIdentifyClusterIdentifyQueryResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeIdentifyTime:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)writeAttributeIdentifyTime:(uint16_t)value completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)move:(uint8_t)moveMode
                 rate:(uint8_t)rate
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToLevel:(uint8_t)level
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveToLevelWithOnOff:(uint8_t)level
              transitionTime:(uint16_t)transitionTime
           completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)moveWithOnOff:(uint8_t)moveMode rate:(uint8_t)rate completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)step:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stepWithOnOff:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stop:(uint8_t)optionMask optionOverride:(uint8_t)optionOverride completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)stopWithOnOff:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCurrentLevel:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeCurrentLevel:(uint16_t)minInterval
                           maxInterval:(uint16_t)maxInterval
                                change:(uint8_t)change
                     completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ConfigureAttributeCurrentLevel(
        onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentLevel:(ResponseHandler)reportHandler
{
    CHIPInt8uAttributeCallbackBridge * onReport = new CHIPInt8uAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentLevel(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)off:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)on:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)toggle:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeOnOff:(ResponseHandler)completionHandler
{
    CHIPBooleanAttributeCallbackBridge * onSuccess = new CHIPBooleanAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeOnOff:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
              completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ConfigureAttributeOnOff(onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeOnOff:(ResponseHandler)reportHandler
{
    CHIPBooleanAttributeCallbackBridge * onReport = new CHIPBooleanAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeOnOff(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)addScene:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
       transitionTime:(uint16_t)transitionTime
            sceneName:(char *)sceneName
            clusterId:(uint16_t)clusterId
               length:(uint8_t)length
                value:(uint8_t)value
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterAddSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterAddSceneResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)getSceneMembership:(uint16_t)groupId completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterGetSceneMembershipResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterGetSceneMembershipResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)recallScene:(uint16_t)groupId
              sceneId:(uint8_t)sceneId
       transitionTime:(uint16_t)transitionTime
    completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)removeAllScenes:(uint16_t)groupId completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterRemoveAllScenesResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterRemoveAllScenesResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)removeScene:(uint16_t)groupId sceneId:(uint8_t)sceneId completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterRemoveSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterRemoveSceneResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)storeScene:(uint16_t)groupId sceneId:(uint8_t)sceneId completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterStoreSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterStoreSceneResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
- (BOOL)viewScene:(uint16_t)groupId sceneId:(uint8_t)sceneId completionHandler:(ResponseHandler)completionHandler
{
    CHIPScenesClusterViewSceneResponseCallbackBridge * onSuccess
        = new CHIPScenesClusterViewSceneResponseCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeSceneCount:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCurrentScene:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeCurrentGroup:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeSceneValid:(ResponseHandler)completionHandler
{
    CHIPBooleanAttributeCallbackBridge * onSuccess = new CHIPBooleanAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeNameSupport:(ResponseHandler)completionHandler
{
    CHIPInt8uAttributeCallbackBridge * onSuccess = new CHIPInt8uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeMeasuredValue:(ResponseHandler)completionHandler
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)configureAttributeMeasuredValue:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                                 change:(int16_t)change
                      completionHandler:(ResponseHandler)completionHandler
{
    CHIPDefaultSuccessCallbackBridge * onSuccess = new CHIPDefaultSuccessCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
    if (!onFailure) {
        delete onSuccess;
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ConfigureAttributeMeasuredValue(
        onSuccess->Cancel(), onFailure->Cancel(), minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        delete onSuccess;
        delete onFailure;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeMeasuredValue:(ResponseHandler)reportHandler
{
    CHIPInt16sAttributeCallbackBridge * onReport = new CHIPInt16sAttributeCallbackBridge(reportHandler, _callbackQueue, true);
    if (!onReport) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeMeasuredValue(onReport->Cancel());
    if (err != CHIP_NO_ERROR) {
        delete onReport;
        return NO;
    }

    return YES;
}

- (BOOL)readAttributeMinMeasuredValue:(ResponseHandler)completionHandler
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeMaxMeasuredValue:(ResponseHandler)completionHandler
{
    CHIPInt16sAttributeCallbackBridge * onSuccess = new CHIPInt16sAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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

- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler
{
    CHIPInt16uAttributeCallbackBridge * onSuccess = new CHIPInt16uAttributeCallbackBridge(completionHandler, _callbackQueue);
    if (!onSuccess) {
        return NO;
    }

    CHIPDefaultFailureCallbackBridge * onFailure = new CHIPDefaultFailureCallbackBridge(completionHandler, _callbackQueue);
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
