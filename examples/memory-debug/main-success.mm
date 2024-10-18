/*
 *   Copyright (c) 2024 Project CHIP Authors
 *   All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include <app/InteractionModelEngine.h>

@interface Test: NSObject
- (void)run;
@end

@implementation Test
- (void)run
{
    chip::app::InteractionModelEngine::GetInstance()->RegisterReadHandlerAppCallback(nullptr);
}
@end

int main(int argc, const char * argv[])
{
    int exitCode = EXIT_SUCCESS;
    @autoreleasepool {
        __auto_type test = [[Test alloc] init];
        [test run];
    }
    return exitCode;
}
