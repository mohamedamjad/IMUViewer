
#ifndef ACCGLWIDGET_H
#define ACCGLWIDGET_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>
#include <GL/glut.h>
#include "centrale.h"
#include <cmath>

#define longueurMaxAxe 1.5
#define valMaxAccArbitraire 30.0

class AccCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
         explicit AccCapteurGL(QWidget *parent = 0);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent( QKeyEvent *keyEvent );
        void timerEvent(QTimerEvent);

        void afficheRepereMobile();
        void afficheRepereFixe();

        void setCentrale(Centrale *);

    public slots:
        void updateGL();

    private:
        Centrale* _pIMU;
};

#endif
