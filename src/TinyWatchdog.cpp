#include <stdint.h>
#include <avr/interrupt.h>
#include "TinyWatchdog.h"

#define watchdogArm(i, r, p) WDTCR = ((i) << WDIE) | ((r) << WDE) | (((p) & 0b1000) << 2) | ((p) & 0b0111)
#define watchdogDisarm() WDTCR = (1 << WDCE) | (1 << WDE); WDTCR = 0

void TinyWatchdog::arm(const uint8_t prescaler, WatchdogCallback callback) {
  onEvent = callback;
  watchdogArm(true, false, prescaler);
}

void TinyWatchdog::armReset(const uint8_t prescaler, WatchdogCallback callback) {
  onEvent = callback;
  watchdogArm(callback!=0, true, prescaler);
}

void TinyWatchdog::disarm() {
  onEvent = 0;
  watchdogDisarm();
}

/*
Watchdog prescaler values
0 -> 16 ms
1 -> 32 ms
2 -> 64 ms
3 -> 0.125 s
4 -> 0.25 s
5 -> 0.5 s
6 -> 1.0 s
7 -> 2.0 s
8 -> 4.0 s
9 -> 8.0 s
*/
TinyWatchdog Watchdog;

inline void _ISRWatchdogEventCallback() {
  if (Watchdog.onEvent) Watchdog.onEvent();
}

ISR(WDT_vect) {
  _ISRWatchdogEventCallback();
}
