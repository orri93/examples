#ifndef TICK_H
#define TICK_H

#include <chrono>

class Tick {
public:
  typedef long long Ticking;

  Tick(const Ticking& interval);
  bool is(const Ticking& tick);
  Ticking millis();

private:
  typedef std::chrono::steady_clock Clock;
  typedef Clock::time_point Point;
  typedef Clock::duration Duration;

  Clock clock_;
  Ticking interval_;
  Ticking next_;
};

#endif // TICK_H

