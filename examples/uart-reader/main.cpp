#include <avr/interrupt.h>
#include <TinyUartReader.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

// continuously read from PB2 (pin 7) at 9600 baud using Timer1 in compare mode
int main() {
  sei();
  uartReader.on(PB2, 9600, Timer1Compare, PinChangeB);
  while (1) {
    if (uartReader.inputAvailable()) {
      uint8_t value = uartReader.read();
      // do something with the value
    }
    idleSleep();
  }
  return 0;
}
