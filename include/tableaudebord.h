#ifndef TABLEAUDEBORD_H
#define TABLEAUDEBORD_H

// Mode test
//#define TESTS_MODE

// Mode run
#define RUN_MODE

// Fréquence du filtre passe-bas permettant de ressortir le signal gravité en Hz
#define freqFiltreGravite 0.18
// Fréquence de ré-échantillonage du signal en Hz ATTENTION DOIT ETRE PAIRE
#define freqEch 100


// Taille de la fenetre utilisée pour le calcul des indicateurs préalables à la classification
#define tailleFenetreStats freqEch-1

#include <QThread>
#include <QTimer>
#include "signal.h"
#include "csv.h"
#include <QVector>
#include "centrale.h"
#include <QTime>
#include "classifieur.h"

/*
    *\class TableauDeBord
    * \brief IMU Viewer : Classe de gestion principale du programme, contient tous les signaux et gère l'avancement à l'intérieur
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class TableauDeBord : public QObject
{
    Q_OBJECT
    public:
    /**
        * \fn TableauDeBord
        * \brief  Constructeur
        * \param fichierCsv Fichier issu de l'acquisition centrale au format : tps en sec, code, accx, accy, accz, code, gyrox, gyroy, gyroz, code, magnex, magney, magnez
    */
        TableauDeBord(const char* fichiercsv);
        /**
            * \fn ~TableauDeBord
            * \brief  Destructeur
        */
        ~TableauDeBord();
        /**
            * \fn getCoinInferieur
            * \brief Renvoie le point inférieur gauche (xmin, ymin, zmin) de l'espace d'évolution de la centrale (QVector<double>)
            * \return Le point sous forme de vecteur (QVector<double>)
        */
        QVector<double> getCoinInferieur();
        /**
            * \fn getCoinSuperieur
            * \brief Renvoie le point supérieur droit (xmax, ymax, zmax) de l'espace d'évolution de la centrale (QVector<double>)
            * \return Le point sous forme de vecteur (QVector<double>)
        */
        QVector<double> getCoinSuperieur();
        /**
            * \fn get_signaux
            * \brief Renvoie le vecteur contenant tous les signaux, tous sont rééchantillonés, il y a les bruts et ceux issus du traitement : [0-1-2] : accéléro sans gravité, accés possible aux données doublement intégrées, [3-4-5] : gyroscope, accés possible aux données intégrées, [6-7-8] : magnétomètre, [9-10-11] : position de la centrale en repère absolu
            * \return Le point sous forme de vecteur (QVector<double>)
        */
        QVector<Signal*> get_signaux();
        /**
            * \fn getiCourant
            * \return Renvoie l'indice courant de parcours des signaux (int)
        */
        int getiCourant();
        /**
            * \fn getnbEch
            * \return Renvoie le nombre d'éléments dans les signaux(int)
        */
        int getnbEch();
        /**
            * \fn setLastTimeToCurrentTime
            * \brief Sets la date mémoire à la date courante
        */
        void setLastTimeToCurrentTime();
        /**
            * \fn setiCourant
            * \brief Sets l'indice courant de parcours du signal
            * \param i Nouvel indice (int)
        */
        void setiCourant(int i);
        /**
            * \fn reInitialiseCapteursCentraleEtProgressionSignal
            * \brief Réinitialise les capteurs de la centrale et vide sa trajectoire, initialise l'indice de parcours du Signal à zéro
        */
        void reInitialiseCapteursCentraleEtProgressionSignal();
        /**
            * \fn setPositionEtCapteursCentrale
            * \brief Règle la position de la centrale et les données de ses capteurs correspondant à un certain instant dans le signal et ajoute la position courante à son historique de trajectoire
            * \param i Ieme élément dans le signal (int)
        */
        void setPositionEtCapteursCentrale(int i);
        /**
            * \fn calculeFenetreCentrale
            * \brief Calcule le parallépipède correspondant à l'espace englobant d'évolution de la centrale
        */
        void calculeFenetreCentrale();
        /**
            * \fn getClassifieur
            * \return Renvoie l'objet classifieur (Classfieur*)
        */
        Classifieur* getClassifieur();
        /**
            * \var _IMU
            * \brief Représente la centrale à un instant donné
        */
        Centrale _IMU;
public slots:
        /**
            * \fn majCentrale
            * \brief Callback d'évolution du temps : fait avancer la centrale dans le temps (en boucle)
        */
        void majCentrale();
    private:
        /**
            * \fn incrementeICourant
            * \brief Incrémente l'indice de parcours du signal de manière à ce que le parcours dans le signal soit réalisé comme en temps réel
            * \return Le pas d'incrémentation, -1 si l'indice a été réinitialisé à zéro (int)
        */
        int incrementeICourant();
        /**
            * \fn creeVecteurSignauxEtClassifie
            * \brief Effectue les traitements sur les signaux, remplit les structures de données correspondantes et lance la classification du mouvement
            * \param donneesBrutes Matrice issue de la lecture du fichier csv (double **)
            * \param uneFreqFiltre Fréquence utilisée pour le filtre passe bas permettant d'isoler la gravité (FrequencyType)
            * \param uneFreqEch Fréquence à appliquer pour le rééchantillonage (FrequencyType)
        */
        void creeVecteurSignauxEtClassifie(double**,  FrequencyType, FrequencyType);

        /**
            * \var _signaux
            * \brief Vecteur contenant tous les signaux, tous sont rééchantillonés, il y a les bruts et ceux issus du traitement : [0-1-2] : accéléro sans gravité, accés possible aux données doublement intégrées, [3-4-5] : gyroscope, accés possible aux données intégrées, [6-7-8] : magnétomètre, [9-10-11] : position de la centrale en repère absolu
        */
        QVector<Signal*> _signaux;

        /**
            * \var _coinInferieur
            * \brief Renvoie le point inférieur gauche (xmin, ymin, zmin) de l'espace d'évolution de la centrale (QVector<double>)
        */
        QVector<double> _coinInferieur;
        /**
            * \var _coinSuperieur
            * \brief Renvoie le point supérieur droit (xmax, ymax, zmax) de l'espace d'évolution de la centrale (QVector<double>)
        */
        QVector<double> _coinSuperieur;

        /**
            * \var _nbEch
            * \brief Nombre d'élément du signal
        */
        int _nbEch;
        /**
            * \var iCourant
            * \brief Indice courant d'évoltuion dans le signal
        */
        int iCourant;
        /**
            * \var _classif
            * \brief Objet permettant d'effectuer la classification et de récupérer ses résultats
        */
        Classifieur* _classif;

        /**
            * \var _lastTime
            * \brief Enregistre le QTime de la dernière itération pour identifier un éventuel décalage entre le temps reel et le temps du signal
        */
        QTime _lastTime;

};

#endif // TABLEAUDEBORD_H
