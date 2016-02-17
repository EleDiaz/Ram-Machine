#include "instruction.hpp"


// INFO: No desordenar el vector, debe estar ordenado en funcion del enum!!
const vector<Instruction::Annotation> Instruction::instructions = {
  {"LOAD", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setAccumulator(mem.getValue(param_,mode_));
    }},
  {"STORE", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setValue(param_, mem.getAccumulator(), mode_);
    }},
  {"READ", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setValue(param_, itape.readTape(), mode_);
    }},
  {"WRITE", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      otape.writeTape(mem.getValue(param_, mode_));
    }},
  {"ADD", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setAccumulator(mem.getValue(param_,mode_) + mem.getValue(0,Memory::Direct));
    }},
  {"SUB", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setAccumulator(mem.getValue(param_,mode_) - mem.getValue(0,Memory::Direct));
    }},
  {"MUL", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setAccumulator(mem.getValue(param_,mode_) * mem.getValue(0,Memory::Direct));
    }},
  {"DIV", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      mem.setAccumulator(mem.getValue(param_,mode_) / mem.getValue(0,Memory::Direct));
    }},
  {"HALT", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      // TODO: Throw error exit program
    }},
  {"JUMP", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      prog.moveTo(mem.getValue(param_, mode_));
    }},
  {"JGZT", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      if (mem.getAccumulator() > 0)
        prog.moveTo(mem.getValue(param_, mode_));
    }},
  {"JZERO", [](int param_, Memory::DirectionMode mode_, Memory & mem,
              ITape & itape, OTape & otape, Program & prog) {
      if (mem.getAccumulator() == 0)
        prog.moveTo(mem.getValue(param_, mode_));
    }},
};
