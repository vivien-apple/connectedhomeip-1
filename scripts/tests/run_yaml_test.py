#!/usr/bin/env -S python3 -B

# Copyright (c) 2022 Project CHIP Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import click
import asyncio
import websockets
import time
import traceback
import json

from yamltests.YamlParser import YamlParser
from yamltests.YamlClusters import YamlClusters
from yamltests.ClustersDefinitions import ClustersDefinitions

from yamltests.adapters.ChipTool import ChipToolAdapter

COLOR_GREEN = '\033[1;92m'
COLOR_RED = '\033[1;31m'
COLOR_YELLOW = '\033[1;33m'
COLOR_GRAY = '\033[0;37m'
COLOR_END = '\033[0m'

MARK_SUCCESS = COLOR_GREEN + u'\N{check mark}' + COLOR_END
MARK_FAILURE = COLOR_RED + u'\N{ballot x}' + COLOR_END
MARK_WARNING = COLOR_YELLOW + u'\N{warning sign}' + COLOR_END


@click.command()
@click.option("--test_file", type=click.Path(exists=True), required=True, default=None, help='Path to the test script to use.')
@click.option("--pics_file", type=click.Path(exists=True), required=False, default=None, help='Path to the PICS file to use.')
@click.option("--clusters_dir", type=click.Path(exists=True), required=False, default="src/app/zap-templates/zcl/data-model/", help='Path to the directory containing clusters definitions.')
@click.option("--server_address", type=str, default="localhost", show_default=True, help='The websocket server address to connect to.')
@click.option("--server_port", type=int, default=9002, show_default=True, help='The websocket server port to connect to.')
@click.option("--self_test", type=bool, default=False, show_default=True, help='Run the test suite against a stub. Useful for development.')
@click.option("--stop_on_error", type=bool, default=False, show_default=True, help='Stop the test suite on first error.')
@click.option("--stop_on_warning", type=bool, default=False, show_default=True, help='Stop the test suite on first warning.')
@click.option("--stop_at_number", type=int, default=-1, show_default=True, help='Stop the the test suite at the specified test number.')
def main(test_file: str, pics_file: str, clusters_dir: str, server_address: str, server_port: int, self_test: bool, stop_on_error: bool, stop_on_warning, stop_at_number: int):
    start = time.time()
    clusters_definitions = ClustersDefinitions(clusters_dir)
    print(f'Took {round((time.time() - start) * 1000, 2)}ms')

    yaml = YamlParser(test_file, pics_file, clusters_definitions)
    adapter = ChipToolAdapter(clusters_definitions)  # TODO Should be configurable
    local_clusters = YamlClusters()

    runner = YamlTestRunner() if self_test else WebSocketTest("ws://" + server_address + ":" + str(server_port))
    asyncio.run(runner.run(yaml, adapter, local_clusters, stop_on_error, stop_on_warning, stop_at_number))


class YamlTestRunner:
    async def start(self):
        return

    async def execute(self, request):
        return "failure"

    async def stop(self):
        return

    async def run(self, yaml, adapter, local_clusters, stop_on_error, stop_on_warning, stop_at_number):
        print(f'Running: "{yaml.name}" with {yaml.tests.count} tests')

        try:
            await self.start()

            successes = 0
            warnings = 0
            errors = 0

            for idx, request in enumerate(yaml.tests):
                print(f'\t\t{idx + 1}. Running {request.label}', end="")

                start = time.time()
                if local_clusters.has(request):
                    response = await local_clusters.execute(request)
                else:
                    response = adapter.decode(await self.execute(adapter.encode(request)))
                end = time.time()

                logger = request.check_response(response, yaml.config)

                duration = round((time.time() - start) * 1000, 2)
                state = MARK_SUCCESS if logger.is_success() else MARK_FAILURE
                print(f'\r{state} {duration}ms')

                for entry in logger.entries:
                    if entry.is_warning():
                        state = MARK_WARNING
                        color = ''
                    elif entry.is_error():
                        state = MARK_FAILURE
                        color = ''
                    else:
                        state = ' '  # Do not mark success to not make the output hard to read
                        color = COLOR_GRAY
                    print(f'\t\t{COLOR_GRAY}  {state} [{entry.category} check] {entry.message}{COLOR_END}')

                if logger.is_failure():
                    expected_response = self.__prepare_data_for_logging(request.response)
                    received_response = self.__prepare_data_for_logging(response)
                    expected_value = json.dumps(expected_response, sort_keys=True, indent=2, separators=(',', ': '))
                    received_value = json.dumps(received_response, sort_keys=True, indent=2, separators=(',', ': '))
                    print(f'Expected Response:')
                    print(expected_value)
                    print('\n')
                    print(f'Received Response:')
                    print(received_value)

                successes += logger.successes
                warnings += logger.warnings
                errors += logger.errors

                if logger.is_failure() and stop_on_error:
                    break

                if logger.warnings and stop_on_warning:
                    break

                if (idx + 1) == stop_at_number:
                    break

            if errors:
                state = MARK_FAILURE
            elif warnings:
                state = MARK_WARNING
            else:
                state = MARK_SUCCESS

            print(f'{state} Test finished with {successes} success, {errors} errors and {warnings} warnings')

            await self.stop()
        except:
            print('\n')
            print(traceback.format_exc())

    def __prepare_data_for_logging(self, data):
        if data is None or not type(data) is dict:
            return data

        result = {}
        for key, value in data.items():
            if isinstance(value, bytes):
                value = value.decode('unicode_escape')
            elif isinstance(value, list):
                value = [self.__prepare_data_for_logging(entry) for entry in value]
            elif isinstance(value, dict):
                value = self.__prepare_data_for_logging(value)
            result[key] = value
        return result


class WebSocketTest(YamlTestRunner):
    def __init__(self, ws_server_address):
        self.ws = None
        self.ws_server_address = ws_server_address

    async def start(self):
        self.ws = await websockets.connect(self.ws_server_address)

    async def execute(self, request):
        if self.ws:
            # If this is an empty request there is no need to pass it over the wire. Sometimes the test is just listening
            # for a report.
            if request:
                await self.ws.send(request)

            payloads = []
            while True:
                payload = await self.ws.recv()
                payloads.append(payload)
                # If no request has been made just quit right away on the first payload.
                # If a request has been sent 'success' or 'failure' will signal the end of it.
                if not request or payload == 'success' or payload == 'failure':
                    break
            return payloads
        return None

    async def stop(self):
        if self.ws:
            await self.ws.close()
            self.ws = None


if __name__ == '__main__':
    main()
