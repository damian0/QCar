#ifndef QELM327SERIAL_H
#define QELM327SERIAL_H

#include "qobddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "serialportsettings.h"
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

private:
    QSerialPort *serialPort;
    SerialPortSettings settings;

    static const int READ_TIMEOUT;
};

#endif // QELM327SERIAL_H
