#ifndef QELM327SIMULATOR_H
#define QELM327SIMULATOR_H

#include "abstractobdhardware.h"
#include <QStringList>

class Elm327Simulator : public AbstractObdHardware
{
public:
    Elm327Simulator();

    bool connect();
    void disconnect();
    QStringList send(QString data);
};

#endif // QELM327SIMULATOR_H
