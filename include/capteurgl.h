
#ifndef CAPTEURGLWIDGET_H
#define CAPTEURGLWIDGET_H

#include <QGLWidget>
#include <QTimerEvent>
#include <GL/glut.h>
#include "centrale.h"
#include <cmath>

#define longueurMaxAxe 1.5
#define valMaxAccArbitraire 30.0

#define COMP_ACC 1
#define COMP_GYRO 2

class CapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
         explicit CapteurGL(QWidget *parent = 0);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent( QKeyEvent *keyEvent );
        void timerEvent(QTimerEvent);

        void setCentrale(Centrale *);
        void setComportement(int);

    public slots:
        void updateGL();

    private:
        Centrale* _pIMU;
        void afficheRepereRVB();
        void accAfficheRepereBlanc();
        int _comportement;
};

#endif
