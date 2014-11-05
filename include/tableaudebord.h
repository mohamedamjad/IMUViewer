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

        Centrale _IMU;

        QVector<double> getCoinInferieur();
        QVector<double> getCoinSuperieur();

    public slots:

        void majCentrale();

   protected :


    private:
        // 0-1-2 : accelero
        // 3-4-5 : gyro
        // 6 7 8 : magnéto
        QVector<Signal*> _signaux;

        // Coordonnées du point inférieur et supérieur de la fenetre d'évolution de la centrale
        QVector<double> _coinInferieur;
        QVector<double> _coinSuperieur;

        // Nb de lignes dans le fichier de départ
        int _nbEch;
        // Représente l'indice courant dans le tableau de données
        int iCourant;

        void creeVecteurSignaux(double**,  FrequencyType, FrequencyType,bool);

        void calculeFenetreCentrale();

};

#endif // TABLEAUDEBORD_H
