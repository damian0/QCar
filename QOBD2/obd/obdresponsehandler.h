#ifndef OBDRESPONSEHANDLER_H
#define OBDRESPONSEHANDLER_H

#include <QStringList>

class ObdResponseHandler
{
public:
    ObdResponseHandler();
    QStringList parseData(QString rawData);
};

#endif // OBDRESPONSEHANDLER_H
