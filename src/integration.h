#ifndef INTEGRATION_H
#define INTEGRATION_H

class Integration
{
public:


    Integration();
    Integration(const float AX[5],const float AY[5],const float AZ[5],const double t[5]);
    int getSize(float* AX);
    float getElt(int i);
    float* Integration_accelo_X();
    float* Integration_accelo_Y();
    float* Integration_accelo_Z();

    //float Integration_vitesse(float* VX, float* VY,float* VZ, float* t);
    ~Integration();

private:

    //char Name;
    float* AX;
    float* AY;
    float* AZ;
    double* t;

};

#endif // INTEGRATION_H
