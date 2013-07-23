#include "obdpiddata.h"

const QString ObdPidData::DEFAULT_PID         = "0100";
const QString ObdPidData::DEFAULT_NAME        = "No name";
const QString ObdPidData::DEFAULT_DESCRIPTION = "No description";
const double ObdPidData::DEFAULT_VALUE        = 0.0;
const QString ObdPidData::DEFAULT_UNIT        = "No unit";

ObdPidData::ObdPidData()
{
    setPID(DEFAULT_PID);
    setName(DEFAULT_NAME);
    setDescription(DEFAULT_DESCRIPTION);
    setValue(DEFAULT_VALUE);
    setUnit(DEFAULT_UNIT);
}

ObdPidData::ObdPidData(QString pid, QString name, QString description, double value, QString unit)
{  
    setPID(pid);
    setName(name);
    setDescription(description);
    setValue(value);
    setUnit(unit);
}

QString ObdPidData::getPid() const
{
    return pid;
}

void ObdPidData::setPID(const QString &value)
{
    this->pid = value;
}

QString ObdPidData::getDescription() const
{
    return description;
}

void ObdPidData::setDescription(const QString &value)
{
    this->description = value;
}

double ObdPidData::getValue() const
{
    return value;
}

void ObdPidData::setValue(double value)
{
    this->value = value;
}

QString ObdPidData::getUnit() const
{
    return unit;
}

void ObdPidData::setUnit(const QString &value)
{
    this->unit = value;
}

QString ObdPidData::getName() const
{
    return name;
}

void ObdPidData::setName(const QString &value)
{
    this->name = value;
}
