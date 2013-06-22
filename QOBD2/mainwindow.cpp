#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/qserialportdiscovery.h"
#include "obd/qelm327serial.h"

#include <QDebug>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialPortSettings settings;
    QSerialPortDiscovery serialPortDiscovery;   
    QList<QSerialPortInfo>* obdDevicesList = serialPortDiscovery.getOBDSerialPortList(settings);

    settings.setSerialPortInfo(obdDevicesList->first());

    QThread *workingThread = new QThread();
    QELM327Serial *elm327 = new QELM327Serial(settings);
    elm327->moveToThread(workingThread);

    connect(workingThread, &QThread::started, elm327, &QELM327Serial::start);

    workingThread->start();

   // elm327->addPID("0100");
    //
   //elm327->addPID("010A");
    elm327->addPID("010C");
    elm327->addPID("010D");

    delete obdDevicesList;
}

MainWindow::~MainWindow()
{
    delete ui;
}
