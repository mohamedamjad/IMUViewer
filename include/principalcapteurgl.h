/*
    * \class PrincipalCapteurGL
    * \brief Classe qui hérite de QGLWidget et qui affiche la centrale dans l'espace ( grand widget principal)
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
#ifndef PRINCIPALGLWIDGET_H
#define PRINCIPALGLWIDGET_H

#include <QGLWidget>
#include <QTimerEvent>
#include <QGLWidget>
#include <QtOpenGL>
#include <GL/glu.h>
#include <iostream>
#include<GL/glut.h>
#include "centrale.h"
#include "CCamera.h"
#include"tableaudebord.h"

class PrincipalCapteurGL : public QGLWidget
{
    Q_OBJECT
    public:
    /**
          * \fn PrincipalCapteurGL
          * \brief Constructeur de PrincipalCapteurGL, cette classe hérite de QGLWidget
          * \param parent
          */
         explicit PrincipalCapteurGL(QWidget *parent = 0);
       /**
         * \fn initializeGL
         *  \brief fonction qui initialise OpenGL dans le PrincipalCapteurGL
         */
        void initializeGL();
        /**
         * \fn resizeGL
         * \brief fonction qui permet de redimensionner le PrincipalCapteurGL
         * \param w : largeur du QGLWidget
         * \param h : hauteur du QGLWidget
         */
        void resizeGL(int w, int h);
        /**
         * \fn paintGL
         * \brief fonction de dessin OpenGL
         */
        void paintGL();
        /**
         * \fn mousePressEvent
         * \brief SLOT déclenché après un clique souris
         * \param event : événement capturé (clique souris)
         */
        void mousePressEvent(QMouseEvent *event);
        /**
         * \fn mouseMoveEvent
         * \brief SLOT déclenché après un mouvement de la souris
         * \param event : événement capturé (mouvement souris)
         */
        void mouseMoveEvent(QMouseEvent *event);
        /**
         * \fn keyPressEvent
         * \brief SLOT déclenché après pression d'une touche clavier
         * \param keyEvent : événement capturé (pression d'une touche clavier)
         */
        void keyPressEvent( QKeyEvent *keyEvent );
        /**
         * \fn timerEvent
         * \brief SLOT déclenché à chaque raffraichissement de la fenêtre
         * \param QTimerEvent : événement capturé (généralement un timeout() SIGNAL)
         */
        void timerEvent(QTimerEvent);
        /**
         * \fn setCentrale
         * \brief setter de _pIMU
         * \param Centrale* : pointeur vers la centrale qu'on va setter
         */
        void setCentrale(Centrale *);
        /**
         * \fn setFenetreEvolutionCentrale
         * \brief à partir des valeur du coin supérieur et coin inférieur du cube d'évolution setter_hauteurFenetre, _largeurFenetre, _profondeurFenetre, _coinInferieur et _coinSuperieur
         */
        void setFenetreEvolutionCentrale(QVector<double>,QVector<double>);

    public slots:
        /**
         * \fn updateGL
         * \brief SLOT du mise à jour du QGLWidget déclenché à chaque raffraîchissement de la fenêtre
         */
        void updateGL();
        /**
         * \fn setProjection
         * \brief SLOT déclenché à chaque fois qu'on change les valeurs du combobox des projections
         */
        void setProjection(int);
    private:
        /**
         * \var _pIMU
         * \brief pointeur vers la centrale inertielle affichée dans le QGLWidget
         */
        Centrale* _pIMU;

        // Coordonnées du point inférieur et supérieur de la fenetre d'évolution de la centrale
        /**
         * \var _coinInferieur
         * \brief vecteur qui contient les 3 coordonnées du coin inférieur du parallépipède d'évolution
         */
        QVector<double> _coinInferieur;
        /**
         * \var _coinSuperieur
         * \brief vecteur qui contient les 3 coordonnées du coin inférieur du parallépipède d'évolution
         */
        QVector<double> _coinSuperieur;
        /**
         * \var _hauteurFenetre
         * \brief hauteur du parallépipède d'évolution
         */
        double _hauteurFenetre;// amplitude Z
        /**
         * \var _largeurFenetre
         * \brief largeur du parallépipède d'évolution
         */
        double _largeurFenetre;// amplitude X
        /**
         * \var _profondeurFenetre
         * \brief profondeur du parallépipède d'évolution
         */
        double _profondeurFenetre;// amplitude Y
        /**
         * \var _pCamera
         * \brief pointeur vers la caméra
         */
        CCamera *_pCamera;
        /**
         * \var _cameraSuitCentrale
         * \brief booléen qui indique est ce qu'on est en mode suivi de la centrale ou non
         */
        bool _cameraSuitCentrale  = false;

        //void afficheSol();
        /**
         * \fn afficheCentrale
         * \brief fonction qui dessine le repère de la centrale
         */
        void afficheCentrale();
        /**
         * \fn  afficheTrajectoireCentrale
         * \brief fonction qui dessine la trajectoire de la contrale
         */
        void afficheTrajectoireCentrale();
        /**
         * \fn suitCentrale
         * \brief basculer ou arrêter le mode suivi de la centrale
         */
        void suitCentrale();
        /**
         * \fn afficheRepereSol
         * \brief afficher le repère sur le point de départ initial de la centrale
         */
        void afficheRepereSol();
        /**
         * \fn afficheCubEvolution
         * \brief fonction qui dessine le parallépipède d'écolution
         */
        void afficheCubEvolution();

        /**
         * \fn  setProjectionX
         * \brief fonction qui permet de changer les paramètres eye et center de la caméra pour avoir une vu suivant l'axe X
         */
        void setProjectionX();
        /**
         * \fn setProjectionY
         * \brief fonction qui permet de changer les paramètres eye et center de la caméra pour avoir une vu suivant l'axe Y
         */
        void setProjectionY();
        /**
         * \fn setProjectionZ
         * \brief fonction qui permet de changer les paramètres eye et center de la caméra pour avoir une vu suivant l'axe Z
         */
        void setProjectionZ();
        /**
         * \fn setProjection3D
         * \brief fonction qui permet de changer les paramètres eye et center de la caméra pour avoir une vu 3D
         */
        void setProjection3D();


};

#endif
