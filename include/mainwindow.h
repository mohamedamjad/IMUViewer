#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableaudebord.h"
#include "principalcapteurgl.h"

#include <iostream>
#include <string>



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

private:
    Ui::MainWindow *ui;

    TableauDeBord *_pTdb;
    
    // Pointeur sur la fenetre d'affichage principale
    PrincipalCapteurGL *_pcGL;

};

#endif // MAINWINDOW_H
