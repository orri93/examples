
// the sensor communicates using SPI, so include the hardware SPI library:
#include <SPI.h>

// include Playing With Fusion MAX31865 libraries
#include <PlayingWithFusion_MAX31865.h>              // core library
#include <PlayingWithFusion_MAX31865_STRUCT.h>       // struct library

#include "max6675.h"

#define SERIAL_BAUD   115200

#define DELAY_SETUP_END  500

#define INTERVAL_MAIN   1000

#define PIN_SCK            3
#define PIN_SC             4
#define PIN_DO             5

#define PIN_SPI_MAX_CS    10

#define MAX_RTD_TYPE       2

// set to 2WIRE or 4WIRE as necessary
#define MAX_WIRES       RTD_3_WIRE

int thermoDO = PIN_DO;
int thermoCS = PIN_SC;
int thermoCLK = PIN_SCK;

double t1, t2;

unsigned long long tick, next = 0;

boolean ismax31865fault = false;

//PWFusion_MAX31865_RTD pwf_max_rtd(PIN_SPI_MAX_CS);
PWFusion_MAX31865_RTD* pwf_max_rtd = nullptr; /* (PIN_SPI_MAX_CS); */
// structures for holding RTD values
struct var_max31865 max_rtd_values;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(SERIAL_BAUD);

  // setup for the the SPI library:
  SPI.begin();                            // begin SPI
  SPI.setClockDivider(SPI_CLOCK_DIV16);   // SPI speed to SPI_CLOCK_DIV16 (1MHz)
  SPI.setDataMode(SPI_MODE3);             // MAX31865 works in MODE1 or MODE3

  // initalize the chip select pin
  pinMode(PIN_SPI_MAX_CS, OUTPUT);

  if(pwf_max_rtd == nullptr) {
    pwf_max_rtd = new PWFusion_MAX31865_RTD(PIN_SPI_MAX_CS);
  }
  // configure channel 0
  pwf_max_rtd->MAX31865_config(&max_rtd_values, MAX_WIRES);
  max_rtd_values.RTD_type = MAX_RTD_TYPE;

  Serial.println("MAX6675 and MAX31865 testing");

  // wait for MAX chip to stabilize
  delay(DELAY_SETUP_END);
}

void loop() {
  tick = millis();

  if(tick >= next) {
    next = tick + INTERVAL_MAIN;

    // basic readout test, just print the current temp
    t1 = thermocouple.readCelsius();

    /* Read max */
    pwf_max_rtd->MAX31865_full_read(&max_rtd_values);

    if(max_rtd_values.status == 0) {
      if(ismax31865fault) {
        ismax31865fault = false;
        Serial.println("Max 31865 recovery!");
      }
      t2 = (((double)max_rtd_values.rtd_res_raw) / 32.0) - 256.0;
    } else {
      if(!ismax31865fault) {
        t2 = -999.0;
        Serial.println("Max 31865 fault!");
        ismax31865fault = true;
      }
    }

    Serial.print(t1, 4);
    Serial.print(",");
    Serial.print(t2, 4);
    Serial.println();
 
  }
}
