#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "appinfo.h"

QString getWindowTitle()
{
    QString title;
    title += qApp->applicationName();
    title += " - " + QObject::tr( VER_COMMENTS );
    title += " - Petrash Ilya ";
    title += " - " + QObject::tr( "version" ) + " " + qApp->applicationVersion();
    return title;
}

#include <QSettings>
#include <QDebug>

/// TODO: обработка ключей аргументов

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName( App::name );
    app.setApplicationVersion( App::version );

    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "utf8" ) );

    MainWindow w;
    w.setWindowTitle( getWindowTitle() );
    w.show();

    return app.exec();
}
