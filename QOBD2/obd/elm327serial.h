#ifndef QELM327SERIAL_H
#define QELM327SERIAL_H

#include "obddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "../tools/serialportsettings.h"
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Elm327Serial : public ObdDevice
{
public:
    explicit Elm327Serial(SerialPortSettings settings, QObject *parent = 0);
    ~Elm327Serial();
    void applySettings();

    /* Getters */
    SerialPortSettings getSettings() const;

    /* Setters */
    void setSettings(const SerialPortSettings &value);    

public slots:
    void close();

protected:
    ObdPidData requestPID(ObdPid *PID);
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
