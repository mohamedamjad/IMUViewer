#ifndef CAPTEUR_H
#define CAPTEUR_H

#include "centrale.h"

class Capteur
{
public:
    Capteur();

    void setCentrale(Centrale *);

protected:
    Centrale* _pIMU;
};

#endif // CAPTEUR_H
