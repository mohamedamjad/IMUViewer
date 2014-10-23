#include "integration_gyro.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
using namespace std ;
integration_gyro::integration_gyro()
{


}


integration_gyro::integration_gyro(const float Vx[5],const float Vy[5],const float Vz[5],const double T[5])
{
   VX=new float [5];
   VY=new float [5];
   VZ=new float [5];
   t=new double [5];
   for (int i=0;i<5;i++)
   {
       VX[i]=Vx[i];
       VY[i]=Vy[i];
       VZ[i]=Vz[i];
       t[i]=T[i];
   }

}

/******************************** Axis X *************************/


float* integration_gyro::Integration_gyro_X()

{

int size= 5;

float* angx=new float [size-1];


for(int i=0;i<size-1;i++)

    {
    angx[i]=(this->VX[i]+(this->VX[i+1]-this->VX[i])/2)*(t[i+1]-t[i])+this->VX[0];
    }
return angx;
}
/******************************** Axis Y *************************/


float* integration_gyro::Integration_gyro_Y()

{

int size= 5;

float* angy=new float [size-1];


for(int i=0;i<size-1;i++)

    {
    angy[i]=(this->VY[i]+(this->VY[i+1]-this->VY[i])/2)*(t[i+1]-t[i])+this->VY[0];
    }
return angy;
}

/******************************** Axis Z *************************/


float* integration_gyro::Integration_gyro_Z()

{

int size= 5;

float* angz=new float [size-1];


for(int i=0;i<size-1;i++)

    {
    angz[i]=(this->VY[i]+(this->VY[i+1]-this->VY[i])/2)*(t[i+1]-t[i])+this->VY[0];
    }
return angz;
}
/******************************test**************************************/
void integration_gyro::test()

{
float* testX=new float [4];
float* testY=new float [4];
const float test[4]={0,1,1,0};
const double temps[4]={0.0,1.0,2.0,3.0};
integration_gyro t1(test,test,test,temps);
testX=t1.Integration_gyro_X();
testY=t1.Integration_gyro_Y();
for(int i=0;i<4;i++)
{

   cout<<"l'element "<<i<<" est "<<testX[i]<<endl;

}
if(testX[0]+testX[1]+testX[2]==2 && testY[0]+testY[1]+testY[2]==2)
{
    cout<<"ok :) "<<endl;

}else
{
   cout<<"NOOO :'("<<endl;

}
}
