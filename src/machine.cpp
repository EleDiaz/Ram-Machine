#include "machine.hpp"

#include <iostream>


Machine::Machine(OTape & otape, ITape & itape, Memory & memory, QObject *parent):
  QAbstractListModel(parent),
  counter_(),
  program_(),
  memory_(memory), // TODO: Esto debe cambiar
  iTape_(itape),
  oTape_(otape),
  stop_(false)
{
}

void Machine::loadFile(QUrl filename) {
  //resetInternalData();
  beginRemoveRows(QModelIndex(), 0, rowCount());
  endRemoveRows();
  ifstream file (filename.path().toStdString());

  if (!file.is_open())
    throw;

  Parser x = Parser(file);  // catch all in parse exceptions
  program_ = x.getProgram(); // continue catching exceptions
  beginInsertRows(QModelIndex(), 0, rowCount()-1);
  endInsertRows();
  reset();
}


void Machine::run(void) {
  if (!stop_) {
    int old = counter_.getCounterNoModify();
    while (!program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_)) { // DANGER POSIBLE INFINITY LOOP
      //int aux = counter_.pos_;
      //cout << "Counter " << aux << endl;
      int newest = counter_.getCounterNoModify();
      emit dataChanged(index(newest,0),index(newest,0));
      emit dataChanged(index(old,0),index(old,0));
      old = counter_.getCounterNoModify();
    }
  }
  stop_ = true;
}

void Machine::step(void) {
  if (!stop_) {
    int old = counter_.getCounterNoModify();
    stop_ = program_[counter_.getCounter()].runAction(memory_, iTape_, oTape_, counter_);
    int newest = counter_.getCounterNoModify();
    emit dataChanged(index(newest,0),index(newest,0));
    emit dataChanged(index(old,0),index(old,0));
  }
}

void Machine::reset(void) {
  stop_ = false;
  counter_.moveTo(0);
  //memory_ = Memory(1000); // TODO: Esto debe cambiar
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

