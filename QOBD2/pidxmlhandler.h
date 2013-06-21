#ifndef PIDXMLHANDLER_H
#define PIDXMLHANDLER_H

#include "obdpid.h"
#include <QString>
#include <QtXml/QXmlDefaultHandler>

class PIDXMLHandler : public QXmlDefaultHandler
{
public:
    PIDXMLHandler(QHash<QString, OBDPID*>* pidsHash);
protected:
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);

    QHash<QString, OBDPID*>* pidsHash;
    QString currentData;
    QString currentPid;
    QString currentUnit;
    QString currentDescription;
    QString currentFormula;

    static const QString PID_TAG;
    static const QString UNIT_TAG;
    static const QString DESCRIPTION_TAG;
    static const QString FORMULA_TAG;
    static const QString ID_ATTRIBUTE;
};

#endif // PIDXMLHANDLER_H
