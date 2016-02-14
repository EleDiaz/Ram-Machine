#pragma once
#include <vector>
#include <list>
#include <map>

#include "instruction.hpp"

using namespace std;

class Instruction;

class Program {
private:
    vector<list<Instruction> > program_;
    int pos_;
    map<string, int> context_;
public:
    Program();
    void insertInstructions(list<Instruction>);
    void moveTo(string tag) {
        pos_ = context_.at(tag);
    }
};
