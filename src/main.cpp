#include <QApplication>
#include "parametres.h"
#include "tests.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{

    #ifdef TESTS_MODE

    Tests::tout();

    #else

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#endif

    return a.exec();
}
