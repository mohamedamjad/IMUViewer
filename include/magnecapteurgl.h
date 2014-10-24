 
#ifndef MAGNEGLWIDGET_H
#define MAGNEGLWIDGET_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>

class MagneCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
         explicit MagneCapteurGL(QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent *keyEvent );
    void timerEvent(QTimerEvent);

};

#endif
