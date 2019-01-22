/* SPI Slave */

#include<SPI.h>                             

#define SERIAL_BAUD 115200
#define FDS_SERIAL_OUTPUT FDS_SERIAL_OUTPUT_DEBUG
//#define FDS_SERIAL_OUTPUT FDS_SERIAL_OUTPUT_CSV

#include "tick.h"
#include "debug.h"

#define PIN_RECEIVE_LED            6
#define PIN_ALIVE_LED              3


#define SPI_MISO_PIN           MISO
#define SPI_PRO_MICRO_SLAVE_CS   10
#define SPI_INTERVAL             10

#define STATUS_NORMAL   0x00
#define STATUS_RECEIVED 0x01

Tick maintick(SPI_INTERVAL);

byte sspireceive, sspisend,
  x = 255,
  status = STATUS_NORMAL,
  ledreceivestage = LOW,
  ledalivestage = HIGH;

unsigned long long tick;

// Inerrrput routine function
ISR (SPI_STC_vect) 
{
  // Value received from master if store in variable slavereceived
  sspireceive = SPDR;
  status = STATUS_RECEIVED;
}

void setup() {
#ifdef PIN_RECEIVE_LED
  pinMode(PIN_RECEIVE_LED, OUTPUT);
  digitalWrite(PIN_RECEIVE_LED, ledreceivestage);
#endif
#ifdef PIN_ALIVE_LED
  pinMode(PIN_ALIVE_LED, OUTPUT);
  digitalWrite(PIN_ALIVE_LED, ledalivestage);
#endif

  FDS_DEBUG_BEGIN();
  FDS_DEBUGLN("SPI Testing - Slave");
  pinMode(SPI_PRO_MICRO_SLAVE_CS, INPUT);
  //digitalWrite(SPI_PRO_MICRO_SLAVE_CS, HIGH);
  FDS_DEBUG("My CS is ");
  FDS_DEBUG(SPI_PRO_MICRO_SLAVE_CS, DEC);
  FDS_DEBUGLN(" and has been configured as Input");
  pinMode(SPI_MISO_PIN, OUTPUT);
  FDS_DEBUG("SPI Slaves MISO pin ");
  FDS_DEBUG(SPI_MISO_PIN);
  FDS_DEBUG(" had been set as Output (Have to Send data to Master)");
  
  //Turn on SPI in Slave Mode
  SPCR |= _BV(SPE);

  //Interuupt ON is set for SPI commnucation
  SPI.attachInterrupt();
}

void loop() {
  tick = millis();

  if(maintick.is(tick)) {
#ifdef PIN_ALIVE_LED
    ledalivestage = ledalivestage == HIGH ? LOW : HIGH;
    digitalWrite(PIN_ALIVE_LED, ledalivestage);
#endif
    switch(status) {
    case STATUS_RECEIVED:
#ifdef PIN_RECEIVE_LED
      ledreceivestage = HIGH;
      digitalWrite(PIN_RECEIVE_LED, ledreceivestage);
#endif
      sspisend = x;
      FDS_DEBUG("Received ");
      FDS_DEBUG(sspireceive);
      FDS_DEBUG(" from master and replying with ");
      FDS_DEBUGLN(sspisend);
      x = x > 0 ? x - 1 : 255;
      SPDR = sspisend;
      status = STATUS_NORMAL;
      break;
    default:
#ifdef PIN_RECEIVE_LED
      if(ledreceivestage == HIGH) {
        ledreceivestage = LOW;
        FDS_DEBUGLN("Turning receive led off");;
        digitalWrite(PIN_RECEIVE_LED, ledreceivestage);
      }
#endif
      break;
    }
  }
}
