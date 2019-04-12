/*
  TinyTimer
*/
#ifndef TinyTimer1_h
#define TinyTimer1_h

#include <TinyTimer.h>
#include <avr/interrupt.h>

#define onCompareEnable1() TIMSK |= (1 << OCIE1A)
#define onCompareDisable1() TIMSK &= ~(1 << OCIE1A)
#define onOverflowEnable1() TIMSK |= (1 << TOIE1)
#define onOverflowDisable1() TIMSK &= ~(1 << TOIE1)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0xFF)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)
#define compareMode1() TCCR1 |= (1 << CTC1)

#define setMatch1(match) OCR1C = match

void setup1(uint16_t match) {
  compareMode1();
  cleanPrescale1();
  uint8_t prescale = 1;
  //bool compensate = false;
  while (match > 0xFF) {
    prescale++;
    //compensate = match & 1;
    if (match & 1) match++;
    match >>= 1;
  }
  //if (!compensate) match--;
  setPrescale1(prescale);
  setMatch1(match - 1);
  onCompareEnable1();
}

void teardown1() {
  onCompareDisable1();
  normalMode1();
}

TinyTimer Timer1(setup1, teardown1);

ISR(TIMER1_COMPA_vect) {
  Timer1.onTimer();
}

#endif
