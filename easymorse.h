/*
 Easymorse - Easy to use Morse code library

 Copyright 2017 Djones A. Boni

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef EASYMORSE_H_
#define EASYMORSE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint32_t easymorse_convert(char ch);
uint8_t easymorse_onoff(uint32_t *code);

#ifdef __cplusplus
}
#endif

#endif /* EASYMORSE_H_ */
