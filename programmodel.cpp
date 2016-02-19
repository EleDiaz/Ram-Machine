#include "programmodel.hpp"

ProgramModel::ProgramModel(QObject *parent)
  : QAbstractListModel(parent)
{
}

int ProgramModel::rowCount(const QModelIndex &parent) const
{
  if (!parent.isValid())
    return 0;

  // FIXME: Implement me!
}

QVariant ProgramModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= m_animals.count())
      return QVariant();

  const Animal &animal = m_animals[index.row()];
  if (role == TypeRole)
      return animal.type();
  else if (role == SizeRole)
      return animal.size();


  return QVariant();
}
