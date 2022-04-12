#include <avr/interrupt.h>
#include <TinyWatchdog.h>
#include <TinySleep.h>

int main() {
  sei();
  Watchdog.arm(9, [](){
    // do something after 8 seconds (prescaler value of 9 translates to 8 seconds)
  });
  deepSleep();
  // at this point the watchdog will interrupt the sleep
  cli();
  deepSleep();
}
