#!/usr/bin/env python3
"""
Copyright (c) 2020 Project CHIP Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

import logging
import os
import time
import sys

from helper.CHIPTestBase import CHIPVirtualHome
from constant import CHIP_PORT
from constant import CIRQUE_URL

logger = logging.getLogger('CHIPBarrierControlTest')
logger.setLevel(logging.INFO)

sh = logging.StreamHandler()
sh.setFormatter(
    logging.Formatter(
        '%(asctime)s [%(name)s] %(levelname)s %(message)s'))
logger.addHandler(sh)

DEVICE_CONFIG = {
    'device0': {
        'type': 'CHIP-Server',
        'base_image': 'chip_server_all_clusters',
        'capability': ['Thread', 'Interactive'],
        'rcp_mode': True,
    },
    'device1': {
        'type': 'CHIP-Tool',
        'base_image': 'chip_tool',
        'capability': ['Thread', 'Interactive'],
        'rcp_mode': True,
    }
}

class TestBarrierControlCluster(CHIPVirtualHome):
    def __init__(self, device_config):
        super().__init__(CIRQUE_URL, device_config)
        self.logger = logger

    def setup(self):
        self.initialize_home()
        self.connect_to_thread_network()

    def test_routine(self):
        self.run_data_model_test()

    def run_data_model_test(self):
        server_ip_address = set()
        tool_device_id = ''

        server_ids = [device['id'] for device in self.non_ap_devices
                      if device['type'] == 'CHIP-Server']
        tool_ids = [device['id'] for device in self.non_ap_devices
                    if device['type'] == 'CHIP-Tool']

        tool_device_id = tool_ids[0]

        for device_id in server_ids:
            server_ip_address.add(self.get_device_thread_ip(device_id))

        commands = collections.OrderedDict()
        commands['go-to-percent'] = "0"
        commands['stop'] = ""

        command = "chip-tool barriercontrol {} {} {} {} 1"
        for ip in server_ip_address:
            for key, value in commands.items():
                ret = self.execute_device_cmd(tool_device_id, command.format(key, value, ip, CHIP_PORT))
                self.assertEqual(ret['return_code'], '0', "{} command failure: {}".format(key, ret['output']))

        time.sleep(1)

if __name__ == "__main__":
    sys.exit(TestBarrierControlCluster(DEVICE_CONFIG).run_test())
