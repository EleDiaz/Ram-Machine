#include <QtGui>
#include <QtQml>

#include "uibind.hpp"
#include "programui.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ProgramUI>("org.machine", 1, 0, "Program");

    UIBind ui;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("ui", &ui);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
