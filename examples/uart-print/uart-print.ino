#include <TinySerial.h>
#include <TinyTimer1.h>
#include <TinyPinChangeB.h>

TinySerial serial(PB2, PB1, Timer1, PinChangeB);

void setup() {
  sei();
  serial.begin(9600);
}

void loop() {
  delay(5000);
  serial.print(F("this is a test\n"));
}
