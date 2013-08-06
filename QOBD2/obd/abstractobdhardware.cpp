#include "abstractobdhardware.h"

AbstractObdHardware::AbstractObdHardware(QObject *parent) : QObject(parent)
{
    deviceName = "OBD II Hardware";
}

QString AbstractObdHardware::getDeviceName() const
{
    return this->deviceName;
}

bool AbstractObdHardware::isConnected() const
{
    return connected;
}
