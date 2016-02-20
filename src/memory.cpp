#include "memory.hpp"

#include <iostream>

Memory::Memory(int size, QObject *parent): memory_(size) {
}

int Memory::getAccumulator(void) {
  return memory_[0];
}

void Memory::setAccumulator(int value) {
  memory_[0] = value;
  //updateModel(0);
  emit dataChanged(index(0,0),index(0,0));
}

void Memory::setValue(int direction, int value, DirectionMode mode) {
  switch (mode) {
  case Direct:
    if (direction <= 0)
      ; // TODO exception !!
    memory_[direction] = value;
    //updateModel(direction);
    emit dataChanged(index(direction,0),index(direction,0));
    break;
  case Indirect:
    if (direction <= 0)
      ; // TODO exeption !!
    if (memory_[direction] <= 0)
      ; // TODO exeption !!
    memory_[memory_[direction]] = value;
    //updateModel(memory_[direction]);
    emit dataChanged(index(memory_[direction],0),index(memory_[direction],0));
    break;
  case Immediate:
    break; // INFO: Este caso no debe darse, el parse se debe asegurar de dar el error apropiado
  }
}

int Memory::getValue(int direction, DirectionMode mode) {
  switch (mode) {
  case Direct:
    if (direction <= 0)
      ; // TODO exception !!
    return memory_[direction];
  case Indirect:
    if (direction <= 0)
      ; // TODO exeption !!
    if (memory_[direction] <= 0)
      ; // TODO exeption !!
    return memory_[memory_[direction]];
  case Immediate:
    return direction; // FIXME: Esto hace el código incoherente
  }
}



void Memory::updateModel(int dir) {
  beginRemoveRows(QModelIndex(), dir, dir);
  endRemoveRows();
  beginInsertRows(QModelIndex(), dir, dir);
  endInsertRows();
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
  else
    return QVariant();
}
