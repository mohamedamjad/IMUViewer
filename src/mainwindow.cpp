#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->glSignalAcc = new PrincipalCapteurGL();


}

MainWindow::~MainWindow()
{
    delete ui;
}
