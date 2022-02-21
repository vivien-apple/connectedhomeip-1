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
const zapPath = '../../../../third_party/zap/repo/dist/src-electron/';
const { zapTypeToEncodableClusterObjectType, zapTypeToDecodableClusterObjectType, asUpperCamelCase, asLowerCamelCase }
= require('../../../../src/app/zap-templates/templates/app/helper.js');
const { isTestOnlyCluster } = require('../../../../src/app/zap-templates/common/simulated-clusters/SimulatedClusters.js');

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
    rootObject += '.' + asLowerCamelCase(this.name);
  }

  if (this.isOptional && !options.hash.forceNotOptional) {
    rootObject += '.Value()';
  }

  return rootObject;
}

async function asEncodableType()
{
  const options = { 'hash' : { ns : this.cluster } };

  let type;
  if ('commandObject' in this) {
    type = this.commandObject.name;
  } else if ('attributeObject' in this) {
    type = this.attributeObject.type;
    this.isArray    = this.attributeObject.isArray;
    this.isOptional = this.attributeObject.isOptional;
    this.isNullable = this.attributeObject.isNullable;
  } else if ('eventObject' in this) {
    type = this.eventObject.type;
  } else {
    throw new Error("Unsupported encodable type");
  }

  if (isTestOnlyCluster(this.cluster)) {
    return `chip::app::Clusters::${asUpperCamelCase(this.cluster)}::Commands::${asUpperCamelCase(type)}::Type`;
  }

  return await zapTypeToEncodableClusterObjectType.call(this, type, options);
}

async function asDecodableType()
{
  const options = { 'hash' : { ns : this.cluster } };
  let type;
  if ('commandObject' in this) {
    type = this.commandObject.responseName;
  } else if ('attributeObject' in this) {
    type = this.attributeObject.type;
    this.isArray    = this.attributeObject.isArray;
    this.isOptional = this.attributeObject.isOptional;
    this.isNullable = this.attributeObject.isNullable;
  } else if ('eventObject' in this) {
    type = this.eventObject.type;
  } else {
    throw new Error("Unsupported decodable type");
  }

  if (isTestOnlyCluster(this.cluster)) {
    return `chip::app::Clusters::${asUpperCamelCase(this.cluster)}::Commands::${asUpperCamelCase(type)}::DecodableType`;
  }

  return await zapTypeToDecodableClusterObjectType.call(this, type, options);
}

//
// Module exports
//
exports.utf8StringLength = utf8StringLength;
exports.asRootObject     = asRootObject;
exports.asDecodableType  = asDecodableType;
exports.asEncodableType  = asEncodableType;
