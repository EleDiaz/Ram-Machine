TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    uibind.cpp \
    src/machine.cpp \
    src/instruction.cpp \
    src/parse.cpp \
    model.cpp \
    tapemodel.cpp \
    programmodel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/machine.hpp \
    src/itape.hpp \
    src/otape.hpp \
    src/parse.hpp \
    src/memory.hpp \
    src/instruction.hpp \
    src/counter.hpp \
    uibind.hpp \
    model.hpp \
    tapemodel.hpp \
    programmodel.hpp


DISTFILES += \
    test.qmodel
