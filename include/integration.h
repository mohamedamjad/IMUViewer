#ifndef INTEGRATION_H
#define INTEGRATION_H

class Integration
{
public:


    Integration();
    Integration(float** S,int n);
    //int getSize(float* AX);
    float getElt(int i);
    float* Integration_accelo_X(int n);
    float* Integration_accelo_Y(int n);
    float* Integration_accelo_Z(int n);
    void test();
    //float Integration_vitesse(float* VX, float* VY,float* VZ, float* t);
    ~Integration();

private:


    float* AX;
    float* AY;
    float* AZ;
    float* t;


};

#endif // INTEGRATION_H
