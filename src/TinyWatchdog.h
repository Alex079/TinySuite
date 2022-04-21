#ifndef TinyWatchdog_h
#define TinyWatchdog_h

#include <stdint.h>

typedef void (*WatchdogCallback)();

/**
 * An interface of the watchog interrupt handler.
 */
class TinyWatchdog {
  friend void _ISRWatchdogEventCallback();
  public:
    /**
     * Run the callback inside an ISR after timeout.
     * @param prescaler An integer value from 0 to 9.
     * Higher prescaler value will cause longer delay.
     * @param callback A pointer to WatchdogCallback function.
     * The function should accept no arguments and return void.
     */
    void arm(const uint8_t prescaler, WatchdogCallback callback);
    /**
     * Run the callback inside an ISR after timeout and then reset after another timeout.
     * If the callback is null, the reset is done after the first timeout.
     * @param prescaler An integer value from 0 to 9.
     * Higher prescaler value will cause longer delay.
     * @param callback A pointer to WatchdogCallback function.
     * The function should accept no arguments and return void.
     */
    void armReset(const uint8_t prescaler, WatchdogCallback callback);
    /**
     * Disable the watchdog.
     */
    void disarm();
  private:
    volatile WatchdogCallback onEvent;
};

/**
 * The instance of watchdog interrupt handler: ISR(WDT_vect)
 * 
 * Watchdog prescaler reference:
 * 0 -> 16 ms
 * 1 -> 32 ms
 * 2 -> 64 ms
 * 3 -> 0.125 s
 * 4 -> 0.25 s
 * 5 -> 0.5 s
 * 6 -> 1.0 s
 * 7 -> 2.0 s
 * 8 -> 4.0 s
 * 9 -> 8.0 s
 */
extern TinyWatchdog Watchdog;

#endif