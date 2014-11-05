#include "gyrograph.h"

gyrograph::gyrograph(QWidget *parent) :
    QGLWidget(parent)
{
}


void gyrograph::initializeGL()

{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}

void gyrograph::resizeGL(int w, int h)
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


void gyrograph::afficheGrille()
{

   // Clear Color and Depth Buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Reset transformations
    glLoadIdentity();
   // Set the camera
   // glMatrixMode(GL_MODELVIEW);
   gluLookAt( 0.0f, 30.0f, 0.0f,
   0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f);
   // Ligne de référence (rouge)
   glColor3f (1,0,0);
   glBegin (GL_LINES);
   glVertex3f (-2000.0,0.0,0.0);
   glVertex3f (2000,0.0,0.0);
   glVertex3f (0.0,0.0,-180.0);
   glVertex3f(0.0,0.0,180.0);
   glEnd();

   // Dessiner un graphe
   glColor3f (0.0,1.0,0.0);
   glBegin(GL_LINE_STRIP);
   glVertex3f (0.0,0.0,0.0);
   glVertex3f (1.0,0.0,0.25);
   glVertex3f (2.0,0.0,0.1);
   glVertex3f (3.0,0.0,0.6);
   glVertex3f (4.0,0.0,0.6);
   glVertex3f (5.0,0.0,0.6);
   glVertex3f (5.0,0.0,0.8);
   glVertex3f (6.0,0.0,1.0);
   glVertex3f (7.0,0.0,1.0);
   glVertex3f (8.0,0.0,1.0);
   glVertex3f (9.0,0.0,1.0);

   glEnd();
}

void gyrograph::paintGL()
{

    // Afficher la grille
    afficheGrille();

}

void gyrograph::mousePressEvent(QMouseEvent *event){}
void gyrograph::mouseMoveEvent(QMouseEvent *event){}
void gyrograph::keyPressEvent( QKeyEvent *keyEvent ){}


void gyrograph::timerEvent(QTimerEvent event)
{
    //updateGL ();

}


void gyrograph::updateGL()
{
    QGLWidget::updateGL ();
}

void gyrograph::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
