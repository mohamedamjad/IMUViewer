#include "principalcapteurgl.h"

PrincipalCapteurGL::PrincipalCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
    std::cout<<"Constructeur principal"<<std::endl;
}

void PrincipalCapteurGL::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3i(0,0,0);
        glVertex3i(1,1,1);
    glEnd();

}
void PrincipalCapteurGL::resizeGL(int width, int height){}

void PrincipalCapteurGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void PrincipalCapteurGL::mousePressEvent(QMouseEvent *event){std::cout<<"Clic principal"<<std::endl;}
void PrincipalCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void PrincipalCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void PrincipalCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



