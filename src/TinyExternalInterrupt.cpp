#include <stdint.h>
#include "TinyExternalInterrupt.h"

void TinyExternalInterrupt::on(ExternalInterruptDetection detection, ExternalInterruptCallback callback) {
  onInterrupt = callback;
  setup(detection);
}

void TinyExternalInterrupt::off() {
  teardown();
  onInterrupt = 0;
}
