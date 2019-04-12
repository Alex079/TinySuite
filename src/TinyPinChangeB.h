/*
  TinyPinChange
*/
#ifndef TinyPinChangeB_h
#define TinyPinChangeB_h

#include <TinyPinChange.h>
#include <avr/interrupt.h>

#define TINY_PINB_CHANGE_MAX 6

volatile PinChangeCallback onPinB[TINY_PINB_CHANGE_MAX] = {};
volatile uint8_t storedPINB;
volatile uint8_t storedGIMSKB;

void setupB(uint8_t pin, PinChangeCallback callback) {
  uint8_t i = 0;
  while ((i < TINY_PINB_CHANGE_MAX) && !onPinB[i]) i++;
  if (i == TINY_PINB_CHANGE_MAX) {
    storedGIMSKB = GIMSK & (1 << PCIE);
    GIMSK |= (1 << PCIE);
  }
  onPinB[pin] = callback;
  storedPINB = PINB;
  PCMSK |= (1 << pin);
}

void teardownB(uint8_t pin) {
  PCMSK &= ~(1 << pin);
  onPinB[pin] = 0;
  uint8_t i = 0;
  while ((i < TINY_PINB_CHANGE_MAX) && !onPinB[i]) i++;
  if (i == TINY_PINB_CHANGE_MAX) {
    GIMSK = (GIMSK & ~(1 << PCIE)) | storedGIMSKB;
  }
}

TinyPinChange PinChangeB(setupB, teardownB);

ISR(PCINT0_vect) {
  uint8_t data = PINB;
  uint8_t changes = (data ^ storedPINB);
  storedPINB = data;
  uint8_t pin = 0;
  while (changes) {
    if ( (changes & 1) && (onPinB[pin]) ) {
      onPinB[pin](pin, data & 1);
    }
    changes >>= 1;
    data >>= 1;
    pin++;
  }
}

#endif
