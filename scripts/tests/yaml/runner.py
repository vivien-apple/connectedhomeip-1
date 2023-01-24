#!/usr/bin/env -S python3 -B

# Copyright (c) 2023 Project CHIP Authors
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

from relative_importer import *  # isort: split

import sys
import traceback

import click
from matter_yamltests.definitions import SpecDefinitions, SpecDefinitionsFromPaths
from matter_yamltests.parser import TestParser, TestParserConfig
from matter_yamltests.parser_builder import TestParserBuilderConfig, TestParserBuilderOptions
from matter_yamltests.parser_config import TestConfigParser
from matter_yamltests.pseudo_clusters.pseudo_clusters import PseudoClusters, get_default_pseudo_clusters
from matter_yamltests.runner import TestRunner, TestRunnerConfig, TestRunnerOptions
from matter_yamltests.websocket_runner import WebSocketRunner, WebSocketRunnerConfig
from paths_finder import PathsFinder
from tests_finder import TestsFinder
from tests_logger import TestParserLogger, TestRunnerLogger, WebSocketRunnerLogger

#
# Options
#


def test_parser_options(f):
    f = click.option("--configuration_name", type=str, required=True, show_default=True,
                     default=TestsFinder.get_default_configuration_name(), help='Name of the collection configuration json file to use.')(f)
    f = click.option("--test_directory", type=click.Path(exists=True), required=True, show_default=True,
                     default=TestsFinder.get_default_directory(), help='Path to the directory containing tests.')(f)
    f = click.option("--specifications_paths", type=click.Path(), required=False, show_default=True,
                     default="src/app/zap-templates/zcl/data-model/chip/*.xml", help='Path to a set of files containing clusters definitions.')(f)
    f = click.option("--PICS", type=click.Path(exists=True), required=False, show_default=True,
                     default='src/app/tests/suites/certification/ci-pics-values', help='Path to the PICS file to use.')(f)
    f = click.option("--stop_on_error", type=bool, required=False, show_default=True,
                     default=True, help='Stop parsing on first error.')(f)
    return f


def test_runner_options(f):
    f = click.option("--adapter", type=str, default=None, required='True',
                     show_default=True, help='The adapter to run the test with.')(f)
    f = click.option("--stop_on_error", type=bool, default=True, show_default=True,
                     help='Stop the test suite on first error.')(f)
    f = click.option("--stop_on_warning", type=bool, default=False, show_default=True,
                     help='Stop the test suite on first warning.')(f)
    f = click.option("--stop_at_number", type=int, default=-1, show_default=True,
                     help='Stop the the test suite at the specified test number.')(f)
    f = click.option("--show_adapter_logs", type=bool, default=False, show_default=True,
                     help='Show additional logs provided by the adapter.')(f)
    f = click.option("--show_adapter_logs_on_error", type=bool, default=True, show_default=True,
                     help='Show additional logs provided by the adapter on error.')(f)
    return f


def websocket_runner_options(f):
    f = click.option("--server_address", type=str, default="localhost", show_default=True,
                     help='The websocket server address to connect to.')(f)
    f = click.option("--server_port", type=int, default=9002, show_default=True,
                     help='The websocket server port to connect to.')(f)
    f = click.option("--server_name", type=str, default=None,
                     required=False, help='Name of a websocket server to run at launch.')(f)
    f = click.option("--server_path", type=click.Path(exists=True), default=None,
                     required=False, help='Path to a websocket server to run at launch.')(f)
    f = click.option("--server_arguments", type=str, default=None, required=False,
                     help='Optional arguments to pass to the websocket server at launch.')(f)
    return f


pass_parser_builder_config = click.make_pass_decorator(TestParserBuilderConfig)


class YamlTestParserGroup(click.Group):
    def format_options(self, ctx, formatter):
        """Writes all the options into the formatter if they exist."""
        if ctx.custom_options:
            params_copy = self.params
            non_custom_params = list(filter(lambda x: x.name not in ctx.custom_options, self.params))
            custom_params = list(filter(lambda x: x.name in ctx.custom_options, self.params))

            self.params = non_custom_params
            super().format_options(ctx, formatter)
            self.params = params_copy

            opts = []
            for param in custom_params:
                rv = param.get_help_record(ctx)
                if rv is not None:
                    opts.append(rv)

            if opts:
                custom_section_title = ctx.params.get('test_name') + ' Options'
                with formatter.section(custom_section_title):
                    formatter.write_dl(opts)
        else:
            super().format_options(ctx, formatter)

    def parse_args(self, ctx, args):
        # Run the parser on the supported arguments first in order to get a
        # the necessary informations to get read the test file and add
        # the potential additional arguments.
        supported_args = self.__remove_custom_args(ctx, args)
        super().parse_args(ctx, supported_args)

        # Add the potential new arguments to the list of supported params and
        # run the parser a new time to read those.
        self.__add_custom_params(ctx)
        return super().parse_args(ctx, args)

    def __remove_custom_args(self, ctx, args):
        # Remove all the unsupported options from the command line string.
        params_name = [param.name for param in self.params]

        supported_args = []
        skipArgument = False
        for arg in args:
            if arg.startswith('--') and arg not in params_name:
                skipArgument = True
                continue
            if skipArgument:
                skipArgument = False
                continue
            supported_args.append(arg)

        return supported_args

    def __add_custom_params(self, ctx):
        tests_finder = TestsFinder(ctx.params.get('test_directory'), ctx.params.get('configuration_name'))
        tests = tests_finder.get(ctx.params.get('test_name'))

        custom_options = {}

        # There is a single test, extract the custom config
        if len(tests) == 1:
            try:
                custom_options = TestConfigParser.get_config(tests[0])
            except Exception as e:
                pass
            for key, value in custom_options.items():
                param = click.Option(['--' + key], required=False, default=value, show_default=True)
                # click converts parameter name to lowercase internally, so we need to override
                # this behavior in order to override the correct key.
                param.name = key
                self.params.append(param)

        ctx.custom_options = custom_options


CONTEXT_SETTINGS = dict(
    default_map={
        'chiptool': {
            'adapter': 'matter_chip_tool_adapter.adapter',
            'server_name': 'chip-tool',
            'server_arguments': 'interactive server',
        },
        'app1': {
            'test_directory': 'examples/placeholder/linux/apps/app1',
            'adapter': 'matter_placeholder_adapter.adapter',
            'server_name': 'chip-app1',
            'server_arguments': '--interactive',
        },
        'app2': {
            'test_directory': 'examples/placeholder/linux/apps/app2',
            'adapter': 'matter_placeholder_adapter.adapter',
            'server_name': 'chip-app2',
            'server_arguments': '--interactive',
        },
    },
    max_content_width=120,
)


@click.group(cls=YamlTestParserGroup, context_settings=CONTEXT_SETTINGS)
@click.argument('test_name')
@test_parser_options
@click.pass_context
def runner_base(ctx, test_directory: str, test_name: str, configuration_name: str, pics: str, specifications_paths: str, stop_on_error: bool, **kwargs):
    specifications = SpecDefinitionsFromPaths(specifications_paths.split(','), get_default_pseudo_clusters())
    tests_finder = TestsFinder(test_directory, configuration_name)

    parser_config = TestParserConfig(pics, specifications, kwargs)
    parser_builder_config = TestParserBuilderConfig(tests_finder.get(test_name), parser_config, hooks=TestParserLogger())
    parser_builder_config.options.stop_on_error = stop_on_error
    while ctx:
        ctx.obj = parser_builder_config
        ctx = ctx.parent


@runner_base.command()
@pass_parser_builder_config
def parse(parser_builder_config: TestParserBuilderConfig):
    """Parse the test suite."""
    runner_config = None

    runner = TestRunner()
    return runner.run(parser_builder_config, runner_config)


@runner_base.command()
@pass_parser_builder_config
def dry_run(parser_builder_config: TestParserBuilderConfig):
    """Simulate a run of the test suite."""
    runner_config = TestRunnerConfig(hooks=TestRunnerLogger())

    runner = TestRunner()
    return runner.run(parser_builder_config, runner_config)


@runner_base.command()
@test_runner_options
@pass_parser_builder_config
def run(parser_builder_config: TestParserBuilderConfig, adapter: str, stop_on_error: bool, stop_on_warning: bool, stop_at_number: int, show_adapter_logs: bool, show_adapter_logs_on_error: bool):
    """Run the test suite."""
    adapter = __import__(adapter, fromlist=[None]).Adapter(parser_builder_config.parser_config.definitions)
    runner_options = TestRunnerOptions(stop_on_error, stop_on_warning, stop_at_number)
    runner_hooks = TestRunnerLogger(show_adapter_logs, show_adapter_logs_on_error)
    runner_config = TestRunnerConfig(adapter, get_default_pseudo_clusters(), runner_options, runner_hooks)

    runner = TestRunner()
    return runner.run(parser_builder_config, runner_config)


@runner_base.command()
@test_runner_options
@websocket_runner_options
@pass_parser_builder_config
def websocket(parser_builder_config: TestParserBuilderConfig, adapter: str, stop_on_error: bool, stop_on_warning: bool, stop_at_number: int, show_adapter_logs: bool, show_adapter_logs_on_error: bool, server_address: str, server_port: int, server_path: str, server_name: str, server_arguments: str):
    """Run the test suite using websockets."""
    adapter = __import__(adapter, fromlist=[None]).Adapter(parser_builder_config.parser_config.definitions)
    runner_options = TestRunnerOptions(stop_on_error, stop_on_warning, stop_at_number)
    runner_hooks = TestRunnerLogger(show_adapter_logs, show_adapter_logs_on_error)
    runner_config = TestRunnerConfig(adapter, get_default_pseudo_clusters(), runner_options, runner_hooks)

    if server_path is None and server_name:
        paths_finder = PathsFinder()
        server_path = paths_finder.get(server_name)

    websocket_runner_hooks = WebSocketRunnerLogger()
    websocket_runner_config = WebSocketRunnerConfig(
        server_address, server_port, server_path, server_arguments, websocket_runner_hooks)

    runner = WebSocketRunner(websocket_runner_config)
    return runner.run(parser_builder_config, runner_config)


@runner_base.command()
@test_runner_options
@websocket_runner_options
@click.pass_context
def chiptool(ctx, *args, **kwargs):
    """Run the test suite using chip-tool."""
    return ctx.forward(websocket)


@runner_base.command()
@test_runner_options
@websocket_runner_options
@click.pass_context
def app1(ctx, *args, **kwargs):
    """Run the test suite using app1."""
    return ctx.forward(websocket)


@runner_base.command()
@test_runner_options
@websocket_runner_options
@click.pass_context
def app2(ctx, *args, **kwargs):
    """Run the test suite using app2."""
    return ctx.forward(websocket)


if __name__ == '__main__':
    success = False
    try:
        success = runner_base(standalone_mode=False)
    except:
        print('')
        traceback.print_exc()

    sys.exit(0 if success else 1)
