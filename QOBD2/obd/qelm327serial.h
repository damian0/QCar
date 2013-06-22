#ifndef QELM327SERIAL_H
#define QELM327SERIAL_H

#include "qobddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "../tools/serialportsettings.h"
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class QELM327Serial : public QOBDDevice
{
public:
    explicit QELM327Serial(SerialPortSettings settings, QObject *parent = 0);
    ~QELM327Serial();
    void applySettings();

    /* Getters */
    SerialPortSettings getSettings() const;

    /* Setters */
    void setSettings(const SerialPortSettings &value);    

protected:
    OBDPIDData requestPID(OBDPID *PID);
    bool searchVehicle();
    void init();

private:
    QStringList writeData(QString data, int timeout);
    QStringList parseData(QString data);

    QSerialPort *serialPort;
    SerialPortSettings settings;

    static const int READ_TIMEOUT;    
};

#endif // QELM327SERIAL_H
