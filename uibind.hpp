#ifndef UIBIND_H
#define UIBIND_H
#include <QDebug>
#include <QObject>

class UIBind : public QObject
{
    Q_OBJECT
public:
    explicit UIBind(QObject *parent = 0);

    Q_INVOKABLE void reset();

    Q_INVOKABLE void load();

    Q_INVOKABLE void run();

    Q_INVOKABLE void step();

    int lenghtInput(void);
    int lenghtOutput(void);
    int getInput(int);
    int getOutput(int);
signals:

public slots:
};

#endif // UIBIND_H
