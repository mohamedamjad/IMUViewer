#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     QTimer *timer = new QTimer(this);
    _pTdb = new TableauDeBord();

    // Affectation de la centrale du tableau de bord aux widgets capteurs
    this->findChild<AccCapteurGL*>("glCapteurAcc")->setCentrale(&_pTdb->_IMU);
    this->findChild<GyroCapteurGL*>("glCapteurGyro")->setCentrale(&_pTdb->_IMU);
    this->findChild<MagneCapteurGL*>("glCapteurMagne")->setCentrale(&_pTdb->_IMU);
    this->findChild<PrincipalCapteurGL*>("glPrincipal")->setCentrale(&_pTdb->_IMU);

    // Mise à jour de la centrale inertielle en suivant le timer
    QObject::connect(timer, SIGNAL(timeout()), _pTdb, SLOT(majCentrale()));
    // Mise à jour des widgets capteurs
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<AccCapteurGL*>("glCapteurAcc"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<GyroCapteurGL*>("glCapteurGyro"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<MagneCapteurGL*>("glCapteurMagne"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<PrincipalCapteurGL*>("glPrincipal"), SLOT(updateGL()));
    // timer à 100 ms
    timer->start(100);
}



MainWindow::~MainWindow()
{
    delete ui;
}



