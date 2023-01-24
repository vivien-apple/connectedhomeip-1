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

import copy
import time
from dataclasses import dataclass, field

from .definitions import SpecDefinitions
from .hooks import TestParserHooks
from .parser import TestParser, TestParserConfig


@dataclass
class TestParserBuilderOptions:
    stop_on_error: bool = True


@dataclass
class TestParserBuilderConfig:
    tests: list[str] = field(default_factory=list)
    parser_config: TestParserConfig = TestParserConfig()
    hooks: TestParserHooks = TestParserHooks()
    options: TestParserBuilderOptions = TestParserBuilderOptions()


class TestParserBuilder:
    def __init__(self, config: TestParserBuilderConfig = TestParserBuilderConfig()):
        self.__tests = copy.copy(config.tests)
        self.__config = config
        self.__duration = 0
        self.__done = False

    def __iter__(self):
        self.__config.hooks.start(len(self.__tests))
        return self

    def __next__(self):  # Python 2: def next(self)
        if len(self.__tests):
            return self.__get_test_parser(self.__tests.pop(0))

        if not self.__done:
            self.__config.hooks.stop(round(self.__duration))
        self.__done = True

        raise StopIteration

    def __get_test_parser(self, test_file):
        start = time.time()

        parser = None
        exception = None
        try:
            self.__config.hooks.test_start(test_file)
            parser = TestParser(test_file, self.__config.parser_config)
        except Exception as e:
            exception = e

        duration = round((time.time() - start) * 1000, 0)
        self.__duration += duration
        if exception:
            self.__config.hooks.test_failure(exception, duration)
            if self.__config.options.stop_on_error:
                raise StopIteration
            return None

        self.__config.hooks.test_success(duration)
        return parser
