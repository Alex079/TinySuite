#include <avr/interrupt.h>
#include "TinyTimer1Compare.h"

#define onCompareEnable1A() TIMSK |= (1 << OCIE1A)
#define onCompareDisable1A() TIMSK &= ~(1 << OCIE1A)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0x0F)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)
#define compareMode1() TCCR1 |= (1 << CTC1)

#define setMatch1C(match) OCR1C = match

TinyTimer Timer1Compare(
  [](uint32_t match) {
    if (match > 0x3FC000) return;
    compareMode1();
    cleanPrescale1();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      match = (match + 1) >> 1;
    }
    setPrescale1(prescale);
    setMatch1C(match - 1);
    onCompareEnable1A();
  },
  []() {
    onCompareDisable1A();
    normalMode1();
  });

inline void _ISRTimerCallbackFunction() {
  if (Timer1Compare.onTimer) Timer1Compare.onTimer();
}

ISR(TIMER1_COMPA_vect) {
  _ISRTimerCallbackFunction();
}
