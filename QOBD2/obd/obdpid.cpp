#include "obdpid.h"
#include <QDebug>

const QString OBDPID::DEFAULT_PID         = "0100";
const QString OBDPID::DEFAULT_NAME        = "No name";
const QString OBDPID::DEFAULT_DESCRIPTION = "No description";
const int OBDPID::DEFAULT_POLL_INTERVAL   = 100;
const QString OBDPID::DEFAULT_FORMULA     = "";
const int OBDPID::DEFAULT_NB_LINES        = 0;

OBDPID::OBDPID()
{
    setPid(DEFAULT_PID);
    setName(DEFAULT_NAME);
    setDescription(DEFAULT_DESCRIPTION);
    setPollInterval(DEFAULT_POLL_INTERVAL);
    setFormula(DEFAULT_FORMULA);
    setNbLines(DEFAULT_NB_LINES);
    pollTime = new QTime();
    pollTime->start();

    createFormulaInterpreter();
}

OBDPID::OBDPID(QString pid, QString name, QString description, QString unit, int pollInterval, QString formula, int nbLines)
{
    setPid(pid);
    setName(name);
    setDescription(description);
    setUnit(unit);
    setPollInterval(pollInterval);
    setFormula(formula);
    setNbLines(nbLines);    
    pollTime = new QTime();
    pollTime->start();

    createFormulaInterpreter();
}

OBDPID::~OBDPID()
{
    delete pollTime;
    delete evaluator;
}

double OBDPID::computeValue(QStringList data)
{
    QString lines = data.join("");
    lines.replace(QString(" "), QString(""));
    if(lines.at(0) == '4' && lines.at(1) == '1')
    {
        lines = lines.mid(4);

        char c;
        QString tmp;
        double value = 1;

        for(int i=0, j=0; i<lines.size(); i+=2, j++)
        {
            tmp.clear();
            tmp += lines.at(i);
            tmp += lines.at(i+1);
            c = j + 65;
            value = (double)(tmp.toInt(0,16));
            evaluator->setVariable(QString(c), value);
        }
        return evaluator->evaluate();
    }
    return -1.0;
}

void OBDPID::createFormulaInterpreter()
{
    evaluator = new ArithmeticEvaluator(formula);
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

QTime *OBDPID::getPollTime() const
{
    return pollTime;
}

void OBDPID::setPollTime(QTime *value)
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

int OBDPID::getNbLines() const
{
    return nbLines;
}

void OBDPID::setNbLines(int value)
{
    nbLines = value;
}

QString OBDPID::getName() const
{
    return name;
}

void OBDPID::setName(const QString &value)
{
    name = value;
}
