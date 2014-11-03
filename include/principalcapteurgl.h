 
#ifndef PRINCIPALGLWIDGET_H
#define PRINCIPALGLWIDGET_H

#include <QGLWidget>
#include <QTimerEvent>
#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <iostream>
#include "centrale.h"

class PrincipalCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
         explicit PrincipalCapteurGL(QWidget *parent = 0);

        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent( QKeyEvent *keyEvent );
        void timerEvent(QTimerEvent);
        void setCentrale(Centrale *);

    public slots:
        void updateGL();

    private:
        Centrale* _pIMU;
};

#endif
