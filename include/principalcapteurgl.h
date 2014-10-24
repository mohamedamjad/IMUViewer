 
#ifndef PRINCIPALGLWIDGET_H
#define PRINCIPALGLWIDGET_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>
#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <iostream>

class PrincipalCapteurGL : virtual public CapteurGL
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
};

#endif
