/*
 Name:		rs485uno2usb2.ino
 Created:	7/14/2019 2:23:09 AM
 Author:	SigurdssonGO
*/

#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10           Rx(8)->RO (MAX845 PIN 1), Tx(9)->DI (MAX845 PIN 4)
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

#include <MAX485.h>

// 4->RE (MAX485 PIN 2), 7->DE (MAX485 PIN 3)
/* Driver Enable set to HIGH to enable transmitting */
#define PIN_RS485_RE    4
/* Receiver Enable set to LOW to enable receive */
#define PIN_RS485_DE    7

#define PIN_INDICATOR_LED_DIRECTION_A 5
#define PIN_INDICATOR_LED_DIRECTION_B 6

#define BAUD_RATE     9600

#define SEND_ALL_BUFFERED

AltSoftSerial altserial;

#if defined(PIN_RS485_RE) && defined(PIN_RS485_DE)
#define USING_MAX_485
#define RS485_MASTER
// Setup max485 Control Input
MAX485 max485(PIN_RS485_RE, PIN_RS485_DE);
bool issending = false, isreceiving = false;
#endif

#if defined(PIN_INDICATOR_LED_DIRECTION_A) || defined(PIN_INDICATOR_LED_DIRECTION_B)
#include <arduinosinled.h>
#endif

#ifdef PIN_INDICATOR_LED_DIRECTION_A
fds::SinLed indleda(PIN_INDICATOR_LED_DIRECTION_A);
#endif

#ifdef PIN_INDICATOR_LED_DIRECTION_B
fds::SinLed indledb(PIN_INDICATOR_LED_DIRECTION_B);
#endif

uint8_t b;

void setup() {

#ifdef PIN_INDICATOR_LED_DIRECTION_A
  indleda.initialize();
#endif

#ifdef PIN_INDICATOR_LED_DIRECTION_B
  indledb.initialize();
#endif

  Serial.begin(BAUD_RATE);
  while (!Serial) { ; /* wait for serial USB-port to connect */ }

  // set the data rate for the SoftwareSerial port connected to the TTL to RS-485 module
  altserial.begin(BAUD_RATE);

#ifdef USING_MAX_485
#ifdef RS485_MASTER
  max485.setMaster();
#else
  // set Slave-Mode (not really necessary since this is the default library configuration)
  max485.setSlave();
#endif
  max485.sending(issending);
#endif
}

void loop() {
#ifdef SEND_ALL_BUFFERED
  while (Serial.available()) {
#else
  if (Serial.available()) {
#endif
#ifdef USING_MAX_485
    if (!issending) {
#ifdef PIN_INDICATOR_LED_DIRECTION_A
      digitalWrite(PIN_INDICATOR_LED_DIRECTION_A, HIGH);
#endif
      issending = true;
      max485.sending(issending);
    }
#endif
    b = Serial.read();
    altserial.write(b);
  }
#ifdef USING_MAX_485
  if (issending) {
#ifdef PIN_INDICATOR_LED_DIRECTION_A
    digitalWrite(PIN_INDICATOR_LED_DIRECTION_A, LOW);
#endif
    issending = false;
    max485.sending(issending);
  }
#endif
#ifdef SEND_ALL_BUFFERED
  while (altserial.available()) {
#else
  if (altserial.available()) {
#endif
#ifdef PIN_INDICATOR_LED_DIRECTION_B
    if (!isreceiving) {
      digitalWrite(PIN_INDICATOR_LED_DIRECTION_B, HIGH);
      isreceiving = true;
    }
#endif
    b = altserial.read();
    Serial.write(b);
  }
#ifdef PIN_INDICATOR_LED_DIRECTION_B
  if (isreceiving) {
    digitalWrite(PIN_INDICATOR_LED_DIRECTION_B, LOW);
    isreceiving = false;
  }
#endif
  }
