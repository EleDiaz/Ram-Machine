#ifndef PROGRAM_CLASS
#define PROGRAM_CLASS

#include <vector>

class Instruction;

#include "instruction.hpp"

using namespace std;

class Program {
private:
  vector<Instruction> program_;
  int pos_;
public:
  Program(vector<Instruction> program);
  vector<Instruction> getProgram(void);
  void moveTo(int newPos);
};
#endif
