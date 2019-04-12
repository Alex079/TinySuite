/*
  TinyNMEA
*/
#ifndef TinyNmea_h
#define TinyNmea_h

#include <stdint.h>

template <class D>
struct NmeaParser {
  char type[3];
  void (*call) (D*, const char*, const uint8_t);
};

#define TINY_NMEA_STATE_NONE 0
#define TINY_NMEA_STATE_TYPE 1
#define TINY_NMEA_STATE_DATA 2
#define TINY_NMEA_STATE_SUM  3

#define TINY_NMEA_CHAR_START '$'
#define TINY_NMEA_CHAR_SPLIT ','
#define TINY_NMEA_CHAR_STOP  '*'

#define TINY_NMEA_SENTENCE_BUFFER_SIZE 70

template <class D>
class TinyNmea {
public:
  TinyNmea(const NmeaParser<D> parsers[], const uint8_t parsersCount) : parsers(parsers), parsersCount(parsersCount) {}
  void next(const char);
  D data = {};
private:
  void dispatch();
  const NmeaParser<D>* parsers;
  const uint8_t parsersCount;
  uint8_t parserIndex;
  uint8_t charIndex, termsCount, checksum;
  uint8_t state = TINY_NMEA_STATE_NONE;
  char temp[5];
  char buffer[TINY_NMEA_SENTENCE_BUFFER_SIZE + 1] = {}; // ${talker:1-2}{type:3},{data:70}*{sum:2} total max length is 80
};

template <class D>
void TinyNmea<D>::next(const char x) {
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

template <class D>
void TinyNmea<D>::dispatch() {
  uint8_t position = 0;
  for (uint8_t termIndex = 0; termIndex < termsCount; termIndex++) {
    parsers[parserIndex].call(&data, &buffer[position], termIndex);
    while (buffer[position++]);
  }
}

#endif
