#include <avr/interrupt.h>
#include "TinyTimer1Compare.h"

#define onCompareEnable1A() TIMSK |= (1 << OCIE1A)
#define onCompareDisable1A() TIMSK &= ~(1 << OCIE1A)

#define setPrescale1(prescale) TCCR1 |= (prescale & 0x0F)
#define cleanPrescale1() TCCR1 &= 0xF0
#define normalMode1() TCCR1 &= ~(1 << CTC1)
#define compareMode1() TCCR1 |= (1 << CTC1)

#define setMatch1C(match) OCR1C = match

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
TinyTimer Timer1Compare(
  [](uint16_t match) {
    compareMode1();
    cleanPrescale1();
    uint8_t prescale = 1;
    while (match > 256) {
      prescale++;
      match = (match >> 1) + (match & 1);
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
