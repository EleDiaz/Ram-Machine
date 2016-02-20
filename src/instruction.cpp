#include "instruction.hpp"


// INFO: No desordenar el vector, debe estar ordenado en funcion del enum!!
const vector<Instruction::Annotation> Instruction::instructions = {
  {"LOAD", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setAccumulator(mem.getValue(param_,mode_));
      return false;
    }},
  {"STORE", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setValue(param_, mem.getAccumulator(), mode_); return false;
    }},
  {"READ", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setValue(param_, itape.readTape(), mode_); return false;
    }},
  {"WRITE", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      otape.writeTape(mem.getValue(param_, mode_)); return false;
    }},
  {"ADD", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setAccumulator(mem.getValue(param_,mode_) + mem.getValue(0,Memory::Direct));
      return false;
    }},
  {"SUB", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setAccumulator(mem.getValue(param_,mode_) - mem.getValue(0,Memory::Direct));
      return false;
    }},
  {"MUL", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setAccumulator(mem.getValue(param_,mode_) * mem.getValue(0,Memory::Direct));
      return false;
    }},
  {"DIV", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      mem.setAccumulator(mem.getValue(param_,mode_) / mem.getValue(0,Memory::Direct));
      return false;
    }},
  {"HALT", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      return true;
    }},
  {"JUMP", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      counter.moveTo(param_);
      return false;
    }},
  {"JGZT", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      if (mem.getAccumulator() > 0)
        counter.moveTo(param_);
      return false;
    }},
  {"JZERO", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Counter & counter) {
      if (mem.getAccumulator() == 0)
        counter.moveTo(param_);
      return false;
    }},
};
