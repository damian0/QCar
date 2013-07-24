#ifndef OBDHARDWAREFACTORY_H
#define OBDHARDWAREFACTORY_H

#include "abstractobdhardware.h"
#include "../tools/serialportsettings.h"

class ObdHardwareFactory
{
public:    
    static AbstractObdHardware *createElm327Simulator();
    static AbstractObdHardware *createElm327Serial(SerialPortSettings settings);
};

#endif // OBDHARDWAREFACTORY_H
