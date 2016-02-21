#pragma once
/**

 */


#include <cstring>
#include <fstream>
#include <QVector>
#include <QUrl>
#include <QAbstractListModel>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class ITape : public QAbstractListModel {
  Q_OBJECT
private:
  QVector<int> tape_;
  int pos_;
public:
  ITape(QVector<int> vec, QObject *parent =0);

  int readTape(void);

  Q_INVOKABLE void loadInput(QUrl);

  Q_INVOKABLE void loadString(QString);

  void reset(void);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
