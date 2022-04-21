#ifndef TinyNmea_h
#define TinyNmea_h

#include <stdint.h>

struct NmeaParser {
  /**
   * Last three symbols of NMEA sentence type designator. Used in parser lookup, type match is "ends with", case-sensitive.
   */
  char type[3];
  /**
   * A pointer to parser function to invoke when the matching NMEA sentence is received.
   * @param term a C-string containing one term from the last NMEA sentence.
   * @param termIndex a 0-based index of the term in the sentence.
   */
  void (*call) (const char* term, const uint8_t termIndex);
};

#define TINY_NMEA_SENTENCE_BUFFER_SIZE 70

class TinyNmea {
  public:
    /**
     * Instantiate the parser.
     * @param parsers A pointer to an array of "NmeaParser" structures.
     * @param parsersCount Size of the "parsers" array.
     */
    TinyNmea(const NmeaParser parsers[], const uint8_t parsersCount) : parsers(parsers), parsersCount(parsersCount) {}
    /**
     * Feed the parser with one character.
     * @param x the next character to process.
     */
    void next(const char x);
  private:
    void dispatch();
    const NmeaParser* parsers;
    const uint8_t parsersCount;
    uint8_t parserIndex;
    uint8_t charIndex, termsCount, checksum;
    enum NmeaState: uint8_t { NONE, TYPE, DATA, SUM } state = NONE;
    char temp[5];
    char buffer[TINY_NMEA_SENTENCE_BUFFER_SIZE + 1] = {}; // ${talker:1-2}{type:3},{data:70}*{sum:2} total max length is 80
};

#endif