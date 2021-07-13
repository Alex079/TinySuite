#include <stdint.h>
#include "TinyBuffer.h"
#include "TinyBufferConst.h"

uint8_t TinyBuffer::countBusy() {
  return (head < tail) ? (TINY_UART_BUFFER_SIZE + head - tail) : (head - tail);
}

uint8_t TinyBuffer::countFree() {
  return TINY_UART_BUFFER_MASK - countBusy();
}

void TinyBuffer::clear() {
  tail = head;
}

void TinyBuffer::put(const uint8_t v) {
  data[head = next_buffer_index(head)] = v;
}

uint8_t TinyBuffer::get() {
  return data[tail = next_buffer_index(tail)];
}

uint8_t TinyBuffer::peek() {
  return data[next_buffer_index(tail)];
}

void TinyBuffer::skip() {
  tail = next_buffer_index(tail);
}
