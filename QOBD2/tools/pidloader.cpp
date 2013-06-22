#include "../tools/pidloader.h"
#include "../xml/pidxmlhandler.h"
#include <QDebug>
#include <QDir>
#include <QtXml/QXmlSimpleReader>

QHash<QString, OBDPID *> &PIDLoader::loadPIDs(QString directory)
{
    QHash<QString, OBDPID*>* h = new QHash<QString, OBDPID*>();   
    QDir xmlDirectory(directory);
    foreach(const QFileInfo &fileInfo, xmlDirectory.entryInfoList())
    {
        if(fileInfo.isFile() && fileInfo.fileName() != "." && fileInfo.fileName() != ".." && fileInfo.completeSuffix() == "xml")
        {
            parsePIDFile(fileInfo.absoluteFilePath(), h);
        }        
    }

    return *h;
}

void PIDLoader::parsePIDFile(QString filename, QHash<QString, OBDPID*>* h)
{
    QXmlSimpleReader xmlReader;
    QFile file(filename);
    QXmlInputSource source(&file);
    PIDXMLHandler handler(h);
    xmlReader.setContentHandler(&handler);
    xmlReader.setErrorHandler(&handler);
    xmlReader.parse(&source);
}
