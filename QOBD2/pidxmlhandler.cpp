#include "pidxmlhandler.h"
#include <QDebug>

const QString PIDXMLHandler::PID_TAG         = "pid";
const QString PIDXMLHandler::UNIT_TAG        = "unit";
const QString PIDXMLHandler::DESCRIPTION_TAG = "description";
const QString PIDXMLHandler::FORMULA_TAG     = "formula";
const QString PIDXMLHandler::ID_ATTRIBUTE    = "id";

PIDXMLHandler::PIDXMLHandler(QHash<QString, OBDPID*>* pidsHash)
{
    this->pidsHash = pidsHash;
}

bool PIDXMLHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if(qName == PID_TAG)
    {
        currentPid = atts.value(ID_ATTRIBUTE);
    }
    else if(qName == UNIT_TAG)
    {
        currentUnit = currentData;
    }
    else if(qName == DESCRIPTION_TAG)
    {
        currentDescription = currentData;
    }
    else if(qName == FORMULA_TAG)
    {
        currentFormula = currentData;
    }
    return true;
}

bool PIDXMLHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if(qName == PID_TAG)
    {                
        OBDPID *pid = new OBDPID(currentPid, currentDescription, currentUnit, OBDPID::DEFAULT_POLL_INTERVAL,currentFormula);
        (*pidsHash)[currentPid] = pid;
    }
    return true;
}

bool PIDXMLHandler::characters(const QString &ch)
{
    currentData = ch;
    return true;
}

bool PIDXMLHandler::fatalError(const QXmlParseException &exception)
{
    qWarning() << "Fatal error on line" << exception.lineNumber()
               << ", column" << exception.columnNumber() << ":"
               << exception.message();

    return false;
}
