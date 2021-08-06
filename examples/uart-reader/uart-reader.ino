#include <avr/interrupt.h>
#include <TinyUartReader.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

int main() {
  sei();
  uartReader.on(PB2, 9600, Timer1Compare, PinChangeB);
  while (1) {
    if (uartReader.inputAvailable()) {
      uartReader.read();
    }
    idleSleep();
  }
  return 0;
}
