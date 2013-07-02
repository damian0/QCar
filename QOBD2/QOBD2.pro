#-------------------------------------------------
#
# Project created by QtCreator 2013-06-03T19:35:30
#
#-------------------------------------------------

QT       += core gui serialport xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOBD2
TEMPLATE = app

INCLUDEPATH += . tools obd xml

# Input
HEADERS += mainwindow.h \
           obd/atcommand.h \
           obd/obdpid.h \
           obd/obdpiddata.h \
           obd/qelm327serial.h \
           obd/qelm327simulator.h \
           obd/qobddevice.h \
           tools/pidloader.h \
           tools/qserialportdiscovery.h \
           tools/serialportsettings.h \
           xml/pidxmlhandler.h \
           obd/interpreter/arithmeticevaluator.h \
    obd/interpreter/arithmetictools.h \
    obd/interpreter/treenode.h
FORMS += mainwindow.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           obd/atcommand.cpp \
           obd/obdpid.cpp \
           obd/obdpiddata.cpp \
           obd/qelm327serial.cpp \
           obd/qelm327simulator.cpp \
           obd/qobddevice.cpp \
           tools/pidloader.cpp \
           tools/qserialportdiscovery.cpp \
           tools/serialportsettings.cpp \
           xml/pidxmlhandler.cpp \
           obd/interpreter/arithmeticevaluator.cpp \
    obd/interpreter/arithmetictools.cpp \
    obd/interpreter/treenode.cpp
