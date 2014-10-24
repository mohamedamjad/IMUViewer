#ifndef TESTS_H
#define TESTS_H

#include "quaternion.h"
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

};

#endif // TESTS_H
