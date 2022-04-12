#include "TinyExternalInterrupt0.h"
#include <avr/interrupt.h>

volatile uint8_t storedGIMSK;
volatile uint8_t storedMCUCR;

#define maskGIMSK (1 << INT0)
#define maskMCUCR ( (1 << ISC01) | (1 << ISC00) )

TinyExternalInterrupt ExternalInterrupt0(
  [](ExternalInterruptDetection detection) {
    storedGIMSK = GIMSK & maskGIMSK;
    storedMCUCR = MCUCR & maskMCUCR;
    MCUCR |= (MCUCR & ~maskMCUCR) | detection;
    GIMSK |= maskGIMSK;
  },
  []() {
    GIMSK = (GIMSK & ~maskGIMSK) | storedGIMSK;
    MCUCR = (MCUCR & ~maskMCUCR) | storedMCUCR;
  });

inline void _ISRExternalInterruptCallbackFunction() {
  if (ExternalInterrupt0.onInterrupt) ExternalInterrupt0.onInterrupt();
}

ISR(INT0_vect) {
  _ISRExternalInterruptCallbackFunction();
}
