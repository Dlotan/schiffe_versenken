#-------------------------------------------------
#
# Project created by QtCreator 2014-12-04T18:30:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = schiffe_versenken
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    eigenerbutton.cpp \
    gegnerbutton.cpp \
    schiffbutton.cpp

HEADERS  += mainwindow.h \
    eigenerbutton.h \
    gegnerbutton.h \
    schiffbutton.h \
    schiffauswahl.h
