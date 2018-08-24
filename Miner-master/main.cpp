#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "minerprocess.h"
#include "minerui.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
  //  QQuickStyle::setStyle("Material");

	qmlRegisterType<MinerProcess>("minerprocess", 1, 0, "MinerProcess");
	qmlRegisterType<MinerUI>("minerui", 1, 0, "MinerUI");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
