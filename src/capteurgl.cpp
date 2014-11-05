#include "capteurgl.h"

CapteurGL::CapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
}



void CapteurGL::setCentrale(Centrale* unPCentrale)
{
    _centrale = unPCentrale;
}


void CapteurGL::initializeGL ()
{
    glClearColor(0,1,0.5,0.1);

}

void CapteurGL::paintGL ()
{
    std::cout<<"Capteur gl paint"<<std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}


void CapteurGL::resizeGL(int width, int height){}

void CapteurGL::mousePressEvent(QMouseEvent *event){std::cout<<"Clic capteur gl"<<std::endl;}
void CapteurGL::mouseMoveEvent(QMouseEvent *event){}
void CapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}
void CapteurGL::timerEvent(QTimerEvent){}
