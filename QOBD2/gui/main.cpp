#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <QtQml>
#include <QThread>
#include <QTimer>
#include "qtquick2applicationviewer.h"

#include "../tools/serialportdiscovery.h"
#include "../tools/serialportsettings.h"
#include "../obd/obdhardwarefactory.h"
#include "../obd/obddevice.h"
#include "obddeviceproxy.h"

void registerCustomTypes();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);    

    registerCustomTypes();

    // Serial port setup
    // Serial port settings
    SerialPortSettings settings;
    SerialPortDiscovery serialPortDiscovery;
    QList<QSerialPortInfo>* ports = serialPortDiscovery.getOBDSerialPortList(settings);

    // We take the first OBD II device in the list
    settings.setSerialPortInfo(ports->first());
    delete ports;

    // We get some hardware
    AbstractObdHardware* elm327Hardware = ObdHardwareFactory::createElm327Serial(settings);

    // And finally the obd device
    ObdDevice obd(elm327Hardware);

    // OBD II dedicated thread
    QThread obdThread(qApp);
    QObject::connect(&obdThread, &QThread::started, &obd, &ObdDevice::start);
    obd.moveToThread(&obdThread);

    // Little hack to get rid of the thread issues
    // we cannot use the obdDevice directly in QML because it runs in a dedicated thread
    ObdDeviceProxy proxy;
    QObject::connect(&obd, &ObdDevice::log, &proxy, &ObdDeviceProxy::logSlot);

    //QML part
    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("obdProxy", &proxy);
    viewer.setMainQmlFile(QStringLiteral("qml/gui/main.qml"));    
    viewer.showExpanded();

    // Start OBD II device
    //QTimer::singleShot(1000, &obd, SLOT(connectHardware()));
    //QTimer::singleShot(2000, &obdThread, SLOT(start()));
    obd.connectHardware();
    obdThread.start();


    return app.exec();
}


void registerCustomTypes()
{
    //qmlRegisterType<ObdDevice>("QObd2", 1, 0, "ObdDevice");
}
