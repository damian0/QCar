#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/serialportdiscovery.h"
#include "obd/elm327serial.h"
#include "obd/interpreter/arithmeticevaluator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

    /*
     *Usage example
     *

    // Serial port discovery
    SerialPortSettings settings;
    QSerialPortDiscovery serialPortDiscovery;   
    QList<QSerialPortInfo>* obdDevicesList = serialPortDiscovery.getOBDSerialPortList(settings);    

    settings.setSerialPortInfo(obdDevicesList->first());

    // ELM 327 dedicated thread
    QThread *workingThread = new QThread();
    QOBDDevice *elm327 = new QELM327Serial(settings);
    elm327->moveToThread(workingThread);    
    connect(workingThread, &QThread::started, elm327, &QELM327Serial::start);
    workingThread->start();    

    // Adding some PID's to the polling loop
    elm327->addPID("010C");  //Engine RPM
    elm327->addPID("010D");  //Vehicle speed

    // Hashtable containing PID's names loaded from XML files
    qDebug() << elm327->availablePIDs();

    // Handle data from OBD device
    connect(elm327, &QELM327Serial::newData, this, &MainWindow::handlePIDData);

    delete obdDevicesList;
    */

}

MainWindow::~MainWindow()
{
    btnStopPressed();
    delete currentDevice;
    delete obdThread;
    delete ui;
}

void MainWindow::init()
{
    updateSerialPortList();
    currentDevice = 0;    
    obdThread = new QThread(this);    
}

void MainWindow::updateSerialPortList()
{
    // Serial port discovery
    SerialPortSettings settings;
    SerialPortDiscovery serialPortDiscovery;
    QList<QSerialPortInfo>* obdDevicesList = serialPortDiscovery.getOBDSerialPortList(settings);

    ui->cbOBDDevices->clear();
    portInfoHash.clear();

    for(int i=0; i<obdDevicesList->size(); i++)
    {
        QString portLocation = obdDevicesList->at(i).systemLocation();
        ui->cbOBDDevices->addItem(portLocation);
        portInfoHash[portLocation] = obdDevicesList->at(i);
    }

    delete obdDevicesList;
}

void MainWindow::handlePIDData(ObdPidData data)
{    
    qDebug() << data.getName() << "(" << data.getPid() << "):" << data.getValue() << data.getUnit();
}

void MainWindow::btnStartPressed()
{    
    if(currentDevice)    
        this->btnStopPressed();

    QString portLocation = ui->cbOBDDevices->currentText();

    if(portInfoHash.contains(portLocation))
    {        
        SerialPortSettings settings(portInfoHash[portLocation]);
        currentDevice = new Elm327Serial(settings);
        currentDevice->moveToThread(obdThread);
        connect(obdThread, &QThread::started, currentDevice, &Elm327Serial::start);
        obdThread->start();

        connect(currentDevice, &Elm327Serial::log, ui->teLog, &QTextEdit::append);
        connect(currentDevice, &Elm327Serial::error, ui->teLog, &QTextEdit::append);
        connect(currentDevice, &Elm327Serial::log, this, &MainWindow::test);

        switchStartStopState();
    }
}

void MainWindow::btnPausePressed()
{
    if(currentDevice)
    {
        currentDevice->pause();
    }
}

void MainWindow::btnStopPressed()
{
    if(currentDevice)
    {
        currentDevice->stop();        
        currentDevice->deleteLater();
        currentDevice = 0;

        obdThread->quit();
        obdThread->wait();

        switchStartStopState();
    }
}

void MainWindow::test(const QString txt)
{
    qDebug() << txt;
}

void MainWindow::switchStartStopState()
{
    ui->btnStart->setEnabled(!ui->btnStart->isEnabled());
    ui->btnStop->setEnabled(!ui->btnStop->isEnabled());
    ui->btnPause->setEnabled(!ui->btnPause->isEnabled());
    ui->cbOBDDevices->setEnabled(!ui->cbOBDDevices->isEnabled());
}
