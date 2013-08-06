#-------------------------------------------------
#
# Project created by QtCreator 2013-06-03T19:35:30
#
#-------------------------------------------------

QT       += core serialport xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QOBD2
TEMPLATE = app

INCLUDEPATH += . tools obd xml

# Input
HEADERS += tools/pidloader.h \
           tools/serialportsettings.h \
           tools/serialportdiscovery.h \
           xml/pidxmlhandler.h \
           obd/interpreter/arithmeticevaluator.h \
           obd/interpreter/arithmetictools.h \
           obd/interpreter/treenode.h \
           obd/elm327serial.h \
           obd/elm327simulator.h \
           obd/obddevice.h \
           obd/abstractobdhardware.h \
           obd/obdresponsehandler.h \
           obd/obdhardwarefactory.h \
           obd/atcommand.h \
           obd/obdpid.h \
           obd/obdpiddata.h

SOURCES += main.cpp \           
           tools/pidloader.cpp \
           tools/serialportsettings.cpp \
           tools/serialportdiscovery.cpp \
           xml/pidxmlhandler.cpp \
           obd/interpreter/arithmeticevaluator.cpp \
           obd/interpreter/arithmetictools.cpp \
           obd/interpreter/treenode.cpp \
           obd/elm327serial.cpp \
           obd/elm327simulator.cpp \
           obd/obddevice.cpp \
           obd/abstractobdhardware.cpp \
           obd/obdresponsehandler.cpp \
           obd/obdhardwarefactory.cpp \    
           obd/atcommand.cpp \
           obd/obdpid.cpp \
           obd/obdpiddata.cpp
