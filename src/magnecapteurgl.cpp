#include "magnecapteurgl.h"

MagneCapteurGL::MagneCapteurGL(QWidget *parent) :
    CapteurGL(parent)
{
}





void MagneCapteurGL::initializeGL()
{}
void MagneCapteurGL::resizeGL(int width, int height){}
void MagneCapteurGL::paintGL(){}
void MagneCapteurGL::mousePressEvent(QMouseEvent *event){}
void MagneCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void MagneCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void MagneCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}

