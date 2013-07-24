#include "obdresponsehandler.h"

ObdResponseHandler::ObdResponseHandler()
{
}

QStringList ObdResponseHandler::parseData(QString rawData)
{
    QStringList splittedData = rawData.split('\r');

    //trim all strings
    splittedData.replaceInStrings(QRegExp("^\\s*||\\s*$"), "");
    //removes all \r
    splittedData.replaceInStrings(QString("\r"), QString(""));
    //removes all >
    splittedData.replaceInStrings(QString(">"), QString(""));
    //removes all empty strings
    splittedData.removeAll(QString(""));

    return splittedData;
}
