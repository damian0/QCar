/*!
  \class SerialPortSettings
  \brief Class containing main rs232 settings (data bits, stop bits, parity bits, ...)

  */
#ifndef SERIALPORTSETTINGS_H
#define SERIALPORTSETTINGS_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortSettings
{
public:
    SerialPortSettings(QSerialPortInfo serialPortInfo = QSerialPortInfo(),
                       QSerialPort::DataBits dataBits = QSerialPort::Data8,
                       QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                       QSerialPort::Parity parityBits = QSerialPort::NoParity,
                       QSerialPort::BaudRate baudRate = QSerialPort::Baud115200,
                       QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl);

    /* Getters */
    QSerialPortInfo getSerialPortInfo() const;    
    QSerialPort::DataBits getDataBits() const;
    QSerialPort::StopBits getStopBits() const;
    QSerialPort::Parity getParityBits() const;
    QSerialPort::BaudRate getBaudRate() const;
    QSerialPort::FlowControl getFlowControl() const;


    /* Setters */
    void setSerialPortInfo(const QSerialPortInfo &value);
    void setDataBits(const QSerialPort::DataBits &value);
    void setStopBits(const QSerialPort::StopBits &value);
    void setParityBits(const QSerialPort::Parity &value);
    void setBaudRate(const QSerialPort::BaudRate &value);
    void setFlowControl(const QSerialPort::FlowControl &value);

private:
    QSerialPortInfo serialPortInfo;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity parityBits;
    QSerialPort::BaudRate baudRate;
    QSerialPort::FlowControl flowControl;   
};

#endif // SERIALPORTSETTINGS_H
