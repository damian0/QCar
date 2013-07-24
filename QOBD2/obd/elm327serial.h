#ifndef ELM327SERIAL_H
#define ELM327SERIAL_H

#include "abstractobdhardware.h"
#include "obdresponsehandler.h"
#include "../tools/serialportsettings.h"
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class Elm327Serial : public AbstractObdHardware
{
    Q_OBJECT
public:
    explicit Elm327Serial(SerialPortSettings settings, QObject *parent = 0);
    ~Elm327Serial();

    bool connect();
    void disconnect();
    QStringList send(QString data);

    /* Getters */
    SerialPortSettings getSettings() const;
    int getTimeout() const;

    /* Setters */
    void setSettings(const SerialPortSettings &value);      
    void setTimeout(int value);

private:    
    bool applySettings();

    int timeout;
    ObdResponseHandler responseHandler;
    SerialPortSettings settings;    
    QSerialPort *serialPort;
};

#endif // ELM327SERIAL_H
