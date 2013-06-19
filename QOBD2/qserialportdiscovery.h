#ifndef QSERIALPORTDISCOVERY_H
#define QSERIALPORTDISCOVERY_H

#include "serialportsettings.h"
#include <QList>

class QSerialPortInfo;

class QSerialPortDiscovery
{
public:
    QSerialPortDiscovery();
    static QList<QSerialPortInfo> *getSerialPortList();
    static QList<QSerialPortInfo> *getOBDSerialPortList(SerialPortSettings settings);
private:
    static bool isOBDDevice(QSerialPort *serialPort);

};

#endif // QSERIALPORTDISCOVERY_H
