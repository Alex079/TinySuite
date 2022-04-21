#ifndef TinyUartWriter_h
#define TinyUartWriter_h

#include <stdint.h>
#include "TinyUartBase.h"
#include "TinyTimer.h"

/**
 * Transmit-only UART.
 */
class TinyUartWriter : public TinyUartWrite {
  public:
    /**
     * Start the UART.
     * The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate.
     * @param tx The tansmitting pin identifier (i.e. PB0, PB1 etc.)
     * @param baud The baud rate for this communication session.
     * @param clockInterrupt Clock interrupt handler, an instance of "TinyTimer" class.
     */
    void on(const uint8_t tx, const uint32_t baud, TinyTimer& clockInterrupt);
    /**
     * Stop the UART. The "timer" will be stopped.
     */
    void off();
  private:
    TinyTimer* timer;
    uint8_t storedDDR, storedPORT, storedMask;
};

/**
 * The instance of transmit-only UART.
 */
extern TinyUartWriter uartWriter;

#endif