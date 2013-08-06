#include "obdpiddata.h"

ObdPidData::ObdPidData(QString pid, QString name, QString description, double value, QString unit)
{  
    setPID(pid);
    setName(name);
    setDescription(description);
    setValue(value);
    setUnit(unit);
}

QString ObdPidData::toString()
{
    return QString("PID Data : %1 %2 %3 %4").arg(pid).arg(name).arg(value).arg(unit);
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
