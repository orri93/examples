/* SPI Master */

#include<SPI.h>                             

#define SERIAL_BAUD 115200
#define FDS_SERIAL_OUTPUT FDS_SERIAL_OUTPUT_DEBUG
//#define FDS_SERIAL_OUTPUT FDS_SERIAL_OUTPUT_CSV

#include "tick.h"
#include "debug.h"

#define PIN_LED                   6

#define SPI_CLK_SPEC SPI_CLOCK_DIV8
#define SPI_PRO_MICRO_SLAVE_CS   10

#define SPI_INTERVAL  100

Tick spitick(SPI_INTERVAL);

byte mspireceive, mspisend, x = 0, ledstage = LOW;

unsigned long long tick;

void setup() {
#ifdef PIN_LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, ledstage);
#endif
  FDS_DEBUG_BEGIN();
  FDS_DEBUGLN("SPI Testing - Master");
  SPI.begin();
  SPI.setClockDivider(SPI_CLK_SPEC);
  FDS_DEBUG("SPI clock divider set to ");
  FDS_DEBUGLN(SPI_CLK_SPEC, DEC);
  pinMode(SPI_PRO_MICRO_SLAVE_CS, OUTPUT);
  FDS_DEBUG("Slave CS is ");
  FDS_DEBUG(SPI_PRO_MICRO_SLAVE_CS, DEC);
  FDS_DEBUGLN(" and has been configured as Output and setting to High for disabled");
  digitalWrite(SPI_PRO_MICRO_SLAVE_CS, HIGH);
}

void loop() {
  tick = millis();

  if(spitick.is(tick)) {
#ifdef PIN_LED
  ledstage = ledstage == HIGH ? LOW : HIGH;
  digitalWrite(PIN_LED, ledstage);
#endif

    digitalWrite(SPI_PRO_MICRO_SLAVE_CS, LOW);
    mspisend = x;
    mspireceive = SPI.transfer(mspisend);
    FDS_DEBUG("Sending ");
    FDS_DEBUG(mspisend);
    FDS_DEBUG(" to slave and receiving ");
    FDS_DEBUG(mspireceive);
    FDS_DEBUGLN(" from slave.");
    digitalWrite(SPI_PRO_MICRO_SLAVE_CS, HIGH);
    x = x < 255 ? x + 1 : 0;
  }
}
