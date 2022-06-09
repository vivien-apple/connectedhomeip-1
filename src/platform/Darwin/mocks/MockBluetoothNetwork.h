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

#import <CoreBluetooth/CoreBluetooth.h>
#import <Network/Network.h>

@protocol PeripheralManagerServerDelegate <NSObject>
- (void)onAdvertisementDataRequest;
- (void)onDiscoverServicesRequest;
- (void)onDiscoverCharacteristicsRequest;
- (void)onSubscribeCharacteristicRequest;
- (void)onUnsubscribeCharacteristicRequest;
- (void)onWriteValueRequest:(NSData *)data;
@end

@protocol CentralManagerServerDelegate <NSObject>
- (void)onAdvertisementDataResponse:(NSDictionary<NSString *, id> *)advertisementData RSSI:(NSNumber *)RSSI;
- (void)onDiscoverServicesResponse:(NSArray<CBService *> *)services;
- (void)onDiscoverCharacteristicsResponse:(NSArray<CBCharacteristic *> *)characteristics;
- (void)onWriteValueResponse;
- (void)onUpdateValue:(NSData *)value;
@end

class MockBluetoothServer {
public:
    MockBluetoothServer(const char * port)
        : mPort(port) {};
    void SetDispatchQueue(dispatch_queue_t queue) { mDispatchQueue = queue; };
    void SetDelegate(id delegate) { mDelegate = delegate; };

    void Start();
    void Stop();
    virtual void OnData(NSData * data) = 0;

protected:
    dispatch_queue_t mDispatchQueue;
    __weak id mDelegate;

private:
    nw_listener_t mListener;
    const char * mPort;
};

class MockBluetoothClient {
public:
    MockBluetoothClient(const char * port)
        : mPort(port) {};

    void SetDispatchQueue(dispatch_queue_t queue) { mDispatchQueue = queue; };
    void SetDelegate(id delegate) { mDelegate = delegate; };

protected:
    dispatch_queue_t mDispatchQueue;
    __weak id mDelegate;

    void SendCommand(NSString * command);
    void SendCommand(NSString * command, NSData * data);

private:
    const char * mPort;

    void SendCommand(NSDictionary * json);
};

class CentralManagerServer : public MockBluetoothServer {
public:
    CentralManagerServer()
        : MockBluetoothServer("8091") {};

    virtual ~CentralManagerServer() {};

    void OnData(NSData *) override;
};

class CentralManagerClient : public MockBluetoothClient {
public:
    CentralManagerClient()
        : MockBluetoothClient("8091") {};

    virtual ~CentralManagerClient() {};

    void UpdateValue(NSData * value);
    void AdvertisementData(NSDictionary<NSString *, id> * advertisementData);
    void DiscoverServices(NSArray<CBService *> * services);
    void DiscoverCharacteristics(NSArray<CBCharacteristic *> * characteristics);
    void WriteResponse();
};

class PeripheralManagerServer : public MockBluetoothServer {
public:
    PeripheralManagerServer()
        : MockBluetoothServer("8090") {};

    virtual ~PeripheralManagerServer() {};

    void OnData(NSData *) override;
};

class PeripheralManagerClient : public MockBluetoothClient {
public:
    PeripheralManagerClient()
        : MockBluetoothClient("8090") {};

    virtual ~PeripheralManagerClient() {};

    void ScanAdvertisement();
    void DiscoverServices(NSArray<CBUUID *> * serviceUUIDs);
    void DiscoverCharacteristics(NSArray<CBUUID *> * uuids, CBService * service);
    void WriteValue(CBCharacteristic * characteristic, NSData * data);
    void SubscribeValue(CBCharacteristic * characteristic);
    void UnsubscribeValue(CBCharacteristic * characteristic);
};
