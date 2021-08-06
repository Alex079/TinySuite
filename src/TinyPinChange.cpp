#include <stdint.h>
#include "TinyPinChange.h"

void TinyPinChange::on(uint8_t pin, PinChangeCallback callback) {
  setup(pin, callback);
}

void TinyPinChange::off(uint8_t pin) {
  teardown(pin);
}
