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
    // Trois vecteurs normés pour l'affichage du graph signal
    QVector<double> _accNorm;
    QVector<double> _gyroNorm;
    QVector<double> _magnNorm;
    // Vecteur pour l'accélo intégré deux fois
    QVector<double> _acc2I;
    // Vecteur pour le gyroscope intégré une fois
    QVector<double> _gyroI;
    // Vecteur Orientation (cumul des gyroI)
    QVector<double> _orientation;
    // Vecteur Position (cumul des acc2I)
    QVector<double> _position;

};

#endif // CENTRALE_H
