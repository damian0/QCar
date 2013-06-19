#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qserialportdiscovery.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    SerialPortSettings settings;
    qDebug() << QSerialPortDiscovery::getOBDSerialPortList(settings)->first().portName();
}

MainWindow::~MainWindow()
{
    delete ui;
}
