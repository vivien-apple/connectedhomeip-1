/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

// THIS FILE IS GENERATED BY ZAP

#pragma once

#include "TestCommand.h"

class Test_TC_DM_1_3_Simulated : public TestCommand
{
public:
    Test_TC_DM_1_3_Simulated() : TestCommand("Test_TC_DM_1_3_Simulated"), mTestIndex(0)
    {
        AddArgument("cluster", &mCluster);
        AddArgument("endpoint", 0, UINT16_MAX, &mEndpoint);
    }

    ~Test_TC_DM_1_3_Simulated() {}

    /////////// TestCommand Interface /////////
    void NextTest() override
    {
        CHIP_ERROR err = CHIP_NO_ERROR;

        if (0 == mTestIndex)
        {
            ChipLogProgress(chipTool, " **** Test Start: Test_TC_DM_1_3_Simulated\n");
        }

        if (mTestCount == mTestIndex)
        {
            ChipLogProgress(chipTool, " **** Test Complete: Test_TC_DM_1_3_Simulated\n");
            SetCommandExitStatus(CHIP_NO_ERROR);
            return;
        }

        Wait();

        // Ensure we increment mTestIndex before we start running the relevant
        // command.  That way if we lose the timeslice after we send the message
        // but before our function call returns, we won't end up with an
        // incorrect mTestIndex value observed when we get the response.
        switch (mTestIndex++)
        {
        case 0:
            ChipLogProgress(chipTool, " ***** Test Step 0 : Wait for the device to be commissioned\n");
            err = TestWaitForTheDeviceToBeCommissioned_0();
            break;
        case 1:
            ChipLogProgress(chipTool, " ***** Test Step 1 : Log OnOff Test Startup\n");
            err = TestLogOnOffTestStartup_1();
            break;
        case 2:
            ChipLogProgress(chipTool, " ***** Test Step 2 : Query Interaction Model Version\n");
            err = TestQueryInteractionModelVersion_2();
            break;
        case 3:
            ChipLogProgress(chipTool, " ***** Test Step 3 : Query Vendor Name\n");
            err = TestQueryVendorName_3();
            break;
        case 4:
            ChipLogProgress(chipTool, " ***** Test Step 4 : Query VendorID\n");
            err = TestQueryVendorID_4();
            break;
        case 5:
            ChipLogProgress(chipTool, " ***** Test Step 5 : Query Product Name\n");
            err = TestQueryProductName_5();
            break;
        case 6:
            ChipLogProgress(chipTool, " ***** Test Step 6 : Query ProductID\n");
            err = TestQueryProductID_6();
            break;
        case 7:
            ChipLogProgress(chipTool, " ***** Test Step 7 : Query Node Label\n");
            err = TestQueryNodeLabel_7();
            break;
        case 8:
            ChipLogProgress(chipTool, " ***** Test Step 8 : Query User Location\n");
            err = TestQueryUserLocation_8();
            break;
        case 9:
            ChipLogProgress(chipTool, " ***** Test Step 9 : Query HardwareVersion\n");
            err = TestQueryHardwareVersion_9();
            break;
        case 10:
            ChipLogProgress(chipTool, " ***** Test Step 10 : Query HardwareVersionString\n");
            err = TestQueryHardwareVersionString_10();
            break;
        case 11:
            ChipLogProgress(chipTool, " ***** Test Step 11 : Query SoftwareVersion\n");
            err = TestQuerySoftwareVersion_11();
            break;
        case 12:
            ChipLogProgress(chipTool, " ***** Test Step 12 : Query SoftwareVersionString\n");
            err = TestQuerySoftwareVersionString_12();
            break;
        case 13:
            ChipLogProgress(chipTool, " ***** Test Step 13 : Query ManufacturingDate\n");
            err = TestQueryManufacturingDate_13();
            break;
        case 14:
            ChipLogProgress(chipTool, " ***** Test Step 14 : Query PartNumber\n");
            err = TestQueryPartNumber_14();
            break;
        case 15:
            ChipLogProgress(chipTool, " ***** Test Step 15 : Query ProductURL\n");
            err = TestQueryProductURL_15();
            break;
        case 16:
            ChipLogProgress(chipTool, " ***** Test Step 16 : Query ProductLabel\n");
            err = TestQueryProductLabel_16();
            break;
        case 17:
            ChipLogProgress(chipTool, " ***** Test Step 17 : Query SerialNumber\n");
            err = TestQuerySerialNumber_17();
            break;
        case 18:
            ChipLogProgress(chipTool, " ***** Test Step 18 : Query LocalConfigDisabled\n");
            err = TestQueryLocalConfigDisabled_18();
            break;
        case 19:
            ChipLogProgress(chipTool, " ***** Test Step 19 : Query Reachable\n");
            err = TestQueryReachable_19();
            break;
        case 20:
            ChipLogProgress(chipTool, " ***** Test Step 20 : Query UniqueID\n");
            err = TestQueryUniqueID_20();
            break;
        }

        if (CHIP_NO_ERROR != err)
        {
            ChipLogError(chipTool, " ***** Test Failure: %s\n", chip::ErrorStr(err));
            SetCommandExitStatus(err);
        }
    }

private:
    std::atomic_uint16_t mTestIndex;
    const uint16_t mTestCount = 21;

    chip::Optional<chip::CharSpan> mCluster;
    chip::Optional<chip::EndpointId> mEndpoint;

    //
    // Tests methods
    //

    CHIP_ERROR TestWaitForTheDeviceToBeCommissioned_0()
    {
        SetIdentity(kIdentityAlpha);
        return WaitForCommissioning();
    }

    CHIP_ERROR TestLogOnOffTestStartup_1()
    {
        SetIdentity(kIdentityAlpha);
        return Log("*** Basic Cluster Tests Ready");
    }

    CHIP_ERROR TestQueryInteractionModelVersion_2()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool,
                     "[Endpoint: 0x%08x Cluster: Basic Attribute: InteractionModelVersion] Query Interaction Model Version",
                     endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::InteractionModelVersion::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryVendorName_3()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: VendorName] Query Vendor Name", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::VendorName::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryVendorID_4()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: VendorID] Query VendorID", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::VendorID::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryProductName_5()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: ProductName] Query Product Name", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::ProductName::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryProductID_6()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: ProductID] Query ProductID", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::ProductID::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryNodeLabel_7()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: NodeLabel] Query Node Label", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::NodeLabel::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryUserLocation_8()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: Location] Query User Location", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::Location::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryHardwareVersion_9()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: HardwareVersion] Query HardwareVersion", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::HardwareVersion::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryHardwareVersionString_10()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: HardwareVersionString] Query HardwareVersionString",
                     endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::HardwareVersionString::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQuerySoftwareVersion_11()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: SoftwareVersion] Query SoftwareVersion", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::SoftwareVersion::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQuerySoftwareVersionString_12()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: SoftwareVersionString] Query SoftwareVersionString",
                     endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::SoftwareVersionString::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryManufacturingDate_13()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: ManufacturingDate] Query ManufacturingDate", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::ManufacturingDate::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryPartNumber_14()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: PartNumber] Query PartNumber", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::PartNumber::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryProductURL_15()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: ProductURL] Query ProductURL", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::ProductURL::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryProductLabel_16()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: ProductLabel] Query ProductLabel", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::ProductLabel::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQuerySerialNumber_17()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: SerialNumber] Query SerialNumber", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::SerialNumber::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryLocalConfigDisabled_18()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: LocalConfigDisabled] Query LocalConfigDisabled",
                     endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::LocalConfigDisabled::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryReachable_19()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: Reachable] Query Reachable", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::Reachable::Id);
        return CHIP_NO_ERROR;
    }

    CHIP_ERROR TestQueryUniqueID_20()
    {
        const chip::EndpointId endpoint = mEndpoint.HasValue() ? mEndpoint.Value() : 0;
        ChipLogError(chipTool, "[Endpoint: 0x%08x Cluster: Basic Attribute: UniqueID] Query UniqueID", endpoint);

        ClearAttributeAndCommandPaths();
        mAttributePath = chip::app::ConcreteAttributePath(endpoint, chip::app::Clusters::Basic::Id,
                                                          chip::app::Clusters::Basic::Attributes::UniqueID::Id);
        return CHIP_NO_ERROR;
    }
};

std::unique_ptr<TestCommand> GetTestCommand(std::string testName)
{
    if (testName == "Test_TC_DM_1_3_Simulated")
    {
        return std::unique_ptr<Test_TC_DM_1_3_Simulated>(new Test_TC_DM_1_3_Simulated());
    }

    return nullptr;
}

void PrintTestCommands()
{
    ChipLogError(chipTool, "Supported commands:");
    ChipLogError(chipTool, "\t* Test_TC_DM_1_3_Simulated");
}
