#include <avr/interrupt.h>
#include <TinyTimer0Overflow.h>
#include <TinyTimer1Overflow.h>

void runOnTimer0() {
  //
}

void runOnTimer1() {
  //
}

int main() {
  sei();
  Timer0Overflow.on(0x3fc00, runOnTimer0);
  Timer1Overflow.on(0x3fc000, runOnTimer1);
  while (1) {
    // do nothing
  }
  return 0;
}
