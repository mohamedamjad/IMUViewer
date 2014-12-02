#include <QApplication>
#include "tests.h"
#include "mainwindow.h"
#include <QCoreApplication>


using namespace std;


int main(int argc, char *argv[])
{
        #ifdef TESTS_MODE

            Tests::tout();
            return 0;
        #else // RUN MODE
            qputenv("LC_NUMERIC",QByteArray("POSIX"));
            glutInit (&argc, argv);
            QApplication a(argc, argv);

            MainWindow w;
            w.show();
            return a.exec();
        #endif
}
