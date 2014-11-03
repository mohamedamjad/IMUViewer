#include <QApplication>
#include "parametres.h"
#include "tests.h"

#include "mainwindow.h"
#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>

#include <csv.h>

using namespace std;


int main(int argc, char *argv[])
{

        #ifdef TESTS_MODE

            Tests::tout();

        #else // RUN MODE

            QApplication a(argc, argv);

            MainWindow w;
            w.show();
        #endif


        return a.exec();
}
