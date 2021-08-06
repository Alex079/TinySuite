#include <avr/io.h>
#include "TinyUartBase.h"
#include "TinyUartConst.h"

#define setHigh(p) PORTB |= (1 << p)
#define setLow(p) PORTB &= ~(1 << p)

uint8_t TinyUartRead::inputAvailable() {
  return inputBuffer.countBusy();
}

uint8_t TinyUartRead::inputCapacity() {
  return inputBuffer.countFree();
}

uint8_t TinyUartRead::peek() {
  return inputBuffer.peek();
}

void TinyUartRead::skip() {
  inputBuffer.skip();
}

void TinyUartRead::skipAll() {
  inputBuffer.clear();
}

uint8_t TinyUartRead::read() {
  return inputBuffer.get();
}

uint8_t TinyUartRead::blockingRead() {
  while (!inputBuffer.countBusy()) {
    idleSleep();
  }
  return inputBuffer.get();
}

void TinyUartRead::onRxPinChange(bool value) {
  inputBit = value;

  switch (inputState) {

    case TINY_UART_STATE_IDLE:
      if (!inputBit) {
        inputBitInProgress = TINY_UART_HALF_BIT_CLK;
        inputState++;
      }
      break;

    case TINY_UART_STATE_STOP:
      if (inputBit) {
        inputBuffer.put(inputByte);
        inputState = TINY_UART_STATE_IDLE;
      }
      else { // emergency restart
        inputBitInProgress = TINY_UART_HALF_BIT_CLK;
        inputState = TINY_UART_STATE_START;
      }
      break;

    default:
      inputByte >>= 1;
      if (inputBit) inputByte |= 128;
      inputState++;
      if (inputState == TINY_UART_STATE_STOP) { // early stop on level change
        inputBuffer.put(inputByte);
        inputState = TINY_UART_STATE_IDLE;
      }
      else {
        inputBitInProgress = TINY_UART_ONE_AND_HALF_BIT_CLK;
      }
      break;

  }
}

void TinyUartRead::onTimerRx() {

  if (!inputState) return; // idle line state

  if (--inputBitInProgress) return; // keep current state

  switch (inputState) {

    case TINY_UART_STATE_START:
      if (inputBit) {
        inputState = TINY_UART_STATE_IDLE;
      }
      else {
        inputBitInProgress = TINY_UART_ONE_BIT_CLK;
        inputState++;
      }
      break;

    case TINY_UART_STATE_STOP:
      if (inputBit) inputBuffer.put(inputByte);
      inputState = TINY_UART_STATE_IDLE;
      break;

    default:
      inputByte >>= 1;
      if (inputBit) inputByte |= 128;
      inputBitInProgress = TINY_UART_ONE_BIT_CLK;
      inputState++;
      break;
  }
}

uint8_t TinyUartWrite::outputRemaining() {
  return outputBuffer.countBusy();
}

uint8_t TinyUartWrite::outputCapacity() {
  return outputBuffer.countFree();
}

void TinyUartWrite::write(const uint8_t v) {
  outputBuffer.put(v);
}

void TinyUartWrite::blockingWrite(const uint8_t v) {
  while (!outputBuffer.countFree()) {
    idleSleep();
  }
  outputBuffer.put(v);
  while (outputBuffer.countBusy()) {
    idleSleep();
  }
}

void TinyUartWrite::onTimerTx() {

  if (!outputState) { // idle line state
    if (outputBuffer.countBusy()) {
      outputBitInProgress = TINY_UART_ONE_BIT_CLK;
      outputState++;
    }
    return;
  }

  if (--outputBitInProgress) return; // hold the line

  switch (outputState) {

    case TINY_UART_STATE_START:
      setLow(output);
      outputByte = outputBuffer.peek();
      outputBitInProgress = TINY_UART_ONE_BIT_CLK;
      outputState++;
      break;

    case TINY_UART_STATE_STOP:
      setHigh(output);
      outputBuffer.skip();
      outputState = TINY_UART_STATE_IDLE;
      break;

    default:
      (outputByte & 1) ? setHigh(output) : setLow(output);
      outputByte >>= 1;
      outputBitInProgress = TINY_UART_ONE_BIT_CLK;
      outputState++;
      break;
  }
}
