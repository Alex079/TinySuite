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
