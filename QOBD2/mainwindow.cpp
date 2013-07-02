#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/qserialportdiscovery.h"
#include "obd/qelm327serial.h"
#include "obd/interpreter/arithmeticevaluator.h"

#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Serial port discovery */
    SerialPortSettings settings;
    QSerialPortDiscovery serialPortDiscovery;   
    QList<QSerialPortInfo>* obdDevicesList = serialPortDiscovery.getOBDSerialPortList(settings);

    settings.setSerialPortInfo(obdDevicesList->first());

    /* ELM 327 dedicated thread */
    QThread *workingThread = new QThread();
    QOBDDevice *elm327 = new QELM327Serial(settings);
    elm327->moveToThread(workingThread);    
    connect(workingThread, &QThread::started, elm327, &QELM327Serial::start);
    workingThread->start();    

    /* Adding some PID's to the polling loop */
    elm327->addPID("010C");  //Engine RPM
    elm327->addPID("010D");  //Vehicle speed

    /* Hashtable containing PID's names loaded from XML files */
    qDebug() << elm327->availablePIDs();

    /* Handle data from OBD device */
    connect(elm327, &QELM327Serial::newData, this, &MainWindow::handlePIDData);

    delete obdDevicesList;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handlePIDData(OBDPIDData data)
{
    qDebug() << data.getName() << "(" << data.getPid() << "):" << data.getValue() << data.getUnit();
}
