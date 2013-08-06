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

    void addPID(QString PIDName);
    void removePID(QString PIDName);
    void setPollInterval(QString PIDName, int interval);
    QHash<QString, QString> availablePIDs();

    /* Getters */
    QString getName() const;
    bool isPaused() const;
    bool isRunning() const;
    bool isVehicleConnected() const;

public slots:
    void start();
    void stop();
    void pause();
    void resume();
    bool connectHardware();
    void disconnectHardware();
    void logHardware(QString message);
    void errorHardware(QString err);

private:
    void init();
    void logF(QString message);
    void pollingLoop();
    int waitingTime();
    bool searchVehicle();
    ObdPidData requestPid(ObdPid* pid);

    bool running;
    bool paused;
    bool vehicleConnected;
    int requestTimeout;
    int pollingLoopFrequency;
    ObdResponseHandler responseHandler;
    AbstractObdHardware *obdHardware;
    QHash<QString,ObdPid*> allPIDsHash;
    QHash<QString,ObdPid*> PIDsToPollHash;

    static const int PAUSE_DELAY_MS;
    
signals:
    Q_SIGNAL void newData(const ObdPidData &pid);
    Q_SIGNAL void log(const QString message);
    Q_SIGNAL void error(QString err);
};

#endif // QOBDDEVICE_H
