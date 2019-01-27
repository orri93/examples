/*
  Software serial multple serial test A

 The circuit:
 * RX is digital pin 8 (connect to TX of other device)
 * TX is digital pin 9 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 */

#include <SoftwareSerial.h>

#include <PacketSerial.h>

#include "tick.h"
#include "types.h"

#define SERIAL_BAUD        115200
#define SERIAL_SOFT_BAUD     9600

#define MESSAGE_SIZE           93

//#define PIN_SOFT_SER_RX         8
//#define PIN_SOFT_SER_TX         9
#define PIN_SOFT_SER_RX         D5
#define PIN_SOFT_SER_TX         D6

//#define PIN_LED_HEARTBEAT       5
#define PIN_LED_HEARTBEAT       D7
//#define PIN_LED_RX              6
#define PIN_LED_RX              D1
//#define PIN_LED_TX              7

#define INTERVAL_HEARTBEAT_LED  0
#define INTERVAL_SOFT_SERIAL 1000

#define DELAY_LED_TEST        500

#define HEARTBEAT_STEPS     0.001

//#define WAIT_FOR_HARDWARE_SERIAL

SoftwareSerial softser(PIN_SOFT_SER_RX, PIN_SOFT_SER_TX);
PacketSerial packser;

struct datastructa stra;
struct datastructb strb;

Tick softtick(INTERVAL_SOFT_SERIAL);
Tick heartbeat(INTERVAL_HEARTBEAT_LED);

byte x = 0;

float heartbeatval, heartbeatat = 0;

char message[MESSAGE_SIZE];

unsigned long long tick;

size_t sizeofa, sizeofb;

void packetreceived(const void* sender, const uint8_t* buffer, size_t size) {
#ifdef PIN_LED_RX
  digitalWrite(PIN_LED_RX, HIGH);
#endif
  if(size >= sizeof(strb)) {
    memcpy(&strb, buffer, sizeof(strb));
    snprintf(
      message,
      MESSAGE_SIZE,
      "Receiving structure with %s as text and l as %d from B",
      strb.text,
      strb.l);
    Serial.println(message);
  } else {
    snprintf(
      message,
      MESSAGE_SIZE,
      "Receiving incorrect size %d when expecting %d",
      size,
      sizeof(strb));
    Serial.println(message);
  }
#ifdef PIN_LED_RX
  digitalWrite(PIN_LED_RX, LOW);
#endif
}

void setup() {
#ifdef PIN_LED_HEARTBEAT
  pinMode(PIN_LED_HEARTBEAT, OUTPUT);
  digitalWrite(PIN_LED_HEARTBEAT, HIGH);
  delay(DELAY_LED_TEST);
  digitalWrite(PIN_LED_HEARTBEAT, LOW);
#endif
#ifdef PIN_LED_RX
  pinMode(PIN_LED_RX, OUTPUT);
  digitalWrite(PIN_LED_RX, HIGH);
  delay(DELAY_LED_TEST);
  digitalWrite(PIN_LED_RX, LOW);
#endif
#ifdef PIN_LED_TX
  pinMode(PIN_LED_TX, OUTPUT);
  digitalWrite(PIN_LED_TX, HIGH);
  delay(DELAY_LED_TEST);
  digitalWrite(PIN_LED_TX, LOW);
#endif
  Serial.begin(SERIAL_BAUD);
#ifdef WAIT_FOR_HARDWARE_SERIAL
  while(!Serial) {
    /* Waiting for serial to become available */
#if defined(PIN_LED_RX) && defined(PIN_LED_TX)
  x = x == 0 ? 1 : 0;
  digitalWrite(PIN_LED_RX, x == 1 ? HIGH : LOW);
  digitalWrite(PIN_LED_TX, x == 1 ? LOW : HIGH);
  delay(5);
#endif
  }
#if defined(PIN_LED_RX) && defined(PIN_LED_TX)
  x = 0;
  digitalWrite(PIN_LED_RX, LOW);
  digitalWrite(PIN_LED_TX, LOW);
#endif
#endif

  Serial.println("Software serial with package serial Testing - Agent A");

  softser.begin(SERIAL_SOFT_BAUD);
  packser.setPacketHandler(&packetreceived);
  packser.setStream(&softser);

  snprintf(
    message,
    MESSAGE_SIZE,
    "Software serial started with RX pin as %u and TX pin as %u setting baud rate to %u.",
    PIN_SOFT_SER_RX,
    PIN_SOFT_SER_TX,
    SERIAL_SOFT_BAUD
    );
  Serial.println(message);
#if defined(PIN_LED_HEARTBEAT) && defined(PIN_LED_RX) && defined(PIN_LED_TX)
  snprintf(
    message,
    MESSAGE_SIZE,
    "Rx LED can be connected to pin %u, RX LED to %u and heartbeat LEDto pin %u.",
    PIN_LED_RX,
    PIN_LED_TX,
    PIN_LED_HEARTBEAT
    );
  Serial.println(message);
#endif

  sizeofa = sizeof(stra);
  if(sizeofa == EXPECTED_SIZE_A) {
    snprintf(
      message,
      MESSAGE_SIZE,
      "Size of data structure a is as expected %u.",
      sizeofa);
    Serial.println(message);
  } else {
    snprintf(
      message,
      MESSAGE_SIZE,
      "Size of data structure a %u is not as expected %u.",
      sizeofa,
      EXPECTED_SIZE_A);
    Serial.println(message);
  }
  sizeofb = sizeof(strb);
  if(sizeofb == EXPECTED_SIZE_B) {
    snprintf(
      message,
      MESSAGE_SIZE,
      "Size of data structure b is as expected %u.",
      sizeofb);
    Serial.println(message);
  } else {
    snprintf(
      message,
      MESSAGE_SIZE,
      "Size of data structure b %u is not as expected %u.",
      sizeofb,
      EXPECTED_SIZE_B);
    Serial.println(message);
  }
}

void loop() {
  tick = millis();

#if defined(PIN_LED_HEARTBEAT)
#if INTERVAL_HEARTBEAT_LED > 0
  if(heartbeat.is(tick)) {
#endif
    heartbeatval = sin(heartbeatat) * 127.5 + 127.5;
    analogWrite(PIN_LED_HEARTBEAT, (int)heartbeatval);
    heartbeatat = heartbeatat <  6.283 /* 2*PI */ ?
      heartbeatat + HEARTBEAT_STEPS : 0.0;
#if INTERVAL_HEARTBEAT_LED > 0
  }
#endif
#endif

  if(softtick.is(tick)) {
#ifdef PIN_LED_TX
    digitalWrite(PIN_LED_TX, HIGH);
#endif
    stra.f = 1.0/((float)x);
    stra.i = (int)(x + 256);
    stra.b = x;
    packser.send((const uint8_t*)(&stra), sizeof(stra));
    snprintf(
      message,
      MESSAGE_SIZE,
      "Sending structure with f as %f, i as %u and b as %i to B",
      stra.f,
      stra.i,
      stra.b);
    Serial.println(message);
#ifdef PIN_LED_TX
    digitalWrite(PIN_LED_TX, LOW);
#endif
    x = x < 255 ? x + 1 : 0;
  }

  packser.update();
}
