#include "principalcapteurgl.h"

PrincipalCapteurGL::PrincipalCapteurGL(QWidget *parent) :
    CapteurGL(parent)
{
    std::cout<<"Constructeur principal"<<std::endl;
}

void PrincipalCapteurGL::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}
void PrincipalCapteurGL::resizeGL(int width, int height){}

void PrincipalCapteurGL::paintGL()
{
    std::cout<<"Princiapl gl paint"<<std::endl;

}


void PrincipalCapteurGL::mousePressEvent(QMouseEvent *event){std::cout<<"Clic principal"<<std::endl;}
void PrincipalCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void PrincipalCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void PrincipalCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



