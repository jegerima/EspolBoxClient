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
    libs.cpp \
    clientsocket.cpp \
    file.cpp \
    textparser.cpp \
    ebfile.cpp

HEADERS += \
    libs.h \
    clientsocket.h \
    file.h \
    textparser.h \
    ebfile.h
    textparser.h
