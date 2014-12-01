 
# include "centrale.h"

Centrale::Centrale()
{
    // Initialisation des vecteurs
    for (int i=0;i<3;i++)
    {
        // Capteurs
        _acc.append(0);
        _gyro.append(0);
        _magn.append(0);
        // Position et orientation
        _orientation.append(0);
        _position.append(0);
    }
}

