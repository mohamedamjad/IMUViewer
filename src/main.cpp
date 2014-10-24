#include <QCoreApplication>
#include "parametres.h"
#include "tests.h"
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
     SampleType *sacclx = new SampleType[n];
     SampleType *saccly = new SampleType[n];
     SampleType *sacclz = new SampleType[n];
     SampleType *tmps = new SampleType[n];

    for (int i=0;i<n;i++)
    {
       sacclx[i]=sens[2][i];
       saccly[i]=sens[3][i];
       sacclz[i]=sens[4][i];
        tmps[i]=sens[0][i];

    }
    Signal saccx(tmps,sacclx,n);
    saccx.passeBas(freqFiltre,freqEch,reEchantillone);

    Signal saccy(tmps,saccly,n);
    saccy.passeBas(freqFiltre,freqEch,reEchantillone);

    Signal saccz(tmps,sacclz,n);
    saccz.passeBas(freqFiltre,freqEch,reEchantillone);

    for (int i=0;i<n;i++)
    {
       TDSmatix[0][i]= tmps[i];
       TDSmatix[0][i]= saccx.get_signal(i);
       TDSmatix[0][i]= saccy.get_signal(i);
       TDSmatix[0][i]= saccz.get_signal(i);

    }

    return TDSmatix;

}



int main(int argc, char *argv[])
{

    //#ifdef TESTS_MODE

    //Tests::tout();

    //#else

    //QCoreApplication a(argc, argv);

//#endif


   //****************** INTEGRATION+CSV+TDS ************************//


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

    return 0;
}
