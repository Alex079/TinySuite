#ifndef TinyTimer_h
#define TinyTimer_h

#include <stdint.h>

typedef void (*TimerCallback)();

typedef void (*TimerSetup)(uint16_t);

typedef void (*TimerTeardown)();

class TinyTimer {
  public:
    TinyTimer(TimerSetup setup, TimerTeardown teardown) : setup(setup), teardown(teardown) {}
    void on(const uint16_t match, TimerCallback callback);
    void off();
    volatile TimerCallback onTimer;
  private:
    TimerSetup setup;
    TimerTeardown teardown;
};

#endif