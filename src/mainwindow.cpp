#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _fichierOuvert = false;
    ui->setupUi(this);
    _pTimer = new QTimer(this);
    chargeFichier("ferdaousse_mixte_cheville.out");


    // Affectation des comportements à chaque capteur
    CapteurGL *capteurAcc = this->findChild<CapteurGL*>("glCapteurAcc");
    CapteurGL *capteurGyro = this->findChild<CapteurGL*>("glCapteurGyro");
    capteurAcc->setComportement(COMP_ACC);
    capteurGyro->setComportement(COMP_GYRO);

    // Affectation des Comboboxs aux widgets appropriés
    for (int i=1;i<=3;i++)
    {
        char idBox[10];
        sprintf(idBox,"comboBox_%d",i);
        QComboBox* cbb = this->findChild<QComboBox*>(idBox);
        cbb->addItem ("Acc. X (m/s2)");
        cbb->addItem ("Acc. Y (m/s2)");
        cbb->addItem ("Acc. Z (m/s2)");
        cbb->addItem ("Gyro. X (rad/s)");
        cbb->addItem ("Gyro. Y (rad/s)");
        cbb->addItem ("Gyro. Z (m/s2)");
        cbb->addItem ("Magn. X (uT)");
        cbb->addItem ("Magn. Y (uT)");
        cbb->addItem ("Magn. Z (uT)");
    }
    gyrograph* glSignalAcc  = this->findChild<gyrograph*>("glSignalAcc");
    gyrograph* glSignalGyro = this->findChild<gyrograph*>("glSignalGyro");
    gyrograph* glSignalMagne= this->findChild<gyrograph*>("glSignalMagne");

    // Mise à jour de la centrale inertielle en suivant le _pTimer
    QObject::connect(_pTimer, SIGNAL(timeout()), _pTdb, SLOT(majCentrale()));
    // Mise à jour des widgets gl en suivant le timer
    QObject::connect(_pTimer, SIGNAL(timeout()), capteurAcc, SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), capteurGyro, SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), this->findChild<PrincipalCapteurGL*>("glPrincipal"), SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), glSignalAcc, SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), glSignalGyro, SLOT(updateGL()));
    QObject::connect(_pTimer, SIGNAL(timeout()), glSignalMagne, SLOT(updateGL()));
    // Maj LCD avec le timer
    QObject::connect(_pTimer, SIGNAL(timeout()), this, SLOT(majLCD()));
    // Maj LCS avec timer
    connect(_pTimer, SIGNAL(timeout()), this, SLOT(setslidervalue()));
    ////////////////////////////////EVENEMENTS UTILISATEUR//////////////////////////////////////////
    // Choix d'un autre signal à visualiser
    QObject::connect(this->findChild<QComboBox*>("comboBox_1"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalAcc"), SLOT(setsignalIndex(int)));
    QObject::connect(this->findChild<QComboBox*>("comboBox_2"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalGyro"), SLOT(setsignalIndex(int)));
    QObject::connect(this->findChild<QComboBox*>("comboBox_3"), SIGNAL(currentIndexChanged(int)), this->findChild<gyrograph*>("glSignalMagne"), SLOT(setsignalIndex(int)));
    QObject::connect (this->findChild<QComboBox*>("comboBox_1"), SIGNAL(currentIndexChanged(int)),this->findChild<gyrograph*>("glSignalAcc"), SLOT(updateLabel()));
    QObject::connect (this->findChild<QComboBox*>("comboBox_2"), SIGNAL(currentIndexChanged(int)),this->findChild<gyrograph*>("glSignalGyro"), SLOT(updateLabel()));
    QObject::connect (this->findChild<QComboBox*>("comboBox_3"), SIGNAL(currentIndexChanged(int)),this->findChild<gyrograph*>("glSignalMagne"), SLOT(updateLabel()));

    // Clic sur pause

    connect(ui->pushButton_3, SIGNAL(clicked()), _pTimer, SLOT(stop()));

    // Clic sur play

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(clicPlay()));

    // Clic sur stop

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(clicStop()));

    //Faire glisser le slider

    connect(ui->horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(dragslidervalue()));
    connect(ui->horizontalSlider, SIGNAL(sliderPressed()), _pTimer, SLOT(stop()));
    connect(ui->actionQuitter, SIGNAL(triggered(bool)),this , SLOT(close()));

    //Clic sur ouvrir un fichier
    connect(ui->actionCharger_un_nouveau_fichier, SIGNAL(triggered(bool)),this , SLOT(loadfile()));
    // Affichage LCD à 8 caractères
     ui->lcdNumber->setDigitCount(8);
}

void MainWindow::chargeFichier(const char* filename)
{
    // On supprime l'ancien tableau de bord si un fichier a déjà été ouvert
    if (_fichierOuvert)delete _pTdb;
    _fichierOuvert = true;

    _pTdb = new TableauDeBord(filename);
    _pTdb->calculeFenetreCentrale ();

    _pcGL = this->findChild<PrincipalCapteurGL*>("glPrincipal");
    _pcGL->setCentrale(&_pTdb->_IMU);

    // Mise à jour des widgets gl
    // Affectation de la centrale du tableau de bord aux widgets capteurs
    this->findChild<CapteurGL*>("glCapteurAcc")->setCentrale(&_pTdb->_IMU);
    this->findChild<CapteurGL*>("glCapteurGyro")->setCentrale(&_pTdb->_IMU);



    // Affectation de la centrale et du tableau de bord aux widgets signaux
    gyrograph* pGyroAcc= this->findChild<gyrograph*>("glSignalAcc");
    pGyroAcc->setCentrale (&_pTdb->_IMU);
    pGyroAcc->setTableauDeBord (_pTdb);
    pGyroAcc->setsignalIndex (0);
    pGyroAcc->setmaxLabel (this->findChild<QLabel*>("label_8"));
    pGyroAcc->setminLabel (this->findChild<QLabel*>("label_9"));

    gyrograph* pGyroGyro= this->findChild<gyrograph*>("glSignalGyro");
    pGyroGyro->setCentrale (&_pTdb->_IMU);
    pGyroGyro->setTableauDeBord (_pTdb);
    pGyroGyro->setsignalIndex (0);
    pGyroGyro->setmaxLabel (this->findChild<QLabel*>("label_10"));
    pGyroGyro->setminLabel (this->findChild<QLabel*>("label_11"));

    gyrograph* pGyroMagne= this->findChild<gyrograph*>("glSignalMagne");
    pGyroMagne->setCentrale (&_pTdb->_IMU);
    pGyroMagne->setTableauDeBord (_pTdb);
    pGyroMagne->setsignalIndex (0);
    pGyroMagne->setmaxLabel (this->findChild<QLabel*>("label_12"));
    pGyroMagne->setminLabel (this->findChild<QLabel*>("label_13"));

    // Modifications sur les QLabel

   this->findChild<QLabel*>("label_8")->setNum (_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalAcc")->getsignalIndex ()]->getMaxSignal ());
   this->findChild<QLabel*>("label_9")->setNum (-_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalAcc")->getsignalIndex ()]->getMaxSignal ());
   this->findChild<QLabel*>("label_10")->setNum (_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalGyro")->getsignalIndex ()]->getMaxSignal ());
   this->findChild<QLabel*>("label_11")->setNum (-_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalGyro")->getsignalIndex ()]->getMaxSignal ());
   this->findChild<QLabel*>("label_12")->setNum (_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalMagne")->getsignalIndex ()]->getMaxSignal ());
   this->findChild<QLabel*>("label_13")->setNum (-_pTdb->get_signaux ()[this->findChild<gyrograph*>("glSignalMagne")->getsignalIndex ()]->getMaxSignal ());

     // Mise à jour de la centrale inertielle en suivant le _pTimer
     QObject::connect(_pTimer, SIGNAL(timeout()), _pTdb, SLOT(majCentrale()));

     // Maj de la classe de mouvement
     QObject::connect(_pTimer, SIGNAL(timeout()), this, SLOT(majClasse()));

     // + fenetre d'évolution de la centrale

     _pcGL->setFenetreEvolutionCentrale(_pTdb->getCoinInferieur(),_pTdb->getCoinSuperieur());

     //initialisation de la taille du slider

      ui->horizontalSlider->setRange(0,_pTdb->getnbEch());

}

//destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // On renvoit la gestion du clavier à la fenetre d'affichage principal
    _pcGL->keyPressEvent(event);
}

//Affichage dans l'écran LCD

void MainWindow::majLCD()
{

    std::ostringstream s;
    s<<(double)_pTdb->getiCourant()/(double)freqEch;
    std::string sttime=s.str();
    ui->lcdNumber->display(QString(sttime.c_str()));
}

void MainWindow::majClasse()
{
       QPixmap marche("../IMUViewer/images/classif_mouvement/marche.png");
    QPixmap course("../IMUViewer/images/classif_mouvement/course.png");
    QPixmap monte("../IMUViewer/images/classif_mouvement/monte.png");
    QPixmap descend("../IMUViewer/images/classif_mouvement/descend.png");
    QPixmap NC("../IMUViewer/images/classif_mouvement/NC.png");

    switch (_pTdb->getClasse(this->_pTdb->getiCourant())) {

    case 1:
        this->findChild<label*>("label_14")->setText ("Marche");
        this->findChild<label*>("label_15")->setPixmap (marche);
        break;
    case 2:
        this->findChild<label*>("label_14")->setText ("Course");
        this->findChild<label*>("label_15")->setPixmap (course);
        break;
    case 3:
        this->findChild<label*>("label_14")->setText ("Monte les escaliers");
        this->findChild<label*>("label_15")->setPixmap (monte);
        break;
    case 4:
        this->findChild<label*>("label_14")->setText ("Descend les excaliers");
        this->findChild<label*>("label_15")->setPixmap (descend);
        break;
    default:
        this->findChild<label*>("label_14")->setText ("Non Classifié");
        this->findChild<label*>("label_15")->setPixmap (NC);
        break;
    }

}

//Initialisation de la valeur du slider

void MainWindow::setslidervalue()
{

    ui->horizontalSlider->setValue(this->_pTdb->getiCourant());
    ui->horizontalSlider->setValue(this->_pTdb->getiCourant());
}

// PLAY
void MainWindow::clicPlay()
{
    // On réaffecte la mémoire de date à la date courante
    _pTdb->setLastTimeToCurrentTime();
    _pTimer->start();


}
// STOP
void MainWindow::clicStop()
{
  _pTimer->stop();
  _pTdb->reInitialiseCapteursCentraleEtProgressionSignal();
  ui->lcdNumber->display(0);
  ui->horizontalSlider->setValue(0);
}

//Faire glisser le slider
void MainWindow::dragslidervalue()
{
    this->_pTdb->setiCourant(ui->horizontalSlider->value());
    _pTimer->start();
    _pTdb->setLastTimeToCurrentTime();


}
//Chargement d'un fichier

void MainWindow::loadfile()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Text files (*.out)"));
    this->chargeFichier(filename.toStdString().c_str());
}
