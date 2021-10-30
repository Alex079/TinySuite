#ifndef TinyWatchdog_h
#define TinyWatchdog_h

#include <stdint.h>

typedef void (*WatchdogCallback)();

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
class TinyWatchdog {
  friend void _ISRWatchdogEventCallback();
  public:
    void arm(const uint8_t prescaler, WatchdogCallback callback);
    void armReset(const uint8_t prescaler, WatchdogCallback callback);
    void disarm();
  private:
    volatile WatchdogCallback onEvent;
};

extern TinyWatchdog Watchdog;

#endif