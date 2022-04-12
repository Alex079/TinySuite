#ifndef TinyWatchdog_h
#define TinyWatchdog_h

#include <stdint.h>

typedef void (*WatchdogCallback)();

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