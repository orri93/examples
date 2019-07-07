#include <Arduino.h>

#define PIN_R 5
#define PIN_G 6
#define PIN_B 9

#define INTERVAL 10

unsigned long tickat, nextat = 0;

unsigned char r = 0, g = 0, b = 0;

unsigned char d = 0;

bool up();
bool down();

void setup()
{
  Serial.begin(9600);
  Serial.println("RGB LED test!");

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);

}

void loop()
{
  tickat = millis();

  if(tickat >= nextat) {
    nextat = tickat + INTERVAL;

    if(d == 0) {
      if(up()) {
        d = 1;
      }
    } else {
      if(down()) {
        d = 0;
      }
    }

    analogWrite(PIN_R, r);
    analogWrite(PIN_G, g);
    analogWrite(PIN_B, b);
  }
}

bool up() {
  if(r < 255) {
    r++;
  } else if(g < 255) {
    g++;
  } else {
    b++;
  }
  return r == 255 && g == 255 && b == 255;
}

bool down() {
  if (r > 0) {
    r--;
  } else if(g > 0) {
    g--;
  } else {
    b--;
  }
  return r == 0 && g == 0 && b == 0;
}