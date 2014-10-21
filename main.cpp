#include <QCoreApplication>
#include "tests.h"


// Mode test
#define TESTS_MODE



int main(int argc, char *argv[])
{

    #ifdef TESTS_MODE

    Tests::tout();

    #else

    QCoreApplication a(argc, argv);

#endif

    return 0;
}
