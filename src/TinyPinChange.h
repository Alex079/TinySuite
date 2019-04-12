/*
  TinyPinChange
*/
#ifndef TinyPinChange_h
#define TinyPinChange_h

#include <stdint.h>

typedef void (*PinChangeCallback)(uint8_t, bool);

typedef void (*PinChangeSetup)(uint8_t, PinChangeCallback);

typedef void (*PinChangeTeardown)(uint8_t);

class TinyPinChange {
public:
  void on(uint8_t pin, PinChangeCallback callback) { setup(pin, callback); }
  void off(uint8_t pin) { teardown(pin); }
  TinyPinChange(PinChangeSetup setup, PinChangeTeardown teardown) : setup(setup), teardown(teardown) {}
protected:
  PinChangeSetup setup;
  PinChangeTeardown teardown;
private:
};

#endif
