#pragma once


class Counter {
private:
  int pos_;

public:
  Counter(void): pos_(0) {}

  void moveTo(int newPos) {
    pos_ = newPos;
  }

  int getCounter(void) {
    return pos_;
  }

  void next(void) {
    pos_++;
  }
};
