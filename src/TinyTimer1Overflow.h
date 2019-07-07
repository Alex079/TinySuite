/*
  TinyTimer
*/
#ifndef TinyTimer1_h
#define TinyTimer1_h

#include <TinyTimer.h>
#include <avr/interrupt.h>

#define onOverflowEnable1() TIMSK |= (1 << TOIE1)
#define onOverflowDisable1() TIMSK &= ~(1 << TOIE1)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0xFF)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)

void setup1Overflow(uint16_t match) {
  cleanPrescale1();
  uint8_t prescale = 1;
  while (match) {
    prescale++;
    if (match & 1) match++;
    match >>= 1;
  }
  setPrescale1(prescale);
  onOverflowEnable1();
}

void teardown1Overflow() {
  onOverflowDisable1();
}

TinyTimer Timer1Overflow(setup1Overflow, teardown1Overflow);

ISR(TIMER1_OVF_vect) {
  Timer1Overflow.onTimer();
}

#endif
