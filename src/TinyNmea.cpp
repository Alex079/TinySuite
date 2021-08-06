#include <stdint.h>
#include <stdlib.h>
#include "TinyNmea.h"
#include "TinyNmeaConst.h"

void TinyNmea::next(const char x) {
  switch (state) {
    case TINY_NMEA_STATE_NONE:
      switch (x) {
        case TINY_NMEA_CHAR_START:
          state = TINY_NMEA_STATE_TYPE;
          charIndex = 0;
          termsCount = 0;
          checksum = 0;
          break;
      }
      break;
    case TINY_NMEA_STATE_TYPE:
      checksum ^= x;
      switch (x) {
        case TINY_NMEA_CHAR_SPLIT:
          if (charIndex > 2) {
            for (parserIndex = 0; parserIndex < parsersCount; parserIndex++) {
              if (parsers[parserIndex].type[0] == temp[charIndex-3] &&
                  parsers[parserIndex].type[1] == temp[charIndex-2] &&
                  parsers[parserIndex].type[2] == temp[charIndex-1]) {
                state = TINY_NMEA_STATE_DATA;
                charIndex = 0;
                termsCount = 0;
                return;
              }
            }
          }
          state = TINY_NMEA_STATE_NONE;
          break;
        default:
          if (charIndex < 5) {
            temp[charIndex++] = x;
          }
          break;
      }
      break;
    case TINY_NMEA_STATE_DATA:
      switch (x) {
        case TINY_NMEA_CHAR_SPLIT:
          checksum ^= x;
          buffer[charIndex++] = 0;
          termsCount++;
          break;
        case TINY_NMEA_CHAR_STOP:
          buffer[charIndex] = 0;
          termsCount++;
          state = TINY_NMEA_STATE_SUM;
          charIndex = 0;
          break;
        default:
          checksum ^= x;
          if (charIndex < TINY_NMEA_SENTENCE_BUFFER_SIZE) {
            buffer[charIndex++] = x;
          }
          break;
      }
      break;
    case TINY_NMEA_STATE_SUM:
      if (charIndex > 1) {
        state = TINY_NMEA_STATE_NONE;
        temp[charIndex] = 0;
        if (strtol(temp, 0, 16) == checksum) {
          dispatch();
        }
      }
      else {
        temp[charIndex++] = x;
      };
      break;
  }
}

void TinyNmea::dispatch() {
  uint8_t position = 0;
  for (uint8_t termIndex = 0; termIndex < termsCount; termIndex++) {
    parsers[parserIndex].call(&buffer[position], termIndex);
    while (buffer[position++]);
  }
}
