#include <avr/interrupt.h>
#include "TinyTimer0Overflow.h"

#define onOverflowEnable0() TIMSK |= (1 << TOIE0)
#define onOverflowDisable0() TIMSK &= ~(1 << TOIE0)

#define setPrescale0(prescale) TCCR0B |= (prescale % 6)
#define cleanPrescale0() TCCR0B &= 0xF8
#define normalMode0() TCCR0A &= ~(1 << WGM00) & ~(1 << WGM01); TCCR0B &= ~(1 << WGM02)

TinyTimer Timer0Overflow(
  [](uint32_t match) {
    if (match > 0x3FC00) return;
    normalMode0();
    cleanPrescale0();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      if (prescale > 3) {
        match = (match + 2) >> 2;
      }
      else {
        match = (match + 4) >> 3;
      }
    }
    setPrescale0(prescale);
    onOverflowEnable0();
  },
  []() {
    onOverflowDisable0();
  });

inline void _ISRTimerCallbackFunction() {
  if (Timer0Overflow.onTimer) Timer0Overflow.onTimer();
}

ISR(TIMER0_OVF_vect) {
  _ISRTimerCallbackFunction();
}
