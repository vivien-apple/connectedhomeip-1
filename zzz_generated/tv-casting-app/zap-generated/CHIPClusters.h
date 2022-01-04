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

// Prevent multiple inclusion
#pragma once

#include <app-common/zap-generated/ids/Clusters.h>

#include <controller/CHIPCluster.h>

namespace chip {
namespace Controller {

class DLL_EXPORT AccountLoginCluster : public ClusterBase
{
public:
    AccountLoginCluster() : ClusterBase(app::Clusters::AccountLogin::Id) {}
    ~AccountLoginCluster() {}
};

class DLL_EXPORT ApplicationBasicCluster : public ClusterBase
{
public:
    ApplicationBasicCluster() : ClusterBase(app::Clusters::ApplicationBasic::Id) {}
    ~ApplicationBasicCluster() {}
};

class DLL_EXPORT ApplicationLauncherCluster : public ClusterBase
{
public:
    ApplicationLauncherCluster() : ClusterBase(app::Clusters::ApplicationLauncher::Id) {}
    ~ApplicationLauncherCluster() {}
};

class DLL_EXPORT AudioOutputCluster : public ClusterBase
{
public:
    AudioOutputCluster() : ClusterBase(app::Clusters::AudioOutput::Id) {}
    ~AudioOutputCluster() {}
};

class DLL_EXPORT ChannelCluster : public ClusterBase
{
public:
    ChannelCluster() : ClusterBase(app::Clusters::Channel::Id) {}
    ~ChannelCluster() {}
};

class DLL_EXPORT ContentLauncherCluster : public ClusterBase
{
public:
    ContentLauncherCluster() : ClusterBase(app::Clusters::ContentLauncher::Id) {}
    ~ContentLauncherCluster() {}
};

class DLL_EXPORT KeypadInputCluster : public ClusterBase
{
public:
    KeypadInputCluster() : ClusterBase(app::Clusters::KeypadInput::Id) {}
    ~KeypadInputCluster() {}
};

class DLL_EXPORT MediaInputCluster : public ClusterBase
{
public:
    MediaInputCluster() : ClusterBase(app::Clusters::MediaInput::Id) {}
    ~MediaInputCluster() {}
};

class DLL_EXPORT MediaPlaybackCluster : public ClusterBase
{
public:
    MediaPlaybackCluster() : ClusterBase(app::Clusters::MediaPlayback::Id) {}
    ~MediaPlaybackCluster() {}
};

class DLL_EXPORT TargetNavigatorCluster : public ClusterBase
{
public:
    TargetNavigatorCluster() : ClusterBase(app::Clusters::TargetNavigator::Id) {}
    ~TargetNavigatorCluster() {}
};

} // namespace Controller
} // namespace chip
