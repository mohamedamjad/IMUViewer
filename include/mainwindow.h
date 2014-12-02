/*
    * \class mainwindow
    * \brief Classe de la fenêtre principale elle contient tous les SIGNALs et les widgets du programme
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tableaudebord.h"
#include "principalcapteurgl.h"
#include <iostream>
#include <string>
#include "gyrograph.h"
#include <QString>
#include <QFileDialog>
#include <QComboBox>
#include <QLabel>
#include "capteurgl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \fn MainWindow
     * \brief Constructeur par copie du mainwindow
     * \param parent : QWidget pour construire MainWindow
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * \fn keyPressEvent
     * \brief fonction appelée à chaque pression d'une touche clavier
     * \param event l'événement qui déclenche la fonction
     */
    void keyPressEvent(QKeyEvent* event);
    /**
     * \fn chargeFichier
     * \brief fonction qui permet de choisir le fichier qu'on va charger
     * \param filename : chemin vers le fichier
     */
    void chargeFichier(const char* filename);
    ~MainWindow();

public slots :
    /**
     * \fn majLCD
     * \brief SLOT qui permet de mettre à jour le LCD à chaque raffraichissement de la fenêtre
     */
    void majLCD();
    /**
     * \fn  setslidervalue
     * \brief SLOT pour changer les valeurs du slider à chaque raffraîchissement de fenêtre
     */
    void setslidervalue();
    /**
     * \fn clicPlay
     * \brief SLOT déclenché lorsqu'on clique sur play
     */
    void clicPlay();
    /**
     * \fn dragslidervalue
     * \brief SLOT déclenché lorsqu'on clique-glisse le slider
     */
    void dragslidervalue();
    /**
     * \fn clicStop
     * \brief SLOT déclenché lorsqu'on clique sur stop
     */
    void clicStop();
    /**
     * \fn loadfile ();
     * \brief SLOT qui lance la fenetre du chargement d'un nouveau fichier
     */
    void loadfile ();
    /**
     * \fn majClasse
     * \brief SLOT de la mise à jour de la classification à chaque raffraîchissement de la fenêtre
     */
    void majClasse();

private:
    Ui::MainWindow *ui;

    /**
     * \var  _pTdb
     * \brief Pointeur sur le tableau de bord qui contient les signaux
     */
    TableauDeBord *_pTdb;
    /**
    * \var _pcGL
    * \brief Pointeur sur la fenetre d'affichage principale
    */
    PrincipalCapteurGL *_pcGL;
    /**
     * \var _pTimer
     * \brief pointeur vers le timer de la fenêtre principale
     */
    QTimer *_pTimer;
    /**
     * \var _fichierOuvert
     * \brief booléen pour indiquer est ce qu'un fichier est ouvert ou non
     */
    bool _fichierOuvert;
};

#endif // MAINWINDOW_H
