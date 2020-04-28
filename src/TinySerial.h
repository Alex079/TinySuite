/*
  TinyUART
*/
#ifndef TinySerial_h
#define TinySerial_h

#include <stdint.h>
#include <TinyUart.h>
#include <Stream.h>

class TinySerial : public Stream {
private:
  uint8_t input, output;
  TinyTimer* timer;
  TinyPinChange* pinChange;
public:
  TinySerial(const uint8_t& rx, const uint8_t& tx, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt) {
    timer = &clockInterrupt;
    pinChange = &rxInterrupt;
    input = rx;
    output = tx;
  }
  void begin(const uint32_t& baud) {
    uart.on(input, output, baud, *timer, *pinChange);
  }
  void end() {
    uart.off();
  }
  virtual int peek() override {
    while (!uart.inputAvailable()) { idleSleep(); }
    return uart.peek();
  }
  virtual int available() override {
    return uart.inputAvailable();
  }
  virtual int read() override {
    return uart.blockingRead();
  }
  virtual size_t write(uint8_t v) override {
    uart.blockingWrite(v);
    return 1;
  }
  virtual void flush() override {
  }
};

#endif
