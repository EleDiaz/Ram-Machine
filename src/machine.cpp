#include "machine.hpp"

#include <iostream>


Machine::Machine(OTape & otape, ITape & itape, Memory & memory, QObject *parent):
  QAbstractListModel(parent),
  counter_(),
  oldCounter_(),
  program_(),
  memory_(memory), // TODO: Esto debe cambiar
  iTape_(itape),
  oTape_(otape),
  stop_(false)
{
}

void Machine::loadFile(QUrl filename) {
  beginRemoveRows(QModelIndex(), 0, rowCount());
  endRemoveRows();
  ifstream file (filename.path().toStdString());

  try {
    if (!file.is_open())
      throw -1;

    Parser x = Parser(file);  // catch all in parse exceptions
    program_ = x.getProgram(); // continue catching exceptions
  }
  catch (const char* e) {
    cout << "Big error " << e << endl;
  }

  beginInsertRows(QModelIndex(), 0, rowCount()-1);
  endInsertRows();
  reset();
}


void Machine::run(void) {
  if (!stop_) {
    try {
      oldCounter_ = counter_.getCounterNoModify();
      while (!program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_)) { // DANGER POSIBLE INFINITY LOOP
        int newest = counter_.getCounterNoModify();
        emit dataChanged(index(newest,0), index(newest,0));
        emit dataChanged(index(oldCounter_,0), index(oldCounter_,0));
        oldCounter_ = newest;
      }
    }
    catch (...) {
      cout << "error big"<< endl;
      stop_ = true;
    }
  }
  stop_ = true;
}

void Machine::step(void) {
  if (!stop_) {
    try {
      oldCounter_ = counter_.getCounterNoModify();
      stop_ = program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_);
      int newest = counter_.getCounterNoModify();
      emit dataChanged(index(newest,0), index(newest,0));
      emit dataChanged(index(oldCounter_,0), index(oldCounter_,0));
      oldCounter_ = newest;
    }
    catch (...) {
      cout << "error big" << endl;
    }
  }
}

void Machine::reset(void) {
  stop_ = false;
  emit dataChanged(index(oldCounter_,0),index(oldCounter_,0));
  counter_.moveTo(0);
  memory_.reset();
  iTape_.reset();
  oTape_.reset();
}

int Machine::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return program_.size();
}

QVariant Machine::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= program_.size())
        return QVariant();

    const Instruction &instruction = program_[index.row()];
    switch (role) {
    case PC:
      return ((counter_.getCounterNoModify() == index.row()) ? "red" : "black");
    case Name:
      return QString::fromStdString(instruction.name());
    case LineNumber:
      return index.row();
    case Param:
      return QString::fromStdString(instruction.showParam());
    }

    return QVariant();
}

QHash<int, QByteArray> Machine::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PC] = "pc";
    roles[Name] = "name";
    roles[LineNumber] = "line";
    roles[Param] = "param";
    return roles;
}

