#include "itape.hpp"

ITape::ITape(QVector<int> vec, QObject *parent)
  : QAbstractListModel(parent),
  tape_(),
  pos_(0)
{
  tape_ = vec;
}

void ITape::loadInput(QUrl filename) {
  beginRemoveRows(QModelIndex(), 0, rowCount());
  tape_.clear();
  endRemoveRows();

  ifstream file (filename.path().toStdString());

  if (!file.is_open())
    throw;

  string line;


  while (getline(file, line)) {
    char * pch = strtok(&line[0u]," ");
    while (pch != nullptr) {
      tape_.push_back(stoi(pch));
      pch = strtok(NULL, " ");
    }
  }
  beginInsertRows(QModelIndex(), 0, rowCount());

  endInsertRows();
}


int ITape::readTape(void) {
  //beginRemoveRows(QModelIndex(),rowCount(), rowCount());
  int aux = tape_[pos_];
  pos_++;
  //tape_.pop_front();
  //endRemoveRows();
  return aux;
}

void ITape::reset(void) {
  pos_ = 0;
}

int ITape::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return tape_.size();
}


QVariant ITape::data(const QModelIndex &index, int role) const
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
