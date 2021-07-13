#include <avr/interrupt.h>
#include <TinyTimer0Overflow.h>
#include <TinyTimer1Overflow.h>

int main() {
  sei();
  Timer0Overflow.on(65535, []() { PORTB ^= (1 << PB0); });
  Timer1Overflow.on(65535, []() { PORTB ^= (1 << PB1); });
  while (1) {
    // do nothing
  }
  return 0;
}

FUSES = {
  .low = 0xFF & FUSE_CKDIV8 & FUSE_SUT0 & FUSE_CKSEL0 & FUSE_CKSEL2 & FUSE_CKSEL3,
  .high = 0xFF & FUSE_SPIEN & FUSE_EESAVE,
  .extended = 0xFF
};