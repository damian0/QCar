#ifndef OBDPID_H
#define OBDPID_H

#include "obdpiddata.h"
#include "interpreter/arithmeticevaluator.h"
#include <QString>
#include <QStringList>
#include <QTime>

class ObdPid
{
public:
    ObdPid();
    ObdPid(QString pid = QString("0100"),
           QString name = QString("No name"),
           QString description = QString("No description"),
           QString unit = QString("No unit"),
           int pollInterval = 100,
           QString formula = QString(),
           int nbLines = 0);
    virtual ~ObdPid();

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
    ArithmeticEvaluator* evaluator;
};

#endif // OBDPID_H
