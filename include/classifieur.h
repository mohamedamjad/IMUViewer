#ifndef CLASSIFIEUR_H
#define CLASSIFIEUR_H

#include <QVector>;
#include "signal.h"
#include <math.h>

#define CLASSE_MARCHE 1
#define CLASSE_COURSE 2
#define MONTE_ESCALIER 3
#define DESCEND_ESCALIER 4
#define NON_CLASSE -1

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
    private:

        QVector<Signal*> *_pSignaux;
        int* _pClasses;
        int _nbSignaux;
        int _tailleFenetreStats;

        bool _estClasse = false;
        int _tailleClasses;
};

#endif // CLASSIFIEUR_H
