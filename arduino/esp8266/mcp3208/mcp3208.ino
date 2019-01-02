// SELPIN   10   //Selection Pin (CS)
// DATAOUT  11   //MOSI 
// DATAIN   12   //MISO 
// SPICLOCK 13   //Clock

#include "AH_MCP320x.h"
#include <SPI.h>

#define BAUD_RATE 115200

#define PIN_CS D8
//#define PIN_DO_MOSI D7
//#define PIN_DI_MISO D6
//#define PIN_

#define INTERVAL 10000

#define CHANNELS 8

byte i;
short v;
unsigned long tick, next = 0;

AH_MCP320x ad(PIN_CS);             //Object definition with D9 as CS, other pins are defined by spi interface (faster mode).
//AH_MCP320x ADC_pin(10,11,12,13);  //Object definition with free definition of communication pins (slower mode).

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.println("Example for MCP3208 with ESP8266");
}

void loop()
{
  tick = millis();
  if(tick > next) {
    for(i = 0; i < CHANNELS; i++) {
      if(i > 0) {
        Serial.print(",");
      }
      v = ad.readCH(i);
      Serial.print(v);
    }
    Serial.println();
    next = tick + INTERVAL;
  }
}