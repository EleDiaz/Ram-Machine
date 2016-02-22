TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    src/machine.cpp \
    src/instruction.cpp \
    src/parse.cpp \
    src/itape.cpp \
    src/otape.cpp \
    src/memory.cpp

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
    src/commonExceptions.hpp


DISTFILES += \
    test.qmodel
