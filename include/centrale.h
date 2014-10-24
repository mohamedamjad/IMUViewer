#ifndef CENTRALE_H
#define CENTRALE_H

#include <QVector>

class Centrale
{
public:
    Centrale();

private:
    // Trois vecteurs pour les trois capteurs
    QVector<double> _acc;
    QVector<double> _gyro;
    QVector<double> _magn;
};

#endif // CENTRALE_H
