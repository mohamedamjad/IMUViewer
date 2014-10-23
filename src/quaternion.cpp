#include "quaternion.h"
#include <math.h>


/**
    *REMARQUES ISSUES DES TESTS:
    *pour les operateurs l'ideal serait de surcharger avec operator+, operator*...
    *le fait de renvoyer un pointeur pour le get est dangereux (on peut le deleter de l'extérieur)
*/


/*
 * Un quaternion est un élément (a, b, c, d) appartient à R4
 * C'est un corps non-commutatif
 * (1, 0, 0, 0) est l'élément neutre de ce corps
 * Le corps des Quaternion est associatif et distributif
 */
Quaternion::Quaternion(float a,float b,float c,float d)
{
    // Tableau temporaire pour stocker les éléments du quaternion
    float *tmp;
    tmp=new float[4];

    tmp[0]=a;
    tmp[1]=b;
    tmp[2]=c;
    tmp[3]=d;

    this->q=tmp;
}

Quaternion::Quaternion(const Quaternion& unQ)
{
    q=new float[4];
    q[0] = unQ.q[0];
    q[1] = unQ.q[1];
    q[2] = unQ.q[2];
    q[3] = unQ.q[3];
}

// Retourne le quaternion dans un tableau de pointeurs
float *Quaternion::getQ ()
{
    return this->q;
}

// Définir les valeurs du quaternion
void Quaternion::setQ (float tmp[4])
{
    this->q[0]=tmp[0];
    this->q[1]=tmp[1];
    this->q[2]=tmp[2];
    this->q[3]=tmp[3];
}

// Addition de 2 quaternions
Quaternion Quaternion::add(Quaternion q1,Quaternion q2)
{
    Quaternion q(0,0,0,0);

    q.q[0]=q1.q[0]+q2.q[0];
    q.q[1]=q1.q[1]+q2.q[1];
    q.q[2]=q1.q[2]+q2.q[2];
    q.q[3]=q1.q[3]+q2.q[3];

    return q;
}

// Multiplication de 2 quaternions
// La multiplication revient à composer les 2 rotations
Quaternion Quaternion::multipQuaternion(Quaternion q1, Quaternion q2)
{
    Quaternion q(1,1,1,1);

    q.q[0]=q1.q[0]*q2.q[0]-q1.q[1]*q2.q[1]-q1.q[2]*q2.q[2]-q1.q[3]*q2.q[3];
    q.q[1]=q1.q[0]*q2.q[1]+q1.q[1]*q2.q[0]+q1.q[2]*q2.q[3]-q1.q[3]*q2.q[2];
    q.q[2]=q1.q[0]*q2.q[2]+q1.q[2]*q2.q[0]-q1.q[1]*q2.q[3]+q1.q[3]*q2.q[1];
    q.q[3]=q1.q[3]*q2.q[0]+q1.q[0]*q2.q[3]+q1.q[1]*q2.q[2]-q1.q[2]*q2.q[1];

    return q;
}

Quaternion Quaternion::inverseQuaternion()
{
    Quaternion tmp(1,1,1,1);

    tmp.q[0]=this->q[0]/(this->q[0]*this->q[0]+this->q[1]*this->q[1]+this->q[2]*this->q[2]+this->q[3]*this->q[3]);
    tmp.q[1]=-this->q[1]/(this->q[0]*this->q[0]+this->q[1]*this->q[1]+this->q[2]*this->q[2]+this->q[3]*this->q[3]);
    tmp.q[1]=-this->q[2]/(this->q[0]*this->q[0]+this->q[1]*this->q[1]+this->q[2]*this->q[2]+this->q[3]*this->q[3]);
    tmp.q[2]=-this->q[3]/(this->q[0]*this->q[0]+this->q[1]*this->q[1]+this->q[2]*this->q[2]+this->q[3]*this->q[3]);

    return tmp;
}

Quaternion Quaternion::divQuaternion(Quaternion q1,Quaternion q2)
{
    return (multipQuaternion(q1,q2.inverseQuaternion ()));
}

void Quaternion::normalise()
{
    float n;

    n=sqrt(this->q[0]*this->q[0]+this->q[1]*this->q[1]+this->q[2]*this->q[2]+this->q[3]*this->q[3]);

    this->q[0]=this->q[0]/n;
    this->q[1]=this->q[1]/n;
    this->q[2]=this->q[2]/n;
    this->q[3]=this->q[3]/n;

}

Quaternion Quaternion::conjugateQuaternion(Quaternion const q)
{
    Quaternion cq(1,1,1,1);

    cq.q[0]=q.q[0];
    cq.q[1]=-q.q[1];
    cq.q[2]=-q.q[2];
    cq.q[3]=-q.q[3];

    return cq;

}

// Appliquer la rotation d'un quaternion sur un vecteur.
// On doit multiplier le quaternion par le vecteur ensuite pas le conjugué du quaternion
// Exemple : U= q.v.cq

float* Quaternion::rotateVectorQuaternion(float vect[3])
{
    // Vecteur résultat qui va être retourner par la routine
    float *resVect;
    resVect= new float[3];

    // Quaternion qui va stocker le résultat
    Quaternion resQuaternion(1,1,1,1);

    // Tranformer le vecteur en Quaternion (sa partie réelle est nulle)
    Quaternion vectQuaternion(1,1,1,1);

    vectQuaternion.q[0]=0;
    vectQuaternion.q[1]=vect[0];
    vectQuaternion.q[2]=vect[1];
    vectQuaternion.q[3]=vect[2];

    // Le nouveau vecteur= Quaternion * Ancien Vecteur * Conjugué du Quaternion
    resQuaternion=multipQuaternion (vectQuaternion, conjugateQuaternion (*this));
    resQuaternion=multipQuaternion (*this, resQuaternion);

    resVect[0]=resQuaternion.q[1];
    resVect[1]=resQuaternion.q[2];
    resVect[2]=resQuaternion.q[3];

    return resVect;

}

// Quaternion à partir d'un axe v
// pour tourner de \theta, autour d'un axe (vecteur unitaire) \vec{v}, on utilise cette routine

Quaternion Quaternion::rotationAxisQuaternion(float theta, float *axis)
{


    // Quaternion résultat
    Quaternion resQuaternion(1,1,1,1);

    resQuaternion.q[0]=cos(theta*0.5);

    resQuaternion.q[1]=axis[0]*sin(theta*0.5);
    resQuaternion.q[2]=axis[1]*sin(theta*0.5);
    resQuaternion.q[3]=axis[2]*sin(theta*0.5);

    return resQuaternion;
}

// Convertir en utilsiatn l'angle d'euler
Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll)
{
    // Quaternion Résultat

    Quaternion resQuaternion(1,1,1,1);

    // On crée 3 Quaternions: 1 pour yaw, 1 pour pitch et le dernier pour roll
    // Et on multiplie les 3.

    float p = pitch;
    float y = yaw;
    float r = roll;

    float sinp = sin(p);
    float siny = sin(y);
    float sinr = sin(r);
    float cosp = cos(p);
    float cosy = cos(y);
    float cosr = cos(r);

    resQuaternion.q[0] = sinr * cosp * cosy - cosr * sinp * siny;
    resQuaternion.q[1] = cosr * sinp * cosy + sinr * cosp * siny;
    resQuaternion.q[2] = cosr * cosp * siny - sinr * sinp * cosy;
    resQuaternion.q[3] = cosr * cosp * cosy + sinr * sinp * siny;

    resQuaternion.normalise();

    return resQuaternion;
}
