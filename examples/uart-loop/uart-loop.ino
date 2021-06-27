#include <avr/interrupt.h>
#include <TinySleep.h>
#include <TinyUart.h>
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

FUSES = {
  .low = 0xFF & FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3,
  .high = 0xFF & FUSE_SPIEN & FUSE_EESAVE,
  .extended = 0xFF
};
