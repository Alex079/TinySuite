#ifndef TinyTimer_h
#define TinyTimer_h

#include <stdint.h>

typedef void (*TimerCallback)();

typedef void (*TimerSetup)(uint32_t match);

typedef void (*TimerTeardown)();

/**
 * An interface of a timer interrupt handler implementation.
 */
class TinyTimer {
  friend void _ISRTimerCallbackFunction();
  public:
    /**
     * Instantiate the wrapper using the provided setup and teardown functions.
     * Normally, the constructor should be invoked only once by an implementation
     * to instantiate the wrapper and make it available for the "ISR" and "main".
     * @param setup A pointer to TimerSetup function.
     * The function should accept "match" value as an argument and should return void.
     * @param teardown A pointer to TimerTeardown function.
     * The function should accept no arguments and return void.
     */
    TinyTimer(TimerSetup setup, TimerTeardown teardown) : setup(setup), teardown(teardown) {}
    /**
     * Register the callback function to run when a condition is met.
     * @param match An amount of timer ticks to count before the callback is invoked.
     * High match values may be not precise because of coarse step of timer prescaler.
     * @param callback A pointer to TimerCallback function.
     * The function should accept no arguments and should return void.
     */
    void on(const uint32_t match, TimerCallback callback);
    /**
     * Unregister the callback function.
     */
    void off();
  private:
    volatile TimerCallback onTimer;
    TimerSetup setup;
    TimerTeardown teardown;
};

#endif