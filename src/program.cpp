#include "program.hpp"


Program::Program(vector<Instruction> program): program_(program), pos_(0) {}

vector<Instruction> Program::getProgram(void) {
  return program_;
}

void Program::moveTo(int newPos) {
  pos_ = newPos;
}
