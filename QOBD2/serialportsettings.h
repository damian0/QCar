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
    SerialPortSettings();
    SerialPortSettings(QSerialPortInfo serialPortInfo);
    SerialPortSettings(QSerialPortInfo serialPortInfo, QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits,
                       QSerialPort::Parity parityBits, QSerialPort::BaudRate baudRate, QSerialPort::FlowControl flowControl);

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

    static const QSerialPort::DataBits DEFAULT_DATA_BITS;
    static const QSerialPort::StopBits DEFAULT_STOP_BITS;
    static const QSerialPort::Parity DEFAULT_PARITY_BITS;
    static const QSerialPort::BaudRate DEFAULT_BAUD_RATE;
    static const QSerialPort::FlowControl DEFAULT_FLOWCONTROL;
};

#endif // SERIALPORTSETTINGS_H
