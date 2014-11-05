 
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

class PrincipalCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
         explicit PrincipalCapteurGL(QWidget *parent = 0);

        void initializeGL();
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
};

#endif
