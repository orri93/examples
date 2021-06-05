/*
 * Raspberry Pi LED Blinking using C (wiringPi)
 * https://www.electronicwings.com/raspberry-pi/how-to-use-wiringpi-library-on-raspberry-pi
 * 
 * gcc -o led_blink led_blink.c -l wiringPi
 * sudo ./led_blink

#include <wiringPi.h>
#include <stdio.h>

/* GPIO26 as per wiringPi, GPIO12 as per BCW, pin no. 32 */
#define LED = 26;

int main() {
  wiringPiSetup();            /* initialize wiringPi setup */
  pinMode(LED, OUTPUT);       /* set GPIO as output */

  while (1) {
    digitalWrite(LED, HIGH);  /* write high on GPIO */
    delay(1000);
    digitalWrite(LED, LOW);   /* write low on GPIO */
    delay(1000);
  }
}
