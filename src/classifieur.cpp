#include "classifieur.h"

Classifieur::Classifieur(QVector <Signal*> *unPSignaux,int unNbSignaux)
{
    _pSignaux = unPSignaux;
    _nbSignaux= unNbSignaux;
}

Classifieur::~Classifieur()
{
    delete _pClasses;
}

// Lancement de la classification
void Classifieur::classe()
{
    if (_pSignaux->size() >= _nbSignaux)
    {
        Signal accX = (*(*_pSignaux)[0]);
        _pClasses = new int[accX.getTaille()];
    }

}




