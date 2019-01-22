#ifndef FDS_MC_TICK_H_
#define FDS_MC_TICK_H_

class Tick {
public:
  Tick(unsigned long interval) :
    interval_(interval),
    next_tick_(0) {
  }
  bool is(unsigned long tick) {
    if(tick >= next_tick_) {
      next_tick_ = tick + interval_;
      return true;
    } else {
      return false;
    }
  }
private:
  unsigned long interval_;
  unsigned long next_tick_;
};

#endif /* FDS_MC_TICK_H_ */