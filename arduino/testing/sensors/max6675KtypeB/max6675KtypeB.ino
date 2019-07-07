// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

/* **************************************************************************
 *  Circuit:
 *    Arduino Uno   Arduino Mega  -->  
 *    CS0: pin  9   CS0: pin  9   -->  CS, CH0
 *    MISO: pin 12  MISO: pin 50  -->  DO
 *    SCK:  pin 13  SCK:  pin 52  -->  CLK
 *    GND           GND           -->  GND
 *    VCC           VCC           -->  Vin
 * **************************************************************************/

// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "max6675.h"

#define PIN_SCK 3
#define PIN_SC  4
#define PIN_DO  5



//#define PIN_SCK 13
//#define PIN_SC  10
//#define PIN_DO  12

int thermoDO = PIN_DO;
int thermoCS = PIN_SC;
int thermoCLK = PIN_SCK;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  //pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  //pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  double t = thermocouple.readCelsius();
  
  Serial.print(t, 4);
  Serial.println("°C");
 
  delay(1000);
}
