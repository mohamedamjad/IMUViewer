#include "acccapteurgl.h"

AccCapteurGL::AccCapteurGL(QWidget *parent) :
    CapteurGL(parent)
{
}

void AccCapteurGL::initializeGL()
{}
void AccCapteurGL::resizeGL(int width, int height){}
void AccCapteurGL::paintGL(){}
void AccCapteurGL::mousePressEvent(QMouseEvent *event){}
void AccCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void AccCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void AccCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



