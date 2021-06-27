#ifndef TinyUartReader_h
#define TinyUartReader_h

#include <stdint.h>
#include "TinyUartBase.h"
#include "../pin/TinyPinChange.h"
#include "../timer/TinyTimer.h"

class TinyUartReader : public TinyUartRead {
  public:
    void on(const uint8_t rx, const uint32_t baud, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt);
    void off();
  private:
    TinyTimer* timer;
    TinyPinChange* pinChange;
    uint8_t storedDDR, storedPORT, storedMask;
};

extern TinyUartReader uartReader;

#endif