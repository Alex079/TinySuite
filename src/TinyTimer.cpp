#include <stdint.h>
#include "TinyTimer.h"

void TinyTimer::on(const uint16_t match, TimerCallback callback) {
  onTimer = callback;
  setup(match);
}

void TinyTimer::off() {
  teardown();
  onTimer = 0;
}
