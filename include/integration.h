#ifndef INTEGRATION_H
#define INTEGRATION_H

class Integration
{
public:


    Integration();
    Integration(const float Ax[5],const float Ay[5],const float Az[5],const double T[5]);
    int getSize(float* AX);
    float getElt(int i);
    float* Integration_accelo_X();
    float* Integration_accelo_Y();
    float* Integration_accelo_Z();
    void test();
    //float Integration_vitesse(float* VX, float* VY,float* VZ, float* t);
    ~Integration();

private:


    float* AX;
    float* AY;
    float* AZ;
    double* t;

};

#endif // INTEGRATION_H
