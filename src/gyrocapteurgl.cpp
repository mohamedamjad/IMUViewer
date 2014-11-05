#include "gyrocapteurgl.h"
#include <iostream>

using namespace std;

GyroCapteurGL::GyroCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
}



void GyroCapteurGL::initializeGL()

{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

void GyroCapteurGL::resizeGL(int w, int h)
{
    if (h == 0)
   h = 1;
   float ratio = w * 1.0 / h;
   // Use the Projection Matrix
   glMatrixMode(GL_PROJECTION);
   // Reset Matrix
   glLoadIdentity();
   // Set the viewport to be the entire window
   glViewport(0, 0, w, h);
   // Set the correct perspective.
   gluPerspective(45,ratio,1,100);
   // Get Back to the Modelview
   glMatrixMode(GL_MODELVIEW);
}


void GyroCapteurGL::afficheRepereFixe()
{
    GLUquadricObj *quadratic;
   quadratic = gluNewQuadric();
   // Clear Color and Depth Buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Reset transformations
   glLoadIdentity();
   // Set the camera
   gluLookAt( -2.0f, 2.0f, -1.33f,
   0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f);
   // Dessiner le centre du repère
   glutWireSphere (0.05f,20,20);
   glPushMatrix ();
   // Dessiner l'axe des X
   glColor3f(0.5,0.5,0.5);
   glTranslatef (0.05f,0.0f,0.0f);
   // glRotatef (90,0.0,0.0,0.0);
   glRotatef (90,0.0,1.0,0.0);
   gluCylinder (quadratic,0.02,0.02,1.5,20,20);
   // Dessiner le sens des X
   glColor3f(0.5,0.5,0.5);
   glTranslatef (0.0f,0.0f,1.5f);
   glutSolidCone (0.1f,0.2,20,20);
   glPopMatrix ();
   glPushMatrix ();
   // Dessiner l'axe des Z
   glColor3f(0.5,0.5,0.5);
   gluCylinder (quadratic,0.02,0.02,1.5,20,20);
   // Dessiner le sens des Z
   glColor3f(0.5,0.5,0.5);
   glTranslatef (0.0f,0.0f,1.5f);
   glutSolidCone (0.1f,0.2,20,20);
   glPopMatrix ();
   glPushMatrix ();
   // Dessiner l'axe des Y
   glColor3f(0.5,0.5,0.5);
   glTranslatef (0.0f,-0.05f,0.0f);
   glRotatef (90,1.0,0.0,0.0);
   // glRotatef (90,0.0,1.0,0.0);
   gluCylinder (quadratic,0.02,0.02,1.5,20,20);
   // Dessiner le sens des Y
   glColor3f(0.5,0.5,0.5);
   glTranslatef (0.0f,0.0f,1.5f);
   glutSolidCone (0.1f,0.2,20,20);
   glPopMatrix ();

   delete quadratic;

}


void GyroCapteurGL::afficheRepereMobile()
{
    GLUquadricObj *quadratic;
   quadratic = gluNewQuadric();
   // Clear Color and Depth Buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Reset transformations
   glLoadIdentity();
   // Set the camera
   gluLookAt( -2.0f, 2.0f, -1.33f,
   0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f);
   glPushMatrix ();

       glRotatef (_pIMU->_orientation[0]*180.0/M_PI,1.0,0.0,0.0);
       glRotatef (_pIMU->_orientation[1]*180.0/M_PI,0.0,1.0,0.0);
       glRotatef (_pIMU->_orientation[2]*180.0/M_PI,0.0,0.0,1.0);

       // Dessiner le centre du repère
       glutWireSphere (0.05f,20,20);
       glPushMatrix ();
           // Dessiner l'axe des X
           glColor3f(1.0,0.0,0.0);
           glTranslatef (0.05f,0.0f,0.0f);
           glRotatef (90,0.0,1.0,0.0);
           gluCylinder (quadratic,0.05,0.05,1.5,20,20);
           // Dessiner le sens des X
           glColor3f(0.5,0.5,0.5);
           glTranslatef (0.0f,0.0f,1.5f);
           glutSolidCone (0.1f,0.2,20,20);
       glPopMatrix ();

       glPushMatrix ();
           // Dessiner l'axe des Z
           glColor3f(0.0,0.0,1.0);
           gluCylinder (quadratic,0.05,0.05,1.5,20,20);
           // Dessiner le sens des Z
           glColor3f(0.5,0.5,0.5);
           glTranslatef (0.0f,0.0f,1.5f);
           glutSolidCone (0.1f,0.2,20,20);
       glPopMatrix ();

       glPushMatrix ();
           // Dessiner l'axe des Y
           glColor3f(0.0,1.0,0.0);
           glTranslatef (0.0f,-0.05f,0.0f);
           glRotatef (90,1.0,0.0,0.0);
           // glRotatef (90,0.0,1.0,0.0);
           gluCylinder (quadratic,0.05,0.05,1.5,20,20);
           // Dessiner le sens des Y
           glColor3f(0.5,0.5,0.5);
           glTranslatef (0.0f,0.0f,1.5f);
           glutSolidCone (0.1f,0.2,20,20);
       glPopMatrix ();

   glPopMatrix ();

   delete quadratic;
}

void GyroCapteurGL::paintGL()
{

    // Afficher le repère mobile
    afficheRepereMobile ();

    // Afficher le repère fixe
    // afficheRepereFixe();

}

void GyroCapteurGL::mousePressEvent(QMouseEvent *event){}
void GyroCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void GyroCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void GyroCapteurGL::timerEvent(QTimerEvent event)
{
    //updateGL ();
}


void GyroCapteurGL::updateGL()
{
    QGLWidget::updateGL ();
}

void GyroCapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
