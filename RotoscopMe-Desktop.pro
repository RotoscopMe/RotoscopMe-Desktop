QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RotoscopMe-Deskop
TEMPLATE = app

HEADERS += \
    gui/mainwindow.h

SOURCES += \
    gui/main.cpp \
    gui/mainwindow.cpp
