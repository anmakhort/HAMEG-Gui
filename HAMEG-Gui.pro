
TARGET = HAMEG-Gui
TEMPLATE = app

QT += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += console

HEADERS += \
    lcrmeasure.h \
    hameg_consts.h

SOURCES += \
    hameggui.cpp \
    lcrmeasure.cpp
