#include "acccapteurgl.h"

AccCapteurGL::AccCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
}

void AccCapteurGL::initializeGL()
{}
void AccCapteurGL::resizeGL(int width, int height){}

void AccCapteurGL::paintGL()

{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
std::cout <<"acc dans le capteur !!!!!!!!!!!!!= " << _pIMU->_acc[0]<< std::endl;
}


void AccCapteurGL::mousePressEvent(QMouseEvent *event){}
void AccCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void AccCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void AccCapteurGL::timerEvent(QTimerEvent event)
{
    std::cout<<"timer event"<<std::endl;
    updateGL();
}



void AccCapteurGL::updateGL()
{

    paintGL();
}

void AccCapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
