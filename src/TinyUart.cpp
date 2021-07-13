#include <stdint.h>
#include <avr/io.h>
#include "TinyUart.h"
#include "TinyUartConst.h"

void TinyUart::on(const uint8_t rx, const uint8_t tx, const uint32_t baud, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt) {
  input = rx;
  output = tx;
  timer = &clockInterrupt;
  pinChange = &rxInterrupt;
  storedMask = (1 << input) | (1 << output);

  inputBuffer.clear();
  outputBuffer.clear();

  inputState = TINY_UART_STATE_IDLE;
  outputState = TINY_UART_STATE_IDLE;

  storedDDR  = DDRB  & storedMask;
  storedPORT = PORTB & storedMask;
  PORTB |= storedMask;
  DDRB &= ~(1 << input);
  DDRB |= (1 << output);

  uint32_t match = (F_CPU * 2) / (baud * TINY_UART_ONE_BIT_CLK);
  if (1 & match) match++;
  match >>= 1;
  timer->on(match, [](){
    uart.onTimerRx();
    uart.onTimerTx();
  });

  pinChange->on(input, [](uint8_t, bool value){
    uart.onRxPinChange(value);
  });
}

void TinyUart::off() {
  timer->off();
  pinChange->off(input);
  DDRB  = (DDRB  & ~storedMask) | storedDDR;
  PORTB = (PORTB & ~storedMask) | storedPORT;
}

TinyUart uart;