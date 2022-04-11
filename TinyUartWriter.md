## Class [TinyUartWriter](src/TinyUartWriter.h)

This class inherits from [TinyUartWrite](TinyUartBase.md).

|Method|Parameters|Return|Description|
|-|-|-|-|
|on|tx, baud, timer||Start the UART. The "timer" will be enabled to interrupt at around "baud" * "TINY_UART_ONE_BIT_CLK" rate.|
|off|||Stop the UART. The "timer" will be stopped.|
