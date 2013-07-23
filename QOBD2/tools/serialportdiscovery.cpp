/*!
  \class SerialPortDiscovery
  \brief The SerialPortDiscovery class lists all serial ports plugged in the system and lists also all OBD devices on the system
  */
#include "serialportdiscovery.h"

const int SerialPortDiscovery::READ_TIMEOUT = 100;

SerialPortDiscovery::SerialPortDiscovery(QObject *parent) :
    QObject(parent)
{
}

/*!
 * \fn QList<QSerialPortInfo> *SerialPortDiscovery::getSerialPortList()
 *
 * \brief Lists all serial ports on the system, don't forget to delete the QList as soon as you don't use anymore!
 * Returns A QList<QSerialPortInfo>* containing all serial ports
 */
QList<QSerialPortInfo> *SerialPortDiscovery::getSerialPortList()
{
    return new QList<QSerialPortInfo>(QSerialPortInfo::availablePorts());
}

/*!
 * \fn QList<QSerialPortInfo> *SerialPortDiscovery::getOBDSerialPortList(SerialPortSettings settings)
 *
 * \brief Lists all serial ports that are OBD devices, testing them with \a settings as rs232 settings. Don't forget to delete the QList as soon as you don't use anymore!
 * Returns A QList<QSerialPortInfo>* containing all OBD devices
 */
QList<QSerialPortInfo> *SerialPortDiscovery::getOBDSerialPortList(SerialPortSettings settings)
{        
    QList<QSerialPortInfo>* allSerialPortList = getSerialPortList();
    QList<QSerialPortInfo>* obdSerialPortList = new QList<QSerialPortInfo>();
    QSerialPort serialPort;

    foreach(const QSerialPortInfo &info, *allSerialPortList)
    {
        serialPort.setPort(info);
        openPort(&serialPort, &settings);

        if(isOBDDevice(&serialPort))
            obdSerialPortList->append(info);
    }

    delete allSerialPortList;

    return obdSerialPortList;
}

/*!
 * \fn bool SerialPortDiscovery::isOBDDevice(QSerialPort *serialPort)
 *
 * \brief Tests if \a serialPort is an OBD device
 *
 * A serial port is considered as an OBD device if it answers "OK" to a "ATSP0\\r" request
 *
 * Returns A QList<QSerialPortInfo>* containing all OBD devices
 */
bool SerialPortDiscovery::isOBDDevice(QSerialPort *serialPort)
{
    QString response = "";
    QByteArray request = "ATSP0\r";

    serialPort->write(request);        
    while(serialPort->waitForReadyRead(READ_TIMEOUT))
    {        
        response += serialPort->readAll();
    }    
    serialPort->close();

    response = response.mid(request.length());
    return response.contains("OK");
}

/*!
 * \fn void SerialPortDiscovery::openPort(QSerialPort *serialPort, SerialPortSettings *settings)
 *
 * \brief Try to configure \a serialPort with \a settings
 */
void SerialPortDiscovery::openPort(QSerialPort *serialPort, SerialPortSettings *settings)
{
    if (!serialPort->open(QIODevice::ReadWrite))
    {
        emit error(QString(tr("failed to open port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setDataBits(settings->getDataBits()))
    {
        emit error(QString(tr("failed to set data bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setStopBits(settings->getStopBits()))
    {
        emit error(QString(tr("failed to set stop bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setParity(settings->getParityBits()))
    {
        emit error(QString(tr("failed to set parity bits on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setFlowControl(settings->getFlowControl()))
    {
        emit error(QString(tr("failed to set flow control on port %1")).arg(serialPort->portName()));
        return;
    }
    if(!serialPort->setBaudRate(settings->getBaudRate()))
    {
        emit error(QString(tr("failed to set baud rate port %1")).arg(serialPort->portName()));
        return;
    }
    serialPort->clear();
}
