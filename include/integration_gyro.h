#ifndef INTEGRATION_GYRO_H
#define INTEGRATION_GYRO_H

class integration_gyro
{
public:

    integration_gyro();
    integration_gyro(float** S,int n);
    float* Integration_gyro_X(int n);
    float* Integration_gyro_Y(int n);
    float* Integration_gyro_Z(int n);
    void test();

private:
    float* VX;
    float* VY;
    float* VZ;
    float* t;


};

#endif // INTEGRATION_GYRO_H
