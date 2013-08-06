#ifndef OBDDEVICEPROXY_H
#define OBDDEVICEPROXY_H

#include <QObject>
#include <QString>
#include "../obd/obdpiddata.h"

class ObdDeviceProxy : public QObject
{
    Q_OBJECT
public:
    explicit ObdDeviceProxy(QObject *parent = 0);    
    
signals:
    Q_SIGNAL void log(const QString message);
    Q_SIGNAL void error(const QString err);
    Q_SIGNAL void newData(const ObdPidData &data);
    
public slots:
    void logSlot(const QString message);
    void errorSlot(const QString err);
    void newDataSlot(const ObdPidData &data);
    
};

#endif // OBDDEVICEPROXY_H
