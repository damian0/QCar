#include "obddeviceproxy.h"

ObdDeviceProxy::ObdDeviceProxy(QObject *parent) :
    QObject(parent)
{
}


void ObdDeviceProxy::logSlot(const QString message)
{
    emit log(message);
}

void ObdDeviceProxy::errorSlot(const QString err)
{
    emit error(err);
}

void ObdDeviceProxy::newDataSlot(const ObdPidData &data)
{
    emit newData(data);
}
