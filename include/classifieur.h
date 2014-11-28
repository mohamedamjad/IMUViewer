#ifndef CLASSIFIEUR_H
#define CLASSIFIEUR_H

#include <QVector>;
#include "signal.h"
#include <math.h>

#define CLASSE_MARCHE 1
#define CLASSE_COURSE 2
#define MONTE_ESCALIER 3
#define DESCEND_ESCALIER 4


class Classifieur
{
    public:
        Classifieur(QVector <Signal*> *,int);
        ~Classifieur();
        void classe();
    private:

        QVector<Signal*> *_pSignaux;
        int* _pClasses;
        int _nbSignaux;

};

#endif // CLASSIFIEUR_H
