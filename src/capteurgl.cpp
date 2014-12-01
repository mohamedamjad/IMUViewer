#include "capteurgl.h"

CapteurGL::CapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}
void CapteurGL::initializeGL()

{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}



void CapteurGL::resizeGL(int w, int h)
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



void CapteurGL::paintGL()
{
   // Clear Color and Depth Buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Reset transformations
   glLoadIdentity();
   // Set the camera
   gluLookAt( -2.0f, 2.0f, -1.33f,
   0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f);

    // Affichage du repere fixe pour un comportement d'accéléromètre
    if ((_comportement & COMP_ACC) == COMP_ACC)
        accAfficheRepereBlanc();

   // Affichage du repere mobile
    afficheRepereRVB();

}

void CapteurGL::setComportement(int unComp)
{
    _comportement = unComp;
}

void CapteurGL::afficheRepereRVB()
{

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    // Déterminiation des coeffcients de longueurs des trois axes rvb
    double coefX,coefY,coefZ;
    if ((_comportement & COMP_ACC) == COMP_ACC)// Comportement d'accéléro
    {

        double absX = abs(_pIMU->_acc[0]);
        double absY = abs(_pIMU->_acc[1]);
        double absZ = abs(_pIMU->_acc[2]);
        coefX = (absX<valMaxAccArbitraire) ? absX/valMaxAccArbitraire : 1.0;
        coefY = (absY<valMaxAccArbitraire) ? absY/valMaxAccArbitraire : 1.0;
        coefZ = (absZ<valMaxAccArbitraire) ? absZ/valMaxAccArbitraire : 1.0;
    }
    else
    {
        coefX = 1;
        coefY = 1;
        coefZ = 1;
    }

    glPushMatrix ();
        if ((_comportement & COMP_GYRO) == COMP_GYRO)// Comportement de gyro : rotation autour des trois axes
        {
            glRotatef (_pIMU->_orientation[0]*180.0/M_PI,1.0,0.0,0.0);
            glRotatef (_pIMU->_orientation[1]*180.0/M_PI,0.0,1.0,0.0);
            glRotatef (_pIMU->_orientation[2]*180.0/M_PI,0.0,0.0,1.0);
        }
        // Dessiner le centre du repère
        glutWireSphere (0.05f,20,20);

        // Dessiner l'axe des X
        glPushMatrix ();
            glColor3f(1.0,0.0,0.0);
            glTranslatef (0.075f,0.0f,0.0f);

            // Si accélération X > 0 en comportement accelero ou comportement gyro
            if (((_pIMU->_acc[0]>0) && ((_comportement & COMP_ACC) == COMP_ACC)) || ((_comportement & COMP_GYRO) == COMP_GYRO))
                glRotatef (90,0.0,1.0,0.0);
            else glRotatef (-90,0.0,1.0,0.0);

            gluCylinder (quadratic,0.05,0.05,coefX*longueurMaxAxe,20,20);

            if ((_comportement & COMP_GYRO) == COMP_GYRO)// Comportement de gyro : dessiner le sens des X
            {
                glColor3f(0.5,0.5,0.5);
                glTranslatef (0.0f,0.0f,1.5f);
                glutSolidCone (0.1f,0.2,20,20);
            }
        glPopMatrix ();

        // Dessiner l'axe des Y
        glPushMatrix ();
            glColor3f(0.0,1.0,0.0);
            glTranslatef (0.0f,-0.05f,0.0f);

            // Si accélération Y > 0 en comportement accelero ou comportement gyro
            if (((_pIMU->_acc[1]>0) && ((_comportement & COMP_ACC) == COMP_ACC)) || ((_comportement & COMP_GYRO) == COMP_GYRO))
                glRotatef (90,1.0,0.0,0.0);
            else glRotatef (-90,1.0,0.0,0.0);

            gluCylinder (quadratic,0.05,0.05,coefY*longueurMaxAxe,20,20);

            if ((_comportement & COMP_GYRO) == COMP_GYRO)// Comportement de gyro : dessiner le sens des Y
            {
                glColor3f(0.5,0.5,0.5);
                glTranslatef (0.0f,0.0f,1.5f);
                glutSolidCone (0.1f,0.2,20,20);
            }
        glPopMatrix ();

        // Dessiner l'axe des Z
        glPushMatrix ();
            glColor3f(0.0,0.0,1.0);

            if ((_pIMU->_acc[2]>0) && ((_comportement & COMP_ACC) == COMP_ACC))
                glRotatef (180,1.0,0.0,0.0);

            gluCylinder (quadratic,0.05,0.05,coefZ*longueurMaxAxe,20,20);

            if ((_comportement & COMP_GYRO) == COMP_GYRO)// Comportement de gyro : dessiner le sens des Z
            {
                glColor3f(0.5,0.5,0.5);
                glTranslatef (0.0f,0.0f,1.5f);
                glutSolidCone (0.1f,0.2,20,20);
            }
            glPopMatrix ();
    glPopMatrix ();

    delete quadratic;
}

void CapteurGL::accAfficheRepereBlanc()
{

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    // Dessiner le centre du repère
    glutWireSphere (0.05f,20,20);

    // Dessiner l'axe des X
    glPushMatrix ();
        glColor3f(1.0,1.0,1.0);
        glTranslatef (0.075f,0.0f,0.0f);
        glRotatef (90,0.0,1.0,0.0);
        gluCylinder (quadratic,0.02,0.02,1.5,20,20);

        // Dessiner le sens des X
        glColor3f(0.5,0.5,0.5);
        glTranslatef (0.0f,0.0f,1.5f);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();

    // Dessiner l'axe des Z
    glPushMatrix ();
        glColor3f(1.0,1.0,1.0);
        gluCylinder (quadratic,0.02,0.02,1.5,20,20);
        // Dessiner le sens des Z
        glColor3f(0.5,0.5,0.5);
        glTranslatef (0.0f,0.0f,1.5f);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();

    // Dessiner l'axe des Y
    glPushMatrix ();
        glColor3f(1.0,1.0,1.0);
        glTranslatef (0.0f,-0.075f,0.0f);
        glRotatef (90,1.0,0.0,0.0);

        gluCylinder (quadratic,0.02,0.02,1.5,20,20);
        // Dessiner le sens des Y
        glColor3f(0.5,0.5,0.5);
        glTranslatef (0.0f,0.0f,1.5f);
        glutSolidCone (0.1f,0.2,20,20);
    glPopMatrix ();

    delete quadratic;
}



void CapteurGL::mousePressEvent(QMouseEvent *event){}
void CapteurGL::mouseMoveEvent(QMouseEvent *event){}
void CapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void CapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



void CapteurGL::updateGL()
{
    QGLWidget::updateGL();
}

void CapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
