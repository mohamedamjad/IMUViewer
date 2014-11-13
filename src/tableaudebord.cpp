
#include "tableaudebord.h"


TableauDeBord::TableauDeBord(const char* fichiercsv)
{   
    // Lecture du fichier des données centrale
    CSV donneesCentrale;
    //_fichiercsv="amjad_marche_cheville.out";
    double **donneesBrutes   = donneesCentrale.readCSV(fichiercsv);

    // Nombre de lignes du fichier
    _nbEch = donneesCentrale.getNbLines();
    // Cree un vecteur de signaux avec toutes les données
    creeVecteurSignaux(donneesBrutes,freqFiltre,freqEch);
    calculeFenetreCentrale();

    ///////////////// Début modification à intégrer
    // Initialisation de l'indice de parcours du signal et des capteurs
    reInitialiseCapteursCentraleEtProgressionSignal();

    // Initialisation du QTime à maintenant
    setLastTimeToCurrentTime();
    ///////////////// Fin modification à intégrer
}


TableauDeBord::~TableauDeBord()
{}

// Calcule la fenête d'évolution de la centrale en simulant son évolution
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
        x+=_signaux[0]->getSignalDoubleIntegre(i);
        y+=_signaux[1]->getSignalDoubleIntegre(i);
        z+=_signaux[2]->getSignalDoubleIntegre(i);

        if (x<_coinInferieur[0])_coinInferieur[0]=x;
        if (y<_coinInferieur[1])_coinInferieur[1]=y;
        if (z<_coinInferieur[2])_coinInferieur[2]=z;

        if (x>_coinSuperieur[0])_coinSuperieur[0]=x;
        if (y>_coinSuperieur[1])_coinSuperieur[1]=y;
        if (z>_coinSuperieur[2])_coinSuperieur[2]=z;
    }
}

QVector<double> TableauDeBord::getCoinInferieur()
{
    return _coinInferieur;
}

QVector<double> TableauDeBord::getCoinSuperieur()
{
    return _coinSuperieur;
}

void TableauDeBord::creeVecteurSignaux(double** donneesBrutes,  FrequencyType uneFreqFiltre, FrequencyType uneFreqEch)
{

    // Données de l'accéléromètre
    for (int i=2;i<=4;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        signalBrut->regulariseEchantillonage(uneFreqEch);
       // signalBrut->passeBas(uneFreqFiltre,uneFreqEch,false);
        signalBrut->doubleIntegre();
        _signaux.append(signalBrut);
    }

    // Données du gyroscope
    for (int i=6;i<=8;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        signalBrut->regulariseEchantillonage(uneFreqEch);
        //signalBrut->passeBas(uneFreqFiltre,uneFreqEch,false);
        signalBrut->integre();
        _signaux.append(signalBrut);
    }
    // Données du magnéto
    for (int i=10;i<=12;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        signalBrut->regulariseEchantillonage(uneFreqEch);
        signalBrut->passeBas(uneFreqFiltre,uneFreqEch,false);
        _signaux.append(signalBrut);
    }

   _nbEch=_signaux[0]->getTaille();
}

///////////////// Début modification à intégrer /////////////////

// Mise à jour des données du capteur de la centrale
void TableauDeBord::majCentrale()
{
    ////////////////// Incrementation iCourant //////////////////
    int pas = incrementeICourant();

    ////////////////// Réinitialisation des capteurs //////////////////
    if (iCourant==0)
    {
        reInitialiseCapteursCentraleEtProgressionSignal();

    }
    //////////////////Mise à jour des indicateurs de position/orientation absolues //////////////////
    else
    {

        // On cumule les valeurs qu'on a sauté...
        for (int i=iCourant;i>iCourant-pas;i--)
        {
            miseenplace(i);


        }

    }
    //////////////////Mise à jour des capteurs temps réel //////////////////

    // Acc
    _IMU._acc[0] = _signaux[0]->getSignal(iCourant);
    _IMU._accNorm[0]=_signaux[0]->normalizeVector (_signaux[0]->getSignal(iCourant));
    _IMU._acc[1] = _signaux[1]->getSignal(iCourant);
    _IMU._accNorm[1]=_signaux[1]->normalizeVector (_signaux[1]->getSignal(iCourant));
    _IMU._acc[2] = _signaux[2]->getSignal(iCourant);
    _IMU._accNorm[2]=_signaux[2]->normalizeVector (_signaux[2]->getSignal(iCourant));
    // Gyro
    _IMU._gyro[0]= _signaux[3]->getSignal(iCourant);
    _IMU._gyroNorm[0]=_signaux[3]->normalizeVector (_signaux[3]->getSignal(iCourant));
    _IMU._gyro[1]= _signaux[4]->getSignal(iCourant);
    _IMU._gyroNorm[1]=_signaux[4]->normalizeVector (_signaux[4]->getSignal(iCourant));
    _IMU._gyro[2]= _signaux[5]->getSignal(iCourant);
    _IMU._gyroNorm[2]=_signaux[5]->normalizeVector (_signaux[5]->getSignal(iCourant));
    // Magnétomètre
    _IMU._magn[0]=_signaux[6]->getSignal(iCourant);
    _IMU._magnNorm[0]=_signaux[6]->normalizeVector (_signaux[6]->getSignal(iCourant));
    _IMU._magn[1]=_signaux[7]->getSignal(iCourant);
    _IMU._magnNorm[1]=_signaux[7]->normalizeVector (_signaux[7]->getSignal(iCourant));
    _IMU._magn[2]=_signaux[8]->getSignal(iCourant);
    _IMU._magnNorm[0]=_signaux[8]->normalizeVector (_signaux[8]->getSignal(iCourant));

    //Position depuis l'accéléro
    _IMU._acc2I[0] = _signaux[0]->getSignalDoubleIntegre(iCourant);
    _IMU._acc2I[1] = _signaux[1]->getSignalDoubleIntegre(iCourant);
    _IMU._acc2I[2] = _signaux[2]->getSignalDoubleIntegre(iCourant);

    // Angle depuis le gyro
    _IMU._gyroI[0]= _signaux[3]->getSignalIntegre(iCourant);
    _IMU._gyroI[1]= _signaux[4]->getSignalIntegre(iCourant);
    _IMU._gyroI[2]= _signaux[5]->getSignalIntegre(iCourant);

    // Vitesse courante
    double vX = _signaux[0]->getSignalIntegre(iCourant);
    double vY = _signaux[1]->getSignalIntegre(iCourant);
    double vZ = _signaux[2]->getSignalIntegre(iCourant);
    _IMU._vitesse  = sqrt(pow(vX,2)+pow(vY,2)+pow(vZ,2));
    //std::cout<< _lastTime.toString().toStdString()<< " => " << vY<<std::endl;

}


/// Incremente iCourant et renvoie le pas utilisé
/// Réinitialise également _lastTime
/// Renvoie -1 si iCourant a été réinitialisé à zéro
int TableauDeBord::incrementeICourant()
{
    QTime maintenant = QTime::currentTime();
    // Nb de ms depuis le dernier tour
    int mSecs = abs(maintenant.msecsTo(_lastTime));


    // période d'échantillonage en ms
    double periodeEchantillonage = 1000/freqEch;


    // Incrémentation du pas = division entière (mSecs / période en mS) arrondie à l'entier le plus pres
    int pas = round((mSecs / periodeEchantillonage));

    if ((iCourant+pas) < (_signaux.at(0)->getTaille()))
    {
        iCourant+=pas;
        // Décalage à rajouter à maintenant pour tomber sur le "maintenant" du signal échantilloné
        //(légèrement supérieur ou inférieur)
        _lastTime = _lastTime.addMSecs(pas*periodeEchantillonage);
        return pas;
    }
    else
    {
        iCourant = 0;
        setLastTimeToCurrentTime();
        return -1;
    }
}


QVector<Signal*> TableauDeBord::get_signaux()
{
    return this->_signaux;
}

int TableauDeBord::getiCourant()
{
    return this->iCourant;
}

void TableauDeBord::setiCourant(int unI)
{

    reInitialiseCapteursCentraleEtProgressionSignal();
    this->iCourant = unI;
    // Rejoue le parcours du signal jusqu'au nouveau iCourant



    for (int i=0;i<iCourant;i++)
    {
       miseenplace(i);

    }

}

int TableauDeBord::getnbEch()
{

    return this->_nbEch;
}

void TableauDeBord::setLastTimeToCurrentTime()
{
    _lastTime = QTime::currentTime();
}


// Réinitialise tous les capteurs ainsi que iCourant
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
    _IMU._distance = 0;

}
void TableauDeBord::miseenplace(int i)
{
    // Orientation : cumul des angles obtenus par intégration du signal gyro
    double angleX = _signaux[3]->getSignalIntegre(i);
    double angleY = _signaux[4]->getSignalIntegre(i);
    double angleZ = _signaux[5]->getSignalIntegre(i);
    _IMU._orientation[0]+= (_IMU._orientation[0]>=2*M_PI) ? angleX : angleX-2*M_PI;
    _IMU._orientation[1]+= (_IMU._orientation[1]>=2*M_PI) ? angleY : angleY-2*M_PI;
    _IMU._orientation[2]+= (_IMU._orientation[2]>=2*M_PI) ? angleZ : angleZ-2*M_PI;
    // Position depuis l'acceleromètre
    double deltaX = _signaux[0]->getSignalDoubleIntegre(i);
    double deltaY = _signaux[1]->getSignalDoubleIntegre(i);
    double deltaZ = _signaux[2]->getSignalDoubleIntegre(i);
    _IMU._position[0]+= deltaX;
    _IMU._position[1]+= deltaY;
    _IMU._position[2]+= deltaZ;
    // On ajoute le point courant de la centrale à la trajectoire
    _IMU._trajectoire.append(_IMU._position);
    // Incrémentation de la distance totale parcourue
    _IMU._distance += sqrt(pow(deltaX,2)+pow(deltaY,2)+pow(deltaZ,2));
}
