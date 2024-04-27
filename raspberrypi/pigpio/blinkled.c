/*
 * Raspberry Pi LED Blinking using C PiGPIO library
 *
 * Compile:
 *   gcc -Wall -pthread -o blinkled blinkled.c -lpigpio -lm
 *
 * Usage:
 *   ./blinkled
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

#include <pigpio.h>

#define LED_PIN 26

volatile sig_atomic_t quit;

void sighandler(int s) {
  quit = 1;
}

int main(int argc, char *argv[]) {
  int r, i, n;
  double x, y;

  quit = 0;

  signal(SIGINT, sighandler);
  signal(SIGTERM, sighandler);
#ifdef SIGBREAK
  signal(SIGBREAK, sighandler);
#endif

  r = gpioInitialise();
  if (r < 0) {
    fprintf(stderr, "GPIO Initializing failed with error code: %d\n", r);
    return EXIT_FAILURE;
  }

  gpioSetMode(LED_PIN, PI_OUTPUT);

  for (i = 0; i < 4; i++) {
    /* printf("Number: %d\n", i); */
    gpioWrite(LED_PIN, 1);
    gpioDelay(300000);
    gpioWrite(LED_PIN, 0);
    gpioDelay(300000);

  }

  for (i = 0; i < 255; i++) {
    gpioPWM(LED_PIN, i);
    gpioDelay(10000);
  }

  for (x = 0.0; x < 628.0; x += 0.1) {
    y = sin(x);
    n = (int)((1.0 + y) * 127);
    /* printf("Number for PWD: %d\ni", n); */
    gpioPWM(LED_PIN, n);
    gpioDelay(10000);
    if (quit) {
      break;
    }
  }

  gpioPWM(LED_PIN, 0);

  printf("Terminating the GPIO\n");
  gpioTerminate();

  return EXIT_SUCCESS;
}

