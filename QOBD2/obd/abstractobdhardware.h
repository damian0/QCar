#ifndef ABSTRACTOBDHARDWARE_H
#define ABSTRACTOBDHARDWARE_H

#include <QObject>
#include <QStringList>

class AbstractObdHardware : public QObject
{
    Q_OBJECT
public:
    AbstractObdHardware(QObject *parent = 0);
    //virtual ~AbstractObdHardware();
    virtual bool connect() = 0;
    virtual void disconnect() = 0;    
    virtual QStringList send(QString data) = 0;

    /* Getters */
    virtual QString getDeviceName();

protected:
    bool connected;
    QString deviceName;

signals:
    void log(QString data);
    void error(QString error);

};

#endif // ABSTRACTOBDHARDWARE_H
