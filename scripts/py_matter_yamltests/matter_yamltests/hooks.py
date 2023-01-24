#
#    Copyright (c) 2023 Project CHIP Authors
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

from .errors import TestStepError


class TestParserHooks():
    def start(self, count: int):
        """ This method is called when the parser starts parsing a set of files."""
        pass

    def stop(self, duration: int):
        """ This method is called when the parser is done parsing a set of files."""
        pass

    def test_start(self, name: str):
        """ This method is called when the parser starts parsing a single file."""
        pass

    def test_failure(self, exception: TestStepError, duration: int):
        """ This method is called when parsing a single file fails."""
        pass

    def test_success(self, duration: int):
        """ This method is called when parsing a single file succeeds."""
        pass


class TestRunnerHooks():
    def start(self, count: int):
        """ This method is called when the runner starts running a set of tests."""
        pass

    def stop(self, duration: int):
        """ This method is called when the runner is done running a set of tests."""
        pass

    def test_start(self, name: str, count: int):
        """ This method is called when the runner starts running a single test."""
        pass

    def test_stop(self, exception: Exception, duration: int):
        """ This method is called when the runner is done running a single test."""
        pass

    def step_skipped(self, name: str):
        """ This method is called when running a step is skipped."""
        pass

    def step_start(self, name: str):
        """ This method is called when the runner starts running a step from the test."""
        pass

    def step_success(self, logger, logs, duration: int):
        """ This method is called when running a step succeeds."""
        pass

    def step_failure(self, logger, logs, duration: int, expected, received):
        """ This method is called when running a step fails."""
        pass

    def step_unknown(self):
        """ This method is called when the result of running a step is unknown. For example during a dry-run."""
        pass


class WebSocketRunnerHooks():
    def connecting(self, url: str):
        """ This method is called when the websocket is attempting to connect to a remote."""
        pass

    def abort(self, url: str):
        """ This method is called when the websocket connection fails and will not be retried."""
        pass

    def success(self, duration: int):
        """ This method is called when the websocket connection is established."""
        pass

    def failure(self, duration: int):
        """ This method is called when the websocket connection fails and will be retried."""
        pass

    def retry(self, interval_between_retries_in_seconds: int):
        """ This method is called when the websocket connection will be retried in the given interval."""
        pass
