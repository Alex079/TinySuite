/*
  TinyTimer
*/
#ifndef TinyTimer0_h
#define TinyTimer0_h

#include <TinyTimer.h>
#include <avr/interrupt.h>

#define onCompareEnable0() TIMSK |= (1 << OCIE0A)
#define onCompareDisable0() TIMSK &= ~(1 << OCIE0A)
#define onOverflowEnable0() TIMSK |= (1 << TOIE0)
#define onOverflowDisable0() TIMSK &= ~(1 << TOIE0)

#define setPrescale0(prescale) TCCR0B |= (prescale % 6)
#define cleanPrescale0() TCCR0B &= 0xF8
#define normalMode0() TCCR0A &= ~(1 << WGM00) & ~(1 << WGM01); TCCR0B &= ~(1 << WGM02)
#define compareMode0() TCCR0A &= ~(1 << WGM00); TCCR0A |= (1 << WGM01); TCCR0B &= ~(1 << WGM02)

#define setMatch0(match) OCR0A = match

void setup0(uint16_t match) {
  compareMode0();
  cleanPrescale0();
  uint8_t prescale = 1;
  //bool compensate = false;
  while (match > 0xFF) {
    prescale++;
    //compensate = match & 4;
    if (match & 0b0100) match += 0b1000;
    match >>= 3;
  }
  //if (!compensate) match --;
  setPrescale0(prescale);
  setMatch0(match - 1);
  onCompareEnable0();
}

void teardown0() {
  onCompareDisable0();
  normalMode0();
}

TinyTimer Timer0(setup0, teardown0);

ISR(TIMER0_COMPA_vect) {
  Timer0.onTimer();
}

#endif
