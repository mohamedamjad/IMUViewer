#ifndef CENTRALE_H
#define CENTRALE_H

#include <QVector>
#include "signal.h"

/*
    *\class Centrale
    * \brief IMU Viewer : Classe permettant d'accéder aux données de la centrale à un instant t ainsi qu'à l'historique de sa trajectoire
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class Centrale
{
public:
    /**
        * \fn Centrale
        * \brief  Constructeur
    */
    Centrale();
    /**
        \var _acc
        \brief Vecteur à trois composantes stockant les valeurs de l'accéléromètre (QVector<double>)
    */
    QVector<double> _acc;
    /**
        \var _gyro
        \brief Vecteur à trois composantes stockant les valeurs du gyroscope (QVector<double>)
    */
    QVector<double> _gyro;
    /**
        \var _magn
        \brief Vecteur à trois composantes stockant les valeurs du magnétomètre (QVector<double>)
    */
    QVector<double> _magn;
    /**
        \var _orientation
        \brief Vecteur à trois composantes représentant l'orientation de la centrale en radians (QVector<double>)
    */
    QVector<double> _orientation;
    /**
        \var _position
        \brief Vecteur à trois composantes contenant la position de la centrale dans le repère absolu (QVector<double>)
    */
    QVector<double> _position;
    /**
        \var _trajectoire
        \brief Vecteur contenant l'historique des positions de la centrale(QVector<QVector<double>>)
    */
    QVector<QVector<double>> _trajectoire;
};

#endif // CENTRALE_H
