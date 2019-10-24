/*
  TinyPinChange
*/
#ifndef TinyPinChangeB_h
#define TinyPinChangeB_h

#include <TinyPinChange.h>
#include <avr/interrupt.h>

#define TINY_PINB_CHANGE_MAX 6

volatile PinChangeCallback onPinChangeB[TINY_PINB_CHANGE_MAX] = {};
volatile uint8_t storedPINB;
volatile uint8_t storedGIMSKB;

TinyPinChange PinChangeB(
  [](uint8_t pin, PinChangeCallback callback) {
    storedGIMSKB = GIMSK & (1 << PCIE);
    GIMSK |= (1 << PCIE);
    onPinChangeB[pin] = callback;
    storedPINB = PINB;
    PCMSK |= (1 << pin);
  },
  [](uint8_t pin) {
    PCMSK &= ~(1 << pin);
    onPinChangeB[pin] = 0;
    GIMSK = (GIMSK & ~(1 << PCIE)) | storedGIMSKB;
  });

ISR(PCINT0_vect) {
  uint8_t data = PINB;
  uint8_t changes = (data ^ storedPINB);
  storedPINB = data;
  uint8_t pin = 0;
  while (changes) {
    if ( (changes & 1) && (onPinChangeB[pin]) ) {
      onPinChangeB[pin](pin, data & 1);
    }
    changes >>= 1;
    data >>= 1;
    pin++;
  }
}

#endif
