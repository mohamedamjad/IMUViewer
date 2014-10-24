#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "centrale.h"

class CapteurGL : virtual public QGLWidget
{
    Q_OBJECT
public:
    explicit CapteurGL(QWidget *parent = 0);
    void setCentrale(Centrale*);

private :
    Centrale* _centrale;
    void initializeGL ();
};

#endif // GLWIDGET_H
