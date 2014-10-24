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
