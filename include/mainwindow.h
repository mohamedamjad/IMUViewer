#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "acccapteurgl.h"
#include "gyrocapteurgl.h"
#include "principalcapteurgl.h"
#include "magnecapteurgl.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AccCapteurGL *_accGL;
    GyroCapteurGL *_gyroGL;
    MagneCapteurGL *_magneGL;
};

#endif // MAINWINDOW_H
