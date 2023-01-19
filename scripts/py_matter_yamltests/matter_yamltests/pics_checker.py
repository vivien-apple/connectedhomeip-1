#
#    Copyright (c) 2023 Project CHIP Authors
#
#    Licensed under the Apache License, Version 2.0 (the 'License');
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an 'AS IS' BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.

import unicodedata

COMMENT_CHARACTER = '#'
VALUE_SEPARATOR = '='
# The only correct value to enable a feature is '1'. All others turns it off.
VALUE_ENABLED = '1'


class PICSChecker():
    __pics: None
    __index: 0

    def __init__(self, pics_file: str):
        if pics_file is not None:
            self.__pics = self.__parse(pics_file)

    def check(self, pics):
        if pics is None:
            return True

        self.__index = 0
        tokens = self.__tokenize(pics)
        return self.__evaluate_expression(tokens, self.__pics)

    def __parse(self, pics_file: str):
        pics = {}
        with open(pics_file) as f:
            line = f.readline()
            while line:
                line = self.__clear_input(line)
                if len(line) and line[0] != COMMENT_CHARACTER:
                    key, value = line.split(VALUE_SEPARATOR)
                    pics[key] = value == VALUE_ENABLED
                line = f.readline()
        return pics

    def __evaluate_expression(self, tokens: list[str], pics: dict):
        leftExpr = self.__evaluate_sub_expression(tokens, pics)
        if self.__index >= len(tokens):
            return leftExpr

        if tokens[self.__index] == ')':
            return leftExpr

        token = tokens[self.__index]

        if token == '&&':
            self.__index += 1
            rightExpr = self.__evaluate_sub_expression(tokens, pics)
            return leftExpr and rightExpr

        if token == '||':
            self.__index += 1
            rightExpr = self.__evaluate_sub_expression(tokens, pics)
            return leftExpr or rightExpr

        raise KeyError(f'Unknown token: {token}')

    def __evaluate_sub_expression(self, tokens: list[str], pics: dict):
        token = tokens[self.__index]
        if token == '(':
            self.__index += 1
            expr = self.__evaluate_expression(tokens, pics)
            if tokens[self.__index] != ')':
                raise KeyError('Missing ")"')

            self.__index += 1
            return expr

        if token == '!':
            self.__index += 1
            expr = self.__evaluate_expression(tokens, pics)
            return not expr

        token = self.__normalize(token)
        self.__index += 1

        if pics.get(token) == None:
            # By default, let's consider that if a PICS item is not defined, it is |false|.
            # It allows to create a file that only contains enabled features.
            return False

        return pics.get(token)

    def __tokenize(self, expression: str):
        token = ''
        tokens = []

        for c in expression:
            if c == ' ' or c == '\n' or c == '\n':
                pass
            elif c == '(' or c == ')' or c == '!':
                if len(token):
                    tokens.append(token)
                    token = ''
                tokens.append(c)
            elif c == '&' or c == '|':
                if len(token) and token[-1] == c:
                    token = token[:-1]
                    if len(token):
                        tokens.append(token)
                        token = ''
                    tokens.append(c + c)
                else:
                    token += c
            else:
                token += c

        if len(token):
            tokens.append(token)
            token = ''

        return tokens

    def __clear_input(self, value: str):
        return ''.join(c for c in value if unicodedata.category(c)[0] != 'C').replace(' ', '').lower()

    def __normalize(self, token: str):
        # Convert to all-lowercase so people who mess up cases don't have things
        # break on them in subtle ways.
        token = token.lower()

        # TODO strip off "(Additional Context)" bits from the end of the code.
        return token
