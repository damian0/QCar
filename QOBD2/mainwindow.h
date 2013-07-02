#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "obd/obdpiddata.h"

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
    void handlePIDData(OBDPIDData data);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
