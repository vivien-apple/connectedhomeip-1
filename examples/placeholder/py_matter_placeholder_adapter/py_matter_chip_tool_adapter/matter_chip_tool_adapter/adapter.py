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

import re
import base64
import json


class Adapter:
    def __init__(self, definitions):
        self.encoder = ChipToolEncoder()
        self.decoder = ChipToolDecoder(definitions)

    def encode(self, request):
        return self.encoder.encode(request)

    def decode(self, response):
        return self.decoder.decode(response)


class ChipToolLog:
    def __init__(self, log):
        self.module = log['module']
        self.level = log['category']

        base64_message = log["message"].encode('utf-8')
        decoded_message_bytes = base64.b64decode(base64_message)
        self.message = decoded_message_bytes.decode('utf-8')


class ChipToolEncoder:
    def encode(self, request):
        cluster = self.__get_cluster_name(request)
        command, command_specifier = self.__get_command_name(request)
        if cluster is None or command is None:
            return ''

        arguments = self.__get_arguments(request)
        base64_arguments = base64.b64encode(
            (f'{{ {arguments} }}').encode('utf-8')).decode('utf-8')

        payload = f'"cluster": "{cluster}", "command": "{command}", "arguments" : "base64:{base64_arguments}"'
        if command_specifier:
            payload += f', "command_specifier": "{command_specifier}"'
        return f'json:{{ {payload} }}'

    def __get_cluster_name(self, request):
        cluster_name = request.cluster
        command_name = request.command

        # CommissionerCommands cluster is named 'pairing' on chip-tool side.
        if cluster_name == 'CommissionerCommands':
            return 'pairing'

        # WaitForCommissionee is under the 'delay' cluster on chip-tool side.
        if cluster_name == 'DelayCommands' and command_name.casefold() == 'WaitForCommissionee'.casefold():
            return 'delay'

        return self.__format_cluster_name(cluster_name)

    def __get_command_name(self, request):
        cluster_name = request.cluster
        command_name = request.command

        # PairWithCode command is 'code' command on chip-tool side.
        if cluster_name == 'CommissionerCommands' and command_name.casefold() == "pairWithCode".casefold():
            return "code", None

        # WaitForReport is a no-op on chip-tool side. So does not forward it to the runner.
        if command_name.casefold() == 'waitForReport'.casefold():
            return None, None

        # 'readAttribute' is converted to 'read attr-name', 'writeAttribute' is converted to 'write attr-name', etc.
        if request.is_attribute:
            return f'{command_name.replace("Attribute", "")}', f'{self.__format_command_name(request.attribute)}'

        # 'readEvent' is converted to 'read event-name', 'subscribeEvent' is converted to 'subscribe event-name', etc.
        if request.is_event:
            return f'{command_name_name.replace("Event", "")}', f'{self.__format_command_name(request.event)}'

        return self.__format_command_name(command_name), None

    def __get_arguments(self, request):
        node_argument_name = 'destination-id'
        if request.group_id:
            node_argument_value = hex(
                0xffffffffffff0000 | int(request.group_id))
        elif request.node_id:
            node_argument_value = hex(request.node_id)
        else:
            raise KeyError('Can not find a node id nor a group id.')

        endpoint_argument_name = 'endpoint-id-ignored-for-group-commands'
        endpoint_argument_value = request.endpoint

        if (request.is_attribute and not request.command == "writeAttribute") or request.is_event:
            endpoint_argument_name = 'endpoint-ids'

        arguments = f'"{node_argument_name}": "{node_argument_value}", "{endpoint_argument_name}": "{endpoint_argument_value}"'
        arguments += self.__maybe_add_command_arguments(request)
        arguments += self.__maybe_add(request.min_interval, "min-interval")
        arguments += self.__maybe_add(request.max_interval, "max-interval")
        arguments += self.__maybe_add(request.timed_interaction_timeout_ms,
                                      "timedInteractionTimeoutMs")
        arguments += self.__maybe_add(request.busy_wait_ms, "busyWaitForMs")
        arguments += self.__maybe_add(request.identity, "commissioner-name")
        arguments += self.__maybe_add(request.fabric_filtered,
                                      "fabric-filtered")

        return arguments

    def __maybe_add_command_arguments(self, request):
        rv = ''

        if request.arguments is None:
            return rv

        for entry in request.arguments['values']:
            name = 'value' if request.is_attribute else entry["name"]
            value = entry['value']

            # This is a gross hack, but for pairing YAML uses nodeId while the argument name is node-id in chip-tool
            if name == 'nodeId' and request.cluster == 'CommissionerCommands' and request.command.casefold() == 'PairWithCode'.casefold():
                name = 'node-id'

            value = self.__try_encode_strings(value)
            value = self.__try_lowercase_member_fields(value)

            if request.command == 'writeAttribute' and name == 'value':
                name = 'attribute-values'

            isString = type(value) is str
            value = json.dumps(value)
            if not isString:
                value = value.replace("\"", "\\\"")
                rv += f', "{name}":"{value}"'
            else:
                rv += f', "{name}":{value}'

        return rv

    def __maybe_add(self, value, name):
        return '' if value is None else f', "{name}":"{value}"'

    def __try_encode_strings(self, value):
        if type(value) is bytes:
            value = 'hex:' + ''.join("{:02x}".format(c) for c in value)
        elif type(value) is list:
            value = [self.__try_encode_strings(entry) for entry in value]
        elif type(value) is dict:
            for key in value:
                value[key] = self.__try_encode_strings(value[key])
        return value

    def __try_lowercase_member_fields(self, value):
        if type(value) is dict:
            mapped_value = {}
            for key in value:
                mapped_value[self.__to_lowercase(
                    key)] = self.__try_lowercase_member_fields(value[key])
            return mapped_value
        elif type(value) is list:
            return [self.__try_lowercase_member_fields(entry) for entry in value]
        else:
            return value

    def __to_lowercase(self, name):
        return name[:1].lower() + name[1:]

    def __format_command_name(self, name):
        return re.sub(r'([a-z])([A-Z])', r'\1-\2', name).replace(' ', '-').replace(':', '-').replace('/', '').replace('_', '-').lower()

    def __format_cluster_name(self, name):
        return name.lower().replace(' ', '').replace('/', '').lower()


class ChipToolDecoder:
    def __init__(self, definitions):
        self.__definitions = definitions

    def decode(self, payload):
        try:
            json_payload = json.loads(payload)
        except Exception as exception:
            raise exception

        decoded_response = {}
        logs = list(map(ChipToolLog, json_payload.get('logs')))

        results = json_payload.get('results')
        if len(results) == 0:
            return decoded_response, logs

        # TODO There could be theorically multiple responses (e.g multiple attribute reads), but for the moment
        #      there is not YAML commands for such things, so we only care of the first one.
        json_response = results[0]
        for key, value in json_response.items():
            if key == 'clusterId':
                decoded_response['cluster'] = self.__definitions.get_cluster_name(
                    value)
            elif key == 'endpointId':
                decoded_response['endpoint'] = value
            elif key == 'commandId':
                clusterId = json_response['clusterId']
                decoded_response['command'] = self.__definitions.get_response_name(
                    clusterId, value)
            elif key == 'attributeId':
                clusterId = json_response['clusterId']
                decoded_response['attribute'] = self.__definitions.get_attribute_name(
                    clusterId, value)
            elif key == 'eventId':
                clusterId = json_response['clusterId']
                decoded_response['event'] = self.__definitions.get_event_name(
                    clusterId, value)
            elif key == 'value':
                decoded_response[key] = self.__try_decode_strings(value)
            elif key == 'error':
                decoded_response[key] = value
            elif key == 'clusterError':
                decoded_response['clusterError'] = value
            else:
                # Raise an error since the other fields probably needs to be translated too.
                raise KeyError(f'Error: field "{key}" in unsupported')

        # jsontlv only returns the field identifier instead of the field name for struct-like construct,
        # it needs to be reconstructed to match the YAML test expectations.
        if 'value' in decoded_response:
            decoded_value = decoded_response['value']
            cluster_name = decoded_response['cluster']
            if 'command' in decoded_response:
                decoded_value = self.__decode_response(
                    cluster_name, decoded_response['command'], decoded_value)
            elif 'attribute' in decoded_response:
                decoded_value = self.__decode_attribute(
                    cluster_name, decoded_response['attribute'], decoded_value)
            elif 'event' in decoded_response:
                decoded_value = self.__decode_event(
                    cluster_name, decoded_response['event'], decoded_value)

            decoded_response['value'] = decoded_value

        return decoded_response, logs

    def __decode_response(self, cluster_name: str, response_name: str, value):
        response = self.__definitions.get_response_by_name(
            cluster_name, response_name)
        return self.__decode(value, cluster_name, response.name, False) if response else value

    def __decode_attribute(self, cluster_name: str, attribute_name: str, value):
        attribute = self.__definitions.get_attribute_by_name(
            cluster_name, attribute_name)
        return self.__decode(value, cluster_name, attribute.definition.data_type.name, attribute.definition.is_list) if attribute else value

    def __decode_event(self, cluster_name: str, event_name: str, value):
        attribute = self.__definitions.get_event_by_name(
            cluster_name, event_name)
        return self.__decode(value, cluster_name, event.data_type.name, event.is_list) if event else value

    def __decode(self, value, cluster_name: str, typename: str, is_list: bool):
        struct = self.__definitions.get_struct_by_name(
            cluster_name, typename.lower())
        if struct is None:
            # Jsoncpp is making float to be stored as a double.
            # For float values that are just stored as an approximation it ends up into
            # a different output than expected when reading them back
            if value and typename.lower() == 'single':
                return float('%g' % value)
            if (typename.lower() == 'octet_string' or typename.lower() == 'long_octet_string') and type(value) is str and value == '':
                return bytes()
            return value

        if type(value) is dict and is_list is False:

            new_value = {}

            fields_mapping = {
                f.code: [f.name, f.data_type.name.lower(), f.is_list] for f in struct.fields}
            if self.__definitions.is_fabric_scoped(struct):
                # FabricIndex is a special case where the framework requires it to be passed even if it is not part of the
                # requested arguments per spec and not part of the XML definition.
                fields_mapping[254] = ['FabricIndex', 'int64u', False]

            for field_key, field_value in value.items():
                field_key = int(field_key)
                if field_key not in fields_mapping:
                    raise KeyError(
                        f'Error: field "{field_key}" in unsupported')
                field_name, field_type, field_is_list = fields_mapping[field_key]
                new_value[field_name] = self.__decode(
                    field_value, cluster_name, field_type, field_is_list)

            value = new_value
        elif type(value) is list and is_list is True:
            value = [self.__decode(v, cluster_name, struct.name, False)
                     for v in value]
        elif value is not None:
            raise TypeError(value, type(value), typename, is_list)

        return value

    def __try_decode_strings(self, value):
        if type(value) is str and value.startswith('base64:'):
            return base64.b64decode(value[7:])
        elif type(value) is list:
            return [self.__try_decode_strings(entry) for entry in value]
        elif type(value) is dict:
            for key in value:
                value[key] = self.__try_decode_strings(value[key])
            return value
        else:
            return value
