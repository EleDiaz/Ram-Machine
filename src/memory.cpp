#include "memory.hpp"

#include <iostream>

Memory::Memory(int size, QObject *parent)
  : memory_(size), lastAccess_(0) {
}

int Memory::getAccumulator(void) {
  return memory_[0];
}

void Memory::setAccumulator(int value) {
  memory_[0] = value;
  updateView(0);
}

void Memory::setValue(int direction, int value, DirectionMode mode) {
  switch (mode) {
  case Direct:
    if (direction <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    memory_[direction] = value;

    updateView(direction);
    break;

  case Indirect:
    if (direction <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    if (memory_[direction] <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    memory_[memory_[direction]] = value;

    updateView(memory_[direction]);
    break;

  case Immediate:
    throw "Esto no debe occurrir Immediate";
    break; // INFO: Este caso no debe darse, el parse se debe asegurar de dar el error apropiado
  }
}

int Memory::getValue(int direction, DirectionMode mode) {
  switch (mode) {
  case Direct:
    if (direction <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    return memory_[direction];
  case Indirect:
    if (direction <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    if (memory_[direction] <= 0)
      throw "Accediendo a la memoria de forma negativa o al registro 0";
    return memory_[memory_[direction]];
  case Immediate:
    return direction; // FIXME: Esto hace el código incoherente
  }
}

void Memory::updateView(int newAccess) {
  int aux = lastAccess_;
  lastAccess_ = newAccess;

  emit dataChanged(index(newAccess,0),index(newAccess,0));
  emit dataChanged(index(aux,0),index(aux,0));
}

void Memory::reset(int size) {
  beginRemoveRows(QModelIndex(), 0, memory_.size());
  endRemoveRows();
  memory_.clear();
  memory_.resize(size);
  beginInsertRows(QModelIndex(), 0, memory_.size()-1);
  endInsertRows();
}

void Memory::reset(void) {
  reset(memory_.size());
}

int Memory::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return memory_.size();
}


QVariant Memory::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= memory_.size())
      return QVariant();

  int value = memory_[index.row()];
  if (role == Qt::DisplayRole) {
    return "R"+QString::number(index.row())+":  "+QString::number(value);
  }
  else if (role == Qt::DecorationRole) {
    return lastAccess_ == index.row() ? "#ACFFA3" : "#66ffffff";
  }
    return QVariant();
}
