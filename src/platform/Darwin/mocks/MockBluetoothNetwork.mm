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

#if !__has_feature(objc_arc)
#error This file must be compiled with ARC. Use -fobjc-arc flag (or convert project to ARC).
#endif

#import "MockBluetoothNetwork.h"
#import "MockBluetoothNetworkJSON.h"

#import <lib/support/logging/CHIPLogging.h>

NSString * const kCommandAdvertisementData = @"advertisementData";
NSString * const kCommandSubscribeCharacteristic = @"subscribeCharacteristic";
NSString * const kCommandUnsubscribeCharacteristic = @"unsubscribeCharacteristic";
NSString * const kCommandDiscoverServices = @"discoverServices";
NSString * const kCommandDiscoverCharacteristics = @"discoverCharacteristics";
NSString * const kCommandWriteValue = @"writeValue";
NSString * const kCommandUpdateValue = @"updateValue";

constexpr const char * kServerAddress = "127.0.0.1";

constexpr const char * kInvalid = "Invalid";
constexpr const char * kWaiting = "Waiting";
constexpr const char * kPreparing = "Preparing";
constexpr const char * kReady = "Ready";
constexpr const char * kFailed = "Failed";
constexpr const char * kCancelled = "Cancelled";
constexpr const char * kUnknown = "Unknown";

void LogListenerState(nw_listener_state_t state, nw_error_t error)
{
    const char * stateAsString = kUnknown;

    switch (state) {
    case nw_listener_state_invalid:
        stateAsString = kInvalid;
        break;
    case nw_listener_state_waiting:
        stateAsString = kWaiting;
        break;
    case nw_listener_state_failed:
        stateAsString = kFailed;
        break;
    case nw_listener_state_cancelled:
        stateAsString = kCancelled;
        break;
    case nw_listener_state_ready:
        stateAsString = kReady;
        break;
    }

    ChipLogDetail(Ble, "Listener: %s (error: %d)", stateAsString, nw_error_get_error_code(error));
}

void LogConnectionState(nw_connection_state_t state, nw_error_t error)
{
    const char * stateAsString = kUnknown;

    switch (state) {
    case nw_connection_state_invalid:
        stateAsString = kInvalid;
        break;
    case nw_connection_state_waiting:
        stateAsString = kWaiting;
        break;
    case nw_connection_state_preparing:
        stateAsString = kPreparing;
        break;
    case nw_connection_state_ready:
        stateAsString = kReady;
        break;
    case nw_connection_state_failed:
        stateAsString = kFailed;
        break;
    case nw_connection_state_cancelled:
        stateAsString = kCancelled;
        break;
    }

    ChipLogDetail(Ble, "Connection: %s (error: %d)", stateAsString, nw_error_get_error_code(error));
}

void MockBluetoothClient::SendCommand(NSDictionary * json)
{
    auto jsonData = [NSJSONSerialization dataWithJSONObject:json options:0 error:NULL];
    auto command = dispatch_data_create([jsonData bytes], [jsonData length], mDispatchQueue, DISPATCH_DATA_DESTRUCTOR_DEFAULT);

    nw_parameters_t parameters
        = nw_parameters_create_secure_udp(NW_PARAMETERS_DISABLE_PROTOCOL, NW_PARAMETERS_DEFAULT_CONFIGURATION);
    nw_endpoint_t endpoint = nw_endpoint_create_host(kServerAddress, mPort);

    nw_connection_t connection = nw_connection_create(endpoint, parameters);
    nw_connection_set_queue(connection, mDispatchQueue);

    nw_connection_set_state_changed_handler(connection, ^(nw_connection_state_t state, nw_error_t error) {
        LogConnectionState(state, error);
        if (state != nw_connection_state_ready) {
            return;
        }

        nw_connection_send(connection, command, NW_CONNECTION_DEFAULT_MESSAGE_CONTEXT, true, ^(nw_error_t sendError) {
            if (sendError != nil) {
                NSLog(@"Error sending command: %@", sendError);
            }
            nw_connection_cancel(connection);
        });
    });

    nw_connection_start(connection);
}

void MockBluetoothClient::SendCommand(NSString * command)
{
    NSDictionary * json = @ {
        @"command" : command,
    };

    SendCommand(json);
}

void MockBluetoothClient::SendCommand(NSString * command, NSData * data)
{
    NSDictionary * json = @ {
        @"command" : command,
        @"data" : [JSONData toJSON:data],
    };

    SendCommand(json);
}

void MockBluetoothServer::Start()
{
    nw_parameters_t parameters
        = nw_parameters_create_secure_udp(NW_PARAMETERS_DISABLE_PROTOCOL, NW_PARAMETERS_DEFAULT_CONFIGURATION);

    nw_endpoint_t endpoint = nw_endpoint_create_host(kServerAddress, mPort);
    nw_parameters_set_local_endpoint(parameters, endpoint);

    mListener = nw_listener_create(parameters);
    nw_listener_set_queue(mListener, mDispatchQueue);

    nw_listener_set_state_changed_handler(mListener, ^(nw_listener_state_t state, nw_error_t error) {
        LogListenerState(state, error);
        if (state == nw_listener_state_invalid) {
            nw_listener_cancel(mListener);
        }
    });

    nw_listener_set_new_connection_handler(mListener, ^(nw_connection_t connection) {
        nw_connection_receive_completion_t messageHandler;
        messageHandler = ^(dispatch_data_t content, nw_content_context_t context, bool is_complete, nw_error_t error) {
            if (error == nil && content != nil) {
                dispatch_data_apply(content, ^bool(dispatch_data_t data, size_t offset, const void * bytes, size_t len) {
                    NSData * jsonData = [NSData dataWithBytes:bytes length:len];
                    OnData(jsonData);
                    return true;
                });
            }
            nw_connection_receive_message(connection, messageHandler);
        };

        nw_connection_set_state_changed_handler(connection, ^(nw_connection_state_t state, nw_error_t error) {
            LogConnectionState(state, error);
            if (state == nw_connection_state_invalid) {
                nw_connection_cancel(connection);
            } else if (state == nw_connection_state_ready) {
                nw_connection_receive_message(connection, messageHandler);
            }
        });

        nw_connection_set_queue(connection, mDispatchQueue);
        nw_connection_start(connection);
    });

    nw_listener_start(mListener);
}

void MockBluetoothServer::Stop() { nw_listener_cancel(mListener); }

// CentralManagerServer

void CentralManagerServer::OnData(NSData * jsonData)
{
    NSDictionary * json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];
    NSString * command = json[@"command"];

    if ([command isEqual:kCommandAdvertisementData]) {
        auto RSSI = [NSNumber numberWithUnsignedInt:-arc4random_uniform(100)];
        [mDelegate onAdvertisementDataResponse:[JSONAdvertisement fromJSON:[JSONData fromJSON:json[@"data"]]] RSSI:RSSI];
    } else if ([command isEqual:kCommandDiscoverServices]) {
        [mDelegate onDiscoverServicesResponse:[JSONServices fromJSON:[JSONData fromJSON:json[@"data"]]]];
    } else if ([command isEqual:kCommandDiscoverCharacteristics]) {
        [mDelegate onDiscoverCharacteristicsResponse:[JSONCharacteristics fromJSON:[JSONData fromJSON:json[@"data"]]]];
    } else if ([command isEqual:kCommandWriteValue]) {
        [mDelegate onWriteValueResponse];
    } else if ([command isEqual:kCommandUpdateValue]) {
        [mDelegate onUpdateValue:[JSONData fromJSON:json[@"data"]]];
    }
}

// CentralManagerClient

void CentralManagerClient::UpdateValue(NSData * value) { SendCommand(kCommandUpdateValue, value); }

void CentralManagerClient::AdvertisementData(NSDictionary<NSString *, id> * advertisementData)
{
    SendCommand(kCommandAdvertisementData, [JSONAdvertisement toJSON:advertisementData]);
}

void CentralManagerClient::DiscoverServices(NSArray<CBService *> * services)
{
    SendCommand(kCommandDiscoverServices, [JSONServices toJSON:services]);
}

void CentralManagerClient::DiscoverCharacteristics(NSArray<CBCharacteristic *> * characteristics)
{
    SendCommand(kCommandDiscoverCharacteristics, [JSONCharacteristics toJSON:characteristics]);
}

void CentralManagerClient::WriteResponse() { SendCommand(kCommandWriteValue); }

// PeripheralManagerServer

void PeripheralManagerServer::OnData(NSData * jsonData)
{
    NSDictionary * json = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:nil];
    NSString * command = json[@"command"];
    if ([command isEqual:kCommandAdvertisementData]) {
        [mDelegate onAdvertisementDataRequest];
    } else if ([command isEqual:kCommandDiscoverServices]) {
        [mDelegate onDiscoverServicesRequest];
    } else if ([command isEqual:kCommandDiscoverCharacteristics]) {
        [mDelegate onDiscoverCharacteristicsRequest];
    } else if ([command isEqual:kCommandSubscribeCharacteristic]) {
        [mDelegate onSubscribeCharacteristicRequest];
    } else if ([command isEqual:kCommandUnsubscribeCharacteristic]) {
        [mDelegate onUnsubscribeCharacteristicRequest];
    } else if ([command isEqual:kCommandWriteValue]) {
        [mDelegate onWriteValueRequest:[JSONData fromJSON:json[@"data"]]];
    }
}

// PeripheralManagerClient

void PeripheralManagerClient::ScanAdvertisement() { SendCommand(kCommandAdvertisementData); }

void PeripheralManagerClient::DiscoverServices(NSArray<CBUUID *> * uuids) { SendCommand(kCommandDiscoverServices); }

void PeripheralManagerClient::DiscoverCharacteristics(NSArray<CBUUID *> * uuids, CBService * service)
{
    SendCommand(kCommandDiscoverCharacteristics);
}

void PeripheralManagerClient::WriteValue(CBCharacteristic * characteristic, NSData * value)
{
    SendCommand(kCommandWriteValue, value);
}

void PeripheralManagerClient::SubscribeValue(CBCharacteristic * characteristic) { SendCommand(kCommandSubscribeCharacteristic); }

void PeripheralManagerClient::UnsubscribeValue(CBCharacteristic * characteristic)
{
    SendCommand(kCommandUnsubscribeCharacteristic);
}
