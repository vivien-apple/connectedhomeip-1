#!/usr/bin/env python3
# Copyright (c) 2021 Project CHIP Authors
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

import os
import pathlib
import re
import sys

import bflb_iot_tool
import bflb_iot_tool.__main__
import firmware_utils

# Additional options that can be use to configure an `Flasher`
# object (as dictionary keys) and/or passed as command line options.
BOUFFALO_OPTIONS = {
    # Configuration options define properties used in flashing operations.
    'configuration': {
        'chipname': {
            'help': "Bouffalolab chip name",
            'default': None,
            'argparse': {
                'metavar': 'CHIP_NAME',
            }
        },
        'pt': {
            'help': 'Partition table for board',
            'default': None,
            'argparse': {
                'metavar': 'PARTITION_TABLE_FILE',
                'type': pathlib.Path
            }
        },
        'dts': {
            'help': 'Device tree file',
            'default': None,
            'argparse': {
                'metavar': 'DEVICE_TREE_FILE',
                'type': pathlib.Path
            }
        },
        'xtal': {
            'help': 'XTAL for board',
            'default': None,
            'argparse': {
                'metavar': 'XTAL',
            }
        },
        'port': {
            'help': 'UART port to flash device',
            'default': None,
            'argparse': {
                'metavar': 'PORT',
            }
        },
        'baudrate': {
            'help': 'UART baudrate to flash device',
            'default': None,
            'argparse': {
                'metavar': 'BAUDRATE',
            },
        },
        'build': {
            'help': 'Build image',
            'default': None,
            'argparse': {
                'action': 'store_true'
            }
        },
        'ota': {
            'help': 'output directory of ota image build',
            'default': None,
            'argparse': {
                'metavar': 'DIR',
                'type': pathlib.Path
            }
        },
        'pk': {
            'help': 'public key to sign and encrypt firmware. Available for OTA image building.',
            'default': None,
            'argparse': {
                'metavar': 'path',
                'type': pathlib.Path
            }
        },
        'sk': {
            'help': 'private key to sign and encrypt firmware. Available for OTA image building.',
            'default': None,
            'argparse': {
                'metavar': 'path',
                'type': pathlib.Path
            }
        },
        'boot2': {
            'help': 'boot2 image.',
            'default': None,
            'argparse': {
                'metavar': 'path',
            }
        }
    },
}


class Flasher(firmware_utils.Flasher):

    isErase = False

    def __init__(self, **options):
        super().__init__(platform=None, module=__name__, **options)
        self.define_options(BOUFFALO_OPTIONS)

    def get_boot_image(self, config_path, boot2_image):

        boot_image_guess = None

        for root, dirs, files in os.walk(config_path, topdown=False):
            for name in files:
                print("get_boot_image", root, boot2_image)
                if boot2_image:
                    return os.path.join(root, boot2_image)
                else:
                    if name == "boot2_isp_release.bin":
                        return os.path.join(root, name)
                    elif not boot_image_guess and name.find("release") >= 0:
                        boot_image_guess = os.path.join(root, name)

        return boot_image_guess

    def get_dts_file(self, config_path, xtal_value):

        for root, dirs, files in os.walk(config_path, topdown=False):
            for name in files:
                if name.find(xtal_value) >= 0:
                    return os.path.join(config_path, name)

        return None

    def verify(self):
        """Not supported"""
        self.log(0, "Verification is done after image flashed.")

    def reset(self):
        """Not supported"""
        self.log(0, "Reset is triggered automatically after image flashed.")

    def actions(self):
        """Perform actions on the device according to self.option."""
        self.log(3, 'Options:', self.option)

        tool_path = os.path.dirname(bflb_iot_tool.__file__)

        options_keys = BOUFFALO_OPTIONS["configuration"].keys()
        arguments = [__file__]
        work_dir = None

        print("self.option", self.option)

        if self.option.reset:
            self.reset()
        if self.option.verify_application:
            self.verify()

        chip_name = None
        chip_config_path = None
        boot2_image = None
        dts_path = None
        xtal_value = None

        is_for_ota_image_building = False
        is_for_programming = False
        has_private_key = False
        has_public_key = False

        boot2_image = None

        command_args = {}
        for (key, value) in dict(vars(self.option)).items():

            if self.option.build and value:
                if "port" in command_args.keys():
                    continue
            else:
                if "ota" in command_args.keys():
                    continue

            if key == "application":
                key = "firmware"
                work_dir = os.path.dirname(os.path.join(os.getcwd(), str(value)))
            elif key == "boot2":
                boot2_image = value
                continue
            elif key in options_keys:
                pass
            else:
                continue

            if value:
                if value == True:
                    arg = ("--{}".format(key)).strip()
                elif isinstance(value, pathlib.Path):
                    arg = ("--{}={}".format(key, os.path.join(os.getcwd(), str(value)))).strip()
                else:
                    arg = ("--{}={}".format(key, value)).strip()

            if key == "chipname":
                chip_name = value
            elif key == "xtal":
                xtal_value = value
            elif key == "dts":
                dts_path = value
            elif "port" == key:
                if value:
                    is_for_programming = True
            elif "build" == key:
                if value:
                    is_for_ota_image_building = True
            elif "pk" == key:
                if value:
                    has_public_key = True
            elif "sk" == key:
                if value:
                    has_private_key = True

            arguments.append(arg)

            print(key, value)

        if is_for_ota_image_building and is_for_programming:
            print("ota imge build can't work with image programming")
            return self

        if is_for_ota_image_building:
            if (has_private_key is not has_public_key) and (has_private_key or has_public_key):
                print("For ota image signature, key pair must be used together")
                return self

        print(dts_path, xtal_value)
        if not dts_path and xtal_value:
            chip_config_path = os.path.join(tool_path, "chips", chip_name, "device_tree")
            dts_path = self.get_dts_file(chip_config_path, xtal_value)
            arguments.append("--dts")
            arguments.append(dts_path)

        if boot2_image:
            chip_config_path = os.path.join(tool_path, "chips", chip_name, "builtin_imgs")
            boot2_image = self.get_boot_image(chip_config_path, boot2_image)
            arguments.append("--boot2")
            arguments.append(boot2_image)
        else:
            if self.option.erase:
                arguments.append("--erase")

                if chip_name == "bl602":
                    chip_config_path = os.path.join(tool_path, "chips", chip_name, "builtin_imgs")
                    boot2_image = self.get_boot_image(chip_config_path, boot2_image)
                    arguments.append("--boot2")
                    arguments.append(boot2_image)

        os.chdir(work_dir)
        arguments[0] = re.sub(r'(-script\.pyw|\.exe)?$', '', arguments[0])
        sys.argv = arguments

        print("arguments", arguments)
        bflb_iot_tool.__main__.run_main()

        return self


if __name__ == '__main__':

    sys.argv[0] = re.sub(r'(-script\.pyw|\.exe)?$', '', sys.argv[0])

    sys.exit(Flasher().flash_command(sys.argv))
