#include "elm327simulator.h"

Elm327Simulator::Elm327Simulator() : AbstractObdHardware()
{    
}

bool Elm327Simulator::connect()
{
    return true;
}

void Elm327Simulator::disconnect()
{
}

QStringList Elm327Simulator::send(QString data)
{
}

QStringList Elm327Simulator::send(QString data, int timeout)
{
    return QStringList(data);
}
