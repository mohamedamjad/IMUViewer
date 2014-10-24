#ifndef INTEGRATION_GYRO_H
#define INTEGRATION_GYRO_H

class integration_gyro
{
public:

    integration_gyro();
    integration_gyro(double** S,int n);
    float* Integration_gyro_X(int n);
    float* Integration_gyro_Y(int n);
    float* Integration_gyro_Z(int n);
    void test();

private:
    double* VX;
    double* VY;
    double* VZ;
    double* t;


};

#endif // INTEGRATION_GYRO_H
