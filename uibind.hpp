#ifndef UIBIND_H
#define UIBIND_H
#include <QtGui>
#include <QtQml>
#include <QQuickView>

#include "src/machine.hpp"
#include "model.hpp"
#include "tapemodel.hpp"

class UIBind
{
public:
    UIBind(TapeModel & itape, TapeModel & oTape, );
};

#endif // UIBIND_H
