#include <QtGui>
#include <QtQml>
#include <QQuickView>

#include <vector>

#include "uibind.hpp"
#include "tapemodel.hpp"

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  // qmlRegisterType<ProgramUI>("org.machine", 1, 0, "Program");

  //UIBind ui();
  AnimalModel model;
    model.addAnimal(Animal("Wolf", "Medium"));
    model.addAnimal(Animal("Polar bear", "Large"));
    model.addAnimal(Animal("Quoll", "Small"));

  vector<int> aux {1,5,8,77,8,5};

  TapeModel itape;
  itape.tape_ = aux;

  TapeModel otape;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("myModel", &model);
  engine.rootContext()->setContextProperty("itape", &itape);
  engine.rootContext()->setContextProperty("otape", &otape);


  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  //QQuickView view;
  //view.setResizeMode(QQuickView::SizeRootObjectToView);

  //QQmlContext *ctxt = view.rootContext();
  //ctxt->setContextProperty("myModel", &model);


  //view.setSource(QUrl("qrc:/main.qml"));
  //view.show();

  return app.exec();
}
