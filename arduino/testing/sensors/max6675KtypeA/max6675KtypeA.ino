/*
  Thermocouple.

  Reads a temperature from a thermocouple based
  on the MAX6675 driver and displays it in the default Serial.

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, April, 2018.
  Released into the public domain.
*/

/* **************************************************************************
 *  Circuit:
 *    Arduino Uno   Arduino Mega  -->  
 *    CS0: pin  9   CS0: pin  9   -->  CS, CH0
 *    MISO: pin 12  MISO: pin 50  -->  DO
 *    SCK:  pin 13  SCK:  pin 52  -->  CLK
 *    GND           GND           -->  GND
 *    VCC           VCC           -->  Vin
 * **************************************************************************/



#include <MAX6675_Thermocouple.h>

#define SCK_PIN 3
#define CS_PIN  4
#define SO_PIN  5

//#define SCK_PIN 13
//#define CS_PIN  10
//#define SO_PIN  12

/**
   How many readings are taken to determine a mean temperature.
   The more values, the longer a calibration is performed,
   but the readings will be more accurate.
*/
#define READINGS_NUMBER 10

/**
   Delay time between a temperature readings
   from the temperature sensor (ms).
*/
#define DELAY_TIME 20

MAX6675_Thermocouple* thermocouple = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  thermocouple = new MAX6675_Thermocouple(
    SCK_PIN, CS_PIN, SO_PIN,
    READINGS_NUMBER, DELAY_TIME
  );
  /* or
    thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
    thermocouple->setReadingsNumber(READINGS_NUMBER);
    thermocouple->setDelayTime(DELAY_TIME);
  */
}

// the loop function runs over and over again forever
void loop() {
  const double celsius = thermocouple->readCelsius();
  const double kelvin = thermocouple->readKelvin();
  Serial.print(celsius, DEC);
  Serial.print("°C, ");
  Serial.print(kelvin, DEC);
  Serial.println("°K");
  delay(500);
}
