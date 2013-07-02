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
    init();
}

QOBDDevice::~QOBDDevice()
{
    foreach(OBDPID* pid, allPIDsHash)
    {
        delete pid;
    }
}

void QOBDDevice::start()
{
    if(!isRunning)
    {
        isRunning = true;
        pollingLoop();        
    }
}

void QOBDDevice::init()
{
    isPaused = false;
    isRunning = false;
    isVehicleConnected = false;
    name = "";

    allPIDsHash = PIDLoader::loadPIDs("./pids/");

    qRegisterMetaType<OBDPIDData>("OBDPIDData");
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
        if(interval < requestTimeout) interval = requestTimeout;
        pid->setPollInterval(interval);
    }
}

QHash<QString, QString> QOBDDevice::availablePIDs()
{
    QHash<QString, QString> availablePIDsHash;

    foreach(const OBDPID* PID, allPIDsHash)
    {
        availablePIDsHash[PID->getPid()] = PID->getName();
    }

    return availablePIDsHash;
}

void QOBDDevice::pollingLoop()
{
    QTime vehicleConnectedTime;
    vehicleConnectedTime.start();
    while(isRunning)
    {        
        if(!isVehicleConnected)
        {
            qDebug() << "trying to connect ...";
            isVehicleConnected = searchVehicle();
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else if(isPaused)
        {
            qDebug() << "paused ...";
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else
        {            
            foreach(OBDPID *PID, PIDsToPollHash)
            {
                if(PID->getPollTime()->elapsed() >= PID->getPollInterval())
                {                    
                    OBDPIDData data = requestPID(PID);
                    emit newData(data);
                    PID->getPollTime()->restart();
                }
            }
            QThread::msleep(waitingTime());
        }
    }
}

int QOBDDevice::waitingTime()
{
    int min = 1000;
    foreach(OBDPID *PID, PIDsToPollHash)
    {
        if(PID->getPollInterval() < min)
            min = PID->getPollInterval();
    }   
    return min-requestTimeout;
}

QString QOBDDevice::getName() const
{
    return name;
}

void QOBDDevice::setName(const QString &value)
{
    name = value;
}
