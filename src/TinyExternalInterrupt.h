#ifndef TinyExternalInterrupt_h
#define TinyExternalInterrupt_h

enum ExternalInterruptDetection {
    LOW, ANY, FALLING, RISING
};

typedef void (*ExternalInterruptCallback)();

typedef void (*ExternalInterruptSetup)(ExternalInterruptDetection);

typedef void (*ExternalInterruptTeardown)();

class TinyExternalInterrupt {
  friend void _ISRExternalInterruptCallbackFunction();
  public:
    TinyExternalInterrupt(ExternalInterruptSetup setup, ExternalInterruptTeardown teardown) : setup(setup), teardown(teardown) {}
    void on(ExternalInterruptDetection, ExternalInterruptCallback);
    void off();
  private:
    volatile ExternalInterruptCallback onInterrupt;
    ExternalInterruptSetup setup;
    ExternalInterruptTeardown teardown;
};

#endif