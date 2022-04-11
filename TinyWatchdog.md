## [TinyWatchdog](src/TinyWatchdog.h)

The interface of the watchog controller.

### Class TinyWatchdog

|Method|Parameters|Return|Description|
|-|-|-|-|
|arm|prescaler, callback||Run the callback inside an ISR after timeout. Higher prescaler value (0-9) will cause longer delay.|
|armReset|prescaler, callback||Run the callback inside an ISR after timeout and then reset after another timeout. If the callback is null, the reset is done after the first timeout. Higher prescaler value (0-9) will cause longer delay.|
|disarm|||Disable the watchdog.|
