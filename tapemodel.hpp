#ifndef TAPEMODEL_H
#define TAPEMODEL_H

#include <vector>

#include <QAbstractListModel>

using namespace std;

class TapeModel : public QAbstractListModel
{
  Q_OBJECT

public:
  TapeModel(QObject *parent = 0);

  // Basic functionality:
  //QModelIndex index(int row, int column,
  //                  const QModelIndex &parent = QModelIndex()) const override;
  //QModelIndex parent(const QModelIndex &index) const override;
  //int popTape(void);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  //int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

//private:
  vector<int> tape_;
};

#endif // TAPEMODEL_H
