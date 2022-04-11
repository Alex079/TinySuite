#include <avr/interrupt.h>
#include <TinyUartWriter.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

// output "A"+<LF> on PB1 (pin 6) at 9600 baud using Timer1 in compare mode and then stop
int main() {
  sei();
  uartWriter.on(PB1, 9600, Timer1Compare);
  uartWriter.write('A');
  uartWriter.write(10);
  while (uartWriter.outputRemaining()) idleSleep();
  uartWriter.off();
  return 0;
}
