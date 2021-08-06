#ifndef TinyUart_h
#define TinyUart_h

#include <stdint.h>
#include <avr/io.h>
#include "TinyUartBase.h"
#include "TinyPinChange.h"
#include "TinyTimer.h"

class TinyUart : public TinyUartRead, public TinyUartWrite {
  public:
    void on(const uint8_t rx, const uint8_t tx, const uint32_t baud, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt);
    void off();
  private:
    TinyTimer* timer;
    TinyPinChange* pinChange;
    uint8_t storedDDR, storedPORT, storedMask;
};

extern TinyUart uart;

#endif