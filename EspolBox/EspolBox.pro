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
    ebfile.cpp \
    parser.cpp \
    listener.cpp

HEADERS += \
    libs.h \
    clientsocket.h \
    file.h \
    ebfile.h \
    parser.h \
    listener.h
