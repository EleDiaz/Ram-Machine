#include "machine.hpp"



Machine::Machine(string filename, list<int> input, QObject *parent) :
  QObject(parent),
  counter_(),
  program_(),
  memory_(1000), // TODO: Esto debe cambiar
  iTape_(input),
  oTape_(),
  stop_(false)
{
  ifstream file (filename);

  if (!file.is_open())
    throw;

  Parser x = Parser(file);  // catch all in parse exceptions
  program_ = x.getProgram(); // continue catching exceptions
  iTape_   = input;
}


void Machine::run(void) {
  if (!stop_)
    while (program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_)); // DANGER POSIBLE INFINITY LOOP
  stop_ = true;
}

void Machine::step(void) {
  if (!stop_)
    stop_ = program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_);
}

void Machine::reset(void) {
  stop_ = false;
  counter_.moveTo(0);
  memory_ = Memory(1000); // TODO: Esto debe cambiar
}
