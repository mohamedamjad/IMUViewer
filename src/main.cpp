#include <QApplication>
#include "parametres.h"
#include "tests.h"

#include "mainwindow.h"
#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <integration.h>
#include <integration_gyro.h>
#include <csv.h>
#include <GL/glut.h>

using namespace std;


int main(int argc, char *argv[])
{

        #ifdef TESTS_MODE

            Tests::tout();

        #else // RUN MODE
            glutInit (&argc, argv);
            QApplication a(argc, argv);
            MainWindow w;
            w.show();
        #endif

        return a.exec();
}
