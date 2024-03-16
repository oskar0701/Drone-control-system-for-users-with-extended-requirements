/* Copyright 2022 The TensorFlow Authors. All Rights Reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
  ==============================================================================*/

#if defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)
#define ARDUINO_EXCLUDE_CODE
#endif  // defined(ARDUINO) && !defined(ARDUINO_ARDUINO_NANO33BLE)

#ifndef ARDUINO_EXCLUDE_CODE

#include "Arduino.h"
#include "command_responder.h"
#include "tensorflow/lite/micro/micro_log.h"

// Toggles the built-in LED every inference, and lights a colored LED depending
// on which word was detected.
void RespondToCommand(int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  static bool is_initialized = false;
  if (!is_initialized) {
    pinMode(D2, OUTPUT); //up command pin
    pinMode(D3, OUTPUT); //down command pin
    pinMode(D4, OUTPUT); //left command pin
    pinMode(D5, OUTPUT); //right command pin
    pinMode(D6, OUTPUT); //forward command pin
    pinMode(D9, OUTPUT); //backward command pin

    is_initialized = true;
  }
  static int32_t last_command_time = 0;

  if (is_new_command) {
    MicroPrintf("Heard %s (%d) @%dms", found_command, score, current_time);

    if (found_command[0] == 'u') {
      digitalWrite(D2, HIGH); //up command supp

    } else if (found_command[0] == 'd') {
      digitalWrite(D3, HIGH); //down command supp

    } else if (found_command[0] == 'l') {
      digitalWrite(D4, HIGH); //left command supp

    } else if (found_command[0] == 'r') {
      digitalWrite(D5, HIGH); //right command supp

    } else if (found_command[0] == 'f') {
      digitalWrite(D6, HIGH); //forward command supp

    } else if (found_command[0] == 'b') {
      digitalWrite(D9, HIGH); //backward command supp
    } else {
      // silence
    }

    last_command_time = current_time;
  }

  // If last_command_time is non-zero but was >1 seconds ago, zero it
  if (last_command_time != 0) {
    if (last_command_time < (current_time - 1000)) {
      last_command_time = 0;
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);  //return to the low state
      digitalWrite(D5, LOW);  //after 1 second of the
      digitalWrite(D6, LOW);  //high state
      digitalWrite(D9, LOW);
    }
  }
}

#endif  // ARDUINO_EXCLUDE_CODE
