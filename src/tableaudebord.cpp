
#include "tableaudebord.h"


TableauDeBord::TableauDeBord()
{

    std::cout<<"Constructeur tdb"<<std::endl;
    // Lecture du fichier des données centrale
    CSV donneesCentrale;
    double **donneesBrutes   = donneesCentrale.readCSV(fichierCsv);
    // Nombre de lignes du fichier
    _nbEch = donneesCentrale.getNbLines();
    // Cree un vecteur de signaux avec toutes les données
    creeVecteurSignaux(donneesBrutes,freqFiltre,freqEch,true);

}


TableauDeBord::~TableauDeBord()
{}


void TableauDeBord::creeVecteurSignaux(double** donneesBrutes,  FrequencyType uneFreqFiltre, FrequencyType uneFreqEch,bool reEchantillone)
{

    // Données de l'accéléromètre
    for (int i=2;i<=4;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        //signalBrut.passeBas(uneFreqFiltre,uneFreqEch,reEchantillone);
        signalBrut->doubleIntegre();
        _signaux.append(signalBrut);
    }

    // Données du gyroscope
    for (int i=6;i<=8;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        //signalBrut.passeBas(uneFreqFiltre,uneFreqEch,reEchantillone);
        signalBrut->integre();
        _signaux.append(signalBrut);
    }
    // Données du magnéto
    for (int i=10;i<=12;i++)
    {
        Signal *signalBrut = new Signal(donneesBrutes,_nbEch,0,i);
        //signalBrut.passeBas(uneFreqFiltre,uneFreqEch,reEchantillone);
        _signaux.append(signalBrut);
    }

}


// Mise à jour des données du capteur de la centrale
void TableauDeBord::majCentrale()
{

    _IMU._acc[0] = _signaux[0]->getSignal(iCourant);
    // Incrémentation de l'indice de parcours des données
    iCourant = (iCourant < (_signaux.at(0)->getTaille() -1)) ? iCourant+1:0;
    std::cout<< iCourant<< "acc = " << _IMU._acc[0]<< std::endl;
}

