#include "uibind.hpp"

UIBind::UIBind(QObject *parent) : QObject(parent)
{

}

void UIBind::reset() {
    qDebug() << "Called the C++ method with";

}

void UIBind::load() {}

void UIBind::run() {}

void UIBind::step() {}

int UIBind::lenghtInput(void) {}
int UIBind::lenghtOutput(void) {}
int UIBind::getInput(int) {}
int UIBind::getOutput(int) {}
