#include "gyrograph.h"
#include <iostream>
#include "math.h"

using namespace std;

gyrograph::gyrograph(QWidget *parent) :
    QGLWidget(parent)
{

}


void gyrograph::initializeGL()

{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // Afficher la grille
    // afficheGrille();

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

int buffer=0;
int tmp=0;

void gyrograph::afficheSignal()
{
    TableauDeBord _tdb;

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
     glLoadIdentity();
    // Set the camera
    // glMatrixMode(GL_MODELVIEW);

        gluLookAt( -buffer*0.3, 30.0f, 0.0f,
              -buffer*0.3, 0.0f, 0.0f,
               0.0f, 0.0f, 1.0f);

     buffer++;
    // Ligne de référence (rouge)
    glColor3f (1,0,0);
    glBegin (GL_LINES);
    glVertex3f (-2000.0,0.0,0.0);
    glVertex3f (2000,0.0,0.0);
    glVertex3f (0.0,0.0,-20.0);
    glVertex3f(0.0,0.0,20.0);
    glEnd();
    // Dessiner un graphe
    glColor3f (0.0,1.0,0.0);
    glBegin(GL_LINE_STRIP);

    for(int i=0;i<buffer;i++)
    {
        glVertex3f(-i*0.30,0.0,_tdb.get_signaux ()[this->signalIndex]->normalizeVector (_tdb.get_signaux ()[this->signalIndex]->getSignal (i)));
    }

    glEnd();

}


void gyrograph::lookat()
{


}

void gyrograph::paintGL()
{

    afficheSignal ();
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

void gyrograph::setsignalIndex(int i)
{
    this->signalIndex=i;
}
