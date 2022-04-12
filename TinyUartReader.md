## Class [TinyUartReader](src/TinyUartReader.h)

This class inherits from [TinyUartRead](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|rx, baud, timer, pinChange||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate. The "pinChange" will be enabled to interrupt on "rx" pin level change.|
|off|||Stop the UART. The "timer" will be stopped, the "pinChange" will be disabled.|
