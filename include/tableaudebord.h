#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H


// Fréquence du filtre passe-bas en Hz
#define freqFiltre 5
// Fréquence de ré-échantillonage du signal en Hz
#define freqEch 50

#define fichierCsv "amjad_marche_cheville.out"

#include <QThread>
#include <QTimer>
#include "signal.h"
#include "csv.h"
#include <QVector>
#include "centrale.h"


class TableauDeBord : public QObject
{
    Q_OBJECT
    public:

        TableauDeBord();
        ~TableauDeBord();
        void creeVecteurSignaux(int,double** ,  FrequencyType , FrequencyType ,bool );
        Centrale _IMU;

    public slots:

        void majCentrale();

   protected :


    private:
        // 0-1-2 : accelero
        // 3-4-5 : gyro
        // 6 7 8 : magnéto
        QVector<Signal*> _signaux;

        // Nb de lignes dans le fichier de départ
        int _nbEch;
        // Représente l'indice courant dans le tableau de données
        int iCourant;

        void creeVecteurSignaux(double**,  FrequencyType, FrequencyType,bool);

};

#endif // TABLEAUDEBORD_H
