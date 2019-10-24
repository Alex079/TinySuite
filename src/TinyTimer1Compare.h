/*
  TinyTimer
*/
#ifndef TinyTimer1_h
#define TinyTimer1_h

#include <TinyTimer.h>
#include <avr/interrupt.h>

#define onCompareEnable1A() TIMSK |= (1 << OCIE1A)
#define onCompareDisable1A() TIMSK &= ~(1 << OCIE1A)
#define onOverflowEnable1() TIMSK |= (1 << TOIE1)
#define onOverflowDisable1() TIMSK &= ~(1 << TOIE1)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0xFF)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)
#define compareMode1() TCCR1 |= (1 << CTC1)

#define setMatch1C(match) OCR1C = match

TinyTimer Timer1Compare(
  [](uint16_t match) {
    compareMode1();
    cleanPrescale1();
    uint8_t prescale = 1;
    while (match > 0xFF) {
      prescale++;
      if (match & 1) match++;
      match >>= 1;
    }
    setPrescale1(prescale);
    setMatch1C(match - 1);
    onCompareEnable1A();
  },
  []() {
    onCompareDisable1A();
    normalMode1();
  });

ISR(TIMER1_COMPA_vect) {
  Timer1Compare.onTimer();
}

#endif
