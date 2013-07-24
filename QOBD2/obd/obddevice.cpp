#include "obddevice.h"
#include "obdpid.h"
#include "obdpiddata.h"
#include "pidloader.h"
#include <QDebug>
#include <QThread>

const int ObdDevice::PAUSE_DELAY_MS = 1000;

ObdDevice::ObdDevice(AbstractObdHardware *obdHardware, QObject *parent) :
    QObject(parent)
{   
    this->obdHardware = obdHardware;
    init();
}

ObdDevice::~ObdDevice()
{
    foreach(ObdPid* pid, allPIDsHash)
    {
        delete pid;
    }
    disconnectHardware();
    delete obdHardware;
}

bool ObdDevice::connectHardware()
{
    return obdHardware->connect();
}

void ObdDevice::disconnectHardware()
{
    obdHardware->disconnect();
}

void ObdDevice::start()
{
    if(!isRunning)
    {
        isRunning = true;
        pollingLoop();        
    }
}

void ObdDevice::init()
{   
    connect(obdHardware, &AbstractObdHardware::log, this, &ObdDevice::logHardware);
    connect(obdHardware, &AbstractObdHardware::error, this, &ObdDevice::errorHardware);

    isPaused = false;
    isRunning = false;
    isVehicleConnected = false;    

    allPIDsHash = PIDLoader::loadPIDs("./pids/");    

    qRegisterMetaType<ObdPidData>("ObdPidData");
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

    foreach(const ObdPid* pid, allPIDsHash)
    {
        availablePIDsHash[pid->getPid()] = pid->getName();
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
            emit log(tr("%1 : searching vehicle ...").arg(obdHardware->getDeviceName()));
            isVehicleConnected = searchVehicle();
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else if(isPaused)
        {
            emit log(tr("%1 : paused ...").arg(obdHardware->getDeviceName()));
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else
        {            
            foreach(ObdPid *pid, PIDsToPollHash)
            {
                if(pid->getPollTime()->elapsed() >= pid->getPollInterval())
                {                    
                    ObdPidData data = requestPid(pid);
                    emit newData(data);
                    pid->getPollTime()->restart();
                }
            }
            QThread::msleep(waitingTime());
        }
    }
    disconnectHardware();
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

ObdPidData ObdDevice::requestPid(ObdPid *pid)
{
    QString request = pid->getPid() + "\r";
    QStringList response = obdHardware->send(request);

    return ObdPidData(pid->getPid(), pid->getName(), pid->getDescription(), pid->computeValue(response), pid->getUnit());
}

bool ObdDevice::searchVehicle()
{
    QString request = "010C1\r";
    QStringList response = obdHardware->send(request);

    if(response.size() < 1)
        return false;
    else
        return response.first().contains("OK");
}

QString ObdDevice::getName() const
{
    if(obdHardware)
        return obdHardware->getDeviceName();
    else
        return QString();
}

void ObdDevice::logHardware(QString message)
{
    emit log(message);
}

void ObdDevice::errorHardware(QString err)
{
    emit error(err);
}
