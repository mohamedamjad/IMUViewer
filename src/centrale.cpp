 
# include "centrale.h"

Centrale::Centrale()
{
    for (int i=0;i<3;i++)
    {
        _acc.append(0);
        _gyro.append(0);
        _magn.append(0);
    }
}
