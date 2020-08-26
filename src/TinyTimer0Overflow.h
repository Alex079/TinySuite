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

/*
CS02 CS01 CS00
0    0    0    stopped
0    0    1    clock
0    1    0    clock /8
0    1    1    clock /64
1    0    0    clock /256
1    0    1    clock /1024
*/
TinyTimer Timer0Overflow(
  [](uint16_t match) {
    normalMode0();
    cleanPrescale0();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      if (prescale > 3) {
        match = (match >> 2) + ((match >> 1) & 1);
      }
      else {
        match = (match >> 3) + ((match >> 2) & 1);
      }
    }
    setPrescale0(prescale);
    onOverflowEnable0();
  },
  []() {
    onOverflowDisable0();
  });

ISR(TIMER0_OVF_vect) {
  Timer0Overflow.onTimer();
}

#endif
