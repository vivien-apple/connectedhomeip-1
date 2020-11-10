#!/usr/bin/env bash

#
# Copyright (c) 2020 Project CHIP Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set -e

SOURCE="${BASH_SOURCE[0]}"
SOURCE_DIR="$(cd -P "$(dirname "$SOURCE")" >/dev/null 2>&1 && pwd)"
REPO_DIR="$SOURCE_DIR/../../../"

chip_tool_dir=$REPO_DIR/examples/chip-tool
chip_app_lighting_dir=$REPO_DIR/examples/lighting-app/linux
chip_app_all_clusters_dir=$REPO_DIR/examples/all-clusters-app/linux

function build_chip_example() {
    # These files should be successfully compiled elsewhere.
    source "$REPO_DIR/scripts/activate.sh" >/dev/null
    set -x
    cd "$1"
    gn gen out/debug --args='bypass_rendezvous=true'
    run_ninja -C out/debug
    docker build -t $2 -f Dockerfile . 2>&1
    set +x
}

function main() {
    pushd .
    build_chip_example $chip_tool_dir chip_tool
    build_chip_example $chip_app_lighting_dir chip_server_lighting
    build_chip_example $chip_app_all_clusters_dir chip_server_all_clusters
    popd
    # Run lighting specific tests
    python3 "$SOURCE_DIR/test-lighting-on-off-cluster.py"

    # Run tests for the all-clusters demo app
    python3 "$SOURCE_DIR/test-on-off-cluster.py"
    python3 "$SOURCE_DIR/test-barrier-control-cluster.py"
    python3 "$SOURCE_DIR/test-color-control-cluster.py"
}

source "$SOURCE_DIR"/shell-helpers.sh
main
