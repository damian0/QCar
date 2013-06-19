#include "qserialportdiscovery.h"
#include <QDebug>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QSerialPortDiscovery::QSerialPortDiscovery()
{
}

QList<QSerialPortInfo> *QSerialPortDiscovery::getSerialPortList()
{
    return new QList<QSerialPortInfo>(QSerialPortInfo::availablePorts());
}

QList<QSerialPortInfo> *QSerialPortDiscovery::getOBDSerialPortList(SerialPortSettings settings)
{
    QList<QSerialPortInfo>* allSerialPortList = getSerialPortList();
    QList<QSerialPortInfo>* obdSerialPortList = new QList<QSerialPortInfo>();
    QSerialPort serialPort;

    foreach(const QSerialPortInfo &info, *allSerialPortList)
    {
        serialPort.setPort(info);
        serialPort.setDataBits(settings.getDataBits());
        serialPort.setStopBits(settings.getStopBits());
        serialPort.setParity(settings.getParityBits());
        serialPort.setFlowControl(settings.getFlowControl());
        serialPort.setBaudRate(settings.getBaudRate());

        if(isOBDDevice(&serialPort))
            obdSerialPortList->append(info);
    }

    delete allSerialPortList;

    return obdSerialPortList;
}

bool QSerialPortDiscovery::isOBDDevice(QSerialPort *serialPort)
{
    QString response = "";
    if (serialPort->open(QIODevice::ReadWrite))
    {
        QByteArray request = "ATSP0\r";

        serialPort->write(request);

        if(serialPort->waitForReadyRead(50))
        {
            response = QString(serialPort->readAll());
            while(serialPort->waitForReadyRead(50))
            {
                response += QString(serialPort->readAll());
            }
        }
        serialPort->close();
    }
    return response.contains("OK");
}
