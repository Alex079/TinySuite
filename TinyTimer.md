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
