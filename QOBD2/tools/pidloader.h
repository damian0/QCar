#ifndef PIDLOADER_H
#define PIDLOADER_H

#include "../obd/obdpid.h"
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include <QString>
#include <QHash>

class PIDLoader
{
public:
    static QHash<QString, ObdPid *> &loadPIDs(QString directory);
private:
    static void parsePIDFile(QString filename, QHash<QString, ObdPid *> *h);
    static bool isPIDFileValid(QString filename);
};

#endif // PIDLOADER_H
