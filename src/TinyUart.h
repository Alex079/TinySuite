#ifndef TinyUart_h
#define TinyUart_h

#include <stdint.h>
#include <avr/io.h>
#include "TinyUartBase.h"
#include "TinyPinChange.h"
#include "TinyTimer.h"

/**
 * Bi-directional UART.
 */
class TinyUart : public TinyUartRead, public TinyUartWrite {
  public:
    /**
     * Start the UART.
     * The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate.
     * The "pinChange" will be enabled to interrupt on "rx" pin level change.
     * @param rx The receiving pin identifier (i.e. PB0, PB1 etc.)
     * @param tx The tansmitting pin identifier (i.e. PB0, PB1 etc.)
     * @param baud The baud rate for this communication session.
     * @param clockInterrupt Clock interrupt handler, an instance of "TinyTimer" class.
     * @param rxInterrupt RX pin interrupt handler, an instance of "TinyPinChange" class.
     */
    void on(const uint8_t rx, const uint8_t tx, const uint32_t baud, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt);
    /**
     * Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.
     */
    void off();
  private:
    TinyTimer* timer;
    TinyPinChange* pinChange;
    uint8_t storedDDR, storedPORT, storedMask;
};

/**
 * The instance of bi-directional UART.
 */
extern TinyUart uart;

#endif