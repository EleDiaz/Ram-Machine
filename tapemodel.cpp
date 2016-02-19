#include "tapemodel.hpp"

TapeModel::TapeModel(QObject *parent)
  : QAbstractListModel(parent)
{
}


int TapeModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return tape_.size();
}


QVariant TapeModel::data(const QModelIndex &index, int role) const
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
