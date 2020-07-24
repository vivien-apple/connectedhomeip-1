/**
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

#include "chip-zcl/chip-zcl-zpro-codec.h"

#import "CHIPDeviceController.h"
#import "CHIPError.h"
#import "CHIPLogging.h"

#include <controller/CHIPDeviceController.h>
#include <inet/IPAddress.h>
#include <system/SystemPacketBuffer.h>

static const char * const CHIP_SELECT_QUEUE = "com.zigbee.chip.select";

// NOTE: Remote device ID is in sync with the echo server device id
//       At some point, we may want to add an option to connect to a device without
//       knowing its id, because the ID can be learned on the first response that is received.
constexpr chip::NodeId kLocalDeviceId = 112233;
constexpr chip::NodeId kRemoteDeviceId = 12344321;

@implementation AddressInfo
- (instancetype)initWithIP:(NSString *)ip
{
    if (self = [super init]) {
        _ip = ip;
    }
    return self;
}
@end

@interface CHIPDeviceController ()

@property (nonatomic, readonly, strong, nonnull) NSRecursiveLock * lock;

// queue used to call select on the system and inet layer fds., remove this with NW Framework.
// primarily used to not block the work queue
@property (atomic, readonly) dispatch_queue_t chipSelectQueue;
// queue used to signal callbacks to the application
@property (readwrite) dispatch_queue_t appCallbackQueue;
@property (readwrite) ControllerOnConnectedBlock onConnectedHandler;
@property (readwrite) ControllerOnMessageBlock onMessageHandler;
@property (readwrite) ControllerOnErrorBlock onErrorHandler;
@property (readonly) chip::DeviceController::ChipDeviceController * cppController;
@property (readwrite) NSData * localKey;
@property (readwrite) NSData * peerKey;

@end

@implementation CHIPDeviceController

+ (CHIPDeviceController *)sharedController
{
    static CHIPDeviceController * controller = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        // initialize the device controller
        controller = [[CHIPDeviceController alloc] init];
    });
    return controller;
}

- (instancetype)init
{
    if (self = [super init]) {

        _lock = [[NSRecursiveLock alloc] init];

        _chipSelectQueue = dispatch_queue_create(CHIP_SELECT_QUEUE, DISPATCH_QUEUE_SERIAL);
        if (!_chipSelectQueue) {
            return nil;
        }

        _cppController = new chip::DeviceController::ChipDeviceController();
        if (!_cppController) {
            CHIP_LOG_ERROR("Error: couldn't create c++ controller");
            return nil;
        }

        if (CHIP_NO_ERROR != _cppController->Init(kLocalDeviceId)) {
            CHIP_LOG_ERROR("Error: couldn't initialize c++ controller");
            delete _cppController;
            _cppController = NULL;
            return nil;
        }
    }
    return self;
}

static void onConnected(
    chip::DeviceController::ChipDeviceController * cppController, chip::Transport::PeerConnectionState * state, void * appReqState)
{
    CHIPDeviceController * controller = (__bridge CHIPDeviceController *) appReqState;
    [controller _dispatchAsyncConnectBlock];
}

static void doKeyExchange(
    chip::DeviceController::ChipDeviceController * cppController, chip::Transport::PeerConnectionState * state, void * appReqState)
{
    CHIPDeviceController * controller = (__bridge CHIPDeviceController *) appReqState;
    [controller _manualKeyExchange:state];
}

static void onMessageReceived(
    chip::DeviceController::ChipDeviceController * deviceController, void * appReqState, chip::System::PacketBuffer * buffer)
{
    CHIPDeviceController * controller = (__bridge CHIPDeviceController *) appReqState;

    size_t data_len = buffer->DataLength();
    // convert to NSData and pass back to the application
    NSMutableData * dataBuffer = [[NSMutableData alloc] initWithBytes:buffer->Start() length:data_len];
    buffer = buffer->Next();

    while (buffer != NULL) {
        data_len = buffer->DataLength();
        [dataBuffer appendBytes:buffer->Start() length:data_len];
        buffer = buffer->Next();
    }

    [controller _dispatchAsyncMessageBlock:dataBuffer];

    // ignore unused variable
    (void) deviceController;
    chip::System::PacketBuffer::Free(buffer);
}

static void onInternalError(chip::DeviceController::ChipDeviceController * deviceController, void * appReqState, CHIP_ERROR error,
    const chip::IPPacketInfo * pi)
{
    CHIPDeviceController * controller = (__bridge CHIPDeviceController *) appReqState;
    [controller _dispatchAsyncErrorBlock:[CHIPError errorForCHIPErrorCode:error]];
}

- (void)_dispatchAsyncErrorBlock:(NSError *)error
{
    CHIP_LOG_METHOD_ENTRY();
    // to avoid retaining "self"
    ControllerOnErrorBlock onErrorHandler = self.onErrorHandler;

    dispatch_async(_appCallbackQueue, ^() {
        onErrorHandler(error);
    });
}

- (void)_dispatchAsyncMessageBlock:(NSData *)data
{
    CHIP_LOG_METHOD_ENTRY();
    // to avoid retaining "self"
    ControllerOnMessageBlock onMessageHandler = self.onMessageHandler;

    dispatch_async(_appCallbackQueue, ^() {
        onMessageHandler(data);
    });
}

- (void)_dispatchAsyncConnectBlock
{
    CHIP_LOG_METHOD_ENTRY();
    // to avoid retaining "self"
    ControllerOnConnectedBlock onConnectedHandler = self.onConnectedHandler;

    dispatch_async(_appCallbackQueue, ^() {
        onConnectedHandler();
    });
}

- (void)_manualKeyExchange:(chip::Transport::PeerConnectionState *)state
{
    [self.lock lock];
    const unsigned char * local_key_bytes = (const unsigned char *) [self.localKey bytes];
    const unsigned char * peer_key_bytes = (const unsigned char *) [self.peerKey bytes];

    CHIP_ERROR err
        = self.cppController->ManualKeyExchange(state, peer_key_bytes, self.peerKey.length, local_key_bytes, self.localKey.length);
    [self.lock unlock];

    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Failed to exchange keys");
        [self _dispatchAsyncErrorBlock:[CHIPError errorForCHIPErrorCode:err]];
    }
}

- (BOOL)connect:(NSString *)ipAddress
      local_key:(NSData *)local_key
       peer_key:(NSData *)peer_key
          error:(NSError * __autoreleasing *)error
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    // cache the keys before calling connect (because connect invokes the manual key exchange)
    self.localKey = local_key.copy;
    self.peerKey = peer_key.copy;

    [self.lock lock];
    chip::Inet::IPAddress addr;
    chip::Inet::IPAddress::FromString([ipAddress UTF8String], addr);
    err = self.cppController->ConnectDevice(
        kRemoteDeviceId, addr, (__bridge void *) self, doKeyExchange, onMessageReceived, onInternalError, CHIP_PORT);
    [self.lock unlock];

    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Error(%d): %@, connect failed", err, [CHIPError errorForCHIPErrorCode:err]);
        if (error) {
            *error = [CHIPError errorForCHIPErrorCode:err];
        }
        return NO;
    }

    // Start the IO pump
    dispatch_async(_chipSelectQueue, ^() {
        self.cppController->ServiceEvents();
    });
    return YES;
}

- (BOOL)connect:(NSString *)deviceName error:(NSError * __autoreleasing *)error
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    [self.lock lock];
    err = self.cppController->ConnectDevice(
        kRemoteDeviceId, [deviceName UTF8String], (__bridge void *) self, onConnected, onMessageReceived, onInternalError);
    [self.lock unlock];

    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Error(%d): %@, connect failed", err, [CHIPError errorForCHIPErrorCode:err]);
        if (error) {
            *error = [CHIPError errorForCHIPErrorCode:err];
        }
        return NO;
    }

    // Start the IO pump
    dispatch_async(_chipSelectQueue, ^() {
        self.cppController->ServiceEvents();
    });
    return YES;
}

- (AddressInfo *)getAddressInfo
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    chip::Transport::PeerAddress peerAddr = chip::Transport::PeerAddress::Uninitialized();
    [self.lock lock];
    err = self.cppController->PopulatePeerAddress(peerAddr);
    [self.lock unlock];
    chip::IPAddress ipAddr = peerAddr.GetIPAddress();
    uint16_t port = peerAddr.GetPort();

    if (err != CHIP_NO_ERROR) {
        return nil;
    }

    // ignore the unused port
    (void) port;
    // A buffer big enough to hold ipv4 and ipv6 addresses
    char ipAddrStr[64];
    ipAddr.ToString(ipAddrStr, sizeof(ipAddrStr));
    NSString * ipAddress = [NSString stringWithUTF8String:ipAddrStr];
    return [[AddressInfo alloc] initWithIP:ipAddress];
}

- (BOOL)sendMessage:(NSData *)message error:(NSError * __autoreleasing *)error
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    [self.lock lock];
    size_t messageLen = [message length];
    const void * messageChars = [message bytes];

    chip::System::PacketBuffer * buffer = chip::System::PacketBuffer::NewWithAvailableSize(messageLen);
    buffer->SetDataLength(messageLen);

    memcpy(buffer->Start(), messageChars, messageLen);
    err = self.cppController->SendMessage((__bridge void *) self, buffer);
    [self.lock unlock];

    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Error(%d): %@, send failed", err, [CHIPError errorForCHIPErrorCode:err]);
        if (error) {
            *error = [CHIPError errorForCHIPErrorCode:err];
        }
        return NO;
    }
    return YES;
}

- (BOOL)sendCHIPCommand:(uint32_t (^)(chip::System::PacketBuffer *, uint16_t))encodeCommandBlock
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    [self.lock lock];
    // FIXME: This needs a better buffersizing setup!
    static const size_t bufferSize = 1024;
    chip::System::PacketBuffer * buffer = chip::System::PacketBuffer::NewWithAvailableSize(bufferSize);

    uint32_t dataLength = encodeCommandBlock(buffer, (uint16_t) bufferSize);
    buffer->SetDataLength(dataLength);

    err = self.cppController->SendMessage((__bridge void *) self, buffer);
    [self.lock unlock];
    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Error(%d): %@, send failed", err, [CHIPError errorForCHIPErrorCode:err]);
        return NO;
    }
    return YES;
}

- (BOOL)sendOnCommand
{
    return [self sendCHIPCommand:^(chip::System::PacketBuffer * buffer, uint16_t bufferSize) {
        // Hardcode endpoint to 1 for now
        return encodeOnCommand(buffer->Start(), bufferSize, 1);
    }];
}

- (BOOL)sendOffCommand
{
    return [self sendCHIPCommand:^(chip::System::PacketBuffer * buffer, uint16_t bufferSize) {
        // Hardcode endpoint to 1 for now
        return encodeOffCommand(buffer->Start(), bufferSize, 1);
    }];
}

- (BOOL)sendToggleCommand
{
    return [self sendCHIPCommand:^(chip::System::PacketBuffer * buffer, uint16_t bufferSize) {
        // Hardcode endpoint to 1 for now
        return encodeToggleCommand(buffer->Start(), bufferSize, 1);
    }];
}

- (BOOL)disconnect:(NSError * __autoreleasing *)error
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    [self.lock lock];

    err = self.cppController->DisconnectDevice();
    [self.lock unlock];

    if (err != CHIP_NO_ERROR) {
        CHIP_LOG_ERROR("Error(%d): %@, disconnect failed", err, [CHIPError errorForCHIPErrorCode:err]);
        if (error) {
            *error = [CHIPError errorForCHIPErrorCode:err];
        }
        return NO;
    }
    return YES;
}

- (BOOL)isConnected
{
    bool isConnected = false;

    [self.lock lock];
    isConnected = self.cppController->IsConnected();
    [self.lock unlock];

    return isConnected ? YES : NO;
}

- (void)registerCallbacks:appCallbackQueue
              onConnected:(ControllerOnConnectedBlock)onConnected
                onMessage:(ControllerOnMessageBlock)onMessage
                  onError:(ControllerOnErrorBlock)onError
{
    self.appCallbackQueue = appCallbackQueue;
    self.onConnectedHandler = onConnected;
    self.onMessageHandler = onMessage;
    self.onErrorHandler = onError;
}

@end
