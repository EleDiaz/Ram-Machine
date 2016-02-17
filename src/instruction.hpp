#ifndef INSTRUCTION_CLASS
#define INSTRUCTION_CLASS
/**
 */
#include <functional>

class Program;

#include "program.hpp"
#include "otape.hpp"
#include "itape.hpp"
#include "memory.hpp"

class Instruction {
public:
  enum IOpcode {
    Load = 0,
    Store,
    Read,
    Write,
    Add,
    Sub,
    Mul,
    Div,
    Halt,
    Jump,
    Jgzt,
    Jzero,
  };

  struct Annotation {
    const string name;
    function<void (int param, Memory::DirectionMode mode
                   , Memory & mem, ITape & itape, OTape & otape
                   , Program & prog)> action;
  };

  // Normal instructions like read store...
  Instruction(Instruction::IOpcode opcode, int param, Memory::DirectionMode mode):
    mode_(nullptr),
    param_(nullptr),
    opcode_(opcode) {
    param_ = &param;
    mode_ = &mode;
  }

  // jump's instructions
  Instruction(int param, IOpcode opcode): mode_(nullptr), param_(nullptr), opcode_(opcode) {
    param_ = &param;
  }

  // Halt instruction
  Instruction(IOpcode opcode): mode_(nullptr), param_(nullptr), opcode_(opcode) {}
  //virtual void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) = 0;

  // Run a instruction depending of token give, if this not represent a valid Intructions it throws a exception
  void runAction(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
    instructions[opcode_];
  }

public:
  // especify a mode of direction memory if is halt is null
  Memory::DirectionMode * mode_;
  // is could be a direction or immediate or tag(int pos), null when halt
  int * param_;
  IOpcode opcode_;
  static const vector<Instruction::Annotation> instructions;
};

// // Carga en el 0 registro de la memoria dato
// class Load : public Instruction {
//   //string show(void) { return; }
//   Load(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(0, mem.getValue(param_,mode_), Memory::Direct);
//   }
// };

// class Store : public Instruction {
//   //string show(void) { return; }
//   Store(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(param_, mem.getValue(0, Memory::Direct), mode_);
//   }

// };


// class Read : public Instruction {
//   //string show(void) { return }
//   Read(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(param_, itape.readTape(), mode_);
//   }

// };

// class Write : public Instruction {
//   //string show(void) { return }
//   Write(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     otape.writeTape(mem.getValue(param_, mode_));
//   }
// };


// class Add : public Instruction {
//   //string show(void) { return }
//   Add(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(0, mem.getValue(param_,mode_)+mem.getValue(0,Memory::Direct), Memory::Direct);
//   }
// };

// class Sub : public Instruction {
//   //string show(void) { return }
//   Sub(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(0, mem.getValue(param_,mode_)-mem.getValue(0,Memory::Direct), Memory::Direct);
//   }
// };

// class Mul : public Instruction {
//   //string show(void) { return }
//   Mul(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(0, mem.getValue(param_,mode_)*mem.getValue(0,Memory::Direct), Memory::Direct);
//   }
// };

// class Div : public Instruction {
//   //string show(void) { return }
//   Div(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     mem.setValue(0, mem.getValue(param_,mode_) / mem.getValue(0,Memory::Direct), Memory::Direct);
//   }
// };


// class Halt : public Instruction {
//   //string show(void) { return }
//   Halt(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     // TODO:
//   }

// };

// class Jump : public Instruction {
//   //string show(void) { return }
//   Jump(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     //prog.moveTo(param_);
//   }

// };
// class Jgtz : public Instruction {
//   //string show(void) { return }
//   Jgtz(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     // TODO:
//   }

// };
// class Jzero : public Instruction {
//   //string show(void) { return }
//   Jzero(int param, Memory::DirectionMode mode): Instruction(param,mode) {}
//   void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
//     // TODO:
//   }

// };


#endif
