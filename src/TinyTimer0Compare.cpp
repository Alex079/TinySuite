#include "TinyTimer0Compare.h"
#include <avr/interrupt.h>

#define onCompareEnable0A() TIMSK |= (1 << OCIE0A)
#define onCompareDisable0A() TIMSK &= ~(1 << OCIE0A)

#define setPrescale0(prescale) TCCR0B |= (prescale % 6)
#define cleanPrescale0() TCCR0B &= 0xF8
#define normalMode0() TCCR0A &= ~(1 << WGM00) & ~(1 << WGM01); TCCR0B &= ~(1 << WGM02)
#define compareMode0() TCCR0A &= ~(1 << WGM00); TCCR0A |= (1 << WGM01); TCCR0B &= ~(1 << WGM02)

#define setMatch0A(match) OCR0A = match

TinyTimer Timer0Compare(
  [](uint32_t match) {
    if (match > 0x3FC00) return;
    compareMode0();
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
    setMatch0A(match - 1);
    onCompareEnable0A();
  },
  []() {
    onCompareDisable0A();
    normalMode0();
  });

inline void _ISRTimerCallbackFunction() {
  if (Timer0Compare.onTimer) Timer0Compare.onTimer();
}

ISR(TIMER0_COMPA_vect) {
  _ISRTimerCallbackFunction();
}
