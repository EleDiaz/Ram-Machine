TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    programui.cpp \
    uibind.cpp \
    src/machine.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    programui.h \
    src/machine.hpp \
    src/itape.hpp \
    src/otape.hpp \
    src/program.hpp \
    src/parse.hpp \
    src/memory.hpp \
    src/instruction.hpp \
    uibind.hpp


DISTFILES += \
    test.qmodel
