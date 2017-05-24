
TARGET = HAMEG-Gui
TEMPLATE = app

QT += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

HEADERS += \
    hameg_consts.h \
    rs232.h \
    settings.h \
    serialconsole.h \
    measurewnd.h \
    LCRGui.h

SOURCES += \
    Application.cpp \
    settings.cpp \
    serialconsole.cpp \
    measurewnd.cpp \
    LCRGui.cpp
