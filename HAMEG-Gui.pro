
TARGET = HAMEG-Gui
TEMPLATE = app

QT += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

HEADERS += \
    include/rs232.h \
    include/settings.h \
    include/serialconsole.h \
    include/measurewnd.h \
    include/LCRGui.h \
    include/hameg_consts.h \

SOURCES += \
    src/Application.cpp \
    src/settings.cpp \
    src/serialconsole.cpp \
    src/measurewnd.cpp \
    src/LCRGui.cpp
