#ifndef SENSOR_H
#define SENSOR_H
#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>

#include <QGLWidget>

class Sensor : public QGLWidget
{
    Q_OBJECT
public:
    explicit Sensor(QWidget *parent = 0);
protected:
    void initializeGL ();
    void paintGL ();
    void resizeGL (int w,int h);


};

#endif // SENSOR_H
