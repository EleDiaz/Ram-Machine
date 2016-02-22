#ifndef MACHINE_H
#define MACHINE_H

#include <QDebug>
#include <QObject>
#include <QUrl>
#include <QAbstractListModel>


#include <list>
#include <fstream>

#include "counter.hpp"
#include "parse.hpp"
#include "instruction.hpp"
#include "memory.hpp"
#include "otape.hpp"
#include "itape.hpp"


class Machine : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(QString error READ error NOTIFY errorChanged)

private:
  Counter counter_;
  int     oldCounter_;
  Program program_;
  Memory& memory_;
  ITape&  iTape_;
  OTape&  oTape_;
  bool    stop_;
  QString error_;

public:
  enum InstructionRoles {
    PC = Qt::UserRole + 1,
    Name,
    LineNumber,
    Param
  };

  Machine(OTape & otape, ITape & itape, Memory & memory, QObject *parent = 0);

  Q_INVOKABLE void loadFile(QUrl filename);

  Q_INVOKABLE void run(void);

  Q_INVOKABLE void step(void);

  Q_INVOKABLE void reset(void);

  QString error(void);

  int rowCount(const QModelIndex & parent = QModelIndex()) const;

  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
  void errorChanged(void);

public slots:
};

#endif // MACHINE_H
