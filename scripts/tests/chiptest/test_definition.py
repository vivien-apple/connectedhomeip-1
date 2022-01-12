#
#    Copyright (c) 2021 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

import logging
import os
import time
from datetime import datetime
import typing
import threading

from enum import Enum, auto
from dataclasses import dataclass
from random import randrange
from xmlrpc.server import SimpleXMLRPCServer

TEST_NODE_ID = '0x12344321'


class TestTarget(Enum):
    ALL_CLUSTERS = auto()
    TV = auto()


@dataclass
class ApplicationPaths:
    chip_tool: typing.List[str]
    all_clusters_app: typing.List[str]
    tv_app: typing.List[str]


@dataclass
class CaptureLine:
    when: datetime
    source: str
    line: str


class ExecutionCapture:
    """
    Keeps track of output lines in a process, to help debug failures.
    """

    def __init__(self):
        self.lock = threading.Lock()
        self.captures = []

    def Log(self, source, line):
        with self.lock:
            self.captures.append(CaptureLine(
                when=datetime.now(),
                source=source,
                line=line.strip('\n')
            ))

    def LogContents(self):
        logging.error('================ CAPTURED LOG START ==================')
        with self.lock:
            for entry in self.captures:
                logging.error('%02d:%02d:%02d.%03d - %-10s: %s',
                              entry.when.hour,
                              entry.when.minute,
                              entry.when.second,
                              entry.when.microsecond/1000,
                              entry.source,
                              entry.line
                              )
        logging.error('================ CAPTURED LOG END ====================')

class Accessory:
    def __init__(self, runner, command):
        self.process = None
        self.runner  = runner
        self.command = command
        self.discriminator = str(randrange(1, 4096))
        self.rebooting = False

        self.__startXMLRPCServer()
        self.start()

    def start(self):
        process, outpipe, errpipe = self.__startServer(self.runner, self.command, self.discriminator);
        self.__waitForServerReady(outpipe)
        self.__updateSetUpCode(outpipe)
        self.process = process

        return True

    def stop(self):
        self.process.kill()
        return True

    def reboot(self):
        self.process.kill()
        self.rebooting = True
        self.start()
        self.rebooting = False 
        return True

    def poll(self):
        if self.rebooting:
          return None
        return self.process.poll()

    def __startServer(self, runner, command, discriminator):
        logging.debug(
            'Executing application under test with discriminator %s.' % discriminator)
        app_cmd = command + ['--discriminator', str(discriminator)]
        return runner.RunSubprocess(app_cmd, name='APP ', wait=False)

    def __waitForServerReady(self,outpipe):
        logging.debug('Waiting for server to listen.')
        start_time = time.time()
        server_is_listening = outpipe.CapturedLogContains("Server Listening")
        while not server_is_listening:
            if time.time() - start_time > 10:
                raise Exception('Timeout for server listening')
            time.sleep(0.1)
            server_is_listening = outpipe.CapturedLogContains("Server Listening")
        logging.debug('Server is listening. Can proceed.')


    def __updateSetUpCode(self, outpipe):
        qrLine = outpipe.FindLastMatchingLine('.*SetupQRCode: *\\[(.*)]')
        if not qrLine:
            raise Exception("Unable to find QR code")
        self.setupCode = qrLine.group(1)

    def __startXMLRPCServer(self):
        server = SimpleXMLRPCServer(('localhost', 8000), logRequests=True)

        server.register_function(self.start, 'start')
        server.register_function(self.stop, 'stop')
        server.register_function(self.reboot, 'reboot')

        #threading.Thread(target=server.serve_forever).start()

@dataclass
class TestDefinition:
    name: str
    run_name: str
    target: TestTarget

    def Run(self, runner, paths: ApplicationPaths):
        """Executes the given test case using the provided runner for execution."""
        runner.capture_delegate = ExecutionCapture()

        try:
            if self.target == TestTarget.ALL_CLUSTERS:
                app_cmd = paths.all_clusters_app
            elif self.target == TestTarget.TV:
                app_cmd = paths.tv_app
            else:
                raise Exception(
                    "Unknown test target - don't know which application to run")

            tool_cmd = paths.chip_tool
            if os.path.exists('/tmp/chip_tool_config.ini'):
                os.unlink('/tmp/chip_tool_config.ini')

            # Remove server all_clusters_app or tv_app storage, so it will be commissionable again
            if os.path.exists('/tmp/chip_kvs'):
                os.unlink('/tmp/chip_kvs')

            accessory = Accessory(runner, app_cmd)

            runner.RunSubprocess(tool_cmd + ['pairing', 'qrcode', TEST_NODE_ID, accessory.setupCode],
                                 name='PAIR', dependencies=[accessory])

            runner.RunSubprocess(tool_cmd + ['tests', self.run_name, TEST_NODE_ID],
                                 name='TEST', dependencies=[accessory])
        except:
            logging.error("!!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!!!")
            runner.capture_delegate.LogContents()
            raise
        finally:
            if accessory.process:
                accessory.process.kill()
