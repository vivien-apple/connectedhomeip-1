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

#ifndef CHIP_CLUSTERS_H
#define CHIP_CLUSTERS_H

#import <Foundation/Foundation.h>

typedef void (^ResponseHandler)(NSError * _Nullable error, NSDictionary * _Nullable values);

@class CHIPDevice;

NS_ASSUME_NONNULL_BEGIN

@interface CHIPLevelControl : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)move:(uint8_t)moveMode
                 rate:(uint8_t)rate
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler;
- (BOOL)moveToLevel:(uint8_t)level
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler;
- (BOOL)moveToLevelWithOnOff:(uint8_t)level
              transitionTime:(uint16_t)transitionTime
           completionHandler:(ResponseHandler)completionHandler;
- (BOOL)moveWithOnOff:(uint8_t)moveMode rate:(uint8_t)rate completionHandler:(ResponseHandler)completionHandler;
- (BOOL)step:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
           optionMask:(uint8_t)optionMask
       optionOverride:(uint8_t)optionOverride
    completionHandler:(ResponseHandler)completionHandler;
- (BOOL)stepWithOnOff:(uint8_t)stepMode
             stepSize:(uint8_t)stepSize
       transitionTime:(uint16_t)transitionTime
    completionHandler:(ResponseHandler)completionHandler;
- (BOOL)stop:(uint8_t)optionMask optionOverride:(uint8_t)optionOverride completionHandler:(ResponseHandler)completionHandler;
- (BOOL)stopWithOnOff:(ResponseHandler)completionHandler;

- (BOOL)readAttributeCurrentLevel:(ResponseHandler)completionHandler;
- (BOOL)configureAttributeCurrentLevel:(uint16_t)minInterval
                           maxInterval:(uint16_t)maxInterval
                                change:(uint8_t)change
                     completionHandler:(ResponseHandler)completionHandler;
- (BOOL)reportAttributeCurrentLevel:(ResponseHandler)reportHandler;
- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

NS_ASSUME_NONNULL_BEGIN

@interface CHIPOnOff : NSObject

- (nullable instancetype)initWithDevice:(CHIPDevice *)device endpoint:(uint8_t)endpoint queue:(dispatch_queue_t)queue;
- (BOOL)off:(ResponseHandler)completionHandler;
- (BOOL)on:(ResponseHandler)completionHandler;
- (BOOL)toggle:(ResponseHandler)completionHandler;

- (BOOL)readAttributeOnOff:(ResponseHandler)completionHandler;
- (BOOL)configureAttributeOnOff:(uint16_t)minInterval
                    maxInterval:(uint16_t)maxInterval
              completionHandler:(ResponseHandler)completionHandler;
- (BOOL)reportAttributeOnOff:(ResponseHandler)reportHandler;
- (BOOL)readAttributeClusterRevision:(ResponseHandler)completionHandler;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END

#endif /* CHIP_CLUSTERS_H */
