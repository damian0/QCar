#-------------------------------------------------
#
# Project created by QtCreator 2013-06-03T19:35:30
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOBD2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qobddevice.cpp \
    qelm327simulator.cpp \
    qelm327serial.cpp \
    obdpiddata.cpp \
    obdpid.cpp \
    atcommand.cpp \
    qserialportdiscovery.cpp \
    serialportsettings.cpp

HEADERS  += mainwindow.h \
    qobddevice.h \
    qelm327simulator.h \
    qelm327serial.h \
    obdpiddata.h \
    obdpid.h \
    atcommand.h \
    qserialportdiscovery.h \
    serialportsettings.h

FORMS    += mainwindow.ui
