#ifndef GYROGRAPH_H
#define GYROGRAPH_H

#include "capteurgl.h"
#include <QGLWidget>
#include <QTimerEvent>
#include<GL/glut.h>
#include <QVector>
#include "signal.h"
#include "tableaudebord.h"
#include <QComboBox>

class gyrograph : public QGLWidget
{
    Q_OBJECT
public:
    explicit gyrograph(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent( QKeyEvent *keyEvent );
    void timerEvent(QTimerEvent);
    void setCentrale(Centrale *);
    void afficheSignal();
    void setTableauDeBord(TableauDeBord *tdb);

public slots:
    void updateGL();
        void setsignalIndex(int i);

private:
    Centrale* _pIMU;
    TableauDeBord* _pTDB;
    int signalIndex;
    QComboBox* combobox;

};

#endif // GYROGRAPH_H
