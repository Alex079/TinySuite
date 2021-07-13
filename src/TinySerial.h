#ifndef TinySerial_h
#define TinySerial_h

#include <stdint.h>
#include <Stream.h>
#include "TinyPinChange.h"
#include "TinyTimer.h"

class TinySerial : public Stream {
  private:
    uint8_t input, output;
    TinyTimer* timer;
    TinyPinChange* pinChange;
  public:
    TinySerial(const uint8_t& rx, const uint8_t& tx, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt);
    void begin(const uint32_t& baud);
    void end();
    virtual int peek() override;
    virtual int available() override;
    virtual int read() override;
    virtual size_t write(uint8_t) override;
    virtual void flush() override;
};

#endif