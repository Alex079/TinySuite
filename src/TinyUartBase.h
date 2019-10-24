/*
  TinyUART
*/
#ifndef TinyUartBase_h
#define TinyUartBase_h

#include <stdint.h>
#include <TinySleep.h>
#include <TinyBuffer.h>

#define TINY_UART_HALF_BIT_CLK         2
#define TINY_UART_ONE_BIT_CLK          3
#define TINY_UART_ONE_AND_HALF_BIT_CLK 5

#define TINY_UART_STATE_IDLE  0
#define TINY_UART_STATE_START 1
// ... data bit states in between
#define TINY_UART_STATE_STOP 10

class TinyUartRead {
public:
  void    onRxPinChange(bool);
  void    onTimerRx();
  uint8_t inputAvailable() { return inputBuffer.countBusy(); }
  uint8_t inputCapacity()  { return inputBuffer.countFree(); }
  uint8_t peek()           { return inputBuffer.peek(); }
  void    skip()           { inputBuffer.skip(); }
  void    skipAll()        { inputBuffer.clear(); }
  uint8_t read()           { return inputBuffer.get(); }
  uint8_t blockingRead()   {
    while (!inputBuffer.countBusy()) { idleSleep(); }
    return inputBuffer.get();
  }
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
    void    onTimerTx();
    uint8_t outputRemaining()              { return outputBuffer.countBusy(); }
    uint8_t outputCapacity()               { return outputBuffer.countFree(); }
    void    write(const uint8_t v)         { outputBuffer.put(v); }
    void    blockingWrite(const uint8_t v) {
      while (!outputBuffer.countFree()) { idleSleep(); }
      outputBuffer.put(v);
      while (outputBuffer.countBusy()) { idleSleep(); }
    }
  protected:
    uint8_t output;
    volatile uint8_t outputState;
    TinyBuffer outputBuffer;
  private:
    volatile uint8_t outputBitInProgress;
    volatile uint8_t outputByte;
};

#endif
