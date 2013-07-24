#include "abstractobdhardware.h"

AbstractObdHardware::AbstractObdHardware(QObject *parent) : QObject(parent)
{
    deviceName = "OBD II device";
}

QString AbstractObdHardware::getDeviceName()
{
    return this->deviceName;
}
