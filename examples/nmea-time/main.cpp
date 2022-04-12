#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>
#include <TinyUartReader.h>
#include <TinyNmea.h>

struct NmeaData {
  bool fresh; // custom data readiness indicator
  char time[18]; // "hh:mm:ss DD/MM/YY"
};

// result data holder
NmeaData data;

// parser configuration array
NmeaParser config[] = {
  // this function will be called for every term in ZDA statement
  {{'Z','D','A'}, [](const char* term, const uint8_t index) {
    // i.e. $GPZDA,201530.00,04,07,2002,00,00*60
    switch (index) {
      case 0: // time (term = "201530.00")
        for (uint8_t i = 0, j = 0; i < 6; i+=2, j+=3) {
          memcpy(&data.time[j], &term[i], 2);
        }
        data.time[2] = ':';
        data.time[5] = ':';
        data.time[8] = ' ';
        break;
      case 1: // day (term = "04")
        memcpy(&data.time[9], &term[0], 2);
        data.time[11] = '/';
        break;
      case 2: // month (term = "07")
        memcpy(&data.time[12], &term[0], 2);
        data.time[14] = '/';
        break;
      case 3: // year (term = "2002")
        memcpy(&data.time[15], &term[2], 2);
        data.time[17] = 0;
        data.fresh = true;
        break;
    }
  }}
};

TinyNmea nmea(config, sizeof(config));

int main() {
  sei();
  // continuously read from PB2 (pin 7) at 9600 baud using Timer1 in compare mode
  uartReader.on(PB2, 9600, Timer1Compare, PinChangeB);
  while (1) {
    while (uartReader.inputAvailable()) {
      // send each symbol to NMEA parser
      nmea.next(uartReader.read());
    }
    if (data.fresh) {
      data.fresh = false;
      // make use of data.time value
    }
    idleSleep();
  }
  return 0;
}
