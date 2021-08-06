#include <stdint.h>
#include <avr/io.h>
#include "TinyUartReader.h"
#include "TinyUartConst.h"

void TinyUartReader::on(const uint8_t rx, const uint32_t baud, TinyTimer& clockInterrupt, TinyPinChange& rxInterrupt) {
  input = rx;
  timer = &clockInterrupt;
  pinChange = &rxInterrupt;

  inputBuffer.clear();

  inputState = TINY_UART_STATE_IDLE;

  storedMask = (1 << input);
  storedDDR  = DDRB  & storedMask;
  storedPORT = PORTB & storedMask;
  PORTB |= storedMask;
  DDRB &= ~storedMask;

  uint32_t match = (F_CPU * 2) / (baud * TINY_UART_ONE_BIT_CLK);
  if (1 & match) match++;
  match >>= 1;
  timer->on(match, [](){
    uartReader.onTimerRx();
  });

  pinChange->on(input, [](uint8_t, bool value){
    uartReader.onRxPinChange(value);
  });
}

void TinyUartReader::off() {
  timer->off();
  pinChange->off(input);
  DDRB  = (DDRB  & ~storedMask) | storedDDR;
  PORTB = (PORTB & ~storedMask) | storedPORT;
}

TinyUartReader uartReader;
