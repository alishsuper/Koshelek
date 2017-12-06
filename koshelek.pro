#-------------------------------------------------
#
# Project created by QtCreator 2017-08-02T20:58:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = koshelek
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    form.cpp \
    pinkod.cpp

HEADERS  += mainwindow.h \
    form.h \
    pinkod.h \
    crypter.h

FORMS    += mainwindow.ui \
    form.ui \
    pinkod.ui
