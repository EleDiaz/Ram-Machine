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
    DirectionMode mode_;
public:
    Instruction(int param, DirectionMode mode):
        param_(param),
        mode_(mode) {}

    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)*mem.getValue(0,Direct), Direct);
    }
};

// Carga en el 0 registro de la memoria dato
class Load : public Instruction {
private:
    Load(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_), Direct);
    }
};

class Store : public Instruction {
    Store(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(param_, mem.getValue(0, Direct), mode_);
    }

};


class Read : public Instruction {
    Read(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(param_, itape.readTape(), mode_);
    }

};

class Write : public Instruction {
    Write(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        otape.writeTape(mem.getValue(param_, mode_));
    }
};


class Add : public Instruction {
    Add(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)+mem.getValue(0,Direct), Direct);
    }
};

class Sub : public Instruction {
    Sub(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)-mem.getValue(0,Direct), Direct);
    }
};

class Mul : public Instruction {
    Mul(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_)*mem.getValue(0,Direct), Direct);
    }
};

class Div : public Instruction {
    Div(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        mem.setValue(0, mem.getValue(param_,mode_) / mem.getValue(0,Direct), Direct);
    }
};


class Halt : public Instruction {
    Halt(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};

class Jump : public Instruction {
    Jump(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        //prog.moveTo(param_);
    }

};
class Jgtz : public Instruction {
    Jgtz(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};
class Jzero : public Instruction {
    Jzero(int param, DirectionMode mode): Instruction(param,mode) {}
    void run(Memory & mem, ITape & itape, OTape & otape, Program & prog) {
        // TODO:
    }

};
