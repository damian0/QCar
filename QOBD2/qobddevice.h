#ifndef QOBDDEVICE_H
#define QOBDDEVICE_H

#include "obdpid.h"
#include "obdpiddata.h"
#include <QObject>
#include <QList>
#include <QHash>

class QOBDDevice : public QObject
{
    Q_OBJECT
public:
    explicit QOBDDevice(QObject *parent = 0);    

    void stop();
    void pause();
    void addPID(QString PIDName);
    void removePID(QString PIDName);
    void setPollInterval(QString PIDName, int interval);

public slots:
    void start();

protected:
    void pollingLoop();
    int waitingTime();
    virtual OBDPIDData requestPID(OBDPID* PID) = 0;

    bool isRunning;
    bool isPaused;
    QHash<QString,OBDPID*> allPIDsHash;
    QHash<QString,OBDPID*> PIDsToPollHash;

    static const int PAUSE_DELAY_MS;
    
signals:
    void newData(OBDPIDData PID);
    void error(QString);
};

#endif // QOBDDEVICE_H
