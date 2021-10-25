#ifndef TinyTimer_h
#define TinyTimer_h

#include <stdint.h>

typedef void (*TimerCallback)();

typedef void (*TimerSetup)(uint32_t);

typedef void (*TimerTeardown)();

class TinyTimer {
  friend void _ISRTimerCallbackFunction();
  public:
    TinyTimer(TimerSetup setup, TimerTeardown teardown) : setup(setup), teardown(teardown) {}
    void on(const uint32_t match, TimerCallback callback);
    void off();
  private:
    volatile TimerCallback onTimer;
    TimerSetup setup;
    TimerTeardown teardown;
};

#endif