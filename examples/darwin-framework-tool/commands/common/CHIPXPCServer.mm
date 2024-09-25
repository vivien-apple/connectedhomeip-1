/*
 *   Copyright (c) 2024 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "CHIPXPCServer.h"

#include "CHIPCommandBridge.h"

@interface AppDeviceControllerServerProtocol ()
@property (nonatomic, readwrite, strong) id<MTRDeviceControllerClientProtocol> clientProxy;
@end

@implementation AppDeviceControllerServerProtocol
- (instancetype)initWithClientProxy:(id<MTRDeviceControllerClientProtocol>)proxy
{
    if ([super init]) {
        _clientProxy = proxy;
    }
    return self;
}

- (void)getAnyDeviceControllerWithCompletion:(MTRDeviceControllerGetterHandler)completion
{
    ChipLogProgress(chipTool, "XPC: getAnyDeviceControllerWithCompletion");
}

- (void)readAttributeWithController:(id _Nullable)controller
                             nodeId:(uint64_t)nodeId
                         endpointId:(NSNumber * _Nullable)endpointId
                          clusterId:(NSNumber * _Nullable)clusterId
                        attributeId:(NSNumber * _Nullable)attributeId
                             params:(NSDictionary<NSString *, id> * _Nullable)params
                         completion:(MTRValuesHandler)completion
{
    ChipLogProgress(chipTool, "XPC: readAttributeWithController");

    if (![controller isKindOfClass:[NSString class]]) {
        ChipLogError(chipTool, "The controller identifier should be a NSString.");
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    std::string identity = std::string([(NSString *) controller UTF8String]);
    auto localController = CHIPCommandBridge::mControllers[identity];
    if (nil == localController) {
        ChipLogError(chipTool, "The controller identity '%s' could not be found.", identity.c_str());
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    auto device = [MTRBaseDevice deviceWithNodeID:@(nodeId) controller:localController];
    auto callbackQueue = dispatch_queue_create("com.chip.command", DISPATCH_QUEUE_SERIAL);

    [device readAttributesWithEndpointID:endpointId
                               clusterID:clusterId
                             attributeID:attributeId
                                  params:[MTRDeviceController decodeXPCReadParams:params]
                                   queue:callbackQueue
                              completion:^(NSArray<NSDictionary<NSString *, id> *> * _Nullable values, NSError * _Nullable error) {
                                  completion([MTRDeviceController encodeXPCResponseValues:values], error);
                              }];
}

- (void)writeAttributeWithController:(id _Nullable)controller
                              nodeId:(uint64_t)nodeId
                          endpointId:(NSNumber *)endpointId
                           clusterId:(NSNumber *)clusterId
                         attributeId:(NSNumber *)attributeId
                               value:(id)value
                   timedWriteTimeout:(NSNumber * _Nullable)timeoutMs
                          completion:(MTRValuesHandler)completion
{
    ChipLogProgress(chipTool, "XPC: writeAttributeWithController");

    if (![controller isKindOfClass:[NSString class]]) {
        ChipLogError(chipTool, "The controller identifier should be a NSString");
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    std::string identity = std::string([(NSString *) controller UTF8String]);
    auto localController = CHIPCommandBridge::mControllers[identity];
    if (nil == localController) {
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    auto device = [MTRBaseDevice deviceWithNodeID:@(nodeId) controller:localController];
    auto callbackQueue = dispatch_queue_create("com.chip.command", DISPATCH_QUEUE_SERIAL);

    [device
        writeAttributeWithEndpointID:endpointId
                           clusterID:clusterId
                         attributeID:attributeId
                               value:value
                   timedWriteTimeout:timeoutMs
                               queue:callbackQueue
                          completion:^(NSArray<NSDictionary<NSString *, id> *> * _Nullable values, NSError * _Nullable error) {
                              completion([MTRDeviceController encodeXPCResponseValues:values], error);
                          }];
}

- (void)invokeCommandWithController:(id _Nullable)controller
                             nodeId:(uint64_t)nodeId
                         endpointId:(NSNumber *)endpointId
                          clusterId:(NSNumber *)clusterId
                          commandId:(NSNumber *)commandId
                             fields:(id)fields
                 timedInvokeTimeout:(NSNumber * _Nullable)timeoutMs
                         completion:(MTRValuesHandler)completion
{
    ChipLogProgress(chipTool, "XPC: invokeCommandWithController");

    if (![controller isKindOfClass:[NSString class]]) {
        ChipLogError(chipTool, "The controller identifier should be a NSString");
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    std::string identity = std::string([(NSString *) controller UTF8String]);
    auto localController = CHIPCommandBridge::mControllers[identity];
    if (nil == localController) {
        completion(nil, [NSError errorWithDomain:MTRErrorDomain code:MTRErrorCodeGeneralError userInfo:nil]);
        return;
    }

    auto device = [MTRBaseDevice deviceWithNodeID:@(nodeId) controller:localController];
    auto callbackQueue = dispatch_queue_create("com.chip.command", DISPATCH_QUEUE_SERIAL);

    [device
        invokeCommandWithEndpointID:endpointId
                          clusterID:clusterId
                          commandID:commandId
                      commandFields:fields
                 timedInvokeTimeout:timeoutMs
                              queue:callbackQueue
                         completion:^(NSArray<NSDictionary<NSString *, id> *> * _Nullable values, NSError * _Nullable error) {
                             completion([MTRDeviceController encodeXPCResponseValues:values], error);
                         }];
}

- (void)subscribeAttributeWithController:(id _Nullable)controller
                                  nodeId:(uint64_t)nodeId
                              endpointId:(NSNumber * _Nullable)endpointId
                               clusterId:(NSNumber * _Nullable)clusterId
                             attributeId:(NSNumber * _Nullable)attributeId
                             minInterval:(NSNumber *)minInterval
                             maxInterval:(NSNumber *)maxInterval
                                  params:(NSDictionary<NSString *, id> * _Nullable)params
                      establishedHandler:(dispatch_block_t)establishedHandler
{
    ChipLogProgress(chipTool, "XPC: subscribeAttributeWithController");

    if (![controller isKindOfClass:[NSString class]]) {
        ChipLogError(chipTool, "The controller identifier should be a NSString");

        establishedHandler();
        // Send an error report so that the client knows of the failure
        [self.clientProxy handleReportWithController:controller
                                              nodeId:nodeId
                                              values:nil
                                               error:[NSError errorWithDomain:MTRErrorDomain
                                                                         code:MTRErrorCodeGeneralError
                                                                     userInfo:nil]];
        return;
    }

    std::string identity = std::string([(NSString *) controller UTF8String]);
    auto localController = CHIPCommandBridge::mControllers[identity];
    if (nil == localController) {
        establishedHandler();
        // Send an error report so that the client knows of the failure
        [self.clientProxy handleReportWithController:controller
                                              nodeId:nodeId
                                              values:nil
                                               error:[NSError errorWithDomain:MTRErrorDomain
                                                                         code:MTRErrorCodeGeneralError
                                                                     userInfo:nil]];
        return;
    }

    auto subscriptionParams = [MTRDeviceController decodeXPCSubscribeParams:params];
    if (subscriptionParams == nil) {
        subscriptionParams = [[MTRSubscribeParams alloc] initWithMinInterval:minInterval maxInterval:maxInterval];
    } else {
        subscriptionParams.minInterval = minInterval;
        subscriptionParams.maxInterval = maxInterval;
    }

    auto device = [MTRBaseDevice deviceWithNodeID:@(nodeId) controller:localController];
    auto callbackQueue = dispatch_queue_create("com.chip.command", DISPATCH_QUEUE_SERIAL);

    [device subscribeToAttributesWithEndpointID:endpointId
                                      clusterID:clusterId
                                    attributeID:attributeId
                                         params:subscriptionParams
                                          queue:callbackQueue
                                  reportHandler:^(
                                      NSArray<NSDictionary<NSString *, id> *> * _Nullable values, NSError * _Nullable error) {
                                      [self.clientProxy
                                          handleReportWithController:controller
                                                              nodeId:nodeId
                                                              values:[MTRDeviceController encodeXPCResponseValues:values]
                                                               error:error];
                                  }
                        subscriptionEstablished:establishedHandler];
}

- (void)stopReportsWithController:(id _Nullable)controller nodeId:(uint64_t)nodeId completion:(dispatch_block_t)completion
{
    ChipLogProgress(chipTool, "XPC: stopReportsWithController");

    if (![controller isKindOfClass:[NSString class]]) {
        ChipLogError(chipTool, "The controller identifier should be a NSString");
        completion();
        return;
    }

    std::string identity = std::string([(NSString *) controller UTF8String]);
    auto localController = CHIPCommandBridge::mControllers[identity];
    if (nil == localController) {
        completion();
        return;
    }

    auto device = [MTRBaseDevice deviceWithNodeID:@(nodeId) controller:localController];
    auto callbackQueue = dispatch_queue_create("com.chip.command", DISPATCH_QUEUE_SERIAL);
    [device deregisterReportHandlersWithQueue:callbackQueue completion:completion];
}

- (void)subscribeWithController:(id _Nullable)controller
                         nodeId:(uint64_t)nodeId
                    minInterval:(NSNumber *)minInterval
                    maxInterval:(NSNumber *)maxInterval
                         params:(NSDictionary<NSString *, id> * _Nullable)params
                    shouldCache:(BOOL)shouldCache
                     completion:(MTRStatusCompletion)completion
{
    ChipLogProgress(chipTool, "XPC: subscribeWithController");
}

- (void)readAttributeCacheWithController:(id _Nullable)controller
                                  nodeId:(uint64_t)nodeId
                              endpointId:(NSNumber * _Nullable)endpointId
                               clusterId:(NSNumber * _Nullable)clusterId
                             attributeId:(NSNumber * _Nullable)attributeId
                              completion:(MTRValuesHandler)completion
{
    ChipLogProgress(chipTool, "XPC: readAttributeCacheWithController");
}

- (void)getDeviceControllerWithFabricId:(uint64_t)fabricId
                             completion:(MTRDeviceControllerGetterHandler)completion
{
    NSLog(@"XPC: getDeviceControllerWithFabricId");
}

- (void)downloadLogWithController:(id _Nullable)controller
                           nodeId:(NSNumber *)nodeId
                             type:(MTRDiagnosticLogType)type
                          timeout:(NSTimeInterval)timeout
                       completion:(void (^)(NSString * _Nullable url, NSError * _Nullable error))completion
{
    ChipLogProgress(chipTool, "XPC: downloadLogWithController");
}

@end

@implementation AppListenerDelegate
- (BOOL)listener:(NSXPCListener *)listener shouldAcceptNewConnection:(NSXPCConnection *)newConnection
{
    newConnection.exportedInterface = [MTRDeviceController xpcInterfaceForServerProtocol];
    newConnection.remoteObjectInterface = [MTRDeviceController xpcInterfaceForClientProtocol];

    auto server = [[AppDeviceControllerServerProtocol alloc] initWithClientProxy:[newConnection remoteObjectProxy]];
    newConnection.exportedObject = server;

    newConnection.invalidationHandler = ^{
        ChipLogProgress(chipTool, "XPC connection disconnected");
    };

    [newConnection resume];
    return YES;
}
@end
