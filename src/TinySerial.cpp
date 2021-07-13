#include <stdint.h>
#include "TinySerial.h"
#include "TinyUart.h"

TinySerial::TinySerial(const uint8_t& rx, const uint8_t& tx, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt) {
  timer = &clockInterrupt;
  pinChange = &rxInterrupt;
  input = rx;
  output = tx;
}

void TinySerial::begin(const uint32_t& baud) {
  uart.on(input, output, baud, *timer, *pinChange);
}

void TinySerial::end() {
  uart.off();
}

int TinySerial::peek() {
  while (!uart.inputAvailable()) { idleSleep(); }
  return uart.peek();
}

int TinySerial::available() {
  return uart.inputAvailable();
}

int TinySerial::read() {
  return uart.blockingRead();
}

size_t TinySerial::write(uint8_t v) {
  uart.blockingWrite(v);
  return 1;
}

void TinySerial::flush() {
}
