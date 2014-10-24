#ifndef QUATERNION_H
#define QUATERNION_H

class Quaternion
{
public:
    float *getQ();
    void setQ(float[]);
    Quaternion(float a, float b, float c, float d);
    Quaternion(const Quaternion&);

    Quaternion add(Quaternion,Quaternion); // testé
    Quaternion multipQuaternion(Quaternion, Quaternion); // testé
    Quaternion inverseQuaternion();
    Quaternion divQuaternion(Quaternion,Quaternion);
    void normalise();
    Quaternion conjugateQuaternion();
    float* rotateVectorQuaternion(float vect[3]);
    Quaternion rotationAxisQuaternion(float theta, float *axis);
    Quaternion FromEuler(float pitch, float yaw, float roll);

private:
    float *q;
};

#endif // QUATERNION_H
