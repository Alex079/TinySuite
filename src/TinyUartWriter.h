#ifndef TinyUartWriter_h
#define TinyUartWriter_h

#include <stdint.h>
#include "TinyUartBase.h"
#include "TinyTimer.h"

class TinyUartWriter : public TinyUartWrite {
  public:
    void on(const uint8_t tx, const uint32_t baud, TinyTimer& clockInterrupt);
    void off();
  private:
    TinyTimer* timer;
    uint8_t storedDDR, storedPORT, storedMask;
};

extern TinyUartWriter uartWriter;

#endif