#pragma once
/**

 */

#include <vector>
#include <functional>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class Memory {
private:
  // representar la memoria mediante un vector tal cual
  vector<int> memory_;
public:
  enum DirectionMode {
    Direct,
    Indirect,
    Immediate
  };

  Memory(int size): memory_(size) {
  }

  int getAccumulator(void) {
    return memory_[0];
  }

  void setAccumulator(int value) {
    memory_[0] = value;
  }

  void setValue(int direction, int value, DirectionMode mode) {
    switch (mode) {
    case Direct:
      if (direction <= 0)
        ; // TODO exception !!
      memory_[direction] = value;
      break;
    case Indirect:
      if (direction <= 0)
        ; // TODO exeption !!
      if (memory_[direction] <= 0)
        ; // TODO exeption !!
      memory_[memory_[direction]] = value;
      break;
    case Immediate:
      break; // INFO: Este caso no debe darse, el parse se debe asegurar de dar el error apropiado
    }
  }

  int getValue(int direction, DirectionMode mode) {
    switch (mode) {
    case Direct:
      if (direction <= 0)
        ; // TODO exception !!
      return memory_[direction];
    case Indirect:
      if (direction <= 0)
        ; // TODO exeption !!
      if (memory_[direction] <= 0)
        ; // TODO exeption !!
      return memory_[memory_[direction]];
    case Immediate:
      return direction; // FIXME: Esto hace el código incoherente
    }
  }

  string representAddressing(const DirectionMode & mod) {
    switch (mod) {
    case Immediate:
      return "=";
    case Direct:
      return "";
    case Indirect:
      return "*";
    }
  }
};
