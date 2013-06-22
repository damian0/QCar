#ifndef OBDPID_H
#define OBDPID_H

#include "obdpiddata.h"
#include <QString>
#include <QStringList>
#include <QTime>

class OBDPID
{
public:
    OBDPID();
    OBDPID(QString pid, QString name, QString description, QString unit, int pollInterval, QString formula, int nbLines = 0);
    virtual ~OBDPID();

    double computeValue(QStringList data);

    /* Getters */
    QString getPid() const;
    QString getName() const;
    QString getDescription() const;
    QString getUnit() const;
    QTime *getPollTime() const;
    int getPollInterval() const;
    QString getFormula() const;
    int getNbLines() const;

    /* Setters */
    void setPid(const QString &value);
    void setName(const QString &value);
    void setDescription(const QString &value);
    void setUnit(const QString &value);
    void setPollTime(QTime *value);
    void setPollInterval(int value);
    void setFormula(const QString &value);
    void setNbLines(int value);

    static const QString DEFAULT_PID;
    static const QString DEFAULT_NAME;
    static const QString DEFAULT_DESCRIPTION;
    static const int DEFAULT_POLL_INTERVAL;
    static const QString DEFAULT_FORMULA;        
    static const int DEFAULT_NB_LINES;        

private:
    void createFormulaInterpreter();

    QString pid;
    QString name;
    QString description;
    QString unit;
    QTime *pollTime;
    int pollInterval;
    QString formula;
    int nbLines;
};

#endif // OBDPID_H
