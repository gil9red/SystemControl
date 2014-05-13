#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

#include "winsystemcommand.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Заполнение вариантов действий.
    {
        ui->options->addItem( tr( "Power off" ),  WinSystemCommand::PowerOff );
        ui->options->addItem( tr( "Reboot" ),     WinSystemCommand::Reboot  );
        ui->options->addItem( tr( "Force" ),      WinSystemCommand::Force );
        ui->options->addItem( tr( "Shutdown" ),   WinSystemCommand::Shutdown );
        ui->options->addItem( tr( "Log off" ),    WinSystemCommand::LogOff );
        ui->options->addItem( tr( "Hibernate" ),  WinSystemCommand::Hibernate );
        ui->options->addItem( tr( "Suspend" ),    WinSystemCommand::Suspend );
        ui->options->addItem( tr( "Screen off" ), WinSystemCommand::ScreenOff );

        ui->options->setCurrentIndex( ui->options->findData( WinSystemCommand::Hibernate ) );
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox_clicked(QAbstractButton * button)
{
    const QDialogButtonBox::ButtonRole role = ui->buttonBox->buttonRole( button );
    if ( role == QDialogButtonBox::ApplyRole )
    {
        int index = ui->options->currentIndex();
        int option = ui->options->itemData( index ).toInt();
        WinSystemCommand::Command command = static_cast < WinSystemCommand::Command > ( option );
        bool successful = WinSystemCommand::execute( command );
        if ( !successful )
        {
            const QString & message = WinSystemCommand::getTextError( command );
            QMessageBox::warning( this, tr( "Warning" ), message );
        }

    } else if ( role == QDialogButtonBox::RejectRole )
    {
        qApp->quit();
    }
}
