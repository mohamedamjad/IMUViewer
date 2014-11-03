#include "gyrocapteurgl.h"

GyroCapteurGL::GyroCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
}



void GyroCapteurGL::initializeGL()
{}
void GyroCapteurGL::resizeGL(int width, int height){}
void GyroCapteurGL::paintGL(){std::cout <<"gyro"<<std::endl;}
void GyroCapteurGL::mousePressEvent(QMouseEvent *event){}
void GyroCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void GyroCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void GyroCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}




void GyroCapteurGL::updateGL()
{

    paintGL();
}

void GyroCapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
