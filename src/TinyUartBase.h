#ifndef TinyUartBase_h
#define TinyUartBase_h

#include <stdint.h>
#include "TinySleep.h"
#include "TinyBuffer.h"

class TinyUartRead {
  public:
    void onRxPinChange(bool);
    void onTimerRx();
    uint8_t inputAvailable();
    uint8_t inputCapacity();
    uint8_t peek();
    void skip();
    void skipAll();
    uint8_t read();
    uint8_t blockingRead();
  protected:
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
    void onTimerTx();
    uint8_t outputRemaining();
    uint8_t outputCapacity();
    void write(const uint8_t);
    void blockingWrite(const uint8_t);
  protected:
    uint8_t output;
    volatile uint8_t outputState;
    TinyBuffer outputBuffer;
  private:
    volatile uint8_t outputBitInProgress;
    volatile uint8_t outputByte;
};

#endif