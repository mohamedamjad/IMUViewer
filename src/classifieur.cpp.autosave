#include "classifieur.h"
// Initialisation des tableaux contenant les images et les labels de classe par classe
std::string Classifieur::imgClasses[] = {"NC.png","marche.png","course.png","monte.png","descend.png"};
std::string Classifieur::labelClasses[] = {"Non Classifie","Marche","Course","Monte les escaliers","Descend les escaliers"};

// Constructeur
Classifieur::Classifieur(QVector <Signal*> *unPSignaux,int uneTailleFenetre)
{
    _pSignaux          = unPSignaux;
    _tailleFenetreStats= uneTailleFenetre;
    _estClasse         = false;
}
// Destructeur
Classifieur::~Classifieur()
{
    if (_estClasse)
        delete _pClasses;
}

// Lancement de la classification
void Classifieur::classe()
{
    // On vérifie que le vecteur des signaux fait bien la taille requise
    if (_pSignaux->size() >= nbSignauxClassif)
    {
        Signal accX       = (*(*_pSignaux)[0]);
        // Il faut que le signal soit au moins de la taille de la fenetre glissante
        if (accX.getTaille()>=_tailleFenetreStats)
        {
            Signal accY       = (*(*_pSignaux)[1]);
            Signal accZ       = (*(*_pSignaux)[2]);
            // Taille du tableau contenant les classes
            _tailleClasses    = accX.getTaille()-_tailleFenetreStats+1;

            if (_tailleClasses > 0)
            {
                // Intialisation du tableau contenant les numéros de classe
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
                // On lance le calcul de stats sur la norme (moyenne, écart type)
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
                        else _pClasses[i]= CLASSE_MONTE_ESCALIER;
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
                // Libération de la mémoire occupée par les pointeurs temporaires
                delete accX2;
                delete accY2;
                delete accZ2;
                delete norme;
                delete normeTmp;
                // Drapeau de classement à true
                _estClasse = true;
            }
         }
    }

}
// Renvoie la classe d'un point dans le signal (le i correspond au i du signal)
int Classifieur::getClasse(int i)
{
    if (_estClasse == true)
    {
        // delta permettant de passer du signal au tableau de classement
        int delta  = (_tailleFenetreStats-1)/2;
        int iClasse= i - delta;
        if ((iClasse>=0) && (iClasse<_tailleClasses))
        {
            return _pClasses[iClasse];
        }
    }
    return NON_CLASSE;
}
// Récupère le label de la classe du ieme élément du signal
QString Classifieur::getLabelClasse(int i)
{
    std::string resStr = Classifieur::labelClasses[getClasse(i)];
    QString res(resStr.c_str());
    return res;
}
// Récupère le nom du fichier du ieme élément du signal
QString Classifieur::getImgClasse(int i)
{
    std::string resStr = Classifieur::imgClasses[getClasse(i)];
    QString res(resStr.c_str());
    return res;
}
