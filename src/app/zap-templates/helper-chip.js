/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
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

/**
 * This module contains the API for templating. For more detailed instructions, read {@tutorial template-tutorial}
 *
 * @module Templating API: toplevel utility helpers
 */

// Import helpers from zap core
const zapPath = '../../../third_party/zap/repo/src-electron/generator/';
const cHelper = require(zapPath + 'helper-c.js')
const zclHelper = require(zapPath + 'helper-zcl.js')
const zclQuery = require(zapPath + '../db/query-zcl.js')
const templateUtil = require(zapPath + 'template-util.js')

/**
 * Produces the top-of-the-file header for a C file.
 *
 * @returns The header content
 */
function chip_header() {
  return `
  /*
  *
  *    Copyright (c) 2020 Project CHIP Authors
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
  */`;
}

function isNumEqual(val1, val2) { return val1 == val2; }

var stringType = ['CHAR_STRING', 'OCTET_STRING', 'LONG_CHAR_STRING', 'LONG_OCTET_STRING'] 

function isString(type) {
   return stringType.includes(type)
}

function asChipUnderlyingType(type, isArray) {
    if (isString(type))
    {
        return 'char *';
    }

    if (isArray) {
        return 'uint8_t *';
    }

    promise = templateUtil.ensureZclPackageId(this).then(packageId => cHelper.asUnderlyingType.call(this, type))
    .catch(err => {
        console.log(err);
        throw err;
    })

    return templateUtil.templatePromise(this.global, promise)
}

function command_arguments(options) {
  var commandArgs = this.commandArgs
  var p

  // When we are coming from commant_tree, then
  // the commandArgs are already present and there is no need
  // to do additional queries.
  if (commandArgs == null) {
    p = templateUtil.ensureZclPackageId(this).then((packageId) => {
      if ('id' in this) {
        // We're functioning inside a nested context with an id, so we will only query for this cluster.
        return zclQuery.selectCommandArgumentsByCommandId(
          this.global.db,
          this.id,
          packageId
        ).then(args => {
          return Promise.all(args.map(arg => zclHelper.isStruct(this.global.db, arg.type, packageId).then(result => {
              if (result == 'struct')
              {
                  return zclQuery.selectStructByName(this.global.db, arg.type, packageId).then(struct => {
                    return zclQuery.selectAllStructItemsById(this.global.db, struct.id).then(items => {
                        return items.map(item => { item.name = item.label; return item; })
                      })
                  })
              }
              else
              {
                  return arg;
              }
            })
          )).then(results => {
            return results.flat();
          })
        })
      } else {
        return zclQuery.selectAllCommandArguments(this.global.db, packageId)
      }
    })
  } else {
    p = Promise.resolve(commandArgs)
  }

  var promise = p.then((args) =>
    templateUtil.collectBlocks(args, options, this)
  )
  return templateUtil.templatePromise(this.global, promise)
}

function asPutCommand(type, label) {
    promise = templateUtil.ensureZclPackageId(this).then(packageId => {
        return cHelper.asUnderlyingType.call(this, type).then(zclType => {
            switch (zclType)
            {
            case 'int8_t':
              return 'Put(static_cast<uint8_t>(' + label + '))'
            case 'uint8_t':
              return 'Put(' + label + ')'
            case 'int16_t':
              return 'Put16(static_cast<uint16_t>(' + label + '))'
            case 'chip::ClusterId':
            case 'uint16_t':
              return 'Put16(' + label + ')'
            case 'int32_t':
              return 'Put32(static_cast<uint32_t>(' + label + '))'
            case 'uint32_t':
              return 'Put32(' + label + ')'
            case 'int64_t':
              return 'Put64(static_cast<uint64_t>(' + label + '))'
            case 'uint64_t':
              return 'Put64(' + label + ')'
            default:
            throw 'Unhandled type: ' + type + ', ' + zclType
            }
        })
    })
    .catch(err => {
        console.log(err);
        throw err;
    })

    return templateUtil.templatePromise(this.global, promise)
}

function pad(label, len, ch = ' ') {
  return label.padEnd(len, ch)
}

function concat() {
  let str = ''
  for (let arg in arguments) {
    if (typeof arguments[arg] != 'object') {
      str += arguments[arg]
    }
  }
  return str
}

function isResponse(name) {
    return name.includes("Response");
}

function isDiscreteType(type) {
    return false
    promise = templateUtil.ensureZclPackageId(this).then(packageId => {
      return zclQuery.selectAtomicByName(this.global.db, type, packageId).then(atomic => {
        if (atomic && atomic.discrete)
        {
        }
        else
        {
        }
      })
    })
    .catch(err => {
        console.log(err);
        throw err;
    })

    return templateUtil.templatePromise(this.global, promise)
}

function asAtomicId(type) {
    promise = templateUtil
                .ensureZclPackageId(this)
                .then(packageId => zclQuery.selectAtomicByName(this.global.db, type, packageId)
                                           .then(atomic => cHelper.asHex(atomic.atomicId, 2)))
    .catch(err => {
        console.log(err);
        throw err;
    })

    return templateUtil.templatePromise(this.global, promise)
}


// WARNING! WARNING! WARNING! WARNING! WARNING! WARNING!
//
// Note: these exports are public API. Templates that might have been created in the past and are
// available in the wild might depend on these names.
// If you rename the functions, you need to still maintain old exports list.
exports.chip_header = chip_header;
exports.isNumEqual = isNumEqual;
exports.asChipUnderlyingType = asChipUnderlyingType;
exports.pad = pad
exports.concat = concat 
exports.isResponse = isResponse
exports.isString = isString
exports.asPutCommand = asPutCommand
exports.isDiscreteType = isDiscreteType
exports.asAtomicId = asAtomicId
exports.command_arguments = command_arguments
