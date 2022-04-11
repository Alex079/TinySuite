# TinySuite

A collection of utilities for ATTiny85.

# Pin change interrupt

## [TinyPinChangeB](src/TinyPinChangeB.h)

The implementation of ATTiny85 port B pin change interrupt handler.

This header exposes an object **PinChangeB** of class [TinyPinChange](TinyPinChange.md)

## Extension points

It is possible to create other implementations as long as they are able to provide an instance of TinyPinChange class.

# Timer interrupt

## [TinyTimer0Compare](src/TinyTimer0Compare.h)

The implementation of ATTiny85 Timer0 "on compare" interrupt handler.

This header exposes an object **Timer0Compare** of class [TinyTimer](TinyTimer.md)

## [TinyTimer0Overflow](src/TinyTimer0Overflow.h)

The implementation of ATTiny85 Timer0 "on overflow" interrupt handler.

This header exposes an object **Timer0Overflow** of class [TinyTimer](TinyTimer.md)

## [TinyTimer1Compare](src/TinyTimer1Compare.h)

The implementation of ATTiny85 Timer1 "on compare" interrupt handler.

This header exposes an object **Timer1Compare** of class [TinyTimer](TinyTimer.md)

## [TinyTimer1Overflow](src/TinyTimer1Overflow.h)

The implementation of ATTiny85 Timer1 "on overflow" interrupt handler.

This header exposes an object **Timer1Overflow** of class [TinyTimer](TinyTimer.md)

[Example](examples/timer-overflow/main.cpp)

## Extension points

It is possible to create other implementations as long as they are able to provide an instance of TinyTimer class.

# Watchdog interrupt

## [TinyWatchdog](src/TinyWatchdog.h)

The implementation of ATTiny85 Watchdog controller.

This header exposes an object **Watchdog** of class [TinyWatchdog](TinyWatchdog.md)

[Example](examples/watchdog/main.cpp)

# Sleep utilities

## [TinySleep](src/TinySleep.h)

A set of shortcut defines to put the ATTiny85 in sleep mode. PRR and ADCSRA are intact.

### Defines

|Name|Description|
|-|-|
|sleep(mode)|Set the specified mode and sleep.|
|deepSleep|Set power down mode, disable BOD, and sleep.|
|idleSleep|Set idle mode and sleep.|

# Buffer

## [TinyBuffer](src/TinyBuffer.h)

The 16-byte ring buffer implementation. This implementation does not perform any validation (i.e. it is possible to "get" when "empty" and "put" when "full"), the caller is expected to maintain the buffer consistency.
<pre>
Head and tail indices are incremented "from left to right".
Start over from the left-hand side on overflow.
"X" - some value, " " - some garbage.
ex.1.
     [ XXXXXXXXX      ] 9/16
      ↑        ↑       
   tail     head       
ex.2.
     [XXXXX          X] 6/16
          ↑         ↑  
       head      tail  
</pre>

### Class TinyBuffer

|Method|Parameters|Return|Description|
|-|-|-|-|
|countBusy||count|Get the size of data.|
|countFree||count|Get the size of free space.|
|clear|||Mark the buffer as empty.|
|put|value||Advance the buffer head and put one byte into head.|
|get||value|Advance the buffer tail and get one byte.|
|peek||value|Peek the value at the next buffer index.|
|skip|||Advance the buffer tail.|

# UART

## [TinyUart](src/TinyUart.h)

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

### Class TinyUart

This class inherits from both [TinyUartRead and TinyUartWrite](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, tx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|

## [TinyUartReader](src/TinyUartReader.h)

The implementation of receive-only UART.

This header exposes an object **uartReader** of class TinyUartReader.

[Example](examples/uart-reader/main.cpp)

### Class TinyUartReader

This class inherits from [TinyUartRead](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|

## [TinyUartWriter](src/TinyUartWriter.h)

The implementation of transmit-only UART.

This header exposes an object **uartWriter** of class TinyUartWriter.

[Example](examples/uart-writer/main.cpp)

### Class TinyUartWriter

This class inherits from [TinyUartWrite](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|tx, baud, timer||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate.|
|off|||Stop the UART. The "timer" will be stopped.|

## [TinySerial](src/TinySerial.h)

The implementation of UART using Stream interface (Stream.h) and Tiny UART (TinyUart.h) backend.

[Example](examples/uart-print/main.cpp)

### Class TinySerial

This class inherits from Stream. See Stream.h from Arduino for details.

# NMEA parser

## [TinyNmea](src/TinyNmea.h)

The NMEA sentence delegating parser implementation.

Features:
- checksum validation
- sentence filtering by type
- delegation of value extraction to provided parsers
- orchestration of parsing

[Example](examples/nmea-time/main.cpp)

### Struct NmeaParser

|Field|Description|
|-|-|
|type|Last three symbols of NMEA sentence type designator. Used in parser lookup, type match is "ends with", case-sensitive.|
|call|A pointer to parser function to invoke when the matching NMEA sentence is received. The function may accept "term" (the C-String containing NMEA term) and "termIndex" (a 0-based index of the term in the sentence).|

### Class TinyNmea

|Method|Parameters|Return|Description|
|-|-|-|-|
|(init)|parsers, parsersCount||Instantiate the parser. The "parsers" is the array of "parsersCount" size, which contains "NmeaParser" structures.|
|next|char||Feed the parser with one character.|

# Known Problems

- Timer0 and Timer1 may not work correctly with ATTinyCore because of the core-specific initialization.
- UART has explicit dependency on port B registers, which makes it harder to use on other ATTinys.
