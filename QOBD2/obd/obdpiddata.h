#ifndef OBDPIDDATA_H
#define OBDPIDDATA_H

#include <QString>

class ObdPidData
{
public:    
    ObdPidData(QString pid = QString("0100"),
               QString name = QString("No name"),
               QString description = QString("No description"),
               double value = 0.0,
               QString unit = QString("No unit"));

    /* Getters */
    QString getPid() const;
    QString getName() const;
    QString getDescription() const;
    double getValue() const;
    QString getUnit() const;

    /* Setters */
    void setPID(const QString &value);
    void setName(const QString &value);
    void setDescription(const QString &value);
    void setValue(double value);
    void setUnit(const QString &value);        

private:

    QString pid;
    QString name;
    QString description;
    double value;
    QString unit;
};

#endif // OBDPIDDATA_H
