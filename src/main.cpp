#include <QApplication>
#include "parametres.h"
#include "tests.h"
<<<<<<< HEAD
#include "mainwindow.h"
=======
#include <QCoreApplication>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <integration.h>
#include <integration_gyro.h>
#include <csv.h>
using namespace std;


//Displayin results after integrations

void affichage(float* X,float* Y, float* Z,int n)
{
    cout<<"le deplacement suivant X "<<endl;
    for (int i=0;i<n-2;i++)

    {
       cout<<X[i]<<endl;
    }
    cout<<"le deplacement suivant Y "<<endl;
    for (int i=0;i<n-2;i++)

    {
       cout<<Y[i]<<endl;
    }
    cout<<"le deplacement suivant Z "<<endl;
    for (int i=0;i<n-2;i++)

    {
       cout<<Z[i]<<endl;
    }
}

// Gather all tds data in a matrix

double** TDS_matix(int n,double** sens,  FrequencyType freqFiltre, FrequencyType freqEch,bool reEchantillone)
{


     double** TDSmatix=new double* [4];

     SampleType *tmps = new SampleType[n];

    Signal saccx(sens,n,0,2);
    saccx.passeBas(freqFiltre,freqEch,reEchantillone);

    Signal saccy(sens,n,0,3);
    saccy.passeBas(freqFiltre,freqEch,reEchantillone);

    Signal saccz(sens,n,0,4);
    saccz.passeBas(freqFiltre,freqEch,reEchantillone);

    for (int i=0;i<n;i++)
    {
       TDSmatix[0][i]= tmps[i];
       TDSmatix[0][i]= saccx.getSignal(i);
       TDSmatix[0][i]= saccy.getSignal(i);
       TDSmatix[0][i]= saccz.getSignal(i);

    }

    return TDSmatix;

}

>>>>>>> 5d0b509f3683a2dbc74305a9e9891e6ebe6a8af8


int main(int argc, char *argv[])
{

    //#ifdef TESTS_MODE

    //Tests::tout();

    //#else

    //QCoreApplication a(argc, argv);

//#endif


   //****************** INTEGRATION+CSV+TDS ************************//

<<<<<<< HEAD
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
=======
>>>>>>> 5d0b509f3683a2dbc74305a9e9891e6ebe6a8af8

    double **sensors=new double*[13];
    double **tdsmatrix=new double*[4];
    CSV fchr;
    sensors=fchr.readCSV("amjad_controle.csv");
    int n=fchr.getNbLines();
    float* X=new float [n-2];
    float* Y=new float [n-2];
    float* Z=new float [n-2];
    float* angX=new float [n-1];
    float* angY=new float [n-1];
    float* angZ=new float [n-1];
    //Signal s(sensors[0][],sensors[][],n);
    Integration I(sensors,n);
    integration_gyro IG(sensors,n);
    X=I.Integration_accelo_X(n);
    Y=I.Integration_accelo_Y(n);
    Z=I.Integration_accelo_Z(n);
    angX=IG.Integration_gyro_X(n);
    angY=IG.Integration_gyro_Y(n);
    angZ=IG.Integration_gyro_Z(n);
    tdsmatrix=TDS_matix(n,sensors,10,3,false);
    affichage(X,Y,Z,n);
    affichage(angX,angY,angZ,n);

    return a.exec();
}
