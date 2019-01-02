#include <Wire.h>

#define BAUD_RATE 115200

#define SLAVE_ADDRESS 0x04

#define TICK_SIZE 4

#define DELAY 10

union {
  byte bytes[TICK_SIZE];
  unsigned long value;
} lt;


unsigned long tick;
unsigned int count = 0;
byte i, v;

void receive(int length) {
  Serial.print("Receive. Number of bytes is ");
  Serial.println(length, DEC);
  Serial.print("Data: ");
  count = 0;
  while(Wire.available()) {
    v = Wire.read();
    Serial.println(v, HEX);
    count++;
  }
  Serial.println();
  Serial.print("Number of bytes available are ");
  Serial.println(count, DEC);
}

void request() {
  Serial.print("Request, sending tick with value as ");
  Serial.print(tick, DEC);
  lt.value = tick;
  for(i = 0; i < TICK_SIZE; i++) {
    Wire.write(lt.bytes[i]);
  }
}

void setup() {
  Serial.begin(BAUD_RATE); // start serial for output
  Serial.println();
  Serial.println("Example for I2C with Raspberry PI");

  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receive);
  Wire.onRequest(request);
}

void loop() {
  tick = millis();
  delay(DELAY);
}
