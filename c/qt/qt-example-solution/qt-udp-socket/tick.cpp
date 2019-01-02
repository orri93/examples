#include "tick.h"

Tick::Tick(const Ticking& interval) : interval_(interval), next_(0) {
  // Do nothing
}

bool Tick::is(const Ticking &tick) {
  if(tick > next_) {
    next_ = tick + interval_;
    return true;
  } else {
    return false;
  }
}

Tick::Ticking Tick::millis() {
  Point point = this->clock_.now();
  Duration duration = point.time_since_epoch();
  std::chrono::milliseconds mssinceepoch =
      std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  return mssinceepoch.count();
}
