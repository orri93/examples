// SELPIN   10   //Selection Pin (CS)
// DATAOUT  11   //MOSI 
// DATAIN   12   //MISO 
// SPICLOCK 13   //Clock

#include "AH_MCP320x.h"
#include <SPI.h>

#define BAUD_RATE 115200

//#define PIN_CS D8
#define PIN_CS 7  /* Pro Micro 3.3V */
//#define PIN_DO_MOSI D7
//#define PIN_DI_MISO D6
//#define PIN_

#define PIN_LED_HEARTBEAT        5

#define INTERVAL 1000

#define HEARTBEAT_STEPS      0.001

#define CHANNELS                 8

#define MESSAGE_SIZE            32

byte i;
short v;
unsigned long tick, next = 0;

char message[MESSAGE_SIZE];

AH_MCP320x ad(PIN_CS);             //Object definition with D9 as CS, other pins are defined by spi interface (faster mode).
//AH_MCP320x ADC_pin(10,11,12,13);  //Object definition with free definition of communication pins (slower mode).

float heartbeatval, heartbeatat = 0;

void setup()
{
  Serial.begin(BAUD_RATE);
  Serial.println("Testing MCP3208");
#ifdef PIN_LED_HEARTBEAT
  pinMode(PIN_LED_HEARTBEAT, OUTPUT);
  digitalWrite(PIN_LED_HEARTBEAT, LOW);
  snprintf(
    message,
    MESSAGE_SIZE,
    "Heartbeat LED can be connected to pin %u",
    PIN_LED_HEARTBEAT);
  Serial.println(message);
#endif
  pinMode(PIN_CS, OUTPUT);
}

void loop()
{
#if defined(PIN_LED_HEARTBEAT)
  heartbeatval = sin(heartbeatat) * 127.5 + 127.5;
  analogWrite(PIN_LED_HEARTBEAT, (int)heartbeatval);
  heartbeatat = heartbeatat <  6.283 /* 2*PI */ ?
    heartbeatat + HEARTBEAT_STEPS : 0.0;
#endif

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