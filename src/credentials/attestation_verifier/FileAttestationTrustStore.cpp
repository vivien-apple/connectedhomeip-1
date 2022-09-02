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
#include "FileAttestationTrustStore.h"

#include <cstdio>
#include <cstring>
#include <string>

extern "C" {
#include <dirent.h>
}

namespace chip {
namespace Credentials {

namespace {
const char * GetFilenameExtension(const char * filename)
{
    const char * dot = strrchr(filename, '.');
    if (!dot || dot == filename)
    {
        return "";
    }
    return dot + 1;
}
} // namespace

FileAttestationTrustStore::FileAttestationTrustStore(const char * paaTrustStorePath, const char * cdTrustStorePath)
{
    VerifyOrReturn(paaTrustStorePath != nullptr || cdTrustStorePath != nullptr);

    if (paaTrustStorePath != nullptr)
    {
        LoadTrustStore(paaTrustStorePath, mPAADerCerts);
        VerifyOrReturn(paaCount());
    }

    if (cdTrustStorePath != nullptr)
    {
        LoadTrustStore(cdTrustStorePath, mCDDerCerts);
        VerifyOrReturn(cdCount());
    }

    mIsInitialized = true;
}

void FileAttestationTrustStore::LoadTrustStore(const char * trustStorePath,
                                               std::vector<std::array<uint8_t, kMaxDERCertLength>> & certs)
{
    DIR * dir;

    dir = opendir(trustStorePath);
    if (dir != nullptr)
    {
        // Nested directories are not handled.
        dirent * entry;
        while ((entry = readdir(dir)) != nullptr)
        {
            const char * fileExtension = GetFilenameExtension(entry->d_name);
            if (strncmp(fileExtension, "der", strlen("der")) == 0)
            {
                FILE * file;

                std::array<uint8_t, kMaxDERCertLength> certificate;
                std::string filename(trustStorePath);

                filename += std::string("/") + std::string(entry->d_name);

                file = fopen(filename.c_str(), "rb");
                if (file != nullptr)
                {
                    uint32_t certificateLength = fread(certificate.data(), sizeof(uint8_t), kMaxDERCertLength, file);
                    if (certificateLength > 0)
                    {
                        certs.push_back(certificate);
                    }
                    fclose(file);
                }
                else
                {
                    certs.clear();
                    break;
                }
            }
        }
        closedir(dir);
    }
}

FileAttestationTrustStore::~FileAttestationTrustStore()
{
    Cleanup();
}

void FileAttestationTrustStore::Cleanup()
{
    mPAADerCerts.clear();
    mCDDerCerts.clear();
    mIsInitialized = false;
}

CHIP_ERROR FileAttestationTrustStore::GetProductAttestationAuthorityCert(const ByteSpan & skid,
                                                                         MutableByteSpan & outPaaDerBuffer) const
{
    // If the constructor has not tried to initialize the PAA certificates database, return CHIP_ERROR_NOT_IMPLEMENTED to use the
    // testing trust store if the DefaultAttestationVerifier is in use.
    if (mIsInitialized && paaCount() == 0)
    {
        return CHIP_ERROR_NOT_IMPLEMENTED;
    }

    VerifyOrReturnError(!mPAADerCerts.empty(), CHIP_ERROR_CA_CERT_NOT_FOUND);
    VerifyOrReturnError(!skid.empty() && (skid.data() != nullptr), CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(skid.size() == Crypto::kSubjectKeyIdentifierLength, CHIP_ERROR_INVALID_ARGUMENT);

    for (auto candidate : mPAADerCerts)
    {
        uint8_t skidBuf[Crypto::kSubjectKeyIdentifierLength] = { 0 };
        MutableByteSpan candidateSkidSpan{ skidBuf };
        if (CHIP_NO_ERROR != Crypto::ExtractSKIDFromX509Cert(ByteSpan{ candidate.data(), candidate.size() }, candidateSkidSpan))
        {
            continue;
        }

        if (skid.data_equal(candidateSkidSpan))
        {
            // Found a match
            return CopySpanToMutableSpan(ByteSpan{ candidate.data(), candidate.size() }, outPaaDerBuffer);
        }
    }

    return CHIP_ERROR_CA_CERT_NOT_FOUND;
}

CHIP_ERROR FileAttestationTrustStore::GetCertificationDeclarationSigningKey(const ByteSpan & skid,
                                                                            Crypto::P256PublicKey & pubKey) const
{
    // If the constructor has not tried to initialize the certification declaration certificates database, return
    // CHIP_ERROR_NOT_IMPLEMENTED to use the testing trust store if the DefaultAttestationVerifier is in use.
    if (mIsInitialized && cdCount() == 0)
    {
        return CHIP_ERROR_NOT_IMPLEMENTED;
    }

    VerifyOrReturnError(!mCDDerCerts.empty(), CHIP_ERROR_CA_CERT_NOT_FOUND);
    VerifyOrReturnError(!skid.empty() && (skid.data() != nullptr), CHIP_ERROR_INVALID_ARGUMENT);
    VerifyOrReturnError(skid.size() == Crypto::kSubjectKeyIdentifierLength, CHIP_ERROR_INVALID_ARGUMENT);

    for (auto candidate : mCDDerCerts)
    {
        uint8_t skidBuf[Crypto::kSubjectKeyIdentifierLength] = { 0 };
        MutableByteSpan candidateSkidSpan{ skidBuf };
        VerifyOrReturnError(CHIP_NO_ERROR ==
                                Crypto::ExtractSKIDFromX509Cert(ByteSpan{ candidate.data(), candidate.size() }, candidateSkidSpan),
                            CHIP_ERROR_INTERNAL);

        if (skid.data_equal(candidateSkidSpan))
        {
            // Found a match
            return Crypto::ExtractPubkeyFromX509Cert(ByteSpan{ candidate.data(), candidate.size() }, pubKey);
        }
    }

    return CHIP_ERROR_CA_CERT_NOT_FOUND;
}

} // namespace Credentials
} // namespace chip
