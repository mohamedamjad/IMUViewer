#include "principalcapteurgl.h"

PrincipalCapteurGL::PrincipalCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
    _coinInferieur.append(0);
    _coinInferieur.append(0);
    _coinInferieur.append(0);
    _coinSuperieur.append(0);
    _coinSuperieur.append(0);
    _coinSuperieur.append(0);
    /**
        *\fn CCamera
        *\brief Constructor
        *\param float anEyeX X initial coordinate for the camera
        *\param float anEyeY Y initial coordinate for the camera
        *\param float anEyeZ Z initial coordinate for the camera
        *\param float anUpX X up vector
        *\param float anUpY Y up vector
        *\param float anUpZ Z up vector
        *\param float aSpeed_cam Distance browsed by the camera, when it will move
        *\param float aRota_cam Angle browsed by the camera, when it will rotate
        *\param float aTeta Initial horizontal orientation
        *\param float aPhi Initial vertical orientation
    */
    _pCamera = new CCamera(-50.0,50.0,-3.0,
                           0.0,0.0,1.0,
                           1.0,0.1,0.2,0.05);
}

void PrincipalCapteurGL::initializeGL()
{
     glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

}
void PrincipalCapteurGL::resizeGL(int w, int h)
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
   gluPerspective(60,ratio,1,10000);
   // Get Back to the Modelview
   glMatrixMode(GL_MODELVIEW);
}

void PrincipalCapteurGL::paintGL()
{
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();

    _pCamera->play();
    afficheCentrale();
    afficheFenetreEvolution();
}

void PrincipalCapteurGL::afficheFenetreEvolution()
{

    /*glBegin(GL_QUAD_STRIP);
        // Face 1
        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinInferieur[2]);
        // Face 2
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinSuperieur[2]);
        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinSuperieur[2]);
        // Face 3
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinSuperieur[2]);
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinSuperieur[2]);
        // Face 4
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinInferieur[2]);
    glEnd();*/
}

 void PrincipalCapteurGL::afficheCentrale()
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    glPushMatrix();

        glTranslatef(_pIMU->_position[0],1,_pIMU->_position[2]);

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
            // Dessiner le cylindre
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
            gluCylinder (quadratic,0.05,0.05,1.5,20,20);
            // Dessiner le sens des Y
            glColor3f(0.5,0.5,0.5);
            glTranslatef (0.0f,0.0f,1.5f);
            glutSolidCone (0.1f,0.2,20,20);
        glPopMatrix ();
    glPopMatrix();
}

 void PrincipalCapteurGL::setFenetreEvolutionCentrale(QVector<double> unCoinInf,QVector<double> unCoinSup)
 {
    _coinInferieur = unCoinInf;
    _coinSuperieur = unCoinSup;

    _largeurFenetre    = _coinSuperieur[0] - _coinInferieur[0];
    _profondeurFenetre = _coinSuperieur[1] - _coinInferieur[1];
    _hauteurFenetre    = _coinSuperieur[2] - _coinInferieur[2];

    std::cout<<"coin inférieur" << _coinInferieur[0] << " " << _coinInferieur[1] << " " << _coinInferieur[2]<< std::endl;
    std::cout<<"coin supérieur" << _coinSuperieur[0] << " " << _coinSuperieur[1] << " " << _coinSuperieur[2]<< std::endl;
    std::cout<<"largeur fenetre = " << _largeurFenetre<< "profondeur fenetre = " << _profondeurFenetre<< "hauteur fenetre = " << _hauteurFenetre<< std::endl;
 }


void PrincipalCapteurGL::mousePressEvent(QMouseEvent *event){std::cout<<"Clic principal"<<std::endl;}
void PrincipalCapteurGL::mouseMoveEvent(QMouseEvent *event){}


void PrincipalCapteurGL::keyPressEvent( QKeyEvent *keyEvent )
{

    switch (keyEvent->key())
    {

        case 'a':// Classical camera mode
        case 'A':// Classical camera mode
            _pCamera->goBack();
        break;
        case 'z':// Classical camera mode
        case 'Z':// Classical camera mode
            _pCamera->go();
        break;

        case '6':
            _pCamera->lookAtRight();
        break;
        case '4':
            _pCamera->lookAtLeft();
        break;
        case '8':
            _pCamera->lookAtTop();
        break;
        case '2':
            _pCamera->lookAtBottom();
        break;

        case 27 :
        case 'q':
            exit(0);
        break;
    }

    updateGL();

}

void PrincipalCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}


void PrincipalCapteurGL::updateGL()
{

    QGLWidget::updateGL();
}

void PrincipalCapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
