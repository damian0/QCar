#include "mainwindow.h"
#include "obd/elm327serial.h"
#include "tools/serialportsettings.h"
#include "tools/serialportdiscovery.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
