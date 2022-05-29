#include <stdint.h>
#include "TinyBuffer.h"

#define next_buffer_index(p) ((p+1) % TINY_BUFFER_SIZE)
#define TINY_BUFFER_CAPACITY (TINY_BUFFER_SIZE - 1)

uint8_t TinyBuffer::countBusy() {
  uint8_t h = head;
  uint8_t t = tail;
  return (h < t) ? (TINY_BUFFER_SIZE + h - t) : (h - t);
}

uint8_t TinyBuffer::countFree() {
  uint8_t h = head;
  uint8_t t = tail;
  return (h < t) ? (t - h - 1) : (TINY_BUFFER_CAPACITY + t - h);
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
