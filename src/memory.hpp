#pragma once
/**

 */

#include <QVector>
#include <QAbstractListModel>

using namespace std;

/** Represents a input tape for Ram-Machine.

 */
class Memory : public QAbstractListModel {
  Q_OBJECT
private:
  // representar la memoria mediante un vector tal cual
  QVector<int> memory_;
  int lastAccess_;
public:
  enum DirectionMode {
    Direct,
    Indirect,
    Immediate
  };

  Memory(int size, QObject *parent = 0);

  int getAccumulator(void);

  void setAccumulator(int value);

  void setValue(int direction, int value, DirectionMode mode);

  int getValue(int direction, DirectionMode mode);

  void updateView(int pos);

  Q_INVOKABLE void reset(int size);

  void reset(void);

  int rowCount(const QModelIndex &parent = QModelIndex()) const;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
