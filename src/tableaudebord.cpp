#include "tableaudebord.h"

// Constructeur à partir d'un fichier csv issu de l'acquisition
TableauDeBord::TableauDeBord(const char* fichiercsv)
{
    // Lecture du fichier des données centrale
    CSV donneesCentrale;
    double **donneesBrutes   = donneesCentrale.readCSV(fichiercsv);

    // Nombre de lignes du fichier
    _nbEch = donneesCentrale.getNbLines();

    // Cree un vecteur de signaux avec toutes les données et classifie le mouvement
    creeVecteurSignauxEtClassifie(donneesBrutes,freqFiltreGravite,freqEch);
    // Calcul de l'espace englobant d'évolution de la centrale
    calculeFenetreCentrale();

    // Initialisation de l'indice de parcours du signal et des capteurs
    reInitialiseCapteursCentraleEtProgressionSignal();

    // Initialisation du QTime à maintenant
    setLastTimeToCurrentTime();

    // Libération donneesBrutes
    for (int i=0; i<13; i++)
        delete [] donneesBrutes[i];
    delete [] donneesBrutes;
}

// Destructeur
TableauDeBord::~TableauDeBord()
{
    if (_classif) delete _classif;
    // On vide le QVector de signaux
    for (int i=0;i<_signaux.size();i++)
    {
        delete _signaux[i];
    }
}


// Calcul de l'espace englobant d'évolution de la centrale
void TableauDeBord::calculeFenetreCentrale()
{
    double x,y,z=0.0;
    _coinInferieur.append(INFINITY);
    _coinInferieur.append(INFINITY);
    _coinInferieur.append(INFINITY);
    _coinSuperieur.append(-INFINITY);
    _coinSuperieur.append(-INFINITY);
    _coinSuperieur.append(-INFINITY);


    // Parcours de toutes les données
    for (int i=0;i<_nbEch-2;i++)
    {
        x = _signaux[9]->getSignalDoubleIntegre(i);
        y = _signaux[10]->getSignalDoubleIntegre(i);
        z = _signaux[11]->getSignalDoubleIntegre(i);

        if (x<_coinInferieur[0])_coinInferieur[0]=x;
        if (y<_coinInferieur[1])_coinInferieur[1]=y;
        if (z<_coinInferieur[2])_coinInferieur[2]=z;

        if (x>_coinSuperieur[0])_coinSuperieur[0]=x;
        if (y>_coinSuperieur[1])_coinSuperieur[1]=y;
        if (z>_coinSuperieur[2])_coinSuperieur[2]=z;
    }
}

// Renvoie le point xmin, ymin, zmin de l'espace englobant d'évolution de la centrale
QVector<double> TableauDeBord::getCoinInferieur()
{
    return _coinInferieur;
}

// Renvoie le point xmax, ymax, zmax de l'espace englobant d'évolution de la centrale
QVector<double> TableauDeBord::getCoinSuperieur()
{
    return _coinSuperieur;
}

//Effectue les traitements sur les signaux, remplit les structures de données correspondantes et lance la classification du mouvement
void TableauDeBord::creeVecteurSignauxEtClassifie(double** donneesBrutes,  FrequencyType uneFreqFiltre, FrequencyType uneFreqEch)
{
    // Données de l'accéléro : récupération et suppression de l'effet de gravité
    // _signaux[0-1-2];
    QVector<Signal*> _signauxTmp;
    for (int i=2;i<=4;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i,tailleFenetreStats);
        signalBrut->regulariseEchantillonage(uneFreqEch);// Rééchantilonnage
        signalBrut->calculStats();// Stats préalables à la classif

        Signal gravite(*signalBrut);
        gravite.passeBas(uneFreqFiltre,uneFreqEch,false);// Gravité extraite à partir d'un filtre passe bas

        Signal *signalSansGravite = *signalBrut - gravite;// On extrait le signal sans gravité
        _signaux.append(signalSansGravite);
        _signauxTmp.append(signalBrut);
    }

    // Classification
    _classif = new Classifieur(&_signauxTmp,tailleFenetreStats);
    _classif->classe();

    // Données du gyroscope : récupération et intégration
    // _signaux[3-4-5];
    for (int i=6;i<=8;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i,tailleFenetreStats);
        signalBrut->regulariseEchantillonage(uneFreqEch);// Rééchantilonnage
        signalBrut->integre();// Intégration (orientation de la centrale au fil du temps)
        _signaux.append(signalBrut);
    }

    // Données du magnéto : récupération
    // _signaux[6-7-8];
    for (int i=10;i<=12;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i,tailleFenetreStats);
        signalBrut->regulariseEchantillonage(uneFreqEch);// Rééchantilonnage
        _signaux.append(signalBrut);
    }

    // Données de l'accéléromètre : changement de repère (repère central => repère absolu)
    // et récupération des nouveaux signaux correspondants
    // _signaux[9-10-11];
    for (int i = 0;i<=2;i++)// Copie signaux
    {
        Signal *signalAccelero = new Signal(*_signaux[i]);
        _signaux.append(signalAccelero);
    }
    Signal::changeRepere(_signaux[9],_signaux[10],_signaux[11],*_signaux[3],*_signaux[4],*_signaux[5]);

    // On double intègre l'accéléro en repère absolu pour obtenir les positions de la centrale
    for (int i = 9;i<=11;i++)_signaux[i]->doubleIntegre();

   _nbEch=_signaux[0]->getTaille();
}


// Evolution du temps et mise à jour des données du capteur de la centrale correspondante
void TableauDeBord::majCentrale()
{
    // Incrémentation de l'indice de parcours dans le signal collé sur le vrai temps
    // Revient à zéro si on est arrivé à la fin du signal
    int pas = incrementeICourant();

    // Réinitialisation de la centrale
    if (iCourant==0)
    {
        reInitialiseCapteursCentraleEtProgressionSignal();
    }
    else
    {
        // Etant donné que l'indice s'incrémente en suivant le vrai temps, il faut accumuler les
        // positions qu'on saute pour l'historique de trajectoire jusqu'à la position courante
        // pour laquelle on garde les données des capteurs
        for (int i=iCourant-pas+1;i<=iCourant;i++)
        {
            setPositionEtCapteursCentrale(i);
        }
    }
    // Maj orientation de la centrale
    double angleX = _signaux[3]->getSignalIntegre(iCourant);
    double angleY = _signaux[4]->getSignalIntegre(iCourant);
    double angleZ = _signaux[5]->getSignalIntegre(iCourant);
    _IMU._orientation[0]= (_IMU._orientation[0]>=2*M_PI) ? angleX : angleX-2*M_PI;
    _IMU._orientation[1]= (_IMU._orientation[1]>=2*M_PI) ? angleY : angleY-2*M_PI;
    _IMU._orientation[2]= (_IMU._orientation[2]>=2*M_PI) ? angleZ : angleZ-2*M_PI;
    // Maj capteurs accélération
    _IMU._acc[0] = _signaux[0]->getSignal(iCourant);
    _IMU._acc[1] = _signaux[1]->getSignal(iCourant);
    _IMU._acc[2] = _signaux[2]->getSignal(iCourant);
}


/// Incremente iCourant et renvoie le pas utilisé
/// Réinitialise également _lastTime
/// Renvoie -1 si iCourant a été réinitialisé à zéro
int TableauDeBord::incrementeICourant()
{
    // Détermination du nb de ms depuis le dernier tour
    QTime maintenant = QTime::currentTime();
    int mSecs = abs(maintenant.msecsTo(_lastTime));

    // période d'échantillonage en ms
    double periodeEchantillonage = 1000/freqEch;

    // pas = division entière (mSecs / période en mS) arrondie à l'entier le plus pres
    // correspond au nb de périodes qu'on a sauté
    int pas = round((mSecs / periodeEchantillonage));

    // On surveille qu'on n'arrive pas à la fin du signal
    if ((iCourant+pas) < (_signaux.at(0)->getTaille()))
    {
        // Incrémentation iCourant
        iCourant+=pas;
        // Décalage à rajouter à maintenant pour tomber sur le "maintenant" du signal échantilloné
        //(légèrement supérieur ou inférieur)
        _lastTime = _lastTime.addMSecs(pas*periodeEchantillonage);
        return pas;
    }
    else
    {
        // On revient au début du signal
        iCourant = 0;
        setLastTimeToCurrentTime();
        return -1;
    }
}

// Renvoie le vecteur contenant tous les signaux, tous sont rééchantillonés, il y a les bruts et ceux issus du traitement : [0-1-2] : accéléro sans gravité, accés possible aux données doublement intégrées, [3-4-5] : gyroscope, accés possible aux données intégrées, [6-7-8] : magnétomètre, [9-10-11] : position de la centrale en repère absolu
QVector<Signal*> TableauDeBord::get_signaux()
{
    return this->_signaux;
}
// Renvoie l'indice courant de parcours du signal
int TableauDeBord::getiCourant()
{
    return this->iCourant;
}
// Set le iCourant
void TableauDeBord::setiCourant(int unI)
{
    // On réinitialise la centrale pour notamment vider l'historique de sa trajectoire
    reInitialiseCapteursCentraleEtProgressionSignal();
    this->iCourant = unI;
    // Rejoue le parcours du signal jusqu'au nouveau iCourant
    for (int i=0;i<iCourant;i++)
    {
       setPositionEtCapteursCentrale(i);
    }
}
// Renvoie le nombre d'éléments du signal
int TableauDeBord::getnbEch()
{
    return this->_nbEch;
}
// Sets la date mémoire à la date courante
void TableauDeBord::setLastTimeToCurrentTime()
{
    _lastTime = QTime::currentTime();
}

// Réinitialise les capteurs de la centrale et vide sa trajectoire, initialise l'indice de parcours du Signal à zéro
void TableauDeBord::reInitialiseCapteursCentraleEtProgressionSignal()
{

    iCourant = 0;
    // Orientation depuis le gyro
    _IMU._orientation[0]=0;
    _IMU._orientation[1]=0;
    _IMU._orientation[2]=0;

    // Postion depuis l'acceleromètre
    _IMU._position[0]=0;
    _IMU._position[1]=0;
    _IMU._position[2]=0;

    // On vide la trajectoire
    _IMU._trajectoire.clear();

}

// Règle la position de la centrale et les données de ses capteurs correspondant à un certain instant dans le signal et ajoute la position courante à son historique de trajectoire
void TableauDeBord::setPositionEtCapteursCentrale(int i)
{
    // Position depuis l'acceleromètre
    _IMU._position[0]= _signaux[9]->getSignalDoubleIntegre(i);
    _IMU._position[1]= _signaux[10]->getSignalDoubleIntegre(i);
    _IMU._position[2]= _signaux[11]->getSignalDoubleIntegre(i);
    // On ajoute le point courant de la centrale à la trajectoire
    _IMU._trajectoire.append(_IMU._position);

}

// Renvoie l'objet classifieur (Classfieur*)
Classifieur* TableauDeBord::getClassifieur()
{
    return _classif;
}


