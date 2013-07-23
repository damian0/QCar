#ifndef QOBDDEVICE_H
#define QOBDDEVICE_H

#include "obdpid.h"
#include "obdpiddata.h"
#include <QObject>
#include <QList>
#include <QHash>

class ObdDevice : public QObject
{
    Q_OBJECT
public:
    explicit ObdDevice(QObject *parent = 0);
    virtual ~ObdDevice();

    void stop();
    void pause();
    void addPID(QString PIDName);
    void removePID(QString PIDName);
    void setPollInterval(QString PIDName, int interval);
    QHash<QString, QString> availablePIDs();

    /* Getters */
    QString getName() const;

    /* Setters */
    void setName(const QString &value);

public slots:
    void start();
    virtual void close();

protected:
    void init();
    void pollingLoop();
    int waitingTime();
    virtual ObdPidData requestPID(ObdPid* PID) = 0;
    virtual bool searchVehicle() = 0;

    bool isRunning;
    bool isPaused;
    bool isVehicleConnected;
    int requestTimeout;
    QString name;
    QHash<QString,ObdPid*> allPIDsHash;
    QHash<QString,ObdPid*> PIDsToPollHash;

    static const int PAUSE_DELAY_MS;
    
signals:
    void newData(ObdPidData PID);
    void log(const QString);
    void error(QString);
};

#endif // QOBDDEVICE_H
