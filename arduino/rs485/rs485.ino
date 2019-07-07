#include <SoftwareSerial.h>



void setup()
{
  Serial.begin(9600);
  Serial.println("RS-485 test!");

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);

}

void loop()
{

}
