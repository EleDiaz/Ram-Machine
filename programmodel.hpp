#ifndef PROGRAMMODEL_H
#define PROGRAMMODEL_H

#include <QAbstractListModel>

#include <vector>

#include "src/instruction.hpp"
#include "src/counter.hpp"

using namespace std;

class ProgramModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum LineRoles {
      CurrentLine = Qt::UserRole + 1,
      Instruction,
      LineNumber,
      Param
  };

  explicit ProgramModel(QObject *parent = 0);

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:


private:
  vector<Instruction> * program_;
  Counter * counter_;
};

#endif // PROGRAMMODEL_H
