#    Copyright (c) 2022 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the 'License');
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an 'AS IS' BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

import sys
import time


class YamlClusters:
    __clusters: None

    def __init__(self):
        self.__clusters = [
            DelayCommandsCluster(),
            LogCommandsCluster(),
            SystemCommandsCluster()
        ]

    def has(self, data):
        return self.__get_cluster(data) != None

    async def execute(self, data):
        cluster = self.__get_cluster(data)
        if cluster:
            return await cluster.do_command(data)
        return 'failure'

    def __get_cluster(self, request):
        for cluster in self.__clusters:
            if request.cluster == cluster.name and cluster.is_supported(request.command):
                return cluster
        return None


class DelayCommandsCluster:
    name = 'DelayCommands'

    async def do_command(self, request):
        if request.command == 'WaitForMs':
            for argument in request.arguments['values']:
                if argument['name'] == 'ms':
                    ms = argument['value']
                    sys.stdout.flush()
                    time.sleep(ms/1000)
                    return 'success'

        return 'failure'

    def is_supported(self, command_name):
        if command_name == 'WaitForMs':
            return True

        return False


class LogCommandsCluster:
    name = 'LogCommands'

    async def do_command(self, request):
        if request.command == 'UserPrompt':
            # TODO Do nothing for the moment...
            return 'success'

        return 'failure'

    def is_supported(self, command_name):
        if command_name == 'UserPrompt':
            return True

        return False


class SystemCommandsCluster:
    name = 'SystemCommands'

    async def do_command(self, request):
        if request.command == 'Reboot':
            # TODO Do nothing for the moment...
            return 'success'

        return 'failure'

    def is_supported(self, command_name):
        if command_name == 'Reboot':
            return True

        return False
