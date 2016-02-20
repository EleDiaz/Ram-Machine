#pragma once
/**

  */
#include <QVector>
#include <QAbstractListModel>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class OTape : public QAbstractListModel {
  Q_OBJECT

private:
  QVector<int> tape_;

public:
  OTape(QObject *parent = 0);

  void writeTape(int val);

  void reset(void);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

};
