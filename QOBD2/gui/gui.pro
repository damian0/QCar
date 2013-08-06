QT       += core gui serialport xml xmlpatterns

# Add more folders to ship with the application, here
folder_01.source = qml/gui
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

INCLUDEPATH += . ../tools ../obd ../xml

HEADERS += ../tools/pidloader.h \
           ../tools/serialportsettings.h \
           ../tools/serialportdiscovery.h \
           ../xml/pidxmlhandler.h \
           ../obd/atcommand.h \
           ../obd/obdpid.h \
           ../obd/obdpiddata.h \
           ../obd/interpreter/arithmeticevaluator.h \
           ../obd/interpreter/arithmetictools.h \
           ../obd/interpreter/treenode.h \
           ../obd/elm327serial.h \
           ../obd/elm327simulator.h \
           ../obd/obddevice.h \
           ../obd/abstractobdhardware.h \
           ../obd/obdresponsehandler.h \
           ../obd/obdhardwarefactory.h \
    obddeviceproxy.h
SOURCES += main.cpp \
           ../tools/pidloader.cpp \
           ../tools/serialportsettings.cpp \
           ../tools/serialportdiscovery.cpp \
           ../xml/pidxmlhandler.cpp \
           ../obd/atcommand.cpp \
           ../obd/obdpid.cpp \
           ../obd/obdpiddata.cpp \
           ../obd/interpreter/arithmeticevaluator.cpp \
           ../obd/interpreter/arithmetictools.cpp \
           ../obd/interpreter/treenode.cpp \
           ../obd/elm327serial.cpp \
           ../obd/elm327simulator.cpp \
           ../obd/obddevice.cpp \
           ../obd/abstractobdhardware.cpp \
           ../obd/obdresponsehandler.cpp \
           ../obd/obdhardwarefactory.cpp \
    obddeviceproxy.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()
