#pragma once
/**

  */

#include <list>

using namespace std;

class UIBind;
/** Represents a input tape for Ram-Machine.

 */
class OTape {
private:
  list<int> tape_;
public:
  OTape(UIBind & ui): tape_() {}
  void writeTape(int val) {
      tape_.push_front(val);
  }
};
