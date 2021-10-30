#include <avr/interrupt.h>
#include <TinyExternalInterrupt0.h>
#include <TinySleep.h>

int main()
{
    sei();
    ExternalInterrupt0.on(LOW, onInterrupt);
    while (1) {
        deepSleep();
    }
    return 0;
}

void onInterrupt() {
    // wakeup and do something when INT0 pin has low level
}
