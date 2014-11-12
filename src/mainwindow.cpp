#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     _pTimer = new QTimer(this);
    _pTdb = new TableauDeBord();

    int max=_pTdb->getnbEch();

    // Affectation de la centrale du tableau de bord aux widgets capteurs
    this->findChild<AccCapteurGL*>("glCapteurAcc")->setCentrale(&_pTdb->_IMU);
    this->findChild<GyroCapteurGL*>("glCapteurGyro")->setCentrale(&_pTdb->_IMU);
    this->findChild<MagneCapteurGL*>("glCapteurMagne")->setCentrale(&_pTdb->_IMU);

    _pcGL = this->findChild<PrincipalCapteurGL*>("glPrincipal");
    _pcGL->setCentrale(&_pTdb->_IMU);


    // Affectation de la centrale et du tableau de bord aux widgets signaux
    this->findChild<gyrograph*>("glSignalAcc")->setCentrale (&_pTdb->_IMU);
    this->findChild<gyrograph*>("glSignalAcc")->setTableauDeBord (_pTdb);
    this->findChild<gyrograph*>("glSignalAcc")->setsignalIndex (0);

    this->findChild<gyrograph*>("glSignalGyro")->setCentrale (&_pTdb->_IMU);
    this->findChild<gyrograph*>("glSignalGyro")->setTableauDeBord (_pTdb);
    this->findChild<gyrograph*>("glSignalGyro")->setsignalIndex (0);

    this->findChild<gyrograph*>("glSignalMagne")->setCentrale (&_pTdb->_IMU);
    this->findChild<gyrograph*>("glSignalMagne")->setTableauDeBord (_pTdb);
    this->findChild<gyrograph*>("glSignalMagne")->setsignalIndex (0);

    // Affectation des Comboboxs aux widgets appropriés
    // Première Combobox (premier espace d'affichage)
    this->findChild<Combobox*>("comboBox_1")->addItem ("Acc. X (m/s2)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Acc. Y (m/s2)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Acc. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Gyro. X (rad/s)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Gyro. Y (rad/s)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Gyro. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Magn. X (uT)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Magn. Y (uT)");
    this->findChild<Combobox*>("comboBox_1")->addItem ("Magn. Z (uT)");
    this->findChild<Combobox*>("comboBox_1")->setgyrograph(this->findChild<gyrograph*>("glSignalAcc"));

    // Première Combobox (deuxième espace d'affichage)
    this->findChild<Combobox*>("comboBox_2")->addItem ("Acc. X (m/s2)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Acc. Y (m/s2)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Acc. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Gyro. X (rad/s)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Gyro. Y (rad/s)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Gyro. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Magn. X (uT)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Magn. Y (uT)");
    this->findChild<Combobox*>("comboBox_2")->addItem ("Magn. Z (uT)");
    this->findChild<Combobox*>("comboBox_2")->setgyrograph(this->findChild<gyrograph*>("glSignalGyro"));


    // Troisième Combobox (troisième espace d'affichage)
    this->findChild<Combobox*>("comboBox_3")->addItem ("Acc. X (m/s2)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Acc. Y (m/s2)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Acc. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Gyro. X (rad/s)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Gyro. Y (rad/s)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Gyro. Z (m/s2)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Magn. X (uT)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Magn. Y (uT)");
    this->findChild<Combobox*>("comboBox_3")->addItem ("Magn. Z (uT)");
    this->findChild<Combobox*>("comboBox_3")->setgyrograph(this->findChild<gyrograph*>("glSignalGyro"));


//    this->findChild<Combobox*>("comboBox_2")->setItemText (1,"Vit. X (m/s2)");
//    this->findChild<Combobox*>("comboBox_2")->setItemText (2,"Vit. Y (m/s2)");
//    this->findChild<Combobox*>("comboBox_2")->setItemText (3,"Vit. Z (m/s2)");
//
//    this->findChild<Combobox*>("comboBox_2")->setItemText (1,"Vit. X (m/s2)");
//    this->findChild<Combobox*>("comboBox_2")->setItemText (2,"Vit. Y (m/s2)");
//    this->findChild<Combobox*>("comboBox_2")->setItemText (3,"Vit. Z (m/s2)");

    // + fenetre d'évolution de la centrale
    _pcGL->setFenetreEvolutionCentrale(_pTdb->getCoinInferieur(),_pTdb->getCoinSuperieur());

    ui->lcdNumber->setDigitCount(8);
    ui->horizontalSlider->setRange(0,max*1000);

    // Mise à jour de la centrale inertielle en suivant le _pTimer
    QObject::connect(_pTimer, SIGNAL(timeout()), _pTdb, SLOT(majCentrale()));
    // Mise à jour des widgets gl
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<AccCapteurGL*>("glCapteurAcc"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<GyroCapteurGL*>("glCapteurGyro"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<MagneCapteurGL*>("glCapteurMagne"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<PrincipalCapteurGL*>("glPrincipal"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<gyrograph*>("glSignalAcc"), SLOT(updateGL()));
    QObject::connect(this->findChild<Combobox*>("comboBox_1"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalAcc"), SLOT(setsignalIndex(int)));
    QObject::connect(this->findChild<Combobox*>("comboBox_2"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalGyro"), SLOT(setsignalIndex(int)));
    QObject::connect(this->findChild<Combobox*>("comboBox_3"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalMagne"), SLOT(setsignalIndex(int)));

    // Mise à jour des gyrograph au crisques environnementaux, smartphone, crowdmapping, SIG, hangement du Combobox




    //if (this->findChild<Combobox*>("comboBox")->curren)





//    QObject::connect (_pCombo1, SIGNAL()), this->findChild<gyrograph*>("glSignalAcc"), SLOT()

    // Mise à jour de l'écran LCD
    QObject::connect(_pTimer, SIGNAL(timeout()), this, SLOT(majLCD()));

    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<gyrograph*>("glSignalGyro"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<gyrograph*>("glSignalMagne"), SLOT(updateGL()));

    // Evolution slider + boutons
    connect(_pTimer, SIGNAL(timeout()), this, SLOT(setslidervalue()));
    connect(ui->pushButton_3, SIGNAL(clicked()), _pTimer, SLOT(stop()));
    // Modif Régis 12/11
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(timer_play()));
    // Fin Régis 12/11
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(timer_stop()));

    // timer calé sur la fréquence d'échantillonage des signaux
    //timer->start(1000/freqEch);
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


void MainWindow::majLCD()
{
    std::ostringstream s;
    s<<(double)_pTdb->getiCourant()/(double)freqEch;
    std::string sttime=s.str();
    ui->lcdNumber->display(QString(sttime.c_str()));
}

void MainWindow::setslidervalue()
{
    int valslider=this->_pTdb->getiCourant();
    int value = ui->horizontalSlider->value()+valslider;
    ui->horizontalSlider->setValue(value);

}

// Ajout Régis 12/11
void MainWindow::timer_play()
{
    // On réaffecte la mémoire de date à la date courante
    _pTdb->setLastTimeToCurrentTime();
    _pTimer->start();

}
// Fin ajout Régis 12/11

void MainWindow::timer_stop()
{
  _pTimer->stop();
  ui->lcdNumber->display(0);
  ui->horizontalSlider->setValue(0);
}

