#include <QCoreApplication>
#include "parametres.h"
#include "tests.h"
#include<QQuaternion>

int main(int argc, char *argv[])
{

    #ifdef TESTS_MODE

    Tests::tout();

    #else

    QCoreApplication a(argc, argv);

#endif

    return 0;
}
