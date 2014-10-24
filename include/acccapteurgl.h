 
#ifndef ACCGLWIDGET_H
#define ACCGLWIDGET_H

#include "capteurgl.h"
#include <QGLWidget>


class AccCapteurGL : virtual public CapteurGL
{
    Q_OBJECT
    public:
         explicit AccCapteurGL(QWidget *parent = 0);
};

#endif
