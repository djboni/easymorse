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

#include "easymorse.h"
#include <stdint.h>
#include <avr/pgmspace.h>

/* The encoded data is read from right to left (lsb to msb).
 * The leftmost set bit is used as end of data marker and is not output.
 * Dashes, dots, end of symbols and spaces (end of word) are encoded as below.
 *
 * dash -             0111
 * dot  .               01
 * end of symbol        00
 * end of word/space  0000
 *
 * The string "HI ME" would output (from the right to the left)
 *
 *    E          M [SPACE]      I          H
 * 0001 0001110111    0000 000101 0001010101
 * <--- <---------    <--- <----- <---------
 */
static const uint32_t morse_code[37] PROGMEM = {
    0x00477777, /* '0' = -----  = 0b10001110111011101110111 */
    0x0011DDDD, /* '1' = .----  =   0b100011101110111011101 */
    0x00047775, /* '2' = ..---  =     0b1000111011101110101 */
    0x00011DD5, /* '3' = ...--  =       0b10001110111010101 */
    0x00004755, /* '4' = ....-  =         0b100011101010101 */
    0x00001155, /* '5' = .....  =           0b1000101010101 */
    0x00004557, /* '6' = -....  =         0b100010101010111 */
    0x00011577, /* '7' = --...  =       0b10001010101110111 */
    0x00045777, /* '8' = ---..  =     0b1000101011101110111 */
    0x00117777, /* '9' = ----.  =   0b100010111011101110111 */
    0x0000011D, /* 'A' = .-     =               0b100011101 */
    0x00001157, /* 'B' = -...   =           0b1000101010111 */
    0x000045D7, /* 'C' = -.-.   =         0b100010111010111 */
    0x00000457, /* 'D' = -..    =             0b10001010111 */
    0x00000011, /* 'E' = .      =                   0b10001 */
    0x00001175, /* 'F' = ..-.   =           0b1000101110101 */
    0x00001177, /* 'G' = --.    =           0b1000101110111 */
    0x00000455, /* 'H' = ....   =             0b10001010101 */
    0x00000045, /* 'I' = ..     =                 0b1000101 */
    0x00011DDD, /* 'J' = .---   =       0b10001110111011101 */
    0x000011D7, /* 'K' = -.-    =           0b1000111010111 */
    0x0000115D, /* 'L' = .-..   =           0b1000101011101 */
    0x00000477, /* 'M' = --     =             0b10001110111 */
    0x00000117, /* 'N' = -.     =               0b100010111 */
    0x00004777, /* 'O' = ---    =         0b100011101110111 */
    0x000045DD, /* 'P' = .--.   =         0b100010111011101 */
    0x00011D77, /* 'Q' = --.-   =       0b10001110101110111 */
    0x0000045D, /* 'R' = .-.    =             0b10001011101 */
    0x00000115, /* 'S' = ...    =               0b100010101 */
    0x00000047, /* 'T' = -      =                 0b1000111 */
    0x00000475, /* 'U' = ..-    =             0b10001110101 */
    0x000011D5, /* 'V' = ...-   =           0b1000111010101 */
    0x000011DD, /* 'W' = .--    =           0b1000111011101 */
    0x00004757, /* 'X' = -..-   =         0b100011101010111 */
    0x00011DD7, /* 'Y' = -.--   =       0b10001110111010111 */
    0x00004577, /* 'Z' = --..   =         0b100010101110111 */
    0x00000010  /* ' ' =        =                   0b10000 */
};

/* Convert character to encoded data. */
uint32_t easymorse_convert(char ch) {
  if(ch >= '0' && ch <= '9') {
    /* Number */
    /* return morse_code[ch - '0']; */
    return pgm_read_dword(&morse_code[ch - '0']);
  }
  else if(ch >= 'A' && ch <= 'Z') {
    /* Uppercase letter */
    /* return morse_code[ch - ('A' - 10)]; */
    return pgm_read_dword(&morse_code[ch - ('A' - 10)]);
  }
  else if(ch >= 'a' && ch <= 'z') {
    /* Lowercase letter */
    /* return morse_code[ch - ('a' - 10)]; */
    return pgm_read_dword(&morse_code[ch - ('a' - 10)]);
  }
  else {
    /* Space */
    /* return morse_code[36]; */
    return pgm_read_dword(&morse_code[36]);
  }
}

/* Return 1/0 if output should be high/low. The variable code will be equal to
 * zero when the encoded data has finished transmitting. */
uint8_t easymorse_onoff(uint32_t *code) {
  uint8_t v = *code & 0x01;
  if(*code < 0x04) {
    *code = 0;
  }
  else {
    *code >>= 1;
  }
  return v;
}

#if 0
/* Arduino demo code. */

#define PIN_MORSE 13

void setup() {
  Serial.begin(9600);
  pinMode(PIN_MORSE, OUTPUT);
  digitalWrite(PIN_MORSE, LOW);
}

void loop() {
  static uint32_t code = 0;

  if(code == 0) {
    /* Data is transmited. Read new character from serial. */
    int16_t ch = Serial.read();
    if(ch > 0) {
      Serial.write(ch);
      code = easymorse_convert(ch);
    }
  }

  /* Switch according to Easymorse rule. */
  if(easymorse_onoff(&code)) {
    digitalWrite(PIN_MORSE, HIGH);
  }
  else {
    digitalWrite(PIN_MORSE, LOW);
  }

  delay(100);
}

#endif
