#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qserialportdiscovery.h"

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

    foreach(const QSerialPortInfo &info, *obdDevicesList)
    {
        qDebug() << info.portName();
    }

    delete obdDevicesList;
}

MainWindow::~MainWindow()
{
    delete ui;
}
