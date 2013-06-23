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
    static QHash<QString, OBDPID *> &loadPIDs(QString directory);
private:
    static void parsePIDFile(QString filename, QHash<QString, OBDPID *> *h);
    static bool isPIDFileValid(QString filename, QString schemaFilename);
};

#endif // PIDLOADER_H
