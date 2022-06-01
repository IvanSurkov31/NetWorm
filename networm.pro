#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T19:31:29
#
#-------------------------------------------------

QT       += core gui

INCLUDEPATH +=C:/qwt/include
LIBS += -L C:/qwt/lib -lqwt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = networm
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h
