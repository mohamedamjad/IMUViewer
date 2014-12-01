/*
    * \class gyrograph
    * \brief Classe qui affiche les signaux en fonction du temps (3 espaces d'affichages)
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
#ifndef GYROGRAPH_H
#define GYROGRAPH_H

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
    /**
     * \fn gyrograph
     * \brief constructeur de la classe gyrograph elle hérite de QGLWidget
     * \param parent
     */
    explicit gyrograph(QWidget *parent = 0);
    /**
     * \fn initializeGL ();
     * \brief initialise OpenGL dans la QGLWidget
     */
    void initializeGL();
    /**
     * \fn resizeGL
     * \brief fonction qui contient les paramètres de redimensionnement du QGLWidget
     * \param w largeur du QGLWidget
     * \param h hauteur du QGLWidget
     */
    void resizeGL(int w, int h);
    /**
     * \fn paintGL
     * \brief fonction qui déssine le signal à chaque raffraichissement de la fenêtre
     */
    void paintGL();
    /**
     * \fn setCentrale
     * \brief setter qui indique la centrale source du signal à afficher
     */
    void setCentrale(Centrale *);
    /**
     * \fn afficheSignal
     * \brief fonction qui affiche le signal elle est appelée dans paintGL
     */
    void afficheSignal();
    /**
     * \fn setTableauDeBord ();
     * \brief Setter du tableau de bord qui contient les signaux qu'on veut afficher
     * \param tdb : le tableau de bord qu'on veut setter
     */
    void setTableauDeBord(TableauDeBord *tdb);
    /**
     * \fn getsignalIndex
     * \brief fonction qui retourne l'indice du signal qu'on affiche, son indice dans le vecteur des signaux
     * \return l'indice du signal courant
     */
    int getsignalIndex();
    /**
     * \fn getpTDB
     * \brief getter qui retourne le tableau de bord qui contient le signal.
     * \return Tableau de bord
     */
    TableauDeBord* getpTDB();
    /**
     * \fn setmaxLabel
     * \brief setter du label qui affiche le seuil max du signal dans la fenêtre
     * \param maxlabel : le label qui affiche le max
     */
    void setmaxLabel(QLabel *maxlabel);
    /**
     * \fn setminLabel
     * \brief setter du label qui affiche le seuil min du signal dans la fenêtre
     * \param maxlabel : le label qui affiche le min
     */
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
