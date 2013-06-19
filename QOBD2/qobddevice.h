#ifndef QOBDDEVICE_H
#define QOBDDEVICE_H

#include <QObject>
#include <QList>

class OBDPID;
class OBDPIDData;

class QOBDDevice : public QObject
{
    Q_OBJECT
public:
    explicit QOBDDevice(QObject *parent = 0);

    void start();
    void stop();
    void pause();
    void addPID(QString PIDName);
    void removePID(QString PIDName);
    void setPollInterval(QString PIDName, int interval);

private:
    bool isRunning;
    QList<OBDPID*> allPIDsList;
    QList<OBDPID*> PIDsToPollList;

    void pollingLoop();
    OBDPIDData requestPID(OBDPID* PID);
    
signals:
    void newData(OBDPIDData PID);
    
public slots:
    
};

#endif // QOBDDEVICE_H
