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

import base64
import json

# Those constants represents the vocabulary used for the incoming JSON.
_CLUSTER_ID = 'clusterId'
_ENDPOINT_ID = 'endpointId'
_COMMAND_ID = 'commandId'
_ATTRIBUTE_ID = 'attributeId'
_EVENT_ID = 'eventId'

# Those constants represents the vocabulary used for the outgoing data.
_CLUSTER = 'cluster'
_ENDPOINT = 'endpoint'
_COMMAND = 'command'
_ATTRIBUTE = 'attribute'
_EVENT = 'event'


# Those constants represents the common vocabulary between input and output.
_ERROR = 'error'
_CLUSTER_ERROR = 'clusterError'
_VALUE = 'value'


class Decoder:
    def __init__(self, specifications):
        self.__specs = specifications
        self.__converter = Converter(specifications)

    def decode(self, payload):
        payload, logs = self.__get_payload_content(payload)
        payload = self.__translate_names(payload)
        payload = self.__converter.convert(payload)

        if len(payload) == 0:
            payload = [{}]
        elif len(payload) > 1 and payload[-1] == {'error': 'FAILURE'}:
            payload = payload[:-1]
        return payload, logs

    def __translate_names(self, payloads):
        translated_payloads = []
        specs = self.__specs

        for payload in payloads:
            translated_payload = {}
            for key, value in payload.items():
                if key == _CLUSTER_ID:
                    key = _CLUSTER
                    value = specs.get_cluster_name(value)
                elif key == _ENDPOINT_ID:
                    key = _ENDPOINT
                elif key == _COMMAND_ID:
                    key = _COMMAND
                    value = specs.get_response_name(
                        payload[_CLUSTER_ID], value)
                elif key == _ATTRIBUTE_ID:
                    key = _ATTRIBUTE
                    value = specs.get_attribute_name(
                        payload[_CLUSTER_ID], value)
                elif key == _EVENT_ID:
                    key = _EVENT
                    value = specs.get_event_name(payload[_CLUSTER_ID], value)
                elif key == _VALUE or key == _ERROR or key == _CLUSTER_ERROR:
                    pass
                else:
                    # Raise an error since the other fields probably needs to be translated too.
                    raise KeyError(f'Error: field "{key}" in unsupported')

                translated_payload[key] = value
            translated_payloads.append(translated_payload)

        return translated_payloads

    def __get_payload_content(self, payload):
        json_payload = json.loads(payload)
        results = json_payload.get('results')
        logs = ChipLog.decode_logs(json_payload.get('logs'))
        return results, logs


class ChipLog:
    def __init__(self, log):
        self.module = log['module']
        self.level = log['category']

        base64_message = log["message"].encode('utf-8')
        decoded_message_bytes = base64.b64decode(base64_message)
        self.message = decoded_message_bytes.decode('utf-8')

    def decode_logs(logs):
        return list(map(ChipLog, logs))


class Converter():
    def __init__(self, specifications):
        self.__specs = specifications
        self.__converters = [
            StructFieldsNameConverter(),
            FloatConverter(),
            OctetStringConverter()
        ]

    def convert(self, payloads):
        return [self._convert(payload) for payload in payloads]

    def _convert(self, rv):
        if _VALUE not in rv or _CLUSTER not in rv:
            return rv

        if _COMMAND in rv:
            out_value = self.__convert_command(rv)
        elif _ATTRIBUTE in rv:
            out_value = self.__convert_attribute(rv)
        elif _EVENT in rv:
            out_value = self.__convert_event(rv)
        else:
            out_value = rv[_VALUE]

        rv[_VALUE] = out_value
        return rv

    def __convert_command(self, rv):
        specs = self.__specs
        cluster_name = rv[_CLUSTER]
        response_name = rv[_COMMAND]
        value = rv[_VALUE]

        response = specs.get_response_by_name(cluster_name, response_name)
        if not response:
            return value

        typename = response.name
        array = False
        return self.__run(value, cluster_name, typename, array)

    def __convert_attribute(self, rv):
        specs = self.__specs
        cluster_name = rv[_CLUSTER]
        attribute_name = rv[_ATTRIBUTE]
        value = rv[_VALUE]

        attribute = specs.get_attribute_by_name(cluster_name, attribute_name)
        if not attribute:
            return value

        typename = attribute.definition.data_type.name
        array = attribute.definition.is_list
        return self.__run(value, cluster_name, typename, array)

    def __convert_event(self, rv):
        specs = self.__specs
        cluster_name = rv[_CLUSTER]
        event_name = rv[_EVENT]
        value = rv[_VALUE]

        event = specs.get_event_by_name(cluster_name, event_name)
        if not event:
            return rv

        typename = event.name
        array = False
        return self.__run(value, cluster_name, typename, array)

    def __run(self, value, cluster_name: str, typename: str, array: bool):
        for converter in self.__converters:
            value = converter.run(self.__specs, value,
                                  cluster_name, typename, array)
        return value


class FloatConverter():
    """
    Jsoncpp is making float to be stored as a double.
    For float values that are just stored as an approximation it ends up into
    a different output than expected when reading them back
    """

    def run(self, specs, value, cluster_name: str, typename: str, array: bool):
        if isinstance(value, dict) and not array:
            struct = specs.get_struct_by_name(
                cluster_name, typename) or specs.get_event_by_name(cluster_name, typename)
            for field in struct.fields:
                field_name = field.name
                field_type = field.data_type.name
                field_array = field.is_list
                if field_name in value:
                    value[field_name] = self.run(
                        specs, value[field_name], cluster_name, field_type, field_array)
        elif isinstance(value, list) and array:
            value = [self.run(specs, v, cluster_name, typename, False)
                     for v in value]
        elif value is not None and typename.lower() == 'single':
            value = float('%g' % value)

        return value


class OctetStringConverter():
    def run(self, specs, value, cluster_name: str, typename: str, array: bool):
        if isinstance(value, dict) and not array:
            struct = specs.get_struct_by_name(
                cluster_name, typename) or specs.get_event_by_name(cluster_name, typename)
            for field in struct.fields:
                field_name = field.name
                field_type = field.data_type.name
                field_array = field.is_list
                if field_name in value:
                    value[field_name] = self.run(
                        specs, value[field_name], cluster_name, field_type, field_array)
        elif isinstance(value, list) and array:
            value = [self.run(specs, v, cluster_name, typename, False)
                     for v in value]
        elif isinstance(value, str) and (typename.lower() == 'octet_string' or typename.lower() == 'long_octet_string'):
            if value == '':
                value = bytes()
            elif value.startswith('base64:'):
                value = base64.b64decode(value[7:])

        return value


class StructFieldsNameConverter():
    """
    Converts fields identifiers to the fields names specified in the cluster definition.
    """

    def run(self, specs, value, cluster_name: str, typename: str, array: bool):
        if isinstance(value, dict) and not array:
            struct = specs.get_struct_by_name(
                cluster_name, typename) or specs.get_event_by_name(cluster_name, typename)
            for field in struct.fields:
                field_code = field.code
                field_name = field.name
                field_type = field.data_type.name
                field_array = field.is_list
                field_nullable = specs.is_nullable(field)
                if str(field_code) in value:
                    value[field_name] = self.run(
                        specs, value[str(field_code)], cluster_name, field_type, field_array)
                    del value[str(field_code)]
                elif field_nullable:
                    # If the fields mapping contains additional values that are not contains
                    # in the response, we need to check if those are Nullables.
                    # This is because nullable values are not part of the TLV, even if they
                    # are not Optionals. That may confuse the test suite that expects those
                    # values to be set.
                    value[field_name] = None

            # FabricIndex is a special case where the framework requires it to be passed even if it is not part of the
            # requested arguments per spec and not part of the XML definition.
            if specs.is_fabric_scoped(struct):
                value['FabricIndex'] = self.run(
                    specs, value[str(254)], cluster_name, 'int64u', False)
                del value[str(254)]

        elif isinstance(value, list) and array:
            value = [self.run(specs, v, cluster_name, typename, False)
                     for v in value]

        return value
