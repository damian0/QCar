#include "qobddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include <QThread>

QOBDDevice::QOBDDevice(QObject *parent) :
    QObject(parent)
{
}

void QOBDDevice::start()
{
    if(!isRunning)
    {
        pollingLoop();
    }
}

void QOBDDevice::stop()
{
    isRunning = false;
}

void QOBDDevice::pause()
{
}

void QOBDDevice::addPID(QString PIDName)
{
    if(allPIDsHash.contains(PIDName))
    {
        PIDsToPollHash[PIDName] = allPIDsHash[PIDName];
    }
}

void QOBDDevice::removePID(QString PIDName)
{
    PIDsToPollHash.remove(PIDName);
}

void QOBDDevice::setPollInterval(QString PIDName, int interval)
{
    OBDPID* pid = allPIDsHash[PIDName];
    if(pid)
    {
        pid->setPollInterval(interval);
    }
}

void QOBDDevice::pollingLoop()
{
    while(isRunning)
    {
        foreach(OBDPID *PID, PIDsToPollHash)
        {
            if(PID->getPollTime().elapsed() >= PID->getPollInterval())
            {
            OBDPIDData data = requestPID(PID);
            emit newData(data);
            PID->getPollTime().restart();
            }
        }
        this->thread()->wait(waitingTime());
    }
}

int QOBDDevice::waitingTime()
{
    int max = 1000;
    foreach(OBDPID *PID, PIDsToPollHash)
    {
        if(PID->getPollInterval() > max)
            max = PID->getPollInterval();
    }
    return max;
}

OBDPIDData QOBDDevice::requestPID(OBDPID *PID)
{
}
