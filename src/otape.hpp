#pragma once
/**

  */

#include <list>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class OTape {
private:
  list<int> tape_;
public:
  OTape(): tape_() {}
  void writeTape(int val) {
      tape_.push_front(val);
  }
};
