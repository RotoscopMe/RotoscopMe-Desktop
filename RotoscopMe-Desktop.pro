QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RotoscopMe-Deskop
TEMPLATE = app

HEADERS += \
    gui/mainwindow.h \
    gui/drawarea.h \
    gui/ToolDialog.h \
    core/projet.h \
    gui/CalqueContainer.h \
    gui/createprojectdialog.h \
    gui/visionnage.h

SOURCES += \
    gui/main.cpp \
    gui/mainwindow.cpp \
    gui/drawarea.cpp \
    gui/ToolDialog.cpp \
    core/projet.cpp \
    gui/CalqueContainer.cpp \
    gui/createprojectdialog.cpp \
    gui/visionnage.cpp

OTHER_FILES +=

RESOURCES += \
    RotoscopMe-Resources.qrc
