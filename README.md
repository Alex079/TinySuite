# TinySuite

A collection of utilities for ATTiny85.

# Pin change interrupt

## [TinyPinChange](src/TinyPinChange.h)

The interface of a pin change interrupt handler implementation.

### Class TinyPinChange

|Method|Parameters|Return|Description|
|-|-|-|-|
|(init)|setup, teardown||Instantiate the wrapper using the provided setup and teardown functions. Normally, the constructor should be invoked only once by an implementation to instantiate the wrapper and make it available for the "ISR" and "main".|
|on|pin, callback||Register the callback function for the pin.|
|off|pin||Unregister the callback function.|

### Types

|Name|Description|
|-|-|
|PinChangeCallback|A pointer to a callback function. The function may accept "pin" and "level" as parameters and should return void.|
|PinChangeSetup|A pointer to a setup function. The function may accept "pin" and "callback" as parameters and should return void.|
|PinChangeTeardown|A pointer to a teardown function. The function may accept "pin" as parameters and should return void.|

## [TinyPinChangeB](src/TinyPinChangeB.h)

The implementation of ATTiny85 port B pin change interrupt handler.

This header exposes
- an object **PinChangeB** of class TinyPinChange

## Extension points

It is possible to create other implementations as long as they are able to provide an instance of TinyPinChange class.

# Timer interrupt

## [TinyTimer](src/TinyTimer.h)

The interface of a timer interrupt handler implementation.

### Class TinyTimer

|Method|Parameters|Return|Description|
|-|-|-|-|
|(init)|setup, teardown||Instantiate the wrapper using the provided setup and teardown functions. Normally, the constructor should be invoked only once by an implementation to instantiate the wrapper and make it available for the "ISR" and "main".|
|on|ticks, callback||Register the callback function to run when a condition is met.|
|off|||Unregister the callback function.|

### Types

|Name|Description|
|-|-|
|TimerCallback|A pointer to a callback function. The function should return void.|
|TimerSetup|A pointer to a setup function. The function may accept "ticks" as parameters and should return void.|
|TimerTeardown|A pointer to a teardown function. The function should return void.|

## [TinyTimer0Compare](src/TinyTimer0Compare.h)

The implementation of ATTiny85 Timer0 "on compare" interrupt handler.

This header exposes
- an object **Timer0Compare** of class TinyTimer

## [TinyTimer0Overflow](src/TinyTimer0Overflow.h)

The implementation of ATTiny85 Timer0 "on overflow" interrupt handler.

This header exposes
- an object **Timer0Overflow** of class TinyTimer

## [TinyTimer1Compare](src/TinyTimer1Compare.h)

The implementation of ATTiny85 Timer1 "on compare" interrupt handler.

This header exposes
- an object **Timer1Compare** of class TinyTimer

## [TinyTimer1Overflow](src/TinyTimer1Overflow.h)

The implementation of ATTiny85 Timer1 "on overflow" interrupt handler.

This header exposes
- an object **Timer1Overflow** of class TinyTimer

## Extension points

It is possible to create other implementations as long as they are able to provide an instance of TinyTimer class.

# Watchdog interrupt

## [TinyWatchdog](src/TinyWatchdog.h)

The implementation of ATTiny85 Watchdog control.

This header exposes
- an object **Watchdog** of class TinyWatchdog

### Class TinyWatchdog

|Method|Parameters|Return|Description|
|-|-|-|-|
|arm|prescaler, callback||Run the callback inside an ISR after timeout. Higher prescaler value (0-9) will cause longer delay.|
|armReset|prescaler, callback||Run the callback inside an ISR after timeout and then reset after another timeout. If the callback is null, the reset is done after the first timeout. Higher prescaler value (0-9) will cause longer delay.|
|disarm|||Disable the watchdog.|

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

## [TinyUartBase](src/TinyUartBase.h)

The base for implementation of UART protocol. Normally, this header does not need to be included explicitly.

### Class TinyUartRead

|Method|Parameters|Return|Description|
|-|-|-|-|
|onRxPinChange|level||The callback used internally to handle pin change interrupt.|
|onTimerRx|||The callback used internally to handle timer interrupt.|
|inputAvailable||count|The amount of buffered incoming bytes.|
|inputCapacity||count|The amount of free space left in the input buffer.|
|peek||value|Get one byte from the input buffer. The buffer is not changed.|
|skip|||Remove one byte from the input buffer.|
|skipAll|||Clear the input buffer.|
|read||value|Get one byte from the input buffer. The value is removed from the buffer.|
|blockingRead||value|Performs checked "read". If there is no data in the input buffer, the main control flow will idle until the data is available.|

### Class TinyUartWrite

|Method|Parameters|Return|Description|
|-|-|-|-|
|onTimerTx|||The callback used internally to handle timer interrupt.|
|outputRemaining||count|The amount of buffered outgoing bytes.|
|outputCapacity||count|The amount of free space left in the output buffer.|
|write|value||Put one byte into the output buffer.|
|blockingWrite|value||Performs checked "write". If there is no free space left in the output buffer, the main control flow will idle until the free space is available. The main control flow will idle until all the outgoing data is sent.|

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

[Example](examples/uart-loop/uart-loop.ino)

### Class TinyUart

This class inherits from both TinyUartRead and TinyUartWrite.

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, tx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|

## [TinyUartReader](src/TinyUartReader.h)

The implementation of receive-only UART.

This header exposes an object **uartReader** of class TinyUartReader.

[Example](examples/uart-reader/uart-reader.ino)

### Class TinyUartReader

This class inherits from TinyUartRead.

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|

## [TinyUartWriter](src/TinyUartWriter.h)

The implementation of transmit-only UART.

This header exposes an object **uartWriter** of class TinyUartWriter.

[Example](examples/uart-writer/uart-writer.ino)

### Class TinyUartWriter

This class inherits from TinyUartWrite.

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|tx, baud, timer||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate.|
|off|||Stop the UART. The "timer" will be stopped.|

## [TinySerial](src/TinySerial.h)

The implementation of UART using Stream interface (Stream.h) and Tiny UART (TinyUart.h) backend.

[Example](examples/uart-print/uart-print.ino)

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

[Example](examples/nmea-time/nmea-time.ino)

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
- Timer0 match value is limited to 16-bit.
- UART has explicit dependency on port B registers, which makes it harder to use on other ATTinys.
