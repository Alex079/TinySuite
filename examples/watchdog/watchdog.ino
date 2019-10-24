#include <TinyWatchdog.h>
#include <TinySleep.h>
#include <avr/interrupt.h>

int main() {
  sei();
  Watchdog.arm(9, [](){
    // do something after 8 seconds
  });
  deepSleep();
  // wakeup and sleep forever
  cli();
  deepSleep();
}
