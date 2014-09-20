#-------------------------------------------------
#
# Project created by QtCreator 2014-09-19T11:46:09
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RulesOfRoadClient
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ConnectionDialog.cpp \
    Connection.cpp

HEADERS  += MainWindow.h \
    ConnectionDialog.h \
    Connection.h

FORMS    += MainWindow.ui \
    ConnectionDialog.ui
