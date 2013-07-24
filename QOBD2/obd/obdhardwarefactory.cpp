#include "obdhardwarefactory.h"
#include "elm327serial.h"
#include "elm327simulator.h"

AbstractObdHardware *ObdHardwareFactory::createElm327Simulator()
{
    return new Elm327Simulator();
}

AbstractObdHardware *ObdHardwareFactory::createElm327Serial(SerialPortSettings settings)
{
    return new Elm327Serial(settings);
}
