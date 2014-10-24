#ifndef INTEGRATION_H
#define INTEGRATION_H

class Integration
{
public:


    Integration();
    Integration(double** S,int n);
    //int getSize(float* AX);
    float getElt(int i);
    float* Integration_accelo_X(int n);
    float* Integration_accelo_Y(int n);
    float* Integration_accelo_Z(int n);
    void test();
    //float Integration_vitesse(float* VX, float* VY,float* VZ, float* t);
    ~Integration();

private:


    double* AX;
    double* AY;
    double* AZ;
    double* t;


};

#endif // INTEGRATION_H
