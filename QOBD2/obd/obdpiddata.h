#ifndef OBDPIDDATA_H
#define OBDPIDDATA_H

#include <QString>

class OBDPIDData
{
public:
    OBDPIDData();
    OBDPIDData(QString PID, QString name, QString description, double value, QString unit);

    /* Getters */
    QString getPID() const;
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

    QString PID;
    QString name;
    QString description;
    double value;
    QString unit;

    static const QString DEFAULT_PID;
    static const QString DEFAULT_NAME;
    static const QString DEFAULT_DESCRIPTION;
    static const double DEFAULT_VALUE;
    static const QString DEFAULT_UNIT;
};

#endif // OBDPIDDATA_H
