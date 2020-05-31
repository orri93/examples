#include <QCursor>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QSysInfo>


int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QQuickView view;

    view.engine()->addImportPath(QGuiApplication::applicationDirPath());
    view.setSource(QUrl::fromLocalFile("plugins.qml"));
    view.show();
    return app.exec();
}
