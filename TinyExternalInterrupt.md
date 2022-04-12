## [TinyExternalInterrupt](src/TinyExternalInterrupt.h)

The interface of an external interrupt handler implementation.

### Class TinyExternalInterrupt

|Method|Parameters|Return|Description|
|-|-|-|-|
|(init)|setup, teardown||Instantiate the wrapper using the provided setup and teardown functions. Normally, the constructor should be invoked only once by an implementation to instantiate the wrapper and make it available for the "ISR" and "main".|
|on|detectionType, callback||Register the callback function to run when the configured INT0 pin level is detected.|
|off|||Unregister the callback function.|

### Types

|Name|Description|
|-|-|
|ExternalInterruptCallback|A pointer to a callback function. The function should return void.|
|ExternalInterruptSetup|A pointer to a setup function. The function may accept ExternalInterruptDetection as parameters and should return void.|
|ExternalInterruptTeardown|A pointer to a teardown function. The function should return void.|
|ExternalInterruptDetection|An enumeration of interrupt detection types: LOW, ANY, FALLING, RISING.|
