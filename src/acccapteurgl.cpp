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

}


void AccCapteurGL::mousePressEvent(QMouseEvent *event){}
void AccCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void AccCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void AccCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



