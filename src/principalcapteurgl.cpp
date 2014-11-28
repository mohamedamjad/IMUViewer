#include "principalcapteurgl.h"
#include "math.h"

using namespace std;

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
    _pCamera = new CCamera(-50.0,50.0,0.0,
                           0.0,0.0,1.0,
                           20.0,0.1,-0.0,-0.0);
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
   gluPerspective(30,ratio,1,100);
   // Get Back to the Modelview
   glMatrixMode(GL_MODELVIEW);
}

void PrincipalCapteurGL::paintGL()
{
    // Distance entre les deux coins Sup et Inf
    double distInfSup=sqrt ((_coinInferieur[0]-_coinSuperieur[0])*(_coinInferieur[0]-_coinSuperieur[0])+(_coinInferieur[1]-_coinSuperieur[1])*(_coinInferieur[1]-_coinSuperieur[1])+(_coinInferieur[2]-_coinInferieur[2])*(_coinInferieur[2]-_coinInferieur[2]));

    //distance de la camera pour voir tout le cube de l'évolution
    double distCam;

    distCam=(distInfSup/2)/tan(15*3.1415/180.0);

    QVector<double> eye(3);
    eye.append (0);
    eye[0]=distCam;
    eye[1]=0;
    eye[2]=0;
    _pCamera->setEye (eye);

    // Centre du cube d'évolution
    QVector<double> centreCube(3);
    centreCube.append (0);
    centreCube[0]=(_coinSuperieur[0]+_coinInferieur[0])/2;
    centreCube[1]=(_coinSuperieur[1]+_coinInferieur[1])/2;
    centreCube[2]=(_coinSuperieur[2]+_coinInferieur[2])/2;

    _pCamera->setCenter (centreCube);

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
    if (_cameraSuitCentrale == true)//Mode suivi de centrale
       suitCentrale();

    _pCamera->play();
    afficheRepereSol();
   // afficheSol();
    afficheCentrale();
    afficheTrajectoireCentrale();
    afficheCubEvolution();

}

void PrincipalCapteurGL::afficheCubEvolution() {

     glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_QUADS);
        glColor3f(0.0,1.0,0.0);

        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinInferieur[2]);

        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinSuperieur[2]);
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinSuperieur[2]);
        glVertex3f(_coinSuperieur[0],_coinInferieur[1],_coinInferieur[2]);
        glColor3f(0.0,0.0,1.0);

        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinSuperieur[2]);
        glVertex3f(_coinSuperieur[0],_coinSuperieur[1],_coinSuperieur[2]);

        glColor3f(1.0,0.0,0.0);

        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinSuperieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinSuperieur[2]);
        glVertex3f(_coinInferieur[0],_coinSuperieur[1],_coinInferieur[2]);

    glEnd ();
}

void PrincipalCapteurGL::afficheRepereSol()
{

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    glColor3f(1.0,1.0,1.0);
    // Dessiner le centre du repère
    glutWireSphere (0.05f,20,20);

    glPushMatrix ();
        // Axe des X
        glColor3f(1.0,0.0,0.0);
        glRasterPos3f(3,0,0);
        glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_10, ((int)'X') );
        glTranslatef (0.075f,0.0f,0.0f);
        glRotatef (90,0.0,1.0,0.0);
        gluCylinder (quadratic,0.025,0.025,2,20,20);
        // Sens des X
        glTranslatef (0.0f,0.0f,2.0);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();

    glPushMatrix ();
        // Axe des Y
        glColor3f(0.0,1.0,0.0);
        glRasterPos3f(0,-3,0);
        glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_10, ((int)'Y') );
        glTranslatef (0.0f,0.075f,0.0f);
        glRotatef (90,1.0,0.0,0.0);
        gluCylinder (quadratic,0.025,0.025,2,20,20);
        // Sens des Y
        glTranslatef (0.0f,0.0f,2.0);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();

    glPushMatrix ();
        // Axe des Z
        glColor3f(0.0,0.0,1.0);
        glRasterPos3f(0,0,3);
        glutBitmapCharacter ( GLUT_BITMAP_HELVETICA_10, ((int)'Z') );
        gluCylinder (quadratic,0.025,0.025,2,20,20);
        // Sens des Z
        glTranslatef (0.0f,0.0f,2);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();


}

void PrincipalCapteurGL::suitCentrale()
{

    if (_pIMU->_trajectoire.size()>29)
    {
        QVector<double> eye = _pIMU->_trajectoire.at(_pIMU->_trajectoire.size()-30);
        eye[0]+=10;eye[1]+=10;eye[2]+=10;// Leger decalage pour voir la trajectoire de la centrale
        _pCamera->setEye(eye);
        _pCamera->setCenter(_pIMU->_position);
    }
}

// Affiche la trajectoire de la centrale
void PrincipalCapteurGL::afficheTrajectoireCentrale()
{
    //_pCamera->setEye ();
    if (_pIMU->_trajectoire.size()>1)
    {
        glBegin(GL_LINE_STRIP);
            glColor3f(0.8,0.8,0.8);//gris
            glVertex3f(_pIMU->_trajectoire.at(0)[0],_pIMU->_trajectoire.at(0)[1],_pIMU->_trajectoire.at(0)[2]);

            for (int i=1;i<_pIMU->_trajectoire.size();i++)
            {
                glVertex3f(_pIMU->_trajectoire.at(i)[0],_pIMU->_trajectoire.at(i)[1],_pIMU->_trajectoire.at(i)[2]);
            }

        glEnd();
    }
}

void PrincipalCapteurGL::afficheSol()
{

    glBegin(GL_POLYGON);
        glColor3f(0.87,0.42,0.07);//citrouille
        glVertex3f(_coinInferieur[0],_coinInferieur[1],_coinInferieur[2]);
        glVertex3f(_coinInferieur[0],_coinInferieur[1]+_profondeurFenetre,_coinInferieur[2]);
        glVertex3f(_coinInferieur[0]+_largeurFenetre,_coinInferieur[1]+_profondeurFenetre,_coinInferieur[2]);
        glVertex3f(_coinInferieur[0]+_largeurFenetre,_coinInferieur[1],_coinInferieur[2]);
    glEnd();
}

 void PrincipalCapteurGL::afficheCentrale()
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    glPushMatrix();

        glTranslatef(_pIMU->_position[0],_pIMU->_position[1],_pIMU->_position[2]);

        glRotatef (_pIMU->_orientation[0]*180.0/M_PI,1.0,0.0,0.0);
        glRotatef (_pIMU->_orientation[1]*180.0/M_PI,0.0,1.0,0.0);
        glRotatef (_pIMU->_orientation[2]*180.0/M_PI,0.0,0.0,1.0);

        // Dessiner le centre du repère
        glutWireSphere (0.05f,20,20);

        glPushMatrix ();
            // Axe des X
            glColor3f(1.0,0.0,0.0);
            glTranslatef (0.05f,0.0f,0.0f);
            glRotatef (90,0.0,1.0,0.0);
            gluCylinder (quadratic,0.05,0.05,1.5,20,20);

            // Sens des X
            glColor3f(0.5,0.5,0.5);
            glTranslatef (0.0f,0.0f,1.5f);
            glutSolidCone (0.1f,0.2,20,20);
        glPopMatrix ();

        glPushMatrix ();
            // Axe des Z
            glColor3f(0.0,0.0,1.0);
            gluCylinder (quadratic,0.05,0.05,1.5,20,20);
            // Sens des Z
            glColor3f(0.5,0.5,0.5);
            glTranslatef (0.0f,0.0f,1.5f);
            glutSolidCone (0.1f,0.2,20,20);
        glPopMatrix ();

        glPushMatrix ();
            // Axe des Y
            glColor3f(0.0,1.0,0.0);
            glTranslatef (0.0f,-0.075f,0.0f);
            glRotatef (90,1.0,0.0,0.0);
            gluCylinder (quadratic,0.05,0.05,1.5,20,20);
            // Sens des Y
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

        case 'S':
        case 's':
            _cameraSuitCentrale = (_cameraSuitCentrale) ? false : true;
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

// Slot pour projeté suivant X lorsque le combobox change
/*void PrincipalCapteurGL::setProjectionX()
{

    // Distance entre les deux coins Sup et Inf
    double distInfSup=sqrt ((_coinInferieur[0]-_coinSuperieur[0])*(_coinInferieur[0]-_coinSuperieur[0])+(_coinInferieur[1]-_coinSuperieur[1])*(_coinInferieur[1]-_coinSuperieur[1])+(_coinInferieur[2]-_coinInferieur[2])*(_coinInferieur[2]-_coinInferieur[2]));

    //distance de la camera pour voir tout le cube de l'évolution
    double distCam;

    distCam=(distInfSup/2)/tan(15*3.1415/180.0);

    QVector<double> eye(3);
    eye.append (0);
    eye[0]=distCam;
    eye[1]=0;
    eye[2]=0;
    _pCamera->setEye (eye);

}

// Slot pour projeté suivant Y lorsque le combobox change
void PrincipalCapteurGL::setProjectionY()
{

}

// Slot pour projeté suivant Y lorsque le combobox change
void PrincipalCapteurGL::setProjectionZ()
{

}*/
