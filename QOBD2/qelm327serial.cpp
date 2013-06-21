#include "qelm327serial.h"
#include <QDebug>

const int QELM327Serial::READ_TIMEOUT = 50;

QELM327Serial::QELM327Serial(SerialPortSettings settings, QObject *parent):QOBDDevice(parent)
{
    setSettings(settings);
    applySettings();
}

QELM327Serial::~QELM327Serial()
{
    delete serialPort;
}

void QELM327Serial::applySettings()
{
    serialPort = new QSerialPort(settings.getSerialPortInfo(), this);
    if(!serialPort->open(QIODevice::ReadWrite))
    {
        emit error(QString(tr("failed to open port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setDataBits(settings.getDataBits()))
    {
        emit error(QString(tr("failed to set data bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setStopBits(settings.getStopBits()))
    {
        emit error(QString(tr("failed to set stop bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setParity(settings.getParityBits()))
    {
        emit error(QString(tr("failed to set parity bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setFlowControl(settings.getFlowControl()))
    {
        emit error(QString(tr("failed to set flow control on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setBaudRate(settings.getBaudRate()))
    {
        emit error(QString(tr("failed to set baud rate port %1")).arg(serialPort->portName()));
        return;
    }
    serialPort->clear();
}

SerialPortSettings QELM327Serial::getSettings() const
{
    return settings;
}


void QELM327Serial::setSettings(const SerialPortSettings &value)
{
    settings = value;
}

OBDPIDData QELM327Serial::requestPID(OBDPID *PID)
{
    QString response = "";
    QByteArray request = PID->getPid().toLocal8Bit();    
    //serialPort->write(request);
    //serialPort->write(QString('\r').toLocal8Bit());

    for(int i = 0;i < PID->getPid().size(); i++)
    {
        serialPort->write(QString(PID->getPid()[i]).toLocal8Bit());
    }
    serialPort->write(QString('\r').toLocal8Bit());

    if (serialPort->waitForBytesWritten(READ_TIMEOUT)) {
        while(serialPort->waitForReadyRead(READ_TIMEOUT))
            response += serialPort->readAll();
    }

    qDebug() << request <<response;

    return PID->computeValue(response);
}
