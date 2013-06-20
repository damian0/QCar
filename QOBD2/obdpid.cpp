#include "obdpid.h"

const QString OBDPID::DEFAULT_PID         = "010C";
const QString OBDPID::DEFAULT_DESCRIPTION = "No description";
const int OBDPID::DEFAULT_POLL_INTERVAL   = 100;
const QString OBDPID::DEFAULT_FORMULA     = "";

OBDPID::OBDPID()
{
    setPid(DEFAULT_PID);
    setDescription(DEFAULT_DESCRIPTION);
    setPollInterval(DEFAULT_POLL_INTERVAL);
    setFormula(DEFAULT_FORMULA);
}

OBDPID::OBDPID(QString pid, QString description, QString unit, int pollInterval, QString formula)
{
    setPid(pid);
    setDescription(description);
    setUnit(unit);
    setPollInterval(pollInterval);
    setFormula(formula);
}

OBDPIDData OBDPID::computeValue(QString data)
{
}

void OBDPID::createFormulaInterpreter()
{
}

QString OBDPID::getPid() const
{
    return pid;
}

void OBDPID::setPid(const QString &value)
{
    pid = value;
}

QString OBDPID::getDescription() const
{
    return description;
}

void OBDPID::setDescription(const QString &value)
{
    description = value;
}

QTime OBDPID::getPollTime() const
{
    return pollTime;
}

void OBDPID::setPollTime(const QTime &value)
{
    pollTime = value;
}

int OBDPID::getPollInterval() const
{
    return pollInterval;
}

void OBDPID::setPollInterval(int value)
{
    pollInterval = value;
}

QString OBDPID::getFormula() const
{
    return formula;
}

void OBDPID::setFormula(const QString &value)
{
    formula = value;
}

QString OBDPID::getUnit() const
{
    return unit;
}

void OBDPID::setUnit(const QString &value)
{
    unit = value;
}
