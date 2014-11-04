#include "acccapteurgl.h"

AccCapteurGL::AccCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

void AccCapteurGL::initializeGL()
{



}
void AccCapteurGL::resizeGL(int w, int h)
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


void AccCapteurGL::paintGL()

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
   //glRotatef(angle, 0.0f, 1.0f, 0.0f);
   // Dessiner le centre du repère
   glutWireSphere (0.05f,20,20);
   glPushMatrix ();
   // Dessiner l'axe des X
   glColor3f(1.0,0.0,0.0);
   glTranslatef (0.05f,0.0f,0.0f);
   // glRotatef (90,0.0,0.0,0.0);
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
   // glTranslatef (0.0f,0.0f,0.0f);
   // glRotatef (90,1.0,0.0,0.0);
   // glRotatef (90,0.0,1.0,0.0);
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

}


void AccCapteurGL::mousePressEvent(QMouseEvent *event){}
void AccCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void AccCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void AccCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



