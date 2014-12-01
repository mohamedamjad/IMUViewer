#include "classifieur.h"

std::string Classifieur::imgClasses[] = {"NC.png","marche.png","course.png","monte.png","descend.png"};
std::string Classifieur::labelClasses[] = {"Non Classifie","Marche","Course","Monte les escaliers","Descend les escaliers"};

Classifieur::Classifieur(QVector <Signal*> *unPSignaux,int uneTailleFenetre)
{
    _pSignaux          = unPSignaux;
    _tailleFenetreStats= uneTailleFenetre;
    _estClasse         = false;
}

Classifieur::~Classifieur()
{
    if (_estClasse)
        delete _pClasses;
}

// Lancement de la classification
void Classifieur::classe()
{
    if (_pSignaux->size() >= nbSignauxClassif)
    {
        Signal accX       = (*(*_pSignaux)[0]);
        if (accX.getTaille()>(_tailleFenetreStats-1))
        {
            Signal accY       = (*(*_pSignaux)[1]);
            Signal accZ       = (*(*_pSignaux)[2]);

            _tailleClasses    = accX.getTaille()-_tailleFenetreStats+1;

            if (_tailleClasses > 0)
            {
                _pClasses         = new int[_tailleClasses];

                // Calcul de la norme de l'accélération
                Signal* accX2 = accX*accX;
                Signal* accY2 = accY*accY;
                Signal* accZ2 = accZ*accZ;
                Signal* normeTmp = *accX2 + *accY2;
                Signal* norme    = *normeTmp + *accZ2;

                for(int i=0;i<norme->getTaille();i++)
                {
                    norme->setSignal(sqrt(norme->getSignal(i)),i);
                }
                norme->calculStats();

                // Classication : parcours du tableau des classes
                for (int i=0;i<_tailleClasses;i++)
                {
                    // Escalier
                    SampleType min = accY.getMin(i);
                    if (min < seuilAccYEscalier)
                    {
                        if (min < seuilAccYMonteDescend)
                            _pClasses[i] = CLASSE_DESCEND_ESCALIER;
                        else _pClasses[i] = CLASSE_MONTE_ESCALIER;
                    }
                    else
                    {
                        // Distinction marche / course
                        SampleType moyenne = norme->getMoyenne(i);
                        if (moyenne < seuilMoyenneNormeAccelerationMarcheOuCourse)
                            _pClasses[i]  = CLASSE_MARCHE;
                        else _pClasses[i] = CLASSE_COURSE;
                    }
                }

                delete accX2;
                delete accY2;
                delete accZ2;
                delete norme;
                delete normeTmp;
                _estClasse = true;
            }
         }
    }

}
// Renvoie la classe d'un point dans le signal (le i c'et le i du signal)
int Classifieur::getClasse(int i)
{
    if (_estClasse == true)
    {
        int delta  = (_tailleFenetreStats-1)/2;
        int iClasse= i - delta;
        if ((iClasse>=0) && (iClasse<_tailleClasses))
        {
            return _pClasses[iClasse];
        }
    }
    return NON_CLASSE;
}

QString Classifieur::getLabelClasse(int i)
{
    std::string resStr = Classifieur::labelClasses[getClasse(i)];
    QString res(resStr.c_str());
    return res;
}

QString Classifieur::getImgClasse(int i)
{
    std::string resStr = Classifieur::imgClasses[getClasse(i)];
    QString res(resStr.c_str());
    return res;
}
