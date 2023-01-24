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

import asyncio
import time
from abc import ABC, abstractmethod
from dataclasses import dataclass

from .adapter import TestAdapter
from .hooks import TestRunnerHooks
from .parser import TestParser, TestParserConfig
from .parser_builder import TestParserBuilder, TestParserBuilderConfig
from .pseudo_clusters.pseudo_clusters import PseudoClusters


@dataclass
class TestRunnerOptions:
    stop_on_error: bool = True
    stop_on_warning: bool = False
    stop_at_number: int = -1


@dataclass
class TestRunnerConfig:
    adapter: TestAdapter = None
    test_clusters: PseudoClusters = PseudoClusters([])
    options: TestRunnerOptions = TestRunnerOptions()
    hooks: TestRunnerHooks = TestRunnerHooks()


class TestRunnerBase(ABC):
    @abstractmethod
    async def start(self):
        pass

    @abstractmethod
    async def stop(self):
        pass

    @abstractmethod
    async def execute(self, request):
        pass

    @abstractmethod
    def run(self, config: TestRunnerConfig):
        pass


class TestRunner(TestRunnerBase):
    async def start(self):
        return

    async def execute(self, request):
        return request

    async def stop(self):
        return

    def run(self, parser_builder_config: TestParserBuilderConfig, runner_config: TestRunnerConfig):
        if runner_config and runner_config.hooks:
            start = time.time()
            runner_config.hooks.start(len(parser_builder_config.tests))

        parser_builder = TestParserBuilder(parser_builder_config)
        for parser in parser_builder:
            if not parser or not runner_config:
                continue

            result = asyncio.run(self._run(parser, runner_config))
            if isinstance(result, Exception):
                raise (result)
            elif not result:
                return False

        if runner_config and runner_config.hooks:
            duration = round((time.time() - start) * 1000)
            runner_config.hooks.stop(duration)

        return True

    async def _run(self, parser: TestParser, config: TestRunnerConfig):
        status = True
        try:
            await self.start()

            hooks = config.hooks
            hooks.test_start(parser.name, parser.tests.count)

            test_duration = 0
            for idx, request in enumerate(parser.tests):
                if not request.is_pics_enabled:
                    hooks.step_skipped(request.label)
                    continue
                elif not config.adapter:
                    hooks.step_start(request.label)
                    hooks.step_unknown()
                    continue
                else:
                    hooks.step_start(request.label)

                start = time.time()
                if config.test_clusters.supports(request):
                    responses, logs = await config.test_clusters.execute(request)
                else:
                    responses, logs = config.adapter.decode(await self.execute(config.adapter.encode(request)))
                duration = round((time.time() - start) * 1000, 2)
                test_duration += duration

                logger = request.post_process_response(responses)

                if logger.is_failure():
                    hooks.step_failure(logger, logs, duration, request.responses, responses)
                else:
                    hooks.step_success(logger, logs, duration)

                if logger.is_failure() and config.options.stop_on_error:
                    status = False
                    break

                if logger.warnings and config.options.stop_on_warning:
                    status = False
                    break

                if (idx + 1) == config.options.stop_at_number:
                    break

            hooks.test_stop(round(test_duration))

        except Exception as exception:
            status = exception
        finally:
            await self.stop()
            return status
