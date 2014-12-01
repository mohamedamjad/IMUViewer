/*
    * \class PrincipalCapteurGL
    * \brief Classe qui hérite de QGLWidget et qui affiche la centrale dans l'espace ( grand widget principal)
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
#ifndef PRINCIPALGLWIDGET_H
#define PRINCIPALGLWIDGET_H

#include <QGLWidget>
#include <QTimerEvent>
#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <iostream>
#include<GL/glut.h>
#include "centrale.h"
#include "CCamera.h"
#include"tableaudebord.h"

class PrincipalCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
    /**
          * \fn PrincipalCapteurGL
          * \brief Constructeur de PrincipalCapteurGL, cette classe hérite de QGLWidget
          * \param parent
          */
         explicit PrincipalCapteurGL(QWidget *parent = 0);
    /**
         * \fn initializeGL
         *  \brief fonction qui initialise OpenGL dans le PrincipalCapteurGL
         */
        void initializeGL();
        /**
         * \fn resizeGL
         * \brief fonction qui permet de redimensionner le PrincipalCapteurGL
         * \param w : largeur du QGLWidget
         * \param h : hauteur du QGLWidget
         */
        void resizeGL(int w, int h);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent( QKeyEvent *keyEvent );
        void timerEvent(QTimerEvent);
        void setCentrale(Centrale *);


        void setFenetreEvolutionCentrale(QVector<double>,QVector<double>);

    public slots:
        void updateGL();
        void setProjection(int);
    private:
        Centrale* _pIMU;

        // Coordonnées du point inférieur et supérieur de la fenetre d'évolution de la centrale
        QVector<double> _coinInferieur;
        QVector<double> _coinSuperieur;
        double _hauteurFenetre;// amplitude Z
        double _largeurFenetre;// amplitude X
        double _profondeurFenetre;// amplitude Y
        CCamera *_pCamera;

        bool _cameraSuitCentrale  = false;

        void afficheSol();
        void afficheCentrale();
        void afficheTrajectoireCentrale();
        void suitCentrale();
        void afficheRepereSol();
        void afficheCubEvolution();

        void setProjectionX();
        void setProjectionY();
        void setProjectionZ();
        void setProjection3D();


};

#endif
