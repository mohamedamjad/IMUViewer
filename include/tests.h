#ifndef TESTS_H
#define TESTS_H

#include "quaternion.h"
#include "integration.h"
#include "integration_gyro.h"
#include "csv.h"
#include "signal.h"
#include <time.h>
#include <iostream>

using namespace std;

class Tests
{
public:
    Tests();

    static bool testQuaternion();
    static bool TdS();
    static bool tout();
    static bool testItegration();
    static double** TDS_matix(int n,double** sens,  FrequencyType freqFiltre, FrequencyType freqEch,bool reEchantillone);
};

#endif // TESTS_H
