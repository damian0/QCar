#include "serialportsettings.h"

SerialPortSettings::SerialPortSettings(QSerialPortInfo serialPortInfo,
                                       QSerialPort::DataBits dataBits,
                                       QSerialPort::StopBits stopBits,
                                       QSerialPort::Parity parityBits,
                                       QSerialPort::BaudRate baudRate,
                                       QSerialPort::FlowControl flowControl)
{
    setSerialPortInfo(serialPortInfo);
    setDataBits(dataBits);
    setStopBits(stopBits);
    setParityBits(parityBits);
    setBaudRate(baudRate);
    setFlowControl(flowControl);
}

QSerialPortInfo SerialPortSettings::getSerialPortInfo() const
{
    return serialPortInfo;
}

void SerialPortSettings::setSerialPortInfo(const QSerialPortInfo &value)
{        
    serialPortInfo = value;
}

QSerialPort::FlowControl SerialPortSettings::getFlowControl() const
{
    return flowControl;
}

void SerialPortSettings::setFlowControl(const QSerialPort::FlowControl &value)
{
    flowControl = value;
}

QSerialPort::BaudRate SerialPortSettings::getBaudRate() const
{
    return baudRate;
}

void SerialPortSettings::setBaudRate(const QSerialPort::BaudRate &value)
{
    baudRate = value;
}

QSerialPort::Parity SerialPortSettings::getParityBits() const
{
    return parityBits;
}

void SerialPortSettings::setParityBits(const QSerialPort::Parity &value)
{
    parityBits = value;
}

QSerialPort::StopBits SerialPortSettings::getStopBits() const
{
    return stopBits;
}

void SerialPortSettings::setStopBits(const QSerialPort::StopBits &value)
{
    stopBits = value;
}

QSerialPort::DataBits SerialPortSettings::getDataBits() const
{
    return dataBits;
}

void SerialPortSettings::setDataBits(const QSerialPort::DataBits &value)
{
    dataBits = value;
}
