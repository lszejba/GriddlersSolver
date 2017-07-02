QT += core
QT -= gui

CONFIG += c++11

TARGET = GriddlersSolver
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    field.cpp \
    fieldline.cpp \
    board.cpp \
    fieldgroup.cpp

DISTFILES += \
    ../notes.txt

HEADERS += \
    field.h \
    fieldline.h \
    board.h \
    fieldgroup.h
