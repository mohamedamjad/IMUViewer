#include "CCamera.h"

/**
    *\fn CCamera
    *\brief Constructor
    *\param CWorld *aWorld Pointer to the world
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
CCamera::CCamera(float anEyeX,float anEyeY,float anEyeZ,float anUpX,float anUpY,float anUpZ,float aSpeed_cam,float aRota_cam,float aTeta,float aPhi):_eyeX(anEyeX),_eyeY(anEyeY),_eyeZ(anEyeZ),_default_eyeX(anEyeX),_default_eyeY(anEyeY),_default_eyeZ(anEyeZ),_upX(anUpX),_upY(anUpY),_upZ(anUpZ),_speed_cam(aSpeed_cam),_rota_cam(aRota_cam),_teta(aTeta),_phi(aPhi),_default_teta(aTeta),_default_phi(aPhi)
{
    //ctor

    _idTrainGoPro   = -1;
    this->updateCoordinatesWithProperties();
}

/**
    *\fn CCamera
    *\brief Destructor
*/
CCamera::~CCamera()
{
    //dtor
}

/**
    *\fn lookAtLeft
    *\brief Looks at left
*/
void CCamera::lookAtLeft()
{
    _phi += _rota_cam;
    this->updateCoordinatesWithProperties();
    this->play();
}

/**
    *\fn lookAtRight
    *\brief Looks at right
*/
void CCamera::lookAtRight()
{
    _phi -= _rota_cam;
    this->updateCoordinatesWithProperties();
    this->play();
}

/**
    *\fn lookAtTop
    *\brief Looks at top
*/
void CCamera::lookAtTop()
{
    _teta -= _rota_cam;
    this->updateCoordinatesWithProperties();
    this->play();
}

/**
    *\fn lookAtBottom
    *\brief Looks at bottom
*/
void CCamera::lookAtBottom()
{
    _teta += _rota_cam;
    this->updateCoordinatesWithProperties();
    this->play();
}

/**
    *\fn go
    *\brief Moves the camera
*/
void CCamera::go()
{
    _eyeX = _eyeX + _speed_cam*cos(_teta) * cos(_phi);
    _eyeY = _eyeY + _speed_cam*cos(_teta) * sin(_phi);
    _eyeZ = _eyeZ + _speed_cam*sin(_teta);
    this->updateCoordinatesWithProperties();
    this->play();

}

/**
    *\fn goBack
    *\brief Moves the camera back
*/
void CCamera::goBack()
{
    _eyeX = _eyeX - _speed_cam*cos(_teta) * cos(_phi);
    _eyeY = _eyeY - _speed_cam*cos(_teta) * sin(_phi);
    _eyeZ = _eyeZ - _speed_cam*sin(_teta);
    this->updateCoordinatesWithProperties();
    this->play();
}

/**
    *\fn lookAtDefault
    *\brief Default camera position
*/
void CCamera::lookAtDefault()
{
    _eyeX = _default_eyeX;
    _eyeY = _default_eyeY;
    _eyeZ = _default_eyeZ;
    _teta = _default_teta;
    _phi = _default_phi;
    this->updateCoordinatesWithProperties();
    this->play();
}


/**
    *\fn setGoProMode
    *\brief Sets the go pro mode enabled
    *\param int idTrain Identifier of train
*/
void CCamera::setGoProMode(int idTrain)
{
    _idTrainGoPro = idTrain;
}

/**
    *\fn setClassicalMode
    *\brief Sets the classical mode enabled by setting the position of the camera to the default
*/
void CCamera::setClassicalMode()
{
    _idTrainGoPro = -1;
    lookAtDefault();
}

/**
    *\fn updateCoordinatesWithProperties
    *\brief Update the point looked by the camera with its properties
*/
void CCamera::updateCoordinatesWithProperties()
{
    std::cout<< "*** Camera**** "<< std::endl;
    std::cout<< "Eye =  "<< _eyeX << " "<< _eyeY <<  " " << _eyeZ<<   std::endl;
    std::cout<< "Center =  "<< _centerX << " "<< _centerY <<  " " << _centerZ<<   std::endl;
    std::cout << "Phi = "<< _phi << std::endl;
    std::cout << "_teta = "<< _teta << std::endl;
    _centerX = _eyeX + cos(_teta) * cos(_phi);
    _centerY = _eyeY + cos(_teta) * sin(_phi);
    _centerZ = _eyeZ + sin(_teta);
}

/**
    *\fn play
    *\brief Call of OpenGL functions to really update the view
*/
void CCamera::play()
{
    gluLookAt(_eyeX,_eyeY,_eyeZ,_centerX,_centerY,_centerZ,_upX,_upY,_upZ);
}


float CCamera::getEyeX()
{
    return _eyeX;
}
float CCamera::getEyeY()
{
        return _eyeY;
}
float CCamera::getEyeZ()
{
        return _eyeZ;
}


void CCamera::setEye(QVector<double> point)
{
    _eyeX = point[0];
    _eyeY = point[1];
    _eyeZ = point[2];

}
void CCamera::setCenter(QVector<double> point)
{
    _centerX = point[0];
    _centerY = point[1];
    _centerZ = point[2];

}
