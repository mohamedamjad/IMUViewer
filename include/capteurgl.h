#ifndef CAPTEURGL_H
#define CAPTEURGL_H

#include <QGLWidget>
#include "centrale.h"
#include <iostream>
#include <QTimerEvent>

/*
   Pour optimisation diagramme de classes et classe intermédiaire entre QGLWIdget et les classes GL correspondant aux capteurs
   mais probleme de polymorphisme, les méthodes petites filles ne sont pas appelées

   ... à voir par la suite....
*/


class CapteurGL : virtual public QGLWidget
{
    Q_OBJECT
public:
    explicit CapteurGL(QWidget *parent = 0);
    void setCentrale(Centrale*);

    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void keyPressEvent( QKeyEvent *keyEvent );
    void timerEvent(QTimerEvent);

protected :
    Centrale* _centrale;

};

#endif // CAPTEURGL_H
