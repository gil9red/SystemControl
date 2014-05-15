#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "appinfo.h"
#include "winsystemcommand.h"

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

QString getHelp()
{
    QString text;
    text += QObject::tr( "Arguments:" ) + "\n";
    text += "-force\n";
    text += "-reboot\n";
    text += "-shutdow\n";
    text += "-logOff\n";
    text += "-hibernate\n";
    text += "-suspend\n";
    text += "-screenOff\n";
    text += "-help";
    return text;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName( App::name );
    app.setApplicationVersion( App::version );

    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "utf8" ) );

    QStringList arguments = app.arguments();
    if ( arguments.count() > 1 )
    {
        arguments.removeFirst(); // Первым является путь кехе
        foreach ( const QString & arg, arguments )
        {
            WinSystemCommand::Command command = (WinSystemCommand::Command) -1;
            if ( arg.contains( "-force", Qt::CaseInsensitive ) )
                command = WinSystemCommand::Force;

            else if ( arg.contains( "-reboot", Qt::CaseInsensitive ) )
                command = WinSystemCommand::Reboot;

            else if ( arg.contains( "-shutdown", Qt::CaseInsensitive ) )
                command = WinSystemCommand::Shutdown;

            else if ( arg.contains( "-logOff", Qt::CaseInsensitive ) )
                command = WinSystemCommand::LogOff;

            else if ( arg.contains( "-hibernate", Qt::CaseInsensitive ) )
                command = WinSystemCommand::Hibernate;

            else if ( arg.contains( "-suspend", Qt::CaseInsensitive ) )
                command = WinSystemCommand::Suspend;

            else if ( arg.contains( "-screenOff", Qt::CaseInsensitive ) )
                command = WinSystemCommand::ScreenOff;

            else if ( arg.contains( "-help", Qt::CaseInsensitive ) )
            {
                qDebug() << getHelp();
                return 0;
            }

            if ( command == -1 )
            {
                qDebug() << QObject::tr( "Unknown command" );
                return 0;
            }

            bool successful = WinSystemCommand::execute( command );
            if ( !successful )
            {
                const QString & message = WinSystemCommand::getTextError( command );
                qDebug() << "Error:" << message;
            }
        }

        return 0;
    }

    MainWindow w;
    w.setWindowTitle( getWindowTitle() );
    w.show();

    return app.exec();
}
