#ifndef FDS_MC_LED_HEARTBEAT_H_
#define FDS_MC_LED_HEARTBEAT_H_

#include <Arduino.h>

#ifndef DELAY_LED_TEST
#define DELAY_LED_TEST 500
#endif

#ifndef HEARTBEAT_STEPS
#define HEARTBEAT_STEPS      0.001
#endif

class LedHeartBeat {
public:
  LedHeartBeat(
    const int& pin,
    const float& step = HEARTBEAT_STEPS,
    const float& start = 0.0) :
    pin_(pin),
    at_(start),
    step_(HEARTBEAT_STEPS) {
    }

  void initialize(
    const uint8_t& ledtestcount = 1,
    const int& delayms = DELAY_LED_TEST) {
    pinMode(pin_, OUTPUT);
    for(uint8_t n = 0; n < ledtestcount; n++) {
      digitalWrite(pin_, HIGH);
      delay(delayms);
      digitalWrite(pin_, LOW);
      delay(delayms);
    }
  }

  void cycle() {
    analogWrite(pin_, (int)(sin(at_) * 127.5 + 127.5));
    at_ = at_ < TWO_PI ? at_ + step_ : 0.0;

  }

private:
  int pin_;
  float at_;
  float step_;
};

#endif
