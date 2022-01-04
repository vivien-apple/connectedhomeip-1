'''
   Copyright (c) 2021 Project CHIP Authors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
'''

from abc import abstractmethod
from construct import Struct, Int64ul, Int32ul, Int16ul, Int8ul
from ctypes import CFUNCTYPE, c_void_p, c_uint32, c_uint64, c_uint8, c_uint16, c_ssize_t
import ctypes
import chip.native
import threading
import chip.tlv
import chip.exceptions
import typing
from dataclasses import dataclass

# The type should match CommandStatus in interaction_model/Delegate.h
# CommandStatus should not contain padding
IMCommandStatus = Struct(
    "Status" / Int16ul,
    "ClusterStatus" / Int8ul,
    "EndpointId" / Int16ul,
    "ClusterId" / Int32ul,
    "CommandId" / Int32ul,
    "CommandIndex" / Int8ul,
)

IMWriteStatus = Struct(
    "NodeId" / Int64ul,
    "AppIdentifier" / Int64ul,
    "Status" / Int16ul,
    "EndpointId" / Int16ul,
    "ClusterId" / Int32ul,
    "AttributeId" / Int32ul,
)

# AttributePath should not contain padding
AttributePathIBstruct = Struct(
    "EndpointId" / Int16ul,
    "ClusterId" / Int32ul,
    "AttributeId" / Int32ul,
)

# EventPath should not contain padding
EventPathIBstruct = Struct(
    "EndpointId" / Int16ul,
    "ClusterId" / Int32ul,
    "EventId" / Int32ul,
)


@dataclass
class AttributePath:
    nodeId: int
    endpointId: int
    clusterId: int
    attributeId: int


@dataclass
class EventPath:
    nodeId: int
    endpointId: int
    clusterId: int
    eventId: int


@dataclass
class AttributeReadResult:
    path: AttributePath
    status: int
    value: 'typing.Any'


@dataclass
class EventReadResult:
    path: EventPath
    value: 'typing.Any'


@dataclass
class AttributeWriteResult:
    path: AttributePath
    status: int

_commandStatusDict = dict()
_commandIndexStatusDict = dict()
_commandStatusLock = threading.RLock()
_commandStatusCV = threading.Condition(_commandStatusLock)

_attributeDict = dict()
_attributeDictLock = threading.RLock()

_writeStatusDict = dict()
_writeStatusDictLock = threading.RLock()

# A placeholder commandHandle, will be removed once we decouple CommandSender with CHIPClusters
PLACEHOLDER_COMMAND_HANDLE = 1
DEFAULT_ATTRIBUTEREAD_APPID = 0
DEFAULT_ATTRIBUTEWRITE_APPID = 0


def _GetCommandStatus(commandHandle: int):
    with _commandStatusLock:
        return _commandStatusDict.get(commandHandle, None)


def _GetCommandIndexStatus(commandHandle: int, commandIndex: int):
    with _commandStatusLock:
        indexDict = _commandIndexStatusDict.get(commandHandle, {})
        return indexDict.get(commandIndex, None)


def _SetCommandStatus(commandHandle: int, val):
    with _commandStatusLock:
        _commandStatusDict[commandHandle] = val
        _commandStatusCV.notify_all()

def ClearCommandStatus(commandHandle: int):
    """
    Clear internal state and prepare for next command, should be called before sending commands.
    """
    with _commandStatusLock:
        _SetCommandStatus(commandHandle, None)
        _commandIndexStatusDict[commandHandle] = {}


def WaitCommandStatus(commandHandle: int):
    """
    Wait for response from device, returns error code.
    ClearCommandStatus should be called before sending command or it will
    return result from last command sent.
    """
    # commandHandle is null, means we are not using IM
    # Note: This should be an error after we fully switched to IM.
    if commandHandle == 0:
        return None
    with _commandStatusCV:
        ret = _GetCommandStatus(commandHandle)
        while ret is None:
            _commandStatusCV.wait()
            ret = _GetCommandStatus(commandHandle)
        return ret


def WaitCommandIndexStatus(commandHandle: int, commandIndex: int):
    """
    Wait for response of particular command from device, returns error code and struct of response info.
    When device returns a command instead of command status, the response info is None.
    ClearCommandStatus should be called before sending command or it will
    return result from last command sent.
    """
    # commandHandle is null, means we are not using IM
    # Note: This should be an error after we fully switched to IM.
    if commandHandle == 0:
        return (0, None)
    err = WaitCommandStatus(commandHandle)
    return (err, _GetCommandIndexStatus(commandHandle, commandIndex))


def GetCommandSenderHandle() -> int:
    handle = chip.native.GetLibraryHandle()
    resPointer = c_uint64()
    res = handle.pychip_InteractionModel_GetCommandSenderHandle(
        ctypes.pointer(resPointer))
    if res != 0:
        raise chip.exceptions.ChipStackError(res)
    ClearCommandStatus(resPointer.value)
    return resPointer.value


def GetAttributeReadResponse(appId: int) -> AttributeReadResult:
    with _attributeDictLock:
        return _attributeDict.get(appId, None)


def GetAttributeWriteResponse(appId: int) -> AttributeWriteResult:
    with _writeStatusDictLock:
        return _writeStatusDict.get(appId, None)
