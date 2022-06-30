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

// pull together Matter headers
#import <Matter/CHIPAttributeCacheContainer.h>
#import <Matter/CHIPCluster.h>
#import <Matter/CHIPClustersObjc.h>
#import <Matter/CHIPCommandPayloadsObjc.h>
#import <Matter/CHIPCommissioningParameters.h>
#import <Matter/CHIPDevice.h>
#import <Matter/CHIPDeviceAttestationDelegate.h>
#import <Matter/CHIPDeviceController+XPC.h>
#import <Matter/CHIPDeviceController.h>
#import <Matter/CHIPDeviceControllerStartupParams.h>
#import <Matter/CHIPDevicePairingDelegate.h>
#import <Matter/CHIPError.h>
#import <Matter/CHIPKeypair.h>
#import <Matter/CHIPManualSetupPayloadParser.h>
#import <Matter/CHIPPersistentStorageDelegate.h>
#import <Matter/CHIPQRCodeSetupPayloadParser.h>
#import <Matter/CHIPSetupPayload.h>
#import <Matter/CHIPStructsObjc.h>
#import <Matter/CHIPThreadOperationalDataset.h>
#import <Matter/MTRCertificates.h>
#import <Matter/MatterClusterConstants.h>
#import <Matter/MatterControllerFactory.h>

#import <Foundation/Foundation.h>
//! Project version number for Matter.
FOUNDATION_EXPORT double MatterVersionNumber;

//! Project version string for Matter.
FOUNDATION_EXPORT const unsigned char MatterVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <Matter/PublicHeader.h>
