#ifndef TinyExternalInterrupt_h
#define TinyExternalInterrupt_h

enum ExternalInterruptDetection {
    LOW, ANY, FALLING, RISING
};

typedef void (*ExternalInterruptCallback)();

typedef void (*ExternalInterruptSetup)(ExternalInterruptDetection);

typedef void (*ExternalInterruptTeardown)();

/**
 * The interface of an external interrupt handler implementation.
 */
class TinyExternalInterrupt {
  friend void _ISRExternalInterruptCallbackFunction();
  public:
    /**
     * Instantiate the handler using the provided setup and teardown functions.
     * Normally, the constructor should be invoked only once by an implementation
     * to instantiate the wrapper and make it available for the "ISR" and "main".
     * @param setup A pointer to ExternalInterruptSetup function.
     * The function should accept "ExternalInterruptDetection" as an argument and should return void.
     * @param teardown A pointer to ExternalInterruptTeardown function.
     * The function should have no arguments and should return void.
     */
    TinyExternalInterrupt(ExternalInterruptSetup setup, ExternalInterruptTeardown teardown) : setup(setup), teardown(teardown) {}
    /**
     * Register the callback function to run when the configured INT0 pin level is detected.
     * @param detection One of available ExternalInterruptDetection types: LOW, ANY, FALLING, RISING.
     * @param callback A pointer to a callback function.
     * The function should have no arguments and should return void.
     */
    void on(ExternalInterruptDetection detection, ExternalInterruptCallback callback);
    /**
     * Unregister the callback function.
     */
    void off();
  private:
    volatile ExternalInterruptCallback onInterrupt;
    ExternalInterruptSetup setup;
    ExternalInterruptTeardown teardown;
};

#endif