#include <TinyUart.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

int main() {
  sei();
  uart.on(PB2, PB1, 9600, Timer1Compare, PinChangeB);
  while (1) {
    if (uart.inputAvailable()) {
      uart.write(uart.read());
    }
    idleSleep();
  }
  return 0;
}
