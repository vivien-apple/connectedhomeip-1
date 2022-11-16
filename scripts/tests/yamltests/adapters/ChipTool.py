# Copyright (c) 2022 Project CHIP Authors
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


class ChipToolAdapter:
    def __init__(self, definitions):
        self.__definitions = definitions

    def encode(self, request):
        def make_as_command(name):
            return re.sub(r'([a-z])([A-Z])', r'\1-\2', name).replace(' ', '-').replace(':', '-').replace('/', '').replace('_', '-').lower()

        def make_as_cluster(name):
            return make_as_command(name.replace(' ', '').lower())

        cluster = make_as_cluster(request.cluster)
        command = make_as_command(request.command)

        # wait-for-report is a no-op on chip-tool side. So does not forward it to the runner.
        if command == 'wait-for-report':
            return None

        # commissionercommands cluster is pairing cluster on chip-tool side.
        if cluster == 'commissionercommands':
            cluster = 'pairing'
            # pair-with-code command is code command on chip-tool side.
            if command == "pair-with-code":
                command = "code"

        # wait-for-commissionee is under the "pairing" cluster in chip-tool.
        if cluster == 'delaycommands' and command == 'wait-for-commissionee':
            cluster = 'pairing'

        isWriteAttribute = command == "write-attribute"

        endpoint_argument_name = 'endpoint-id-ignored-for-group-commands'
        if request.isAttribute:
            if not isWriteAttribute:
                endpoint_argument_name = 'endpoint-ids'
            command = f'{command.replace("-attribute", "")} {make_as_command(request.attribute)}'
        elif request.isEvent:
            endpoint_argument_name = 'endpoint-ids'
            command = f'{command.replace("-event", "")} {make_as_command(request.event)}'
        arguments = f'"destination-id": "{hex(request.nodeId)}", "{endpoint_argument_name}": "{request.endpoint}"'

        if not request.arguments is None:
            for entry in request.arguments['values']:
                name = entry["name"]
                value = entry['value']

                # This is a gross hack, but for pairing YAML uses nodeId while the argument name is node-id in chip-tool
                if name == 'nodeId' and cluster == 'pairing' and command == 'code':
                    name = 'node-id'

                value = self.__try_encode_strings(value)
                value = self.__try_lowercase_member_fields(value)

                if isWriteAttribute and name == 'value':
                    name = 'attribute-values'

                isString = type(value) is str
                value = json.dumps(value)
                if not isString:
                    value = value.replace("\"", "\\\"")
                    arguments += f', "{name}":"{value}"'
                else:
                    arguments += f', "{name}":{value}'

        if not request.minInterval is None:
            arguments += f', "min-interval":"{request.minInterval}"'

        if not request.maxInterval is None:
            arguments += f', "max-interval":"{request.maxInterval}"'

        if not request.timedInteractionTimeoutMs is None:
            arguments += f', "timedInteractionTimeoutMs":"{request.timedInteractionTimeoutMs}"'

        if not request.busyWaitMs is None:
            arguments += f', "busyWaitForMs":"{request.busyWaitMs}"'

        if not request.identity is None:
            arguments += f', "commissioner-name":"{request.identity}"'

        if not request.fabricFiltered is None:
            arguments += f', "fabric-filtered":"{request.fabricFiltered}"'

        base64Arguments = base64.b64encode((f'{{ {arguments} }}').encode('utf-8')).decode('utf-8')
        return f'{cluster} {command} arguments {base64Arguments}'

    def decode(self, responses):
        # TODO There could be theorically multiple responses (e.g multiple attribute reads), but for the moment
        #      there is not YAML commands for such things, so we only care of the first one.
        response = responses[0]

        # If this is a generic response, there is nothing to do.
        if response == 'success' or response == 'failure':
            return response

        decoded_response = {}

        json_response = json.loads(response)

        for key, value in json_response.items():
            if key == 'clusterId':
                decoded_response['cluster'] = self.__definitions.get_cluster_name(value)
            elif key == 'endpointId':
                decoded_response['endpoint'] = value
            elif key == 'commandId':
                clusterId = json_response['clusterId']
                decoded_response['command'] = self.__definitions.get_command_name(clusterId, value)
            elif key == 'attributeId':
                clusterId = json_response['clusterId']
                decoded_response['attribute'] = self.__definitions.get_attribute_name(clusterId, value)
            elif key == 'eventId':
                clusterId = json_response['clusterId']
                decoded_response['event'] = self.__definitions.get_event_name(clusterId, value)
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
            mapping = None
            if 'command' in decoded_response:
                mapping = self.__definitions.get_response_mapping(decoded_response['command'])
            elif 'attribute' in decoded_response:
                mapping = self.__definitions.get_attribute_mapping(decoded_response['attribute'])
            elif 'event' in decoded_response:
                mapping = self.__definitions.get_event_mapping(decoded_response['event'])

            if mapping:
                decoded_response['value'] = self.__apply_fields_mapping(decoded_response['value'], mapping)

        return decoded_response

    def __apply_fields_mapping(self, value, mapping):
        if type(value) is dict and 'type' in mapping:
            value = {'value': self.__apply_mapping(value, mapping['type'])}
        elif type(value) is dict:
            mapped_value = {}
            for key in value:
                field_mapping = mapping[key]
                mapped_value[field_mapping['name']] = self.__apply_mapping(value[key], field_mapping['type'])
            value = mapped_value
        elif type(value) is list:
            value = [self.__apply_mapping(entry, mapping['type']) for entry in value]

        return value

    def __apply_mapping(self, value, type_name):
        if type(value) is dict:
            mapping = self.__definitions.get_type_mapping(type_name)
            if mapping:
                mapped_value = {}
                for key in value:
                    mapped_value[mapping[key]['name']] = self.__apply_mapping(value[key], mapping[key]['type'])
                value = mapped_value
        elif type(value) is list:
            mapping = self.__definitions.get_type_mapping(type_name)
            if mapping:
                value = [self.__apply_mapping(entry, type_name) for entry in value]

        return value

    def __try_lowercase_member_fields(self, value):
        if type(value) is dict:
            mapped_value = {}
            for key in value:
                mapped_value[self.__to_lowercase(key)] = self.__try_lowercase_member_fields(value[key])
            return mapped_value
        elif type(value) is list:
            return [self.__try_lowercase_member_fields(entry) for entry in value]
        else:
            return value

    def __to_lowercase(self, name):
        return name[:1].lower() + name[1:]

    def __try_encode_strings(self, value):
        if type(value) is bytes:
            value = 'hex:' + ''.join("{:02x}".format(c) for c in value)
        elif type(value) is list:
            value = [self.__try_encode_strings(entry) for entry in value]
        elif type(value) is dict:
            for key in value:
                value[key] = self.__try_encode_strings(value[key])
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
