#ifndef INTEGRATION_GYRO_H
#define INTEGRATION_GYRO_H

class integration_gyro
{
public:

    integration_gyro();
    integration_gyro(const float Vx[5],const float Vy[5],const float Vz[5],const double T[5]);
    float* Integration_gyro_X();
    float* Integration_gyro_Y();
    float* Integration_gyro_Z();
    void test();

private:
    float* VX;
    float* VY;
    float* VZ;
    double* t;


};

#endif // INTEGRATION_GYRO_H
