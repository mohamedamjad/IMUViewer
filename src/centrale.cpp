 
# include "centrale.h"

Centrale::Centrale()
{
    for (int i=0;i<3;i++)
    {
        _acc.append(0);
        _gyro.append(0);
        _magn.append(0);
        _accNorm.append(0);
        _gyroNorm.append(0);
        _magnNorm.append(0);
        _acc2I.append(0);
        _gyroI.append(0);
        _orientation.append(0);
        _position.append(0);
    }
}


