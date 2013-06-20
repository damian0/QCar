#include "qelm327serial.h"

const int QELM327Serial::READ_TIMEOUT = 50;

QELM327Serial::QELM327Serial(SerialPortSettings settings)
{
    setSettings(settings);
    applySettings();
}

void QELM327Serial::applySettings()
{
    serialPort.setPort(settings.getSerialPortInfo());
    if(!serialPort.open(QIODevice::ReadWrite))
    {
        emit error(QString(tr("failed to open port %1")).arg(serialPort.portName()));
        return;
    }
    if(!serialPort.setDataBits(settings.getDataBits()))
    {
        emit error(QString(tr("failed to set data bits on port %1")).arg(serialPort.portName()));
        return;
    }
    if(!serialPort.setStopBits(settings.getStopBits()))
    {
        emit error(QString(tr("failed to set stop bits on port %1")).arg(serialPort.portName()));
        return;
    }
    if(!serialPort.setParity(settings.getParityBits()))
    {
        emit error(QString(tr("failed to set parity bits on port %1")).arg(serialPort.portName()));
        return;
    }
    if(!serialPort.setFlowControl(settings.getFlowControl()))
    {
        emit error(QString(tr("failed to set flow control on port %1")).arg(serialPort.portName()));
        return;
    }
    if(!serialPort.setBaudRate(settings.getBaudRate()))
    {
        emit error(QString(tr("failed to set baud rate port %1")).arg(serialPort.portName()));
        return;
    }
    serialPort.clear();
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
    QByteArray request = (PID->getPid() + '\r').toLocal8Bit();
    serialPort.write(request);

    while(serialPort.waitForReadyRead(READ_TIMEOUT))
    {
        response += serialPort.readAll();
    }

    return PID->computeValue(response);
}
