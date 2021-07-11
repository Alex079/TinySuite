#ifndef TinyNmea_h
#define TinyNmea_h

#include <stdint.h>
#include "TinyNmeaConst.h"

struct NmeaParser {
  char type[3];
  void (*call) (const char*, const uint8_t);
};

#define TINY_NMEA_SENTENCE_BUFFER_SIZE 70

class TinyNmea {
  public:
    TinyNmea(const NmeaParser parsers[], const uint8_t parsersCount) : parsers(parsers), parsersCount(parsersCount) {}
    void next(const char);
  private:
    void dispatch();
    const NmeaParser* parsers;
    const uint8_t parsersCount;
    uint8_t parserIndex;
    uint8_t charIndex, termsCount, checksum;
    uint8_t state = TINY_NMEA_STATE_NONE;
    char temp[5];
    char buffer[TINY_NMEA_SENTENCE_BUFFER_SIZE + 1] = {}; // ${talker:1-2}{type:3},{data:70}*{sum:2} total max length is 80
};

#endif