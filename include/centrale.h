#ifndef CENTRALE_H
#define CENTRALE_H

#include <QVector>

class Centrale
{
public:
    Centrale();
    void setAccX(double);

    // Trois vecteurs pour les trois capteurs
    QVector<double> _acc;
    QVector<double> _gyro;
    QVector<double> _magn;
    // Vecteur pour l'accélo intégré deux fois
    QVector<double> _acc2I;
    // Vecteur pour le gyroscope intégré une fois
    QVector<double> _gyroI;
};

#endif // CENTRALE_H
