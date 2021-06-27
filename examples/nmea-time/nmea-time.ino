#include <string.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <TinySleep.h>
#include <TinyTimer1Compare.h>
#include <TinyPinChangeB.h>
#include <TinyUartReader.h>
#include <TinyNmea.h>

struct NmeaData {
  bool fresh;
  char time[18]; // "hh:mm:ss DD/MM/YY"
};

NmeaData data;

NmeaParser config[] = {
  {{'Z','D','A'}, [](const char* term, const uint8_t index) {
    // $GPZDA,201530.00,04,07,2002,00,00*60
    switch (index) {
      case 0: // time
        for (uint8_t i = 0, j = 0; i < 6; i+=2, j+=3) {
          memcpy(&data.time[j], &term[i], 2);
        }
        data.time[2] = ':';
        data.time[5] = ':';
        data.time[8] = ' ';
        break;
      case 1: // day
        memcpy(&data.time[9], &term[0], 2);
        data.time[11] = '/';
        break;
      case 2: // month
        memcpy(&data.time[12], &term[0], 2);
        data.time[14] = '/';
        break;
      case 3: // year
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
  uartReader.on(PB2, 9600, Timer1Compare, PinChangeB);
  while (1) {
    while (uartReader.inputAvailable()) {
      nmea.next(uartReader.read());
    }
    if (data.fresh) {
      data.fresh = false;
      //data.time;
    }
    idleSleep();
  }
  return 0;
}
