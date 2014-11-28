#include "classifieur.h"

Classifieur::Classifieur(QVector <Signal*> *unPSignaux,int unNbSignaux,int uneTailleFenetre)
{
    _pSignaux           = unPSignaux;
    _nbSignaux          = unNbSignaux;
    _tailleFenetreStats = uneTailleFenetre;
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
    if (_pSignaux->size() >= 3)
    {
        Signal accX       = (*(*_pSignaux)[0]);
        if (accX.getTaille()>(_tailleFenetreStats-1))
        {
            Signal accY       = (*(*_pSignaux)[1]);
            Signal accZ       = (*(*_pSignaux)[2]);
            int delta         = (_tailleFenetreStats-1)/2;
            _tailleClasses    = accX.getTaille()-_tailleFenetreStats+1;
            std::cout << _tailleClasses<< std::endl;
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
                    std::cout << min << std::endl;
                    if (min < seuilAccYEscalier)
                    {
                        if (min < seuilAccYMonteDescend)
                            _pClasses[i] = DESCEND_ESCALIER;
                        else _pClasses[i] = MONTE_ESCALIER;
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
            return _pClasses[i];
    }
    return NON_CLASSE;
}



