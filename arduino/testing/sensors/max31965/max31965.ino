/* **************************************************************************
 * ADDITIONAL NOTES:
 * This file configures then runs a program on an Arduino Uno to read a 2-ch
 * MAX31865 RTD-to-digital converter breakout board and print results to
 * a serial port. Communication is via SPI built-in library.
 *    - Configure Arduino Uno
 *    - Configure and read resistances and statuses from MAX31865 IC 
 *      - Write config registers (MAX31865 starts up in a low-power state)
 *      - RTD resistance register
 *      - High and low status thresholds 
 *      - Fault statuses
 *    - Write formatted information to serial port
 *  Circuit:
 *    Arduino Uno   Arduino Mega  -->  SEN-30201
 *    CS0: pin  9   CS0: pin  9   -->  CS, CH0
 *    MOSI: pin 11  MOSI: pin 51  -->  SDI (must not be changed for hardware SPI)
 *    MISO: pin 12  MISO: pin 50  -->  SDO (must not be changed for hardware SPI)
 *    SCK:  pin 13  SCK:  pin 52  -->  SCLK (must not be changed for hardware SPI)
 *    GND           GND           -->  GND
 *    5V            5V            -->  Vin (supply with same voltage as Arduino I/O, 5V)
 * **************************************************************************/

// the sensor communicates using SPI, so include the hardware SPI library:
#include <SPI.h>
// include Playing With Fusion MAX31865 libraries
#include <PlayingWithFusion_MAX31865.h>              // core library
#include <PlayingWithFusion_MAX31865_STRUCT.h>       // struct library

#define BAUD_RATE 115200

#define MAX_DIAGNOSTICS

//#define PIN_CS D8
#define PIN_MAX_CS       10  /* Pro Micro 3.3V */
#define PIN_MAX_SDI_MOSI 11
#define PIN_MAX_SDO_MISO 12
#define PIN_MAX_CLK      13

#define MAX_PT1000
//#define MAX_PT100

// set to 2WIRE or 4WIRE as necessary
#define MAX_WIRES       RTD_3_WIRE

#define PIN_LED_HEARTBEAT        5

#define INTERVAL              1000

#define HEARTBEAT_STEPS      0.001

#define MESSAGE_SIZE            32

#define DELAY_SETUP            100

#if defined(MAX_PT100)
#define MAX_RTD_TYPE 1
#elif defined(MAX_PT1000)
#define MAX_RTD_TYPE 2
#endif
// Use software SPI: CS, DI, DO, CLK
#if defined(PIN_MAX_SDI_MOSI) && defined(PIN_MAX_SDO_MISO) && defined(PIN_MAX_CLK)
  PWFusion_MAX31865_RTD pwf_max_rtd(PIN_MAX_CS);
#else
  PWFusion_MAX31865_RTD pwf_max_rtd(PIN_MAX_CS);
#endif

// structures for holding RTD values
struct var_max31865 max_rtd_values;

unsigned long tick, next = 0;

char message[MESSAGE_SIZE];

float max_resistance, max_temperature, heartbeatval, heartbeatat = 0;

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
  // setup for the the SPI library:
  SPI.begin();                            // begin SPI
  SPI.setClockDivider(SPI_CLOCK_DIV16);   // SPI speed to SPI_CLOCK_DIV16 (1MHz)
  SPI.setDataMode(SPI_MODE3);             // MAX31865 works in MODE1 or MODE3

    // initalize the chip select pin
  pinMode(PIN_MAX_CS, OUTPUT);

  // configure channel 0
  pwf_max_rtd.MAX31865_config(&max_rtd_values, MAX_WIRES);
  max_rtd_values.RTD_type = MAX_RTD_TYPE;

  // give the sensor time to set up
  delay(DELAY_SETUP);
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
    pwf_max_rtd.MAX31865_full_read(&max_rtd_values);
    if(max_rtd_values.status == 0) {
#ifdef MAX_DIAGNOSTICS
#if defined(MAX_PT100)
      // handle values for PT100
      max_resistance = ((double)max_rtd_values.rtd_res_raw) * 400.0 / 32768.0;
      Serial.print(max_resistance, 2);
      Serial.print(",");
#elif defined(MAX_PT1000)
      // handle values for PT1000
      max_resistance = ((double)max_rtd_values.rtd_res_raw) * 4000.0 / 32768.0;
      Serial.print(max_resistance, 2);
      Serial.print(",");
#endif
#endif
      max_temperature = (((double)max_rtd_values.rtd_res_raw) / 32.0) - 256.0;
      Serial.print(max_temperature, 2);
    } else {
      Serial.print("F:");
      Serial.print(max_rtd_values.status);
    }
    Serial.println();
    next = tick + INTERVAL;
  }
}