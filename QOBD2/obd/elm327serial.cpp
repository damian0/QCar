#include "elm327serial.h"
#include <QDebug>
#include <QStringListIterator>
#include <QRegExp>
#include <QThread>

Elm327Serial::Elm327Serial(SerialPortSettings settings, QObject *parent) : AbstractObdHardware(parent)
{    
    setSettings(settings);
    setTimeout(1000);
    serialPort = 0;
    connected = false;
}

Elm327Serial::~Elm327Serial()
{    
    disconnect();
    delete serialPort;        
}

bool Elm327Serial::applySettings()
{    
    serialPort = new QSerialPort(settings.getSerialPortInfo(), this);

    if(!serialPort->open(QIODevice::ReadWrite))
    {        
        emit error(QString(tr("failed to open port %1")).arg(serialPort->portName()));
        return false;
    }
    if(!serialPort->setDataBits(settings.getDataBits()))
    {
        emit error(QString(tr("failed to set data bits on port %1")).arg(serialPort->portName()));
        return false;
    }
    if(!serialPort->setStopBits(settings.getStopBits()))
    {
        emit error(QString(tr("failed to set stop bits on port %1")).arg(serialPort->portName()));
        return false;
    }
    if(!serialPort->setParity(settings.getParityBits()))
    {
        emit error(QString(tr("failed to set parity bits on port %1")).arg(serialPort->portName()));
        return false;
    }
    if(!serialPort->setFlowControl(settings.getFlowControl()))
    {
        emit error(QString(tr("failed to set flow control on port %1")).arg(serialPort->portName()));
        return false;
    }
    if(!serialPort->setBaudRate(settings.getBaudRate()))
    {
        emit error(QString(tr("failed to set baud rate port %1")).arg(serialPort->portName()));
        return false;
    }    

    serialPort->clear();    
    return true;
}

void Elm327Serial::disconnect()
{
    if(serialPort)
    {
        serialPort->close();
        delete serialPort;
        serialPort = 0;
        emit log(QString("%1 : disconnected").arg(deviceName));
    }
    connected = false;
}

bool Elm327Serial::connect()
{    
    disconnect();
    bool ok = applySettings();

    if(!ok) return false;

    connected = true;
    deviceName = send("ATZ\r").first();
    emit log(QString("%1 : connected").arg(deviceName));

    return true;
}

QStringList Elm327Serial::send(QString data)
{
    if(!connected)
    {
        return QStringList();
    }
    else
    {
        QString buffer;

        serialPort->write(data.toLocal8Bit());

        while(serialPort->waitForReadyRead(timeout))
        {
            buffer += serialPort->readAll();
        }

        //removes the request from response
        buffer = buffer.mid(data.length());

        return responseHandler.parseData(buffer);
    }
}

int Elm327Serial::getTimeout() const
{
    return timeout;
}

SerialPortSettings Elm327Serial::getSettings() const
{
    return settings;
}

void Elm327Serial::setTimeout(int value)
{
    timeout = value;
}

void Elm327Serial::setSettings(const SerialPortSettings &value)
{
    settings = value;
}
