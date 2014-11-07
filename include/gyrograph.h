#ifndef GYROGRAPH_H
#define GYROGRAPH_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>
#include<GL/glut.h>
#include <QVector>
#include "signal.h"
#include "tableaudebord.h"

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
    void afficheSignal();
    void lookat();
    void setsignalIndex(int i);

public slots:
    void updateGL();

private:
    Centrale* _pIMU;
    int signalIndex;

};

#endif // GYROGRAPH_H
