#include "obddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "pidloader.h"
#include <QDebug>
#include <QThread>

const int ObdDevice::PAUSE_DELAY_MS = 1000;

ObdDevice::ObdDevice(QObject *parent) :
    QObject(parent)
{   
    init();
}

ObdDevice::~ObdDevice()
{
    foreach(ObdPid* pid, allPIDsHash)
    {
        delete pid;
    }
}

void ObdDevice::start()
{
    if(!isRunning)
    {
        isRunning = true;
        pollingLoop();        
    }
}

void ObdDevice::close()
{
}

void ObdDevice::init()
{
    isPaused = false;
    isRunning = false;
    isVehicleConnected = false;
    name = "";

    allPIDsHash = PIDLoader::loadPIDs("./pids/");

    qRegisterMetaType<ObdPidData>("OBDPIDData");
}

void ObdDevice::stop()
{
    isRunning = false;    
}

void ObdDevice::pause()
{
    isPaused = !isPaused;
}

void ObdDevice::addPID(QString PIDName)
{
    if(allPIDsHash.contains(PIDName))
    {        
        PIDsToPollHash[PIDName] = allPIDsHash[PIDName];
    }
}

void ObdDevice::removePID(QString PIDName)
{
    PIDsToPollHash.remove(PIDName);
}

void ObdDevice::setPollInterval(QString PIDName, int interval)
{
    ObdPid* pid = allPIDsHash[PIDName];
    if(pid)
    {
        if(interval < requestTimeout) interval = requestTimeout;
        pid->setPollInterval(interval);
    }
}

QHash<QString, QString> ObdDevice::availablePIDs()
{
    QHash<QString, QString> availablePIDsHash;

    foreach(const ObdPid* PID, allPIDsHash)
    {
        availablePIDsHash[PID->getPid()] = PID->getName();
    }

    return availablePIDsHash;
}

void ObdDevice::pollingLoop()
{
    QTime vehicleConnectedTime;
    vehicleConnectedTime.start();
    while(isRunning)
    {        
        if(!isVehicleConnected)
        {
            emit log(tr("trying to connect ..."));
            isVehicleConnected = searchVehicle();
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else if(isPaused)
        {
            emit log(tr("paused ..."));
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else
        {            
            foreach(ObdPid *PID, PIDsToPollHash)
            {
                if(PID->getPollTime()->elapsed() >= PID->getPollInterval())
                {                    
                    ObdPidData data = requestPID(PID);
                    emit newData(data);
                    PID->getPollTime()->restart();
                }
            }
            QThread::msleep(waitingTime());
        }
    }
    close();
}

int ObdDevice::waitingTime()
{
    int min = 1000;
    foreach(ObdPid *PID, PIDsToPollHash)
    {
        if(PID->getPollInterval() < min)
            min = PID->getPollInterval();
    }   
    return min-requestTimeout;
}

QString ObdDevice::getName() const
{
    return name;
}

void ObdDevice::setName(const QString &value)
{
    name = value;
}
