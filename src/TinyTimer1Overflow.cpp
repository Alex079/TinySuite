#include <avr/interrupt.h>
#include "TinyTimer1Overflow.h"

#define onOverflowEnable1() TIMSK |= (1 << TOIE1)
#define onOverflowDisable1() TIMSK &= ~(1 << TOIE1)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0x0F)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)

TinyTimer Timer1Overflow(
  [](uint32_t match) {
    if (match > 0x3FC000) return;
    normalMode1();
    cleanPrescale1();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      match = (match + 1) >> 1;
    }
    setPrescale1(prescale);
    onOverflowEnable1();
  },
  []() {
    onOverflowDisable1();
  });

inline void _ISRTimerCallbackFunction() {
  if (Timer1Overflow.onTimer) Timer1Overflow.onTimer();
}

ISR(TIMER1_OVF_vect) {
  _ISRTimerCallbackFunction();
}
