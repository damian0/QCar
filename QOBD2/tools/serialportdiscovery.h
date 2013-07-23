#ifndef QSERIALPORTDISCOVERY_H
#define QSERIALPORTDISCOVERY_H

#include "../tools/serialportsettings.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QObject>

class SerialPortDiscovery : public QObject
{
    Q_OBJECT
public:    
    explicit SerialPortDiscovery(QObject *parent = 0);

    QList<QSerialPortInfo> *getSerialPortList();
    QList<QSerialPortInfo> *getOBDSerialPortList(SerialPortSettings settings);
private:
    bool isOBDDevice(QSerialPort *serialPort);
    void openPort(QSerialPort *serialPort, SerialPortSettings *settings);

    static const int READ_TIMEOUT;

signals:
    void error(const QString);
    
};

#endif // QSERIALPORTDISCOVERY_H
