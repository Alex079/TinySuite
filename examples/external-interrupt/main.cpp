#include <avr/interrupt.h>
#include <TinyExternalInterrupt0.h>
#include <TinySleep.h>

void onInterrupt() {
    // wakeup and do something
}

int main()
{
    sei();
    // interrupt when INT0 (pin 7) has LOW level (RISING or FALLING do not wake up from deep sleep)
    ExternalInterrupt0.on(LOW, onInterrupt);
    while (1) {
        deepSleep();
    }
    return 0;
}
