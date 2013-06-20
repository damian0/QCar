#include "obdpiddata.h"

const QString OBDPIDData::DEFAULT_PID         = "010C";
const QString OBDPIDData::DEFAULT_DESCRIPTION = "No description";
const double OBDPIDData::DEFAULT_VALUE        = 0.0;
const QString OBDPIDData::DEFAULT_UNIT        = "No unit";

OBDPIDData::OBDPIDData()
{
    setPID(DEFAULT_PID);
    setDescription(DEFAULT_DESCRIPTION);
    setValue(DEFAULT_VALUE);
    setUnit(DEFAULT_UNIT);
}

OBDPIDData::OBDPIDData(QString PID, QString description, double value, QString unit)
{
    setPID(PID);
    setDescription(description);
    setValue(value);
    setUnit(unit);
}

QString OBDPIDData::getPID() const
{
    return PID;
}

void OBDPIDData::setPID(const QString &value)
{
    PID = value;
}

QString OBDPIDData::getDescription() const
{
    return description;
}

void OBDPIDData::setDescription(const QString &value)
{
    description = value;
}

double OBDPIDData::getValue() const
{
    return value;
}

void OBDPIDData::setValue(double value)
{
    value = value;
}

QString OBDPIDData::getUnit() const
{
    return unit;
}

void OBDPIDData::setUnit(const QString &value)
{
    unit = value;
}
