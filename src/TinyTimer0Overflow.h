/*
  TinyTimer
*/
#ifndef TinyTimer0_h
#define TinyTimer0_h

#include <TinyTimer.h>
#include <avr/interrupt.h>

#define onOverflowEnable0() TIMSK |= (1 << TOIE0)
#define onOverflowDisable0() TIMSK &= ~(1 << TOIE0)

#define setPrescale0(prescale) TCCR0B |= (prescale % 6)
#define cleanPrescale0() TCCR0B &= 0xF8
#define normalMode0() TCCR0A &= ~(1 << WGM00) & ~(1 << WGM01); TCCR0B &= ~(1 << WGM02)

void setup0Overflow(uint16_t match) {
  cleanPrescale0();
  uint8_t prescale = 1;
  while (match) {
    prescale++;
    if (match & 0b0100) match += 0b0100;
    match >>= 3;
  }
  setPrescale0(prescale);
  onOverflowEnable0();
}

void teardown0Overflow() {
  onOverflowDisable0();
}

TinyTimer Timer0Overflow(setup0Overflow, teardown0Overflow);

ISR(TIMER0_OVF_vect) {
  Timer0Overflow.onTimer();
}

#endif
