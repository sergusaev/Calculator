#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "buttonsmodel.h"
#include "processor.h"
#include "argument.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    ButtonsModel buttonsModel;
    qmlRegisterType<Button>("Button", 1, 0, "Button");
    qmlRegisterSingletonInstance("Processor", 1, 0, "Processor", Processor::instance());
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("buttonsModel", &buttonsModel);
    engine.load(url);

    return app.exec();
}
