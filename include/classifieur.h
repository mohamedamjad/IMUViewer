#ifndef CLASSIFIEUR_H
#define CLASSIFIEUR_H

#include <QVector>
#include <QString>
#include "signal.h"
#include <math.h>
#include <string.h>

#define NON_CLASSE 0
#define CLASSE_MARCHE 1
#define CLASSE_COURSE 2
#define CLASSE_MONTE_ESCALIER 3
#define CLASSE_DESCEND_ESCALIER 4


// Parametres de classification empiriques
#define seuilMoyenneNormeAccelerationMarcheOuCourse 14
#define seuilAccYEscalier 0
#define seuilAccYMonteDescend -3


class Classifieur
{
    public:
        Classifieur(QVector <Signal*> *,int,int);
        ~Classifieur();
        void classe();
        int getClasse(int);
        QString getLabelClasse(int);
        QString getImgClasse(int);
    private:
        static std::string imgClasses[];
        static std::string labelClasses[];
        QVector<Signal*> *_pSignaux;

        int* _pClasses;
        int _nbSignaux;
        int _tailleFenetreStats;

        bool _estClasse = false;
        int _tailleClasses;
};

#endif // CLASSIFIEUR_H
