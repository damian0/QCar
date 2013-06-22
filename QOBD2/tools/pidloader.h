#ifndef PIDLOADER_H
#define PIDLOADER_H

#include "../obd/obdpid.h"
#include <QString>
#include <QHash>

class PIDLoader
{
public:
    static QHash<QString, OBDPID *> &loadPIDs(QString directory);
private:
    static void parsePIDFile(QString filename, QHash<QString, OBDPID *> *h);
};

#endif // PIDLOADER_H
