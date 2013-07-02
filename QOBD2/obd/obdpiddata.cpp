#include "obdpiddata.h"

const QString OBDPIDData::DEFAULT_PID         = "0100";
const QString OBDPIDData::DEFAULT_NAME        = "No name";
const QString OBDPIDData::DEFAULT_DESCRIPTION = "No description";
const double OBDPIDData::DEFAULT_VALUE        = 0.0;
const QString OBDPIDData::DEFAULT_UNIT        = "No unit";

OBDPIDData::OBDPIDData()
{
    setPID(DEFAULT_PID);
    setName(DEFAULT_NAME);
    setDescription(DEFAULT_DESCRIPTION);
    setValue(DEFAULT_VALUE);
    setUnit(DEFAULT_UNIT);
}

OBDPIDData::OBDPIDData(QString pid, QString name, QString description, double value, QString unit)
{  
    setPID(pid);
    setName(name);
    setDescription(description);
    setValue(value);
    setUnit(unit);
}

QString OBDPIDData::getPid() const
{
    return pid;
}

void OBDPIDData::setPID(const QString &value)
{
    this->pid = value;
}

QString OBDPIDData::getDescription() const
{
    return description;
}

void OBDPIDData::setDescription(const QString &value)
{
    this->description = value;
}

double OBDPIDData::getValue() const
{
    return value;
}

void OBDPIDData::setValue(double value)
{
    this->value = value;
}

QString OBDPIDData::getUnit() const
{
    return unit;
}

void OBDPIDData::setUnit(const QString &value)
{
    this->unit = value;
}

QString OBDPIDData::getName() const
{
    return name;
}

void OBDPIDData::setName(const QString &value)
{
    this->name = value;
}
