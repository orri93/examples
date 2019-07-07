#include <SoftwareSerial.h>
#include <MAX485.h>

// 8->RE (MAX485 PIN 2), 9->DE (MAX485 PIN 3)
/* Driver Enable set to HIGH to enable transmitting */
#define PIN_RE 8
/* Receiver Enable set to LOW to enable receive */
#define PIN_DE 9
// RX(10)->RO (MAX845 PIN 1), TX(11)->DI (MAX845 PIN 4)
#define PIN_RO 10
#define PIN_DI 11

#define SERIAL_BAUD 9600
#define RS485_BAUD  9600

#define RS485_MASTER

#define SEND_ALL_BUFFERED

// Setup SoftSerial Port to receive TTL data from receiver 
SoftwareSerial softser(PIN_RO, PIN_DI);

// Setup max485 Control Input
MAX485 max485(PIN_RE, PIN_DE);

char b, issending = false;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(SERIAL_BAUD);
  while (!Serial) {
    ; // wait for serial USB-port to connect
  }
  // set the data rate for the SoftwareSerial port connected to the TTL to RS-485 module
  softser.begin(RS485_BAUD);
#ifdef RS485_MASTER
  max485.setMaster();
#else
  // set Slave-Mode (not really necessary since this is the default library configuration)
  max485.setSlave();
#endif
  max485.sending(issending);
} 

void loop() {
#ifdef SEND_ALL_BUFFERED
  while(Serial.available()) {
#else
  if(Serial.available()) {
#endif
    if(!issending) {
      issending = true;
      max485.sending(issending);
    }
    b = Serial.read();
    softser.write(b); 
  }
  if(issending) {
    issending = false;
    max485.sending(issending);
  }
#ifdef SEND_ALL_BUFFERED
  while(softser.available()) {
#else
  if (softser.available()) {
#endif
    b = softser.read();
    Serial.write(b);
  }
}
