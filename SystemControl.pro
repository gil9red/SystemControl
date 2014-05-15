QT       += core gui

TARGET = SystemControl
TEMPLATE = app
CONFIG   += console

DESTDIR = ../bin

SOURCES += main.cpp\
        mainwindow.cpp \
    winsystemcommand.cpp

HEADERS  += mainwindow.h \
    appinfo.h \
    winsystemcommand.h

FORMS    += mainwindow.ui

win32:
{
    RC_FILE = app.rc
    OTHER_FILES += app.rc
}
