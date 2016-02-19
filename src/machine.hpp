#ifndef MACHINE_H
#define MACHINE_H

#include <QDebug>
#include <QObject>

#include <list>
#include <fstream>

#include "counter.hpp"
#include "parse.hpp"
#include "instruction.hpp"
#include "memory.hpp"
#include "otape.hpp"
#include "itape.hpp"


class Machine : public QObject {
  Q_OBJECT
private:
  Counter counter_;
  Program program_;
  Memory  memory_;
  ITape   iTape_;
  OTape   oTape_;
  bool    stop_;

public:
  explicit Machine(string filename, list<int> input, QObject *parent = 0);

  Q_INVOKABLE void run(void);

  Q_INVOKABLE void step(void);

  Q_INVOKABLE void reset(void);

signals:
  void loaded();

public slots:
};

#endif // MACHINE_H
