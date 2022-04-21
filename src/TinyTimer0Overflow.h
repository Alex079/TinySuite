#ifndef TinyTimer0Overflow_h
#define TinyTimer0Overflow_h

#include "TinyTimer.h"

/**
 * The instance of Timer0 Overflow interrupt handler: ISR(TIMER0_OVF_vect)
 * 
 * Max match value: 0x3FC00
 * 
 * Prescaler reference:
 * CS02 CS01 CS00 Result
 * 0    0    0    stopped
 * 0    0    1    clock
 * 0    1    0    clock /8
 * 0    1    1    clock /64
 * 1    0    0    clock /256
 * 1    0    1    clock /1024
 */
extern TinyTimer Timer0Overflow;

#endif
