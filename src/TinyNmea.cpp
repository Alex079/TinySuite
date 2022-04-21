#include <stdint.h>
#include <stdlib.h>
#include "TinyNmea.h"

enum NmeaMarker: char {
  START_MARKER = '$',
  SPLIT_MARKER = ',',
  STOP_MARKER = '*'
};

void TinyNmea::next(const char x) {
  switch (state) {
    case NONE:
      switch (x) {
        case START_MARKER:
          state = TYPE;
          charIndex = 0;
          termsCount = 0;
          checksum = 0;
          break;
      }
      break;
    case TYPE:
      checksum ^= x;
      switch (x) {
        case SPLIT_MARKER:
          if (charIndex > 2) {
            for (parserIndex = 0; parserIndex < parsersCount; parserIndex++) {
              if (parsers[parserIndex].type[0] == temp[charIndex-3] &&
                  parsers[parserIndex].type[1] == temp[charIndex-2] &&
                  parsers[parserIndex].type[2] == temp[charIndex-1]) {
                state = DATA;
                charIndex = 0;
                termsCount = 0;
                return;
              }
            }
          }
          state = NONE;
          break;
        default:
          if (charIndex < 5) {
            temp[charIndex++] = x;
          }
          break;
      }
      break;
    case DATA:
      switch (x) {
        case SPLIT_MARKER:
          checksum ^= x;
          buffer[charIndex++] = 0;
          termsCount++;
          break;
        case STOP_MARKER:
          buffer[charIndex] = 0;
          termsCount++;
          state = SUM;
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
    case SUM:
      if (charIndex > 1) {
        state = NONE;
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
