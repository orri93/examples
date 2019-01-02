#-------------------------------------------------
#
# Project created by QtCreator 2019-01-02T12:43:01
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = qt-udp-socket
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINE += WIN32_LEAN_AND_MEAN

SOURCES += main.cpp \
    usesocket.cpp \
    tick.cpp

HEADERS += \
    usesocket.h \
    tick.h
