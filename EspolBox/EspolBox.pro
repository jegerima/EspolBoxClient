#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T12:06:39
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = EspolBox
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    file.cpp \
    textparser.cpp \
    libs.cpp \
    clientsocket.cpp

HEADERS += \
    file.h \
    textparser.h \
    libs.h \
    clientsocket.h
