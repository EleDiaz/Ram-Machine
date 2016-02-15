#pragma once
/**
 */

#include "program.hpp"
#include "memory.hpp"
#include "itape.hpp"
#include "otape.hpp"

class Program;

class Instruction {
protected:
    int param_;
    Memory::DirectionMode mode_;
public:
    Instruction(int param, Memory::DirectionMode mode):
        param_(param),
        mode_(mode) {}

    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) = 0;

    string show(void);

    string name(void);
};

// Carga en el 0 registro de la memoria dato
class Load : public Instruction {
    string show(void) { return; }
    Load(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_), Direct);
    }
};

class Store : public Instruction {
    string show(void) { return; }
    Store(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(param_, mem.getValue(0, Direct), mode_);
    }

};


class Read : public Instruction {
    string show(void) { return }
    Read(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(param_, itape.readTape(), mode_);
    }

};

class Write : public Instruction {
    string show(void) { return }
    Write(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        otape.writeTape(mem.getValue(param_, mode_));
    }
};


class Add : public Instruction {
    string show(void) { return }
    Add(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)+mem.getValue(0,Direct), Direct);
    }
};

class Sub : public Instruction {
    string show(void) { return }
    Sub(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)-mem.getValue(0,Direct), Direct);
    }
};

class Mul : public Instruction {
    string show(void) { return }
    Mul(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)*mem.getValue(0,Direct), Direct);
    }
};

class Div : public Instruction {
    string show(void) { return }
    Div(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_) / mem.getValue(0,Direct), Direct);
    }
};


class Halt : public Instruction {
    string show(void) { return }
    Halt(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};

class Jump : public Instruction {
    string show(void) { return }
    Jump(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        //prog.moveTo(param_);
    }

};
class Jgtz : public Instruction {
    string show(void) { return }
    Jgtz(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};
class Jzero : public Instruction {
    string show(void) { return }
    Jzero(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};
