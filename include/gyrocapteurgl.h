 
#ifndef GYROGLWIDGET_H
#define GYROGLWIDGET_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>

class GyroCapteurGL : virtual public CapteurGL
{
    Q_OBJECT
    public:
         explicit GyroCapteurGL(QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent *keyEvent );
    void timerEvent(QTimerEvent);
};

#endif
