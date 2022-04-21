#ifndef TinyTimer1Compare_h
#define TinyTimer1Compare_h

#include "TinyTimer.h"

/**
 * The instance of Timer1 Compare interrupt handler: ISR(TIMER1_COMPA_vect)
 * 
 * Max match value: 0x3FC000
 * 
 * Prescaler reference:
 * CS13 CS12 CS11 CS10 Result
 * 0    0    0    0    stopped
 * 0    0    0    1    clock
 * 0    0    1    0    clock /2
 * 0    0    1    1    clock /4
 * 0    1    0    0    clock /8
 * 0    1    0    1    clock /16
 * 0    1    1    0    clock /32
 * 0    1    1    1    clock /64
 * 1    0    0    0    clock /128
 * 1    0    0    1    clock /256
 * 1    0    1    0    clock /512
 * 1    0    1    1    clock /1024
 * 1    1    0    0    clock /2048
 * 1    1    0    1    clock /4096
 * 1    1    1    0    clock /8192
 * 1    1    1    1    clock /16384
 */
extern TinyTimer Timer1Compare;

#endif