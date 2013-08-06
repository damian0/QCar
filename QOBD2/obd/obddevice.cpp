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
    if(!running && obdHardware->isConnected())
    {
        running = true;
        pollingLoop();        
    }
}

void ObdDevice::init()
{   
    connect(obdHardware, &AbstractObdHardware::log, this, &ObdDevice::logHardware);
    connect(obdHardware, &AbstractObdHardware::error, this, &ObdDevice::errorHardware);

    paused = false;
    running = false;
    vehicleConnected = false;
    requestTimeout = ObdPid::DEFAULT_POLL_INTERVAL;
    pollingLoopFrequency = 0;

    allPIDsHash = PIDLoader::loadPIDs("./pids/");    

    qRegisterMetaType<ObdPidData>("ObdPidData");
}

void ObdDevice::logF(QString message)
{
    emit log(tr("%1 : %2").arg(obdHardware->getDeviceName()).arg(message));
}

void ObdDevice::stop()
{
    running = false;
}

void ObdDevice::pause()
{
    paused = true;
}

void ObdDevice::resume()
{
    paused = false;
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
    logF(tr("Polling loop started"));

    QTime loopPeriod;

    while(running)
    {        
        loopPeriod.restart();
        if(!vehicleConnected)
        {
            logF(tr("searching vehicle ..."));
            vehicleConnected = searchVehicle();
            QThread::msleep(PAUSE_DELAY_MS);
        }
        else if(paused)
        {
            logF(tr("paused ..."));
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
                    logF(data.toString());
                    //logF(QString("%1 %2").arg(pid->getName()).arg(pid->getPollTime()->elapsed()));
                    pid->getPollTime()->restart();
                }
            }
            QThread::msleep(waitingTime());
        }
        pollingLoopFrequency = 1000 / loopPeriod.elapsed();
    }
    logF(tr("Polling loop finished"));
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
    QString nbLines = (pid->getNbLines()  != 0) ? QString::number(pid->getNbLines()) : ""; //Adds the number of lines to the request, in order to speed up requests
    QString request = QString("%1%2\r").arg(pid->getPid()).arg(nbLines);
    QStringList response = obdHardware->send(request, requestTimeout);

    vehicleConnected = responseHandler.isVehicleConnected(response);

    return ObdPidData(pid->getPid(), pid->getName(), pid->getDescription(), pid->computeValue(response), pid->getUnit());
}

bool ObdDevice::searchVehicle()
{
    QString request = "01001\r";
    QStringList response = obdHardware->send(request, 4000);

    return responseHandler.isVehicleConnected(response);
}

QString ObdDevice::getName() const
{
    if(obdHardware)
        return obdHardware->getDeviceName();
    else
        return QString();
}

bool ObdDevice::isPaused() const
{
    return paused;
}

bool ObdDevice::isRunning() const
{
    return running;
}

bool ObdDevice::isVehicleConnected() const
{
    return vehicleConnected;
}

void ObdDevice::logHardware(QString message)
{        
    emit log(message);
}

void ObdDevice::errorHardware(QString err)
{
    emit error(err);
}
