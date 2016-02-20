#include <QtGui>
#include <QtQml>
#include <QQuickView>
#include <QtWidgets/QApplication>


#include "src/machine.hpp"
#include "src/itape.hpp"
#include "src/otape.hpp"
#include "src/memory.hpp"


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QVector<int> aux = {};
  ITape itape (aux);
  OTape otape;
  Memory memory(10);

  Machine machine(otape, itape, memory);

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("machine", &machine);
  engine.rootContext()->setContextProperty("memory", &memory);
  engine.rootContext()->setContextProperty("itape", &itape);
  engine.rootContext()->setContextProperty("otape", &otape);


  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  return app.exec();
}
