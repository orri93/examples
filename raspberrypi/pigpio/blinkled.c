/*
 * Raspberry Pi LED Blinking using C PiGPIO library
 *
 * Compile:
 *   gcc -Wall -pthread -o blinkled blinkled.c -lpigpio
 *
 * Usage:
 *   ./blinkled
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>

#define LED_PIN 26

int main(int argc, char *argv[]) {
  int r, i;

  r = gpioInitialise();
  if (r < 0) {
    fprintf(stderr, "GPIO Initializing failed with error code: %d\n", r);
    return EXIT_FAILURE;
  }

  gpioSetMode(LED_PIN, PI_OUTPUT);

  for (i = 0; i < 10; i++) {
    printf("Number: %d\n", i);
    gpioWrite(LED_PIN, 1);
    gpioDelay(300000);
    gpioWrite(LED_PIN, 0);
    gpioDelay(300000);
  }

  gpioTerminate();

  return EXIT_SUCCESS;
}

