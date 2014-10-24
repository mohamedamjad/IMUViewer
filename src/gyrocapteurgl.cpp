#include "gyrocapteurgl.h"

GyroCapteurGL::GyroCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
}



void GyroCapteurGL::initializeGL()
{}
void GyroCapteurGL::resizeGL(int width, int height){}
void GyroCapteurGL::paintGL(){}
void GyroCapteurGL::mousePressEvent(QMouseEvent *event){}
void GyroCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void GyroCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void GyroCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



