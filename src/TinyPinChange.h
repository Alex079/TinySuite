#ifndef TinyPinChange_h
#define TinyPinChange_h

#include <stdint.h>

typedef void (*PinChangeCallback)(uint8_t pin, bool level);

typedef void (*PinChangeSetup)(uint8_t pin, PinChangeCallback callback);

typedef void (*PinChangeTeardown)(uint8_t pin);

/**
 * The interface of a pin change interrupt handler implementation.
 */
class TinyPinChange {
  public:
    /**
     * Instantiate the handler using the provided setup and teardown functions.
     * Normally, this constructor should be invoked only once by an implementation
     * to instantiate the wrapper and make it available for the "ISR" and "main".
     * @param setup A pointer to PinChangeSetup function.
     * The function should accept "pin" and "callback" as arguments and should return void.
     * @param teardown A pointer to PinChangeTeardown function.
     * The function should accept "pin" as an argument and should return void.
     */
    TinyPinChange(PinChangeSetup setup, PinChangeTeardown teardown) : setup(setup), teardown(teardown) {}
    /**
     * Register the callback function for the pin.
     * @param pin The pin identifier (i.e. PB0, PB1 etc.)
     * @param callback A pointer to PinChangeCallback function.
     * The function should accept "pin" and "level" as arguments and should return void.
     */
    void on(uint8_t pin, PinChangeCallback callback);
    /**
     * Unregister the callback function.
     */
    void off(uint8_t pin);
  private:
    PinChangeSetup setup;
    PinChangeTeardown teardown;
};

#endif