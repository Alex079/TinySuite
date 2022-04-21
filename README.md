# TinySuite

A collection of utilities for ATTiny85.

## Pin change interrupt

### [TinyPinChangeB](src/TinyPinChangeB.h)

The implementation of ATTiny85 port B pin change interrupt handler.

This header exposes an object **PinChangeB** of class [TinyPinChange](src/TinyPinChange.h).

## External interrupt

### [TinyExternalInterrupt0](src/TinyExternalInterrupt0.h)

The implementation of ATTiny85 external interrupt handler.

This header exposes an object **ExternalInterrupt0** of class [TinyExternalInterrupt](src/TinyExternalInterrupt.h).

[Example](examples/external-interrupt/main.cpp)

## Timer interrupt

### [TinyTimer0Compare](src/TinyTimer0Compare.h)

The implementation of ATTiny85 Timer0 "on compare" interrupt handler.

This header exposes an object **Timer0Compare** of class [TinyTimer](src/TinyTimer.h).

### [TinyTimer0Overflow](src/TinyTimer0Overflow.h)

The implementation of ATTiny85 Timer0 "on overflow" interrupt handler.

This header exposes an object **Timer0Overflow** of class [TinyTimer](src/TinyTimer.h).

### [TinyTimer1Compare](src/TinyTimer1Compare.h)

The implementation of ATTiny85 Timer1 "on compare" interrupt handler.

This header exposes an object **Timer1Compare** of class [TinyTimer](src/TinyTimer.h).

### [TinyTimer1Overflow](src/TinyTimer1Overflow.h)

The implementation of ATTiny85 Timer1 "on overflow" interrupt handler.

This header exposes an object **Timer1Overflow** of class [TinyTimer](src/TinyTimer.h).

[Example](examples/timer-overflow/main.cpp)

## Watchdog interrupt

### [TinyWatchdog](src/TinyWatchdog.h)

The implementation of ATTiny85 Watchdog controller.

This header exposes an object **Watchdog** of class TinyWatchdog.

[Example](examples/watchdog/main.cpp)

## Utilities

### [TinySleep](src/TinySleep.h)

A set of shortcut defines to put the ATTiny85 in sleep mode. PRR and ADCSRA are intact.

This header exposes:

|Name|Description|
|-|-|
|sleep(mode)|Set the specified mode and sleep.|
|deepSleep|Set power down mode, disable BOD, and sleep.|
|idleSleep|Set idle mode and sleep.|

### [TinyBuffer](src/TinyBuffer.h)

The 16-byte ring buffer implementation. This implementation does not perform any validation (i.e. it is possible to "get" when "empty" and "put" when "full"), the caller is expected to maintain the buffer consistency.

This header exposes the class **TinyBuffer**.

## UART

### [TinyUart](src/TinyUart.h)

The implementation of UART protocol:
- 8-bit value transmission
- one start and one stop bit, no parity bit
- no overrun / underrun / break detection

Features:
- 16-byte input and 16-byte output buffers
- full duplex transmission
- up to 19200 baud at 16 MHz internal oscillator
- can use any pins for RX and TX
- can use Timer0 or Timer1
- RX and TX are the IDs from the board definition (i.e. PB0)

This header exposes an object **uart** of class TinyUart.

[Example](examples/uart-loop/main.cpp)

### [TinyUartReader](src/TinyUartReader.h)

The implementation of receive-only UART.

This header exposes an object **uartReader** of class TinyUartReader.

[Example](examples/uart-reader/main.cpp)

### [TinyUartWriter](src/TinyUartWriter.h)

The implementation of transmit-only UART.

This header exposes an object **uartWriter** of class TinyUartWriter.md.

[Example](examples/uart-writer/main.cpp)

### [TinySerial](src/TinySerial.h)

The implementation of UART using Stream interface (Stream.h) and Tiny UART (TinyUart.h) backend.

This header exposes the class **TinySerial**.

This class inherits from Stream. See Stream.h from Arduino for details.

[Example](examples/uart-print/main.cpp)

## NMEA parser

### [TinyNmea](src/TinyNmea.h)

The NMEA sentence delegating parser implementation.

Features:
- checksum validation
- sentence filtering by type
- delegation of value extraction to provided parsers
- orchestration of parsing

This header exposes
- NmeaParser structure
- TinyNmea class

[Example](examples/nmea-time/main.cpp)

## Known Problems

- Timer0 and Timer1 may not work correctly with ATTinyCore because of the core-specific initialization.
- UART has explicit dependency on port B registers, which makes it harder to use on other ATTinys.
