/*
  TinySleep
*/
#ifndef TinySleep_h
#define TinySleep_h

#include <avr/sleep.h>

#define sleep(mode) set_sleep_mode(mode); sleep_mode()

#define deepSleep() set_sleep_mode(SLEEP_MODE_PWR_DOWN); sleep_bod_disable(); sleep_mode()

#define idleSleep() sleep(SLEEP_MODE_IDLE)

#endif
