#ifndef OBDPID_H
#define OBDPID_H

#include "obdpiddata.h"
#include <QString>
#include <QTime>

class OBDPID
{
public:
    OBDPID();
    OBDPID(QString pid, QString description, QString unit, int pollInterval, QString formula);
    OBDPIDData computeValue(QString data);

    /* Getters */
    QString getPid() const;
    QString getDescription() const;
    QString getUnit() const;
    QTime getPollTime() const;
    int getPollInterval() const;
    QString getFormula() const;

    /* Setters */
    void setPid(const QString &value);
    void setDescription(const QString &value);
    void setUnit(const QString &value);
    void setPollTime(const QTime &value);
    void setPollInterval(int value);
    void setFormula(const QString &value);

    static const QString DEFAULT_PID;
    static const QString DEFAULT_DESCRIPTION;
    static const int DEFAULT_POLL_INTERVAL;
    static const QString DEFAULT_FORMULA;

private:
    void createFormulaInterpreter();

    QString pid;
    QString description;
    QString unit;
    QTime pollTime;
    int pollInterval;
    QString formula;   
};

#endif // OBDPID_H
