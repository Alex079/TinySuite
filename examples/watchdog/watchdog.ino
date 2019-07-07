#include <TinyWatchdog.h>
#include <TinySleep.h>

int main() {
  sei();
  Watchdog.arm(9, [](){
    // do something after 1000*2^(9+1) cycles
  });
  ADCSRA = 0;
  deepSleep();
  // wakeup and sleep forever
  cli();
  ADCSRA = 0;
  deepSleep();
}
