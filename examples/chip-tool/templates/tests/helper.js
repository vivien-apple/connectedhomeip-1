/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

// Import helpers from zap core
const zapPath   = '../../../../third_party/zap/repo/dist/src-electron/';
const appHelper = require('../../../../src/app/zap-templates/templates/app/helper.js');

function utf8StringLength(str)
{
  return new TextEncoder().encode(str).length
}

/*
 * Returns the name to used for accessing a given property of
 * a decodable type.
 *
 */
function asRootObject(options)
{
  // The default name for decodable types is 'value'.
  let rootObject = 'value';

  // The decodable type for commands is a struct by default, even if the
  // command just returns a single value.
  if (this.parent.isCommand) {
    rootObject += '.' + appHelper.asLowerCamelCase(this.name);
  }

  if (this.isOptional && !options.hash.forceNotOptional) {
    rootObject += '.Value()';
  }

  return rootObject;
}

//
// Module exports
//
exports.utf8StringLength = utf8StringLength;
exports.asRootObject     = asRootObject;
