#include <TinyUartWriter.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

int main() {
  sei();
  uartWriter.on(PB1, 9600, Timer1Compare);
  uartWriter.write('A');
  uartWriter.write(10);
  while (uartWriter.outputRemaining()) idleSleep();
  uartWriter.off();
  return 0;
}
