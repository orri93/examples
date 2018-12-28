// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

// I2C               Arduino    NodeMCU I2C
// SDA (Data)        A4         D2 SDA
// SCL (the clock)   A5         D1 SCL

#include <Wire.h>

#define ADDRESS 9

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(115200);           // start serial for output
  Serial.println("Wire ready");
}

byte x = 0;

void loop() {
  Serial.print("Start transmitting with x as ");
  Serial.println(x);
  Wire.beginTransmission(ADDRESS); // transmit to slave
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
}

