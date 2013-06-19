#include "qobddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"

QOBDDevice::QOBDDevice(QObject *parent) :
    QObject(parent)
{
}

void QOBDDevice::start()
{
    if(!isRunning)
    {
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
}

void QOBDDevice::removePID(QString PIDName)
{
}

void QOBDDevice::setPollInterval(QString PIDName, int interval)
{
}

void QOBDDevice::pollingLoop()
{
    while(isRunning)
    {
        for(int i=0; i<PIDsToPollList.size(); i++)
        {
            requestPID(PIDsToPollList.at(i));
        }
    }
}

OBDPIDData QOBDDevice::requestPID(OBDPID *PID)
{
}
