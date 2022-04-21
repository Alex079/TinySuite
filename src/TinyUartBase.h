#ifndef TinyUartBase_h
#define TinyUartBase_h

#include <stdint.h>
#include "TinySleep.h"
#include "TinyBuffer.h"

class TinyUartRead {
  public:
    /**
     * Get the amount of buffered incoming bytes.
     */
    uint8_t inputAvailable();
    /**
     * Get the amount of free space left in the input buffer.
     */
    uint8_t inputCapacity();
    /**
     * Get one byte from the input buffer. The buffer is not changed.
     */
    uint8_t peek();
    /**
     * Remove one byte from the input buffer.
     */
    void skip();
    /**
     * Clear the input buffer.
     */
    void skipAll();
    /**
     * Get one byte from the input buffer. The value is removed from the buffer.
     */
    uint8_t read();
    /**
     * Perform checked "read".
     * If there is no data in the input buffer, the main control flow will idle until the data is available.
     */
    uint8_t blockingRead();
  protected:
    void onRxPinChange(bool);
    void onTimerRx();
    uint8_t input;
    volatile uint8_t inputState;
    TinyBuffer inputBuffer;
  private:
    volatile uint8_t inputBitInProgress;
    volatile uint8_t inputByte;
    volatile bool inputBit;
};

class TinyUartWrite {
  public:
    /**
     * Get the amount of buffered outgoing bytes.
     */
    uint8_t outputRemaining();
    /**
     * Get the amount of free space left in the output buffer.
     */
    uint8_t outputCapacity();
    /**
     * Put one byte into the output buffer.
     * @param x The value to output.
     */
    void write(const uint8_t x);
    /**
     * Perform checked "write".
     * If there is no free space left in the output buffer, the main control flow will idle until the free space is available.
     * Additionally, the main control flow will idle until all the outgoing data is sent.
     * @param x The value to output.
     */
    void blockingWrite(const uint8_t x);
  protected:
    void onTimerTx();
    uint8_t output;
    volatile uint8_t outputState;
    TinyBuffer outputBuffer;
  private:
    volatile uint8_t outputBitInProgress;
    volatile uint8_t outputByte;
};

#endif