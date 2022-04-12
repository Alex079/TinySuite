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
