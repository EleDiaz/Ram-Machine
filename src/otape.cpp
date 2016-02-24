#include "otape.hpp"

OTape::OTape(QObject *parent)
  : QAbstractListModel(parent),
    tape_() {}

void OTape::writeTape(int val) { // TODO
  beginRemoveRows(QModelIndex(), 0, rowCount());
  endRemoveRows();
  tape_.push_back(val);
  //insertRow(tape_.size()-1)
  beginInsertRows(QModelIndex(), 0, rowCount()-1);
  endInsertRows();
}

void OTape::reset(void) {
  beginRemoveRows(QModelIndex(), 0, rowCount());
  endRemoveRows();
  tape_.clear();
}

void OTape::saveTape(void) {
  // ofstream file (filename.path().toStdString());
  ofstream file ("salida.out");
  if (!file.is_open())
    throw;

  for (int value : tape_) {
    file << value << "\n";
  }
  file.close();
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
