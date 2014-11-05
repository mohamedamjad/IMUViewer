#include "acccapteurgl.h"

AccCapteurGL::AccCapteurGL(QWidget *parent) :
    QGLWidget(parent)
{
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
}
void AccCapteurGL::initializeGL()

{
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
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
   // Clear Color and Depth Buffers
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   // Reset transformations
   glLoadIdentity();
   // Set the camera
   gluLookAt( -2.0f, 2.0f, -1.33f,
   0.0f, 0.0f, 0.0f,
   0.0f, 0.0f, 1.0f);

    // Affichage du repere fixe
   afficheRepereFixe();

   // Affichage du repere mobile
    afficheRepereMobile();

}

void AccCapteurGL::afficheRepereMobile()
{

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();


    double absX = abs(_pIMU->_acc[0]);
    double absY = abs(_pIMU->_acc[1]);
    double absZ = abs(_pIMU->_acc[2]);

    double coefX = (absX<valMaxAccArbitraire) ? absX/valMaxAccArbitraire : 1.0;
    double coefY = (absY<valMaxAccArbitraire) ? absY/valMaxAccArbitraire : 1.0;
    double coefZ = (absZ<valMaxAccArbitraire) ? absZ/valMaxAccArbitraire : 1.0;

// Translate pour les axes 0.05 => 0.075

    // Dessiner l'axe des X
    glPushMatrix ();
        glColor3f(1.0,0.0,0.0);
        glTranslatef (0.075f,0.0f,0.0f);

        if (_pIMU->_acc[0]>0)
            glRotatef (90,0.0,1.0,0.0);
        else glRotatef (-90,0.0,1.0,0.0);

        gluCylinder (quadratic,0.05,0.05,coefX*longueurMaxAxe,20,20);
    glPopMatrix ();

    // Dessiner l'axe des Y
    glPushMatrix ();
        glColor3f(0.0,1.0,0.0);
        glTranslatef (0.0f,-0.05f,0.0f);

        if (_pIMU->_acc[1]>0)
            glRotatef (90,1.0,0.0,0.0);
        else glRotatef (-90,1.0,0.0,0.0);

        gluCylinder (quadratic,0.05,0.05,coefY*longueurMaxAxe,20,20);
    glPopMatrix ();

    // Dessiner l'axe des Z
    glPushMatrix ();
        glColor3f(0.0,0.0,1.0);

        if (_pIMU->_acc[2]<0)
            glRotatef (180,1.0,0.0,0.0);

        gluCylinder (quadratic,0.05,0.05,coefZ*longueurMaxAxe,20,20);

    glPopMatrix ();

    delete quadratic;
}

void AccCapteurGL::afficheRepereFixe()
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



void AccCapteurGL::mousePressEvent(QMouseEvent *event){}
void AccCapteurGL::mouseMoveEvent(QMouseEvent *event){}
void AccCapteurGL::keyPressEvent( QKeyEvent *keyEvent ){}


void AccCapteurGL::timerEvent(QTimerEvent event)
{
    updateGL();
}



void AccCapteurGL::updateGL()
{
    QGLWidget::updateGL();
}

void AccCapteurGL::setCentrale(Centrale *uneCentrale)
{
    _pIMU = uneCentrale;
}
