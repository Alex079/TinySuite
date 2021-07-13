#ifndef TinyBuffer_h
#define TinyBuffer_h

#include <stdint.h>
#include "TinyBufferConst.h"

class TinyBuffer {
  private:
    volatile uint8_t data[TINY_UART_BUFFER_SIZE];
    volatile uint8_t head = 0;
    volatile uint8_t tail = 0;
  public:
    uint8_t countBusy();
    uint8_t countFree();
    void clear();
    void put(const uint8_t);
    uint8_t get();
    uint8_t peek();
    void skip();
};

#endif