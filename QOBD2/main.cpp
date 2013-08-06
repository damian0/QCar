#include <QCoreApplication>
#include <QThread>
#include "tools/serialportdiscovery.h"
#include "tools/serialportsettings.h"
#include "obd/obdhardwarefactory.h"
#include "obd/obddevice.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    /**
     * QOBD2 usage example
     */

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

    // And finally the obd device (logical)
    ObdDevice obd(elm327Hardware);

    // OBD II dedicated thread
    QThread obdThread(qApp);
    QObject::connect(&obdThread, &QThread::started, &obd, &ObdDevice::start);
    obd.moveToThread(&obdThread);

    // Connections here
    //QObject::connect(&obd, &ObdDevice::log, &yourObject, &YourClass::itsSlot);
    //QObject::connect(&obd, &ObdDevice::error, &yourObject, &YourClass::itsSlot);
    //QObject::connect(&obd, &ObdDevice::newData, &yourObject, &YourClass::itsSlot);

    // Start OBD II device
    obd.connectHardware();
    obdThread.start();

    return app.exec();
}
