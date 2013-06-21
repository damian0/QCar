#include "qobddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "pidloader.h"
#include <QDebug>
#include <QThread>

const int QOBDDevice::PAUSE_DELAY_MS = 1000;

QOBDDevice::QOBDDevice(QObject *parent) :
    QObject(parent)
{
    isPaused = false;
    isRunning = false;

    allPIDsHash = PIDLoader::loadPIDs("./pids/");    
}

void QOBDDevice::start()
{
    if(!isRunning)
    {
        isRunning = true;
        pollingLoop();        
    }
}

void QOBDDevice::stop()
{
    isRunning = false;
}

void QOBDDevice::pause()
{
    isPaused = !isPaused;
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
        if(isPaused)
        {
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else
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
            QThread::msleep(waitingTime());            
        }
    }
}

int QOBDDevice::waitingTime()
{
    int max = (PIDsToPollHash.size() <= 0)?1000:0;
    foreach(OBDPID *PID, PIDsToPollHash)
    {
        if(PID->getPollInterval() > max)
            max = PID->getPollInterval();
    }
    return max + 50;
}

OBDPIDData QOBDDevice::requestPID(OBDPID *PID)
{
}
