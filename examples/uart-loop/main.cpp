#include <avr/interrupt.h>
#include <TinySleep.h>
#include <TinyUart.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

// continuously read bytes from PB2 (pin 7) and repeat them to PB1 (pin 6)
// at 9600 baud using Timer1 in compare mode
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

/* Commented out because Arduino dumps ELF file into HEX file for flashing
// FUSES = {
//   .low = 0xFF & FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3, // F_CPU: 16 MHz
//   .high = 0xFF & FUSE_SPIEN & FUSE_EESAVE,
//   .extended = 0xFF
// };
*/
