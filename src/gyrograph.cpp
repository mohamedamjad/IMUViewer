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
int i;
int tmp=0;

void gyrograph::afficheSignal()
{


    // Set the camera
    // glMatrixMode(GL_MODELVIEW);
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
     glLoadIdentity();
        gluLookAt( -buffer*0.4, 30.0f, 0.0f,
              -buffer*0.4, 0.0f, 0.0f,
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

 if(buffer%100==0)
 {
     tmp=+90;
 }
 for(i=buffer-220;i<buffer;i++)
 {
     glVertex3f(-i*0.40,0.0,_pTDB->get_signaux ()[this->signalIndex]->normalizeVector (_pTDB->get_signaux ()[this->signalIndex]->getSignal (i)));
 }

 if (_pTDB->get_signaux ()[this->signalIndex]->getTaille ()==buffer)
{
     buffer=0;
     glColor3f(1,0,0);
     glBegin(GL_LINES);
     glVertex3f (0.0,0.0,-20.0);
     glVertex3f(0.0,0.0,20.0);
     glEnd();
 }
 glEnd();
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
    //this->afficheSignal ();
}

void gyrograph::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}

void gyrograph::setTableauDeBord(TableauDeBord *tdb)
{
    _pTDB=tdb;
}

void gyrograph::setsignalIndex(int i)
{
    this->signalIndex=i;

}
