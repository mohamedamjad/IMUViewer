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
#include <QLabel>

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
    int getsignalIndex();
    TableauDeBord* getpTDB();
    void setmaxLabel(QLabel *maxlabel);
    void setminLabel(QLabel *minlabel);

public slots:
    void updateGL();
    void setsignalIndex(int i);
    void updateLabel();

private:
    Centrale* _pIMU;
    TableauDeBord* _pTDB;
    int signalIndex;
    QLabel* _maxLabel;
    QLabel* _minLabel;

};

#endif // GYROGRAPH_H
