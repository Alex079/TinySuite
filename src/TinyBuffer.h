#ifndef TinyBuffer_h
#define TinyBuffer_h

#include <stdint.h>

#define TINY_BUFFER_SIZE 16

/**
 * The 16-byte circular (ring) buffer implementation.
 * This implementation does not perform any validation (i.e. it is possible to "get" when "empty" and "put" when "full"), the caller is expected to maintain the buffer consistency.
 */
class TinyBuffer {
  private:
    volatile uint8_t data[TINY_BUFFER_SIZE];
    volatile uint8_t head = 0;
    volatile uint8_t tail = 0;
  public:
    /**
     * Get the count of bytes in this buffer.
     */
    uint8_t countBusy();
    /**
     * Get the size of free space in this buffer.
     */
    uint8_t countFree();
    /**
     * Mark this buffer as empty.
     */
    void clear();
    /**
     * Write one byte.
     */
    void put(const uint8_t);
    /**
     * Read next byte.
     */
    uint8_t get();
    /**
     * Get next byte from this buffer but do not mark it as read.
     */
    uint8_t peek();
    /**
     * Mark next byte as read without returning it.
     */
    void skip();
};

#endif