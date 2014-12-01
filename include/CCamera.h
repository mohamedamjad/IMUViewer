#ifndef CCAMERA_H
#define CCAMERA_H

#include "GL/glut.h"
#include <iostream>
#include <math.h>
#include <QVector>

/*
    *\class CCamera
    * \brief IMU Viewer : Classe de gestion de caméra
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class CCamera
{
    public:
/**
    *\fn CCamera
    *\brief Constructor
    *\param float anEyeX X initial coordinate for the camera
    *\param float anEyeY Y initial coordinate for the camera
    *\param float anEyeZ Z initial coordinate for the camera
    *\param float anUpX X up vector
    *\param float anUpY Y up vector
    *\param float anUpZ Z up vector
    *\param float aSpeed_cam Distance browsed by the camera, when it will move
    *\param float aRota_cam Angle browsed by the camera, when it will rotate
    *\param float aTeta Initial horizontal orientation
    *\param float aPhi Initial vertical orientation
*/
        CCamera(float,float,float,float,float,float,float,float,float,float);
        /**
        *\fn CCamera
        *\brief Destructor
        */
        virtual ~CCamera();
        /**
            *\fn lookAtLeft
            *\brief Looks at left
        */
        void lookAtLeft();
        /**
            *\fn lookAtRight
            *\brief Looks at right
        */
        void lookAtRight();
        /**
            *\fn lookAtTop
            *\brief Looks at top
        */
        void lookAtTop();
        /**
            *\fn lookAtBottom
            *\brief Looks at bottom
        */
        void lookAtBottom();
        /**
            *\fn go
            *\brief Moves the camera
        */
        void go();
        /**
            *\fn goBack
            *\brief Moves the camera back
        */
        void goBack();
        /**
            *\fn lookAtDefault
            *\brief Default camera position
        */
        void lookAtDefault();
        /**
            *\fn goPro
            *\brief Moves the camera if it is on goPro mode
        */
        void goPro();
        /**
            *\fn setGoProMode
            *\brief Sets the go pro mode enabled
            *\param int idTrain Identifier of train
        */
        void setGoProMode(int);

        /**
            *\fn setClassicalMode
            *\brief Sets the classical mode enabled by setting the position of the camera to the default
        */
        void setClassicalMode();


        /**
            *\fn play
            *\brief Call of OpenGL functions to really update the view
        */
        void play();

        /**
            *\fn getEyeX
            *\brief Renvoie la composante X de la position de la caméra
        */
        float getEyeX();
        /**
            *\fn getEyeY
            *\brief Renvoie la composante Y de la position de la caméra
        */
        float getEyeY();
        /**
            *\fn getEyeZ
            *\brief Renvoie la composante Z de la position de la caméra
        */
        float getEyeZ();
        /**
            *\fn setEye
            *\brief Sets une nouvelle position à la caméra
            *\param point Nouvelle position de caméra (QVector<double>)
        */
        void setEye(QVector<double>);
        /**
            *\fn setCenter
            *\brief Sets un nouveau point à regarder pour la caméra
            *\param point Nouveau point à regarder par la caméra
        */
        void setCenter(QVector<double>);

    protected:
    private:
        /**
            \var _eyeX
            \var _eyeY
            \var _eyeZ
            \brief Coordinates of the camera
        */
        float _eyeX,_eyeY,_eyeZ;
        /**
            \var _default_eyeX
            \var _default_eyeY
            \var _default_eyeZ
            \brief Default coordinates of the camera
        */
        float _default_eyeX,_default_eyeY,_default_eyeZ;
        /**
            \var _centerX
            \var _centerY
            \var _centerZ
            \brief Point looked by the camera
        */
        float _centerX,_centerY,_centerZ;
        /**
            \var _upX
            \var _upY
            \var _upZ
            \brief Direction of the up vector
        */
        float _upX,_upY,_upZ;
        /**
            \var _speed_cam
            \brief Distance browsed by the camera
        */
        float _speed_cam;
        /**
            \var _rota_cam
            \brief Angle for a rotation
        */
        float _rota_cam;
        /**
            \var _teta
            \brief Vertical orientation of camera
        */
        float _teta;
        /**
            \var _phi
            \brief Horizontal orientation of camera
        */
        float _phi;
        /**
            \var _phi
            \brief Horizontal orientation of camera
        */
        float _default_teta,_default_phi;
        /**
            \var _idTrainGoPro
            \brief Identifier of train for GoPro mode
        */
        int _idTrainGoPro;

        /**
            *\fn updateCoordinatesWithProperties
            *\brief Update the point looked by the camera with its properties
        */
        void updateCoordinatesWithProperties();
};

#endif // CCAMERA_H
