#include <avr/interrupt.h>
#include "TinyTimer1Overflow.h"

#define onOverflowEnable1() TIMSK |= (1 << TOIE1)
#define onOverflowDisable1() TIMSK &= ~(1 << TOIE1)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0x0F)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)

/*
CS13 CS12 CS11 CS10
0    0    0    0    stopped
0    0    0    1    clock
0    0    1    0    clock /2
0    0    1    1    clock /4
0    1    0    0    clock /8
0    1    0    1    clock /16
0    1    1    0    clock /32
0    1    1    1    clock /64
1    0    0    0    clock /128
1    0    0    1    clock /256
1    0    1    0    clock /512
1    0    1    1    clock /1024
1    1    0    0    clock /2048
1    1    0    1    clock /4096
1    1    1    0    clock /8192
1    1    1    1    clock /16384
*/
TinyTimer Timer1Overflow(
  [](uint16_t match) {
    normalMode1();
    cleanPrescale1();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      match = (match >> 1) + (match & 1);
    }
    setPrescale1(prescale);
    onOverflowEnable1();
  },
  []() {
    onOverflowDisable1();
  });

ISR(TIMER1_OVF_vect) {
  Timer1Overflow.onTimer();
}
