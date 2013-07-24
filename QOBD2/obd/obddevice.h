#ifndef QOBDDEVICE_H
#define QOBDDEVICE_H

#include "obdpid.h"
#include "obdpiddata.h"
#include "abstractobdhardware.h"
#include "obdresponsehandler.h"
#include <QObject>
#include <QList>
#include <QHash>

class ObdDevice : public QObject
{
    Q_OBJECT
public:
    explicit ObdDevice(AbstractObdHardware *obdHardware, QObject *parent = 0);
    virtual ~ObdDevice();

    bool connectHardware();
    void disconnectHardware();
    void start();
    void stop();
    void pause();    
    void addPID(QString PIDName);
    void removePID(QString PIDName);
    void setPollInterval(QString PIDName, int interval);
    QHash<QString, QString> availablePIDs();

    /* Getters */
    QString getName() const;

public slots:
    void logHardware(QString message);
    void errorHardware(QString err);

private:
    void init();
    void pollingLoop();
    int waitingTime();
    bool searchVehicle();
    ObdPidData requestPid(ObdPid* pid);

    bool isRunning;
    bool isPaused;
    bool isVehicleConnected;
    int requestTimeout;
    ObdResponseHandler responseHandler;
    AbstractObdHardware *obdHardware;
    QHash<QString,ObdPid*> allPIDsHash;
    QHash<QString,ObdPid*> PIDsToPollHash;

    static const int PAUSE_DELAY_MS;
    
signals:
    void newData(ObdPidData PID);
    void log(const QString);
    void error(QString);
};

#endif // QOBDDEVICE_H
