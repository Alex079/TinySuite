#include <avr/interrupt.h>
#include <Arduino.h>
#include <TinySerial.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>

TinySerial serial(PB2, PB1, Timer1Compare, PinChangeB);

void setup() {
  sei();
  serial.begin(9600);
}

void loop() {
  delay(5000);
  serial.print(F("this is a test\n"));
}
