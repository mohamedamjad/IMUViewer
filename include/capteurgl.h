
#ifndef CAPTEURGLWIDGET_H
#define CAPTEURGLWIDGET_H

#include <QGLWidget>
#include <QTimerEvent>
#include <GL/glut.h>
#include "centrale.h"
#include <cmath>

// Longueur maximale d'un axe pour le comportement accéléromètre
#define longueurMaxAxe 1.5
// Valeur maximale arbitraire que prend le capteur pour le comportement accéléro
#define valMaxAccArbitraire 30.0

// Constantes de comportement
#define COMP_ACC 1
#define COMP_GYRO 2

/*
    *\class CapteurGL
    * \brief IMU Viewer : Classe permettant d'afficher un capteur en OpenGL avec un comportement dynamique
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class CapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
        /**
            * \fn CapteurGL
            * \brief  Constructeur
            * \param parent Parent (QWidget *)
        */
        explicit CapteurGL(QWidget *parent = 0);
        /**
            * \fn initializeGL
            * \brief  Initialise le moteur OpenGL
            * \param parent Parent (QWidget *)
        */
        void initializeGL();
        /**
            * \fn resizeGL
            * \brief Appelée sur un évènement de redimensionnement de fenêtre
            * \param w Largeur (int)
            * \param h Hauteur (int)
        */
        void resizeGL(int w, int h);
        /**
            * \fn paintGL
            * \brief Callback d'affichage OpenGL
        */
        void paintGL();
        /**
            * \fn setCentrale
            * \brief Affecte une centrale au CapteurGL
            * \param uneCentrale Centrale à setter (Centrale*)
        */
        void setCentrale(Centrale *);
        /**
            * \fn setComportement
            * \brief Affecte un comportement au capteur
            * \param unComp nouveau comportement : les valeurs possibles sont COMP_ACC COMP_GYRO, possibilité de mettre les deux avec COMP_ACC|COMP_GYRO(int)
        */
        void setComportement(int);

    public slots:
        /**
            * \fn paintGL
            * \brief Callback de mise à jour OpenGL
        */
        void updateGL();

    private:
        /**
            * \fn afficheRepereRVB
            * \brief Affiche le repère RVB mobile
        */
        void afficheRepereRVB();
        /**
            * \fn accAfficheRepereBlanc
            * \brief Affiche le repère blanc fixe
        */
        void accAfficheRepereBlanc();
        /**
            \var Centrale*
            \brief Pointeur sur une centrale
        */
        Centrale* _pIMU;
        /**
            \var _comportement
            \brief Comportement dynamique de la centrale
        */
        int _comportement;
};

#endif
