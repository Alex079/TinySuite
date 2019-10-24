/*
  TinyWatchdog
*/
#ifndef TinyWatchdog_h
#define TinyWatchdog_h

#include <avr/io.h>
#include <avr/interrupt.h>

typedef void (*WatchdogCallback)();

#define watchdogArm(i, r, p) WDTCR = ((i) << WDIE) | ((r) << WDE) | (((p) & 0b1000) << 2) | ((p) & 0b0111)
#define watchdogDisarm() WDTCR = (1 << WDCE) | (1 << WDE); WDTCR = 0

class TinyWatchdog {
public:
  void arm(const uint8_t prescaler, WatchdogCallback callback) {
    onEvent = callback;
    watchdogArm(true, false, prescaler);
  }
  void armReset(const uint8_t prescaler, WatchdogCallback callback) {
    onEvent = callback;
    watchdogArm(callback!=0, true, prescaler);
  }
  void disarm() {
    watchdogDisarm();
  }
  volatile WatchdogCallback onEvent;
};

TinyWatchdog Watchdog;

ISR(WDT_vect) {
  if (Watchdog.onEvent) Watchdog.onEvent();
}

#endif
