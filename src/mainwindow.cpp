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
    this->findChild<gyrograph*>("glSignalAcc")->setCentrale (&_pTdb->_IMU);

    _pcGL = this->findChild<PrincipalCapteurGL*>("glPrincipal");
    _pcGL->setCentrale(&_pTdb->_IMU);
    // + fenetre d'évolution de la centrale
    _pcGL->setFenetreEvolutionCentrale(_pTdb->getCoinInferieur(),_pTdb->getCoinSuperieur());

    //// DEBUT MODIFICATION A INTEGRER
    // Affichage en décimal
    ui->lcdNumber->setDigitCount(8);
    //// FIN MODIFICATION A INTEGRER

    // Mise à jour de la centrale inertielle en suivant le timer
    QObject::connect(timer, SIGNAL(timeout()), _pTdb, SLOT(majCentrale()));
    // Mise à jour des widgets capteurs
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<AccCapteurGL*>("glCapteurAcc"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<GyroCapteurGL*>("glCapteurGyro"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<MagneCapteurGL*>("glCapteurMagne"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<PrincipalCapteurGL*>("glPrincipal"), SLOT(updateGL()));
    QObject::connect(timer, SIGNAL(timeout()), this->findChild<gyrograph*>("glSignalAcc"), SLOT(updateGL()));

    //// DEBUT MODIFICATION A INTEGRER
    // Mise à jour de l'écran LCD
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(majLCD()));
    //// FIN MODIFICATION A INTEGRER

    // timer calé sur la fréquence d'échantillonage des signaux
    timer->start(1000/freqEch);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // On renvoit la gestion du clavier à la fenetre d'affichage principal
    _pcGL->keyPressEvent(event);
}

//// DEBUT MODIFICATION A INTEGRER
void MainWindow::majLCD()
{
    std::ostringstream s;
    s<<(double)_pTdb->getICourant()/(double)freqEch;
    std::string sttime=s.str();
    ui->lcdNumber->display(QString(sttime.c_str()));

}
//// FIN MODIFICATION A INTEGRER
