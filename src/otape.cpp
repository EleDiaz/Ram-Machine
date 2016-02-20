#include "otape.hpp"

OTape::OTape(QObject *parent)
  : QAbstractListModel(parent),
    tape_() {}

void OTape::writeTape(int val) { // TODO
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  tape_.push_front(val);
  //insertRow(tape_.size()-1)
  endInsertRows();
}

void OTape::reset(void) {
  beginRemoveRows(QModelIndex(), 0, rowCount());
  endRemoveRows();
  tape_.clear();
}

int OTape::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return tape_.size();
}


QVariant OTape::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= tape_.size())
      return QVariant();

  int value = tape_[index.row()];
  if (role == Qt::DisplayRole) {
    return value;
  }
  else
    return QVariant();
}
