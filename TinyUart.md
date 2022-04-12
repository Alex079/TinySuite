## Class [TinyUart](src/TinyUart.h)

This class inherits from both [TinyUartRead and TinyUartWrite](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, tx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|
