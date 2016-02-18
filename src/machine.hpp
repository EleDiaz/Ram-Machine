#ifndef MACHINE_H
#define MACHINE_H

#include <list>

#include "counter.hpp"
#include "parse.hpp"
#include "instruction.hpp"
#include "otape.hpp"
#include "itape.hpp"


class Machine {
private:
  Counter counter_;
  Program program_;
  ITape   iTape_;
  OTape   oTape_;

public:
  Machine(string filename, list<int> input);

  void run(void);

  void step(void);

  void reset(void);
};

#endif // MACHINE_H
