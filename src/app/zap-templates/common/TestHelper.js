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

const basePath = '../../../../';
const testPath = 'src/app/zap-templates/tests/';
const YAML     = require(basePath + 'third_party/zap/repo/node_modules/yaml');
const fs       = require('fs');
const path     = require('path');

function parse(name)
{
  const filepath = path.resolve(__dirname, basePath + testPath + name + '.yaml');
  const data     = fs.readFileSync(filepath, { encoding : 'utf8', flag : 'r' });
  const yaml     = YAML.parse(data);

  yaml.tests.forEach((test, index) => {
    test['index'] = index;

    if (test['command']) {
      test.isCommand = true;
    } else if (test['attribute']) {
      test.isAttribute = true;
    }
  });

  return yaml;
}

//
// Module exports
//
exports.parse = parse;
