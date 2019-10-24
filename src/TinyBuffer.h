/*
  TinyUART
*/
#ifndef TinyBuffer_h
#define TinyBuffer_h

#include <stdint.h>

#define TINY_UART_BUFFER_SIZE 16
#define TINY_UART_BUFFER_MASK 15
#define next_buffer_index(p) ((p+1) & TINY_UART_BUFFER_MASK)

class TinyBuffer {
private:
  volatile uint8_t data[TINY_UART_BUFFER_SIZE];
  volatile uint8_t head = 0;
  volatile uint8_t tail = 0;
public:
  uint8_t countBusy() {
    return (head < tail) ? (TINY_UART_BUFFER_SIZE + head - tail) : (head - tail);
  }
  uint8_t countFree() {
    return TINY_UART_BUFFER_MASK - countBusy();
  }
  void clear() {
    tail = head;
  }
  void put(const uint8_t v) {
    data[head = next_buffer_index(head)] = v;
  }
  uint8_t get() {
    return data[tail = next_buffer_index(tail)];
  }
  uint8_t peek() {
    return data[next_buffer_index(tail)];
  }
  void skip() {
    tail = next_buffer_index(tail);
  }
};

#endif
