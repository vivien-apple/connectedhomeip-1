/*
 *   Copyright (c) 2022 Project CHIP Authors
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

#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <lib/support/SafeInt.h>

class CustomArgumentParser
{
public:
    static CHIP_ERROR Put(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        if (value.isObject())
        {
            return CustomArgumentParser::PutObject(writer, tag, value);
        }

        if (value.isArray())
        {
            return CustomArgumentParser::PutArray(writer, tag, value);
        }

        if (value.isString())
        {
            if (IsOctetString(value))
            {
                return CustomArgumentParser::PutOctetString(writer, tag, value);
            }
            else if (IsUnsignedNumberPrefix(value))
            {
                return CustomArgumentParser::PutUnsignedFromString(writer, tag, value);
            }
            else if (IsSignedNumberPrefix(value))
            {
                return CustomArgumentParser::PutSignedFromString(writer, tag, value);
            }

            return CustomArgumentParser::PutCharString(writer, tag, value);
        }

        if (value.isNull())
        {
            return chip::app::DataModel::Encode(*writer, tag, chip::app::DataModel::Nullable<uint8_t>());
        }

        if (value.isBool())
        {
            return chip::app::DataModel::Encode(*writer, tag, value.asBool());
        }

        if (value.isUInt())
        {
            return chip::app::DataModel::Encode(*writer, tag, value.asLargestUInt());
        }

        if (value.isInt())
        {
            return chip::app::DataModel::Encode(*writer, tag, value.asLargestInt());
        }

        if (value.isNumeric())
        {
            return chip::app::DataModel::Encode(*writer, tag, value.asDouble());
        }

        return CHIP_ERROR_NOT_IMPLEMENTED;
    }

private:
    static CHIP_ERROR PutArray(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        chip::TLV::TLVType outer;
        ReturnErrorOnFailure(writer->StartContainer(tag, chip::TLV::kTLVType_Array, outer));

        Json::ArrayIndex size = value.size();

        for (Json::ArrayIndex i = 0; i < size; i++)
        {
            ReturnErrorOnFailure(CustomArgumentParser::Put(writer, chip::TLV::AnonymousTag(), value[i]));
        }

        return writer->EndContainer(outer);
    }

    static CHIP_ERROR PutObject(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        chip::TLV::TLVType outer;
        ReturnErrorOnFailure(writer->StartContainer(tag, chip::TLV::kTLVType_Structure, outer));

        for (auto const & id : value.getMemberNames())
        {
            auto index = std::stoul(id, nullptr, 0);
            VerifyOrReturnError(chip::CanCastTo<uint8_t>(index), CHIP_ERROR_INVALID_ARGUMENT);
            ReturnErrorOnFailure(CustomArgumentParser::Put(writer, chip::TLV::ContextTag(static_cast<uint8_t>(index)), value[id]));
        }

        return writer->EndContainer(outer);
    }

    static CHIP_ERROR PutOctetString(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        size_t size = strlen(value.asCString());
        VerifyOrReturnError(size % 2 == 0, CHIP_ERROR_INVALID_STRING_LENGTH);

        chip::Platform::ScopedMemoryBuffer<uint8_t> buffer;
        VerifyOrReturnError(buffer.Calloc(size / 2), CHIP_ERROR_NO_MEMORY);
        size_t octetCount = chip::Encoding::HexToBytes(value.asCString() + hexPrefixLen, size - hexPrefixLen, buffer.Get(),
                                                       (size - hexPrefixLen) / 2);
        VerifyOrReturnError(octetCount != 0, CHIP_ERROR_NO_MEMORY);

        return chip::app::DataModel::Encode(*writer, tag, chip::ByteSpan(buffer.Get(), octetCount));
    }

    static CHIP_ERROR PutCharString(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        size_t size = strlen(value.asCString());

        chip::Platform::ScopedMemoryBuffer<char> buffer;
        VerifyOrReturnError(buffer.Calloc(size), CHIP_ERROR_NO_MEMORY);
        strncpy(buffer.Get(), value.asCString(), size);

        return chip::app::DataModel::Encode(*writer, tag, chip::CharSpan(buffer.Get(), size));
    }

    static CHIP_ERROR PutUnsignedFromString(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        size_t size = strlen(value.asCString());
        char numberAsString[21];

        chip::Platform::ScopedMemoryBuffer<char> buffer;
        strncpy(numberAsString, value.asCString() + unsignedPrefixLen, size - unsignedPrefixLen);

        auto numberAsUint = std::stoull(numberAsString, nullptr, 0);
        return chip::app::DataModel::Encode(*writer, tag, numberAsUint);
    }

    static CHIP_ERROR PutSignedFromString(chip::TLV::TLVWriter * writer, chip::TLV::Tag tag, Json::Value & value)
    {
        size_t size = strlen(value.asCString());
        char numberAsString[21];

        chip::Platform::ScopedMemoryBuffer<char> buffer;
        strncpy(numberAsString, value.asCString() + signedPrefixLen, size - signedPrefixLen);

        auto numberAsInt = std::stoll(numberAsString, nullptr, 0);
        return chip::app::DataModel::Encode(*writer, tag, numberAsInt);
    }

    static bool IsOctetString(Json::Value & value) { return (strncmp(value.asCString(), hexPrefix, hexPrefixLen) == 0); }

    static bool IsUnsignedNumberPrefix(Json::Value & value)
    {
        return (strncmp(value.asCString(), unsignedPrefix, unsignedPrefixLen) == 0);
    }

    static bool IsSignedNumberPrefix(Json::Value & value)
    {
        return (strncmp(value.asCString(), signedPrefix, signedPrefixLen) == 0);
    }

    static constexpr char hexPrefix[]         = "hex:";
    static constexpr char signedPrefix[]      = "s:";
    static constexpr char unsignedPrefix[]    = "u:";
    static constexpr size_t hexPrefixLen      = ArraySize(hexPrefix) - 1;      // ignore null character
    static constexpr size_t signedPrefixLen   = ArraySize(signedPrefix) - 1;   // ignore null character
    static constexpr size_t unsignedPrefixLen = ArraySize(unsignedPrefix) - 1; // ignore null character
};

class CustomArgument
{
public:
    ~CustomArgument()
    {
        if (mData != nullptr)
        {
            chip::Platform::MemoryFree(mData);
        }
    }

    CHIP_ERROR Parse(const char * label, const char * json)
    {
        Json::Reader reader;
        Json::Value value;
        reader.parse(json, value);

        mData = static_cast<uint8_t *>(chip::Platform::MemoryCalloc(sizeof(uint8_t), mDataMaxLen));
        VerifyOrReturnError(mData != nullptr, CHIP_ERROR_NO_MEMORY);

        chip::TLV::TLVWriter writer;
        writer.Init(mData, mDataMaxLen);

        ReturnErrorOnFailure(CustomArgumentParser::Put(&writer, chip::TLV::AnonymousTag(), value));

        mDataLen = writer.GetLengthWritten();
        return writer.Finalize();
    }

    CHIP_ERROR Encode(chip::TLV::TLVWriter & writer, chip::TLV::Tag tag) const
    {
        chip::TLV::TLVReader reader;
        reader.Init(mData, mDataLen);
        reader.Next();

        return writer.CopyElement(tag, reader);
    }

private:
    uint8_t * mData                       = nullptr;
    uint32_t mDataLen                     = 0;
    static constexpr uint32_t mDataMaxLen = 4096;
};
