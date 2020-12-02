
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

- (BOOL)BarrierControlGoToPercent:(CHIPDeviceCallback)onCompletion percentOpen:(uint8_t)percentOpen
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.BarrierControlGoToPercent(callback, percentOpen);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)BarrierControlStop:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.BarrierControlStop(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeBarrierMovingState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierMovingState(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeBarrierSafetyStatus:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierSafetyStatus(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeBarrierCapabilities:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierCapabilities(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeBarrierPosition:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeBarrierPosition(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)ResetToFactoryDefaults:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ResetToFactoryDefaults(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeZclVersion:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZclVersion(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePowerSource:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePowerSource(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)MoveColor:(CHIPDeviceCallback)onCompletion
              rateX:(int16_t)rateX
              rateY:(int16_t)rateY
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveColor(callback, rateX, rateY, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveColorTemperature:(CHIPDeviceCallback)onCompletion
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
        callback, moveMode, rate, colorTemperatureMinimum, colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveHue:(CHIPDeviceCallback)onCompletion
           moveMode:(uint8_t)moveMode
               rate:(uint8_t)rate
        optionsMask:(uint8_t)optionsMask
    optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveHue(callback, moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveSaturation:(CHIPDeviceCallback)onCompletion
              moveMode:(uint8_t)moveMode
                  rate:(uint8_t)rate
           optionsMask:(uint8_t)optionsMask
       optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveSaturation(callback, moveMode, rate, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToColor:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.MoveToColor(callback, colorX, colorY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToColorTemperature:(CHIPDeviceCallback)onCompletion
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
        = self.cppCluster.MoveToColorTemperature(callback, colorTemperature, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToHue:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.MoveToHue(callback, hue, direction, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToHueAndSaturation:(CHIPDeviceCallback)onCompletion
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
        = self.cppCluster.MoveToHueAndSaturation(callback, hue, saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToSaturation:(CHIPDeviceCallback)onCompletion
              saturation:(uint8_t)saturation
          transitionTime:(uint16_t)transitionTime
             optionsMask:(uint8_t)optionsMask
         optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToSaturation(callback, saturation, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StepColor:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.StepColor(callback, stepX, stepY, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StepColorTemperature:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.StepColorTemperature(callback, stepMode, stepSize, transitionTime, colorTemperatureMinimum,
        colorTemperatureMaximum, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StepHue:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.StepHue(callback, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StepSaturation:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.StepSaturation(callback, stepMode, stepSize, transitionTime, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StopMoveStep:(CHIPDeviceCallback)onCompletion optionsMask:(uint8_t)optionsMask optionsOverride:(uint8_t)optionsOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StopMoveStep(callback, optionsMask, optionsOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentHue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentHue(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeCurrentHue:(CHIPDeviceCallback)onCompletion
                      minInterval:(uint16_t)minInterval
                      maxInterval:(uint16_t)maxInterval
                         onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentHue(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentSaturation(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeCurrentSaturation:(CHIPDeviceCallback)onCompletion
                             minInterval:(uint16_t)minInterval
                             maxInterval:(uint16_t)maxInterval
                                onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentSaturation(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeRemainingTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeRemainingTime(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentX(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeCurrentX:(CHIPDeviceCallback)onCompletion
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                       onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentX(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentY(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeCurrentY:(CHIPDeviceCallback)onCompletion
                    minInterval:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
                       onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentY(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeDriftCompensation:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeDriftCompensation(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCompensationText:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCompensationText(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorTemperature:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTemperature(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeColorTemperature:(CHIPDeviceCallback)onCompletion
                            minInterval:(uint16_t)minInterval
                            maxInterval:(uint16_t)maxInterval
                               onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeColorTemperature(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorMode:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorMode(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorControlOptions(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorControlOptions:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorControlOptions(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeNumberOfPrimaries:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNumberOfPrimaries(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary1X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary1Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary1Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary1Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary2X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary2Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary2Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary2Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary3X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary3Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary3Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary3Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary4X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary4Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary4Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary4Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary5X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary5Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary5Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary5Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary6X:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6X(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary6Y:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Y(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributePrimary6Intensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributePrimary6Intensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeWhitePointX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointX(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeWhitePointX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointX(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeWhitePointY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeWhitePointY(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeWhitePointY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeWhitePointY(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointRX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRX(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointRX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRX(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointRY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRY(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointRY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRY(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointRIntensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointRIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointRIntensity(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointGX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGX(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointGX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGX(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointGY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGY(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointGY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGY(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointGIntensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointGIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointGIntensity(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointBX:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBX(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointBX:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBX(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointBY:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBY(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointBY:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBY(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorPointBIntensity(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeColorPointBIntensity:(CHIPDeviceCallback)onCompletion value:(uint8_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeColorPointBIntensity(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeEnhancedCurrentHue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedCurrentHue(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeEnhancedColorMode:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeEnhancedColorMode(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorLoopActive:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopActive(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorLoopDirection:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopDirection(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorLoopTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorLoopTime(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorCapabilities:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorCapabilities(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorTempPhysicalMin:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMin(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeColorTempPhysicalMax:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeColorTempPhysicalMax(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCoupleColorTempToLevelMinMireds:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCoupleColorTempToLevelMinMireds(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeStartUpColorTemperatureMireds(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeStartUpColorTemperatureMireds:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeStartUpColorTemperatureMireds(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)ClearAllPins:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearAllPins(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearAllRfids:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearAllRfids(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearHolidaySchedule(callback, scheduleId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearPin(callback, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearRfid(callback, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearWeekdaySchedule(callback, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ClearYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ClearYeardaySchedule(callback, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetHolidaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetHolidaySchedule(callback, scheduleId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetLogRecord:(CHIPDeviceCallback)onCompletion logIndex:(uint16_t)logIndex
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetLogRecord(callback, logIndex);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetPin:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetPin(callback, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetRfid:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetRfid(callback, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetUserType(callback, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetWeekdaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetWeekdaySchedule(callback, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetYeardaySchedule:(CHIPDeviceCallback)onCompletion scheduleId:(uint8_t)scheduleId userId:(uint16_t)userId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetYeardaySchedule(callback, scheduleId, userId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)LockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.LockDoor(callback, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetHolidaySchedule:(CHIPDeviceCallback)onCompletion
                    scheduleId:(uint8_t)scheduleId
                localStartTime:(uint32_t)localStartTime
                  localEndTime:(uint32_t)localEndTime
    operatingModeDuringHoliday:(uint8_t)operatingModeDuringHoliday
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err
        = self.cppCluster.SetHolidaySchedule(callback, scheduleId, localStartTime, localEndTime, operatingModeDuringHoliday);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetPin:(CHIPDeviceCallback)onCompletion
        userId:(uint16_t)userId
    userStatus:(uint8_t)userStatus
      userType:(uint8_t)userType
           pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetPin(callback, userId, userStatus, userType, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetRfid:(CHIPDeviceCallback)onCompletion
         userId:(uint16_t)userId
     userStatus:(uint8_t)userStatus
       userType:(uint8_t)userType
             id:(char *)id
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetRfid(callback, userId, userStatus, userType, id);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetUserType:(CHIPDeviceCallback)onCompletion userId:(uint16_t)userId userType:(uint8_t)userType
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetUserType(callback, userId, userType);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetWeekdaySchedule:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err
        = self.cppCluster.SetWeekdaySchedule(callback, scheduleId, userId, daysMask, startHour, startMinute, endHour, endMinute);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)SetYeardaySchedule:(CHIPDeviceCallback)onCompletion
                scheduleId:(uint8_t)scheduleId
                    userId:(uint16_t)userId
            localStartTime:(uint32_t)localStartTime
              localEndTime:(uint32_t)localEndTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.SetYeardaySchedule(callback, scheduleId, userId, localStartTime, localEndTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)UnlockDoor:(CHIPDeviceCallback)onCompletion pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.UnlockDoor(callback, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)UnlockWithTimeout:(CHIPDeviceCallback)onCompletion timeoutInSeconds:(uint16_t)timeoutInSeconds pin:(char *)pin
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.UnlockWithTimeout(callback, timeoutInSeconds, pin);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeLockState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockState(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeLockState:(CHIPDeviceCallback)onCompletion
                     minInterval:(uint16_t)minInterval
                     maxInterval:(uint16_t)maxInterval
                        onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeLockState(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeLockType:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeLockType(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeActuatorEnabled:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeActuatorEnabled(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)AddGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddGroup(callback, groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)AddGroupIfIdentifying:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId groupName:(char *)groupName
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.AddGroupIfIdentifying(callback, groupId, groupName);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetGroupMembership:(CHIPDeviceCallback)onCompletion groupCount:(uint8_t)groupCount groupList:(uint16_t)groupList
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetGroupMembership(callback, groupCount, groupList);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)RemoveAllGroups:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveAllGroups(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)RemoveGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveGroup(callback, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ViewGroup:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewGroup(callback, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeNameSupport:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)ReadAttributeZoneState:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneState(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeZoneType:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneType(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeZoneStatus:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneStatus(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeIasCieAddress(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeIasCieAddress:(CHIPDeviceCallback)onCompletion value:(uint64_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeIasCieAddress(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeZoneId:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeZoneId(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)Identify:(CHIPDeviceCallback)onCompletion identifyTime:(uint16_t)identifyTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Identify(callback, identifyTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)IdentifyQuery:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.IdentifyQuery(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeIdentifyTime(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)WriteAttributeIdentifyTime:(CHIPDeviceCallback)onCompletion value:(uint16_t)value
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.WriteAttributeIdentifyTime(callback, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)Move:(CHIPDeviceCallback)onCompletion
          moveMode:(uint8_t)moveMode
              rate:(uint8_t)rate
        optionMask:(uint8_t)optionMask
    optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Move(callback, moveMode, rate, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToLevel:(CHIPDeviceCallback)onCompletion
              level:(uint8_t)level
     transitionTime:(uint16_t)transitionTime
         optionMask:(uint8_t)optionMask
     optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToLevel(callback, level, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveToLevelWithOnOff:(CHIPDeviceCallback)onCompletion level:(uint8_t)level transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveToLevelWithOnOff(callback, level, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)MoveWithOnOff:(CHIPDeviceCallback)onCompletion moveMode:(uint8_t)moveMode rate:(uint8_t)rate
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.MoveWithOnOff(callback, moveMode, rate);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)Step:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.Step(callback, stepMode, stepSize, transitionTime, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StepWithOnOff:(CHIPDeviceCallback)onCompletion
             stepMode:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StepWithOnOff(callback, stepMode, stepSize, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)Stop:(CHIPDeviceCallback)onCompletion optionMask:(uint8_t)optionMask optionOverride:(uint8_t)optionOverride
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Stop(callback, optionMask, optionOverride);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StopWithOnOff:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StopWithOnOff(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentLevel(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeCurrentLevel:(CHIPDeviceCallback)onCompletion
                        minInterval:(uint16_t)minInterval
                        maxInterval:(uint16_t)maxInterval
                           onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeCurrentLevel(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)Off:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Off(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)On:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.On(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)Toggle:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.Toggle(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeOnOff:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeOnOff(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeOnOff:(CHIPDeviceCallback)onCompletion
                 minInterval:(uint16_t)minInterval
                 maxInterval:(uint16_t)maxInterval
                    onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeOnOff(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)AddScene:(CHIPDeviceCallback)onCompletion
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

    CHIP_ERROR err = self.cppCluster.AddScene(callback, groupId, sceneId, transitionTime, sceneName, clusterId, length, value);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)GetSceneMembership:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.GetSceneMembership(callback, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)RecallScene:(CHIPDeviceCallback)onCompletion
            groupId:(uint16_t)groupId
            sceneId:(uint8_t)sceneId
     transitionTime:(uint16_t)transitionTime
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RecallScene(callback, groupId, sceneId, transitionTime);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)RemoveAllScenes:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveAllScenes(callback, groupId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)RemoveScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.RemoveScene(callback, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)StoreScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.StoreScene(callback, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}
- (BOOL)ViewScene:(CHIPDeviceCallback)onCompletion groupId:(uint16_t)groupId sceneId:(uint8_t)sceneId
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ViewScene(callback, groupId, sceneId);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeSceneCount:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneCount(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentScene:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentScene(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeCurrentGroup:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeCurrentGroup(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeSceneValid:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeSceneValid(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeNameSupport:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeNameSupport(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
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

- (BOOL)ReadAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMeasuredValue(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReportAttributeMeasuredValue:(CHIPDeviceCallback)onCompletion
                         minInterval:(uint16_t)minInterval
                         maxInterval:(uint16_t)maxInterval
                            onChange:(CHIPDeviceCallback)onChange
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIPCallbackBridge * change = new CHIPCallbackBridge(onChange, _callbackQueue);
    if (!change) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReportAttributeMeasuredValue(callback, minInterval, maxInterval, change);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        change->Cancel();
        delete callback;
        delete change;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeMinMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMinMeasuredValue(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeMaxMeasuredValue:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeMaxMeasuredValue(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

- (BOOL)ReadAttributeClusterRevision:(CHIPDeviceCallback)onCompletion
{
    CHIPCallbackBridge * callback = new CHIPCallbackBridge(onCompletion, _callbackQueue);
    if (!callback) {
        return NO;
    }

    CHIP_ERROR err = self.cppCluster.ReadAttributeClusterRevision(callback);
    if (err != CHIP_NO_ERROR) {
        callback->Cancel();
        delete callback;
        return NO;
    }
    return YES;
}

@end
