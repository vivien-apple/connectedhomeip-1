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

#import "CHIPCallbackBridge.h"
#import "CHIPClustersObjc.h"
#import "CHIPDevice.h"
#import "CHIPDevice_Internal.h"

#include <controller/CHIPClusters.h>

@interface CHIPBarrierControl ()

@property (readonly) chip::Controller::BarrierControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBarrierControl

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)barrierControlGoToPercent:(CHIPDeviceCallback)onCompletion percentOpen:(uint8_t)percentOpen
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.BarrierControlGoToPercent(callback, nullptr, percentOpen);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)barrierControlStop:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.BarrierControlStop(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierMovingState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierMovingState(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierSafetyStatus:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierSafetyStatus(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierCapabilities:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierCapabilities(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeBarrierPosition:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierPosition(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPBasic ()

@property (readonly) chip::Controller::BasicCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBasic

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)mfgSpecificPing:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MfgSpecificPing(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)resetToFactoryDefaults:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ResetToFactoryDefaults(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZclVersion:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZclVersion(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePowerSource:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePowerSource(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPBinding ()

@property (readonly) chip::Controller::BindingCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPBinding

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)bind:(CHIPDeviceCallback)onCompletion
        nodeId:(chip::NodeId)nodeId
       groupId:(chip::GroupId)groupId
    endpointId:(chip::EndpointId)endpointId
     clusterId:(chip::ClusterId)clusterId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Bind(callback, nullptr, nodeId, groupId, endpointId, clusterId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)unbind:(CHIPDeviceCallback)onCompletion
        nodeId:(chip::NodeId)nodeId
       groupId:(chip::GroupId)groupId
    endpointId:(chip::EndpointId)endpointId
     clusterId:(chip::ClusterId)clusterId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Unbind(callback, nullptr, nodeId, groupId, endpointId, clusterId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPColorControl ()

@property (readonly) chip::Controller::ColorControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPColorControl

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)moveColor:(CHIPDeviceCallback)onCompletion
              rateX:(int16_t)rateX
              rateY:(int16_t)rateY
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveColor(callback, nullptr, rateX, rateY, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveColorTemperature:(CHIPDeviceCallback)onCompletion
                    moveMode:(uint8_t)moveMode
                        rate:(uint16_t)rate
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveColorTemperature(
        callback, nullptr, moveMode, rate, colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveHue:(CHIPDeviceCallback)onCompletion
           moveMode:(uint8_t)moveMode
               rate:(uint8_t)rate
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveHue(callback, nullptr, moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveSaturation:(CHIPDeviceCallback)onCompletion
              moveMode:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveSaturation(callback, nullptr, moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToColor:(CHIPDeviceCallback)onCompletion
             colorX:(uint16_t)colorX
             colorY:(uint16_t)colorY
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToColor(callback, nullptr, colorX, colorY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToColorTemperature:(CHIPDeviceCallback)onCompletion
              colorTemperature:(uint16_t)colorTemperature
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.MoveToColorTemperature(callback, nullptr, colorTemperature, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToHue:(CHIPDeviceCallback)onCompletion
                hue:(uint8_t)hue
          direction:(uint8_t)direction
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToHue(callback, nullptr, hue, direction, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToHueAndSaturation:(CHIPDeviceCallback)onCompletion
                           hue:(uint8_t)hue
                    saturation:(uint8_t)saturation
                transitionTime:(uint16_t)transitionTime
                   optionsMask:(uint8_t)optionsMask
               optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.MoveToHueAndSaturation(callback, nullptr, hue, saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToSaturation:(CHIPDeviceCallback)onCompletion
              saturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToSaturation(callback, nullptr, saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stepColor:(CHIPDeviceCallback)onCompletion
              stepX:(int16_t)stepX
              stepY:(int16_t)stepY
     transitionTime:(uint16_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepColor(callback, nullptr, stepX, stepY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stepColorTemperature:(CHIPDeviceCallback)onCompletion
                    stepMode:(uint8_t)stepMode
                    stepSize:(uint16_t)stepSize
              transitionTime:(uint16_t)transitionTime
     colorTemperatureMinimum:(uint16_t)colorTemperatureMinimum
     colorTemperatureMaximum:(uint16_t)colorTemperatureMaximum
                 optionsMask:(uint8_t)optionsMask
             optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepColorTemperature(callback, nullptr, stepMode, stepSize, transitionTime,
        colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stepHue:(CHIPDeviceCallback)onCompletion
           stepMode:(uint8_t)stepMode
           stepSize:(uint8_t)stepSize
     transitionTime:(uint8_t)transitionTime
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepHue(callback, nullptr, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stepSaturation:(CHIPDeviceCallback)onCompletion
              stepMode:(uint8_t)stepMode
              stepSize:(uint8_t)stepSize
        transitionTime:(uint8_t)transitionTime
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.StepSaturation(callback, nullptr, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stopMoveStep:(CHIPDeviceCallback)onCompletion optionsMask:(uint8_t)optionsMask optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StopMoveStep(callback, nullptr, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentHue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentHue(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentHue:(CHIPDeviceCallback)onCompletion
                         onChange:(CHIPDeviceCallback)onChange
                      minInterval:(uint16_t)minInterval
                      maxInterval:(uint16_t)maxInterval
                           change:(uint8_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ReportAttributeCurrentHue(completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentSaturation(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion
                                onChange:(CHIPDeviceCallback)onChange
                             minInterval:(uint16_t)minInterval
                             maxInterval:(uint16_t)maxInterval
                                  change:(uint8_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentSaturation(
        completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeRemainingTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeRemainingTime(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentX(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentX:(CHIPDeviceCallback)onCompletion
                       onChange:(CHIPDeviceCallback)onChange
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ReportAttributeCurrentX(completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentY(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentY:(CHIPDeviceCallback)onCompletion
                       onChange:(CHIPDeviceCallback)onChange
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                         change:(uint16_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ReportAttributeCurrentY(completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeDriftCompensation:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeDriftCompensation(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCompensationText:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCompensationText(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTemperature:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTemperature(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeColorTemperature:(CHIPDeviceCallback)onCompletion
                               onChange:(CHIPDeviceCallback)onChange
                            minInterval:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                                 change:(uint16_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeColorTemperature(
        completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorMode:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorMode(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorControlOptions(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorControlOptions(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNumberOfPrimaries:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNumberOfPrimaries(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary1Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary2Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary3Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary4Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary5Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6X(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Y(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributePrimary6Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Intensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeWhitePointX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointX(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeWhitePointX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointX(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeWhitePointY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointY(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeWhitePointY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointY(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRX(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRX(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRY(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRY(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRIntensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRIntensity(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGX(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGX(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGY(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGY(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGIntensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGIntensity(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBX(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBX(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBY(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBY(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBIntensity(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBIntensity(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeEnhancedCurrentHue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedCurrentHue(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeEnhancedColorMode:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedColorMode(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopActive:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopActive(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopDirection:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopDirection(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorLoopTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopTime(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorCapabilities:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorCapabilities(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTempPhysicalMin:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMin(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeColorTempPhysicalMax:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMax(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCoupleColorTempToLevelMinMireds:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCoupleColorTempToLevelMinMireds(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeStartUpColorTemperatureMireds(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeStartUpColorTemperatureMireds(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPDoorLock ()

@property (readonly) chip::Controller::DoorLockCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPDoorLock

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)clearAllPins:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearAllPins(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearAllRfids:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearAllRfids(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearHolidaySchedule(callback, nullptr, scheduleId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearPin(callback, nullptr, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearRfid(callback, nullptr, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearWeekdaySchedule(callback, nullptr, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)clearYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearYeardaySchedule(callback, nullptr, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetHolidaySchedule(callback, nullptr, scheduleId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getLogRecord:(CHIPDeviceCallback)onCompletion logIndex:(uint16_t)logIndex
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetLogRecord(callback, nullptr, logIndex);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetPin(callback, nullptr, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetRfid(callback, nullptr, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetUserType(callback, nullptr, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetWeekdaySchedule(callback, nullptr, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetYeardaySchedule(callback, nullptr, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)lockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.LockDoor(callback, nullptr, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setHolidaySchedule:(CHIPDeviceCallback)onCompletion
                    scheduleId:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetHolidaySchedule(
        callback, nullptr, scheduleId, localStartTime, localEndTime, operatingModeDuringHoliday);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setPin:(CHIPDeviceCallback)onCompletion
        userId:(uint16_t)userId
    userStatus:(uint8_t)userStatus
      userType:(uint8_t)userType
           pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetPin(callback, nullptr, userId, userStatus, userType, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setRfid:(CHIPDeviceCallback)onCompletion
         userId:(uint16_t)userId
     userStatus:(uint8_t)userStatus
       userType:(uint8_t)userType
             id:(char *)id
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetRfid(callback, nullptr, userId, userStatus, userType, id);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId userType:(uint8_t)userType
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetUserType(callback, nullptr, userId, userType);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setWeekdaySchedule:(CHIPDeviceCallback)onCompletion
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
                  daysMask:(uint8_t)daysMask
                 startHour:(uint8_t)startHour
               startMinute:(uint8_t)startMinute
                   endHour:(uint8_t)endHour
                 endMinute:(uint8_t)endMinute
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetWeekdaySchedule(
        callback, nullptr, scheduleId, userId, daysMask, startHour, startMinute, endHour, endMinute);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)setYeardaySchedule:(CHIPDeviceCallback)onCompletion
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetYeardaySchedule(callback, nullptr, scheduleId, userId, localStartTime, localEndTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)unlockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.UnlockDoor(callback, nullptr, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)unlockWithTimeout:(CHIPDeviceCallback)onCompletion timeoutInSeconds:(uint16_t)timeoutInSeconds pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.UnlockWithTimeout(callback, nullptr, timeoutInSeconds, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeLockState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockState(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeLockState:(CHIPDeviceCallback)onCompletion
                        onChange:(CHIPDeviceCallback)onChange
                     minInterval:(uint16_t)minInterval
                     maxInterval:(uint16_t)maxInterval
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.ReportAttributeLockState(completionCallback, nullptr, changeCallback, minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeLockType:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockType(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeActuatorEnabled:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeActuatorEnabled(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPGroups ()

@property (readonly) chip::Controller::GroupsCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPGroups

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)addGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddGroup(callback, nullptr, groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)addGroupIfIdentifying:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddGroupIfIdentifying(callback, nullptr, groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getGroupMembership:(CHIPDeviceCallback)onCompletion groupCount:(uint8_t)groupCount groupList:(uint16_t)groupList
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetGroupMembership(callback, nullptr, groupCount, groupList);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)removeAllGroups:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveAllGroups(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)removeGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveGroup(callback, nullptr, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)viewGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewGroup(callback, nullptr, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNameSupport:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPIasZone ()

@property (readonly) chip::Controller::IasZoneCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPIasZone

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)readAttributeZoneState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneState(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneType:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneType(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneStatus:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneStatus(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeIasCieAddress(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion value:(uint64_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeIasCieAddress(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeZoneId:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneId(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPIdentify ()

@property (readonly) chip::Controller::IdentifyCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPIdentify

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)identify:(CHIPDeviceCallback)onCompletion identifyTime:(uint16_t)identifyTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Identify(callback, nullptr, identifyTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)identifyQuery:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.IdentifyQuery(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeIdentifyTime(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)writeAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeIdentifyTime(callback, nullptr, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPLevelControl ()

@property (readonly) chip::Controller::LevelControlCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPLevelControl

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)move:(CHIPDeviceCallback)onCompletion
          moveMode:(uint8_t)moveMode
              rate:(uint8_t)rate
        optionMask:(uint8_t)optionMask
    optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Move(callback, nullptr, moveMode, rate, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToLevel:(CHIPDeviceCallback)onCompletion
              level:(uint8_t)level
     transitionTime:(uint16_t)transitionTime
         optionMask:(uint8_t)optionMask
     optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToLevel(callback, nullptr, level, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveToLevelWithOnOff:(CHIPDeviceCallback)onCompletion level:(uint8_t)level transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToLevelWithOnOff(callback, nullptr, level, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)moveWithOnOff:(CHIPDeviceCallback)onCompletion moveMode:(uint8_t)moveMode rate:(uint8_t)rate
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveWithOnOff(callback, nullptr, moveMode, rate);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)step:(CHIPDeviceCallback)onCompletion
          stepMode:(uint8_t)stepMode
          stepSize:(uint8_t)stepSize
    transitionTime:(uint16_t)transitionTime
        optionMask:(uint8_t)optionMask
    optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Step(callback, nullptr, stepMode, stepSize, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stepWithOnOff:(CHIPDeviceCallback)onCompletion
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepWithOnOff(callback, nullptr, stepMode, stepSize, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stop:(CHIPDeviceCallback)onCompletion optionMask:(uint8_t)optionMask optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Stop(callback, nullptr, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)stopWithOnOff:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StopWithOnOff(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentLevel(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion
                           onChange:(CHIPDeviceCallback)onChange
                        minInterval:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                             change:(uint8_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentLevel(
        completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPOnOff ()

@property (readonly) chip::Controller::OnOffCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPOnOff

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)off:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Off(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)on:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.On(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)toggle:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Toggle(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeOnOff:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOnOff(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeOnOff:(CHIPDeviceCallback)onCompletion
                    onChange:(CHIPDeviceCallback)onChange
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeOnOff(completionCallback, nullptr, changeCallback, minInterval, maxInterval);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPScenes ()

@property (readonly) chip::Controller::ScenesCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPScenes

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)addScene:(CHIPDeviceCallback)onCompletion
           groupId:(uint16_t)groupId
           sceneId:(uint8_t)sceneId
    transitionTime:(uint16_t)transitionTime
         sceneName:(char *)sceneName
         clusterId:(chip::ClusterId)clusterId
            length:(uint8_t)length
             value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.AddScene(callback, nullptr, groupId, sceneId, transitionTime, sceneName, clusterId, length, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)getSceneMembership:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetSceneMembership(callback, nullptr, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)recallScene:(CHIPDeviceCallback)onCompletion
            groupId:(uint16_t)groupId
            sceneId:(uint8_t)sceneId
     transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RecallScene(callback, nullptr, groupId, sceneId, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)removeAllScenes:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveAllScenes(callback, nullptr, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)removeScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveScene(callback, nullptr, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)storeScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StoreScene(callback, nullptr, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)viewScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewScene(callback, nullptr, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeSceneCount:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneCount(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentScene:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentScene(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeCurrentGroup:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentGroup(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeSceneValid:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneValid(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeNameSupport:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end

@interface CHIPTemperatureMeasurement ()

@property (readonly) chip::Controller::TemperatureMeasurementCluster cppCluster;
@property (readonly, nonatomic) dispatch_queue_t callbackQueue;
@end

@implementation CHIPTemperatureMeasurement

- (instancetype)initWithDevice:(CHIPDevice *)device endpoint:(chip::EndpointId)endpoint queue:(dispatch_queue_t)queue
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

- (BOOL)readAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMeasuredValue(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)reportAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion
                            onChange:(CHIPDeviceCallback)onChange
                         minInterval:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                              change:(int16_t)change
{
    CHIPCallbackBridge * completionCallback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!completionCallback) {
        return NO;
    }

    CHIPCallbackBridge * changeCallback = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!changeCallback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeMeasuredValue(
        completionCallback, nullptr, changeCallback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        completionCallback->Cancel();
        changeCallback->Cancel();
        delete completionCallback;
        delete changeCallback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeMinMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMinMeasuredValue(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeMaxMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMaxMeasuredValue(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)readAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback, nullptr);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end
