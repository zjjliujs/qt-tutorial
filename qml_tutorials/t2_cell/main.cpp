#include <QGuiApplication>
#include <QQmlApplicationEngine>

void loadQml (QGuiApplication * app, QQmlApplicationEngine * engine, const char * qmlRes) {
    const QUrl url(qmlRes);

    QObject::connect(engine
                     , &QQmlApplicationEngine::objectCreated
                     , app
    , [url](QObject * obj, const QUrl & objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine->load(url);

}

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    loadQml(&app, &engine, "qrc:/Cell.qml");
    loadQml(&app, &engine, "qrc:/main.qml");

    return app.exec();
}
