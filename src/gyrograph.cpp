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
        gluLookAt( -_pTDB->getiCourant ()*0.4, 30.0f, 0.0f,
              -_pTDB->getiCourant ()*0.4, 0.0f, 0.0f,
               0.0f, 0.0f, 1.0f);

     //buffer++;

     // Ligne de référence (rouge)
 glColor3f (1,0,0);
 glBegin (GL_LINES);
 glVertex3f (-60*_pTDB->getiCourant (),0.0,0.0);
 glVertex3f (60*_pTDB->getiCourant (),0.0,0.0);
 glVertex3f (0.0,0.0,-20.0);
 glVertex3f(0.0,0.0,20.0);
 glEnd();
 // Dessiner un graphe
 glColor3f (0.0,1.0,0.0);
 glBegin(GL_LINE_STRIP);

 if(_pTDB->getiCourant ()%100==0)
 {
     tmp=+90;
 }
 for(i=_pTDB->getiCourant ()-220;i<_pTDB->getiCourant ();i++)
 {
     glVertex3f(-i*0.40,0.0,_pTDB->get_signaux ()[this->signalIndex]->normalizeVector (_pTDB->get_signaux ()[this->signalIndex]->getSignal (i)));

 }
 glEnd();
}

void gyrograph::paintGL()
{

    afficheSignal ();
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

void gyrograph::setmaxLabel(QLabel *maxlabel)
{
    _maxLabel=maxlabel;
}

void gyrograph::setminLabel(QLabel *minlabel)
{
    _minLabel=minlabel;
}
 int gyrograph::getsignalIndex ()
 {
     return this->signalIndex;
 }
 TableauDeBord* gyrograph::getpTDB()
 {
     return _pTDB;
 }

void gyrograph::updateLabel()
 {
    this->_maxLabel->setNum (this->_pTDB->get_signaux ()[this->getsignalIndex ()]->getMaxSignal ());
    this->_minLabel->setNum (-this->_pTDB->get_signaux ()[this->getsignalIndex ()]->getMaxSignal ());

 }
