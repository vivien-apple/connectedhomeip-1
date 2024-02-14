#
#    Copyright (c) 2022 Project CHIP Authors
#    All rights reserved.
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
#

# TODO Once yamltest is a proper self contained module we can move this file
# to a more appropriate spot. For now, having this file to do some quick checks
# is arguably better then no checks at all.

import io
import tempfile
import unittest
from unittest.mock import mock_open, patch

from matter_yamltests.definitions import ParseSource, SpecDefinitions
from matter_yamltests.parser import TestParser, TestParserConfig

simple_test_description = '''<?xml version="1.0"?>
  <configurator>
    <enum name="TestEnum" type="enum8">
      <cluster code="0x1234"/>
      <item name="A" value="0x0"/>
      <item name="B" value="0x1"/>
      <item name="C" value="0x2"/>
    </enum>

    <struct name="TestStruct">
        <cluster code="0x1234"/>
        <item name="a" type="boolean"/>
    </struct>

    <cluster>
      <name>Test</name>
      <code>0x1234</code>

      <command source="client" code="1" name="test"></command>
    </cluster>
  </configurator>
'''

simple_test_yaml = '''
name: Test Cluster Tests

config:
    nodeId: 0x12344321
    cluster: "Test"
    endpoint: 1

tests:
    - label: "Send Test Command"
      command: "test"
'''


def mock_open_with_parameter_content(content):
    file_object = mock_open(read_data=content).return_value
    file_object.__iter__.return_value = content.splitlines(True)
    return file_object


@patch('builtins.open', new=mock_open_with_parameter_content)
class TestYamlParser(unittest.TestCase):
    def setUp(self):
        self._definitions = SpecDefinitions(
            [ParseSource(source=io.StringIO(simple_test_description), name='simple_test_description')])

    def test_able_to_iterate_over_all_parsed_tests(self):
        # self._yaml_parser.tests implements `__next__`, which does value substitution. We are
        # simply ensure there is no exceptions raise.
        parser_config = TestParserConfig(None, self._definitions)
        yaml_parser = TestParser(simple_test_yaml, parser_config)
        count = 0
        for idx, test_step in enumerate(yaml_parser.tests):
            count += 1
            pass
        self.assertEqual(count, 1)

    def test_config(self):
        parser_config = TestParserConfig(None, self._definitions)
        yaml_parser = TestParser(simple_test_yaml, parser_config)
        for idx, test_step in enumerate(yaml_parser.tests):
            self.assertEqual(test_step.node_id, 0x12344321)
            self.assertEqual(test_step.cluster, 'Test')
            self.assertEqual(test_step.endpoint, 1)

    def test_config_override(self):
        config_override = {'nodeId': 12345,
                           'cluster': 'TestOverride', 'endpoint': 4}
        parser_config = TestParserConfig(
            None, self._definitions, config_override)
        yaml_parser = TestParser(simple_test_yaml, parser_config)
        for idx, test_step in enumerate(yaml_parser.tests):
            self.assertEqual(test_step.node_id, 12345)
            self.assertEqual(test_step.cluster, 'TestOverride')
            self.assertEqual(test_step.endpoint, 4)

    def test_config_override_unknown_field(self):
        config_override = {'unknown_field': 1}
        parser_config = TestParserConfig(
            None, self._definitions, config_override)

        yaml_parser = TestParser(simple_test_yaml, parser_config)
        self.assertIsInstance(yaml_parser, TestParser)


def main():
    unittest.main()


if __name__ == '__main__':
    main()
