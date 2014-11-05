#ifndef GYROGRAPH_H
#define GYROGRAPH_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>
#include<GL/glut.h>

class gyrograph : public QGLWidget
{
    Q_OBJECT
public:
    explicit gyrograph(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent *keyEvent );
    void timerEvent(QTimerEvent);
    void setCentrale(Centrale *);
    void afficheGrille();

public slots:
    void updateGL();

private:
    Centrale* _pIMU;


};

#endif // GYROGRAPH_H
