#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableaudebord.h"
#include "principalcapteurgl.h"
#include <iostream>
#include <string>
#include "gyrograph.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent* event);

    ~MainWindow();

public slots :
    void majLCD();
    void setslidervalue();
    // Ajout Régis 12/11
    void clicPlay();
    // Fin Régis 12/11
    void clicStop();


private:
    Ui::MainWindow *ui;

    TableauDeBord *_pTdb;
    
    // Pointeur sur la fenetre d'affichage principale
    PrincipalCapteurGL *_pcGL;

    QTimer *_pTimer;
};

#endif // MAINWINDOW_H
