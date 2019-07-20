#include "ledheartbeat.h"

#define PIN_LED_R 5
#define PIN_LED_G 6
#define PIN_LED_B 9

#define STEP_R    0.1
#define STEP_G    0.5
#define STEP_B    0.9

#define START_R      0.0
#define START_G  HALF_PI
#define START_B       PI

#define TEST_COUNT_R   6
#define TEST_COUNT_G   8
#define TEST_COUNT_B  10

#define TEST_DELAY_R  10
#define TEST_DELAY_G  50
#define TEST_DELAY_B 100

LedHeartBeat ledr(PIN_LED_R, STEP_R, START_R);
LedHeartBeat ledg(PIN_LED_G, STEP_G, START_G);
LedHeartBeat ledb(PIN_LED_B, STEP_B, START_B);

void setup() {
  ledr.initialize(TEST_COUNT_R, TEST_DELAY_R);
  ledg.initialize(TEST_COUNT_G, TEST_DELAY_G);
  ledb.initialize(TEST_COUNT_B, TEST_DELAY_B);
}

void loop() {
  ledr.cycle();
  ledg.cycle();
  ledb.cycle();
}
