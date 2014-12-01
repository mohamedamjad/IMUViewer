#ifndef CLASSIFIEUR_H
#define CLASSIFIEUR_H

#include <QVector>
#include <QString>
#include "signal.h"
#include <math.h>
#include <string.h>

// Labels de classes utilisés dans le présent code
#define NON_CLASSE 0
#define CLASSE_MARCHE 1
#define CLASSE_COURSE 2
#define CLASSE_MONTE_ESCALIER 3
#define CLASSE_DESCEND_ESCALIER 4


// Parametres de classification empiriques
// Seuil de norme d'accélération pour le passage de la course à la marche
#define seuilMoyenneNormeAccelerationMarcheOuCourse 14
// Seuil d'accélération en Y pour le passage de la marche / course aux escaliers
#define seuilAccYEscalier 0
// Seuil d'accélération en Y pour la distinction des deux classes : monte escalier / descend escalier
#define seuilAccYMonteDescend -3

// Nombre de signaux utilisés pour la classification
#define nbSignauxClassif 3

/*
    *\class Classifieur
    * \brief IMU Viewer : Classe permettant de classer un mouvement à partir de signaux bruts d'accéléromètre placés dans une chaussette
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class Classifieur
{
    public:
        /**
            * \fn Classifieur
            * \brief  Constructeur
            * \param unPSignaux Pointeur sur les signaux de l'accéromètre brut (QVector<Signal*>*)
            * \param uneTailleFenetre Taille de la fenêtre à glisser sur le signal pour la classification (doit être impaire, les paramètres de classification sont définis pour fonctionner sur une freqEch à 100 hz et une fenetre à 99, changer les parametres de seuil de classif dans classifieur.h si fréquance d'échantillonage ou taille de fenetre différentes)
        */
        Classifieur(QVector <Signal*> *,int);
        /**
            * \fn ~Classifieur
            * \brief  Destructeur
        */
        ~Classifieur();
        /**
            * \fn classe
            * \brief  Lance la classification, au début et à la fin du Signal, le mouvement ne peut être classé (effet du à la taille de la fenetre)
        */
        void classe();
        /**
            * \fn getClasse
            * \brief Renvoie la classe pour le ieme élément du signal
            * \param i ieme élément du Signal (int)
            * \return Renvoie l'entier correspondant à la classe (int)
        */
        int getClasse(int);
        /**
            * \fn getLabelClasse
            * \brief Renvoie le label de la classe pour le ieme élément du signal
            * \param i Indice de l'élément du Signal (int)
            * \return Renvoie le label correspondant au mouvement (QString)
        */
        QString getLabelClasse(int);
        /**
            * \fn getImgClasse
            * \brief Renvoie le nom du fichier image correspondant à la classe du ieme élément du Signal
            * \param i Indice de l'élément du Signal (int)
            * \return Renvoie le nom du fichier correspondant au mouvement (QString)
        */
        QString getImgClasse(int);
    private:
        /**
            \var imgClasses
            \brief Contient le nom des fichiers images correspondant à chaque classe de mouvement
        */
        static std::string imgClasses[];
        /**
            \var labelClasses
            \brief Contient le label de chaque classe de mouvement
        */
        static std::string labelClasses[];
        /**
            \var _pSignaux
            \brief Pointeur vers les signaux de l'accéléromètre servant à la classification (QVector<Signal*> *)
        */
        QVector<Signal*> *_pSignaux;

        /**
            \var _pClasses
            \brief Tableau de taille taille signal-_tailleFenetreStats+1 stockant pour chaque élément du signal (décalé de (_tailleFenetreStats-1)/2)l'entier correspondant à la classe ()(int*)
        */
        int* _pClasses;
        /**
            \var _tailleFenetreStats
            \brief Taille de la fenêtre à faire glisser sur le signal pour le classer (int)
        */
        int _tailleFenetreStats;
        /**
            \var _estClasse
            \brief Booléen permettant de savoir si la classification a d'ores et déjà été effectuée (bool)
        */
        bool _estClasse = false;
        /**
            \var _tailleClasses
            \brief Taille du tableau contenant les classes, correspond ainsi au nb d'éléments du signal étant classé (int)
        */
        int _tailleClasses;
};

#endif // CLASSIFIEUR_H
