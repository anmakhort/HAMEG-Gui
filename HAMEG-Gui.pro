
TARGET = HAMEG-Gui
TEMPLATE = app

QT += core gui charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += console

HEADERS += \
    include/rs232.h \
    include/settings.h \
    include/serialconsole.h \
    include/measurewnd.h \
    include/LCRGui.h \
    include/manager.h \
    include/freqpanel.h \
    include/btnpanel.h \
    include/adtpanel.h \
    include/serializer.h

SOURCES += \
    src/Application.cpp \
    src/settings.cpp \
    src/serialconsole.cpp \
    src/measurewnd.cpp \
    src/LCRGui.cpp \
    src/manager.cpp \
    src/rs232.cpp \
    src/freqpanel.cpp \
    src/btnpanel.cpp \
    src/adtpanel.cpp \
    src/serializer.cpp
