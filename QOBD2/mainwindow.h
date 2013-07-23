#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QThread>
#include "obd/obdpiddata.h"
#include "obd/elm327serial.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handlePIDData(ObdPidData data);
    void updateSerialPortList();
    void btnStartPressed();
    void btnPausePressed();
    void btnStopPressed();
    void test(const QString txt);
    
private:
    void init();    
    void switchStartStopState();

    QThread *obdThread;
    QHash<QString, QSerialPortInfo> portInfoHash;
    ObdDevice *currentDevice;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
