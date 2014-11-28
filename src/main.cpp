#include <QApplication>
#include "tableaudebord.h"
#include "tests.h"

#include "mainwindow.h"
#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>

#include <csv.h>
#include <GL/glut.h>

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
