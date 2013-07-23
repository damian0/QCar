#include "elm327serial.h"
#include <QDebug>
#include <QStringListIterator>
#include <QRegExp>
#include <QThread>

const int Elm327Serial::READ_TIMEOUT    = 1000;

Elm327Serial::Elm327Serial(SerialPortSettings settings, QObject *parent):ObdDevice(parent)
{
    setSettings(settings);
    applySettings();
    init();
}

Elm327Serial::~Elm327Serial()
{    
    delete serialPort;    
}

void Elm327Serial::applySettings()
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

SerialPortSettings Elm327Serial::getSettings() const
{
    return settings;
}


void Elm327Serial::setSettings(const SerialPortSettings &value)
{
    settings = value;
}

void Elm327Serial::close()
{
    serialPort->close();
}

ObdPidData Elm327Serial::requestPID(ObdPid *PID)
{        
    int nbLines = PID->getNbLines();
    QString pattern = (!nbLines)?"%1\r":"%1%2\r";
    QString request = QString(pattern).arg(PID->getPid()).arg(nbLines);

    QStringList response = writeData(request, requestTimeout);    
    double value = PID->computeValue(response);
    ObdPidData pidData(PID->getPid(), PID->getName(), PID->getDescription(), value, PID->getUnit());
    return pidData;
}

bool Elm327Serial::searchVehicle()
{    
    QStringList response = writeData("0100\r", 4*READ_TIMEOUT);
    return !response.contains("UNABLE TO CONNECT>") && !response.contains("SEARCHING...");
}

void Elm327Serial::init()
{
    ObdDevice::init();
    requestTimeout = 40;
    name = writeData("ATZ\r", READ_TIMEOUT).first();

    emit log(QString(tr("Device : %1")).arg(name));
    emit log(QString(tr("Auto-select protocol : %1")).arg(writeData("ATSP0\r", READ_TIMEOUT).first()));
}

QStringList Elm327Serial::writeData(QString data, int timeout)
{    
    QString buffer;
    serialPort->write(data.toLocal8Bit());

    if (serialPort->waitForBytesWritten(timeout))
    {        
        while(serialPort->waitForReadyRead(timeout))
        {
            buffer += serialPort->readAll();
        }
    }
    //removes the request from response
    QString pattern = QString("^%1").arg(data);
    buffer.replace(QRegExp(pattern), "");
    return parseData(buffer);
}

QStringList Elm327Serial::parseData(QString data)
{
    QStringList splittedData = data.split('\r');

    //trim all strings
    splittedData.replaceInStrings(QRegExp("^\\s*||\\s*$"), "");
    //removes all \r
    splittedData.replaceInStrings(QString("\r"), QString(""));
    //removes all >
    splittedData.replaceInStrings(QString(">"), QString(""));
    //removes all empty strings
    splittedData.removeAll(QString(""));

    return splittedData;
}
