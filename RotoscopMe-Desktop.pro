QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RotoscopMe-Deskop
TEMPLATE = app

HEADERS += \
    gui/mainwindow.h \
    gui/drawarea.h \
    gui/ToolDialog.h

SOURCES += \
    gui/main.cpp \
    gui/mainwindow.cpp \
    gui/drawarea.cpp \
    gui/ToolDialog.cpp
