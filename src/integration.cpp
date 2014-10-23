#include <integration.h>
#include <math.h>
#include <stdio.h>
#include "csv.h"
#include <integration.h>
#include <iostream>

using namespace std;



Integration::Integration()
{
//ctor
}
Integration::Integration(float** S,int n)
{
   AX=new float [n];
   AY=new float [n];
   AZ=new float [n];
   t=new float [n];
   for (int i=0;i<n;i++)
   {
       AX[i]=S[2][i];
       AY[i]=S[3][i];
       AZ[i]=S[4][i];
       t[i]=S[0][i];
   }

}
/******************************** get element of table *************************/

float Integration:: getElt(int i)
{
return this->AX[i];
}

//******************************** Axis X *************************//


float* Integration::Integration_accelo_X(int n)
{

int size= n;

float* Vtx=new float [size-1];
float* X=new float [size-2];
//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vtx[i]=(this->AX[i]+(this->AX[i+1]-this->AX[i])/2)*(this->t[i+1]-this->t[i])+this->AX[0];
    }
//Calcul of position

//int sizevt= size-1;

for(int i=0;i<size-2;i++)

    {
    X[i]=(Vtx[i]+(Vtx[i+1]-Vtx[i])/2)*(t[i+1]-t[i])+Vtx[0];
    }
return X;
}

//******************************** Axis Y *************************//


float* Integration::Integration_accelo_Y(int n)

{

int size= n ;
float* Vty=new float [size-1];
float* Y=new float [size-2];

//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vty[i]=(this->AY[i]+(this->AY[i+1]-this->AY[i])/2)*(this->t[i+1]-this->t[i])+this->AY[0];
    }
//Calcul of position


for(int i=0;i<size-2;i++)

    {
    Y[i]=(Vty[i]+(Vty[i+1]-Vty[i])/2)*(t[i+1]-t[i])+Vty[0];
    }
return Y;
}

//******************************** Axis Z *************************//


float* Integration::Integration_accelo_Z(int n)

{

int size= n;

float* Vtz=new float [size-1];
float* Z=new float [size-2];
/*//remove the gravity
for(int i=0;i<size;i++)
    {
    this->AZ[i]=this->AZ[i]-9.81;
    }*/
//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vtz[i]=(this->AZ[i]+(this->AZ[i+1]-this->AZ[i])/2)*(this->t[i+1]-this->t[i])+this->AZ[0];
    }
//Calcul of position


for(int i=0;i<size-2;i++)

    {
    Z[i]=(Vtz[i]+(Vtz[i+1]-Vtz[i])/2)*(t[i+1]-t[i])+Vtz[0];
    }
return Z;
}

/*//teeeeeest//
void Integration::test()

{
 float* testX=new float [4];
float* testY=new float [4];
const float test[4]={0,1,1,0};
const double temps[4]={0.0,1.0,2.0,3.0};
Integration t1(test,test,test,temps);
testX=t1.Integration_accelo_X();
testY=t1.Integration_accelo_Y();
for(int i=0;i<3;i++)
{

   cout<<"l'element "<<i<<" est "<<testX[i]<<endl;
   cout<<"l'element "<<i<<" est "<<testY[i]<<endl;

}
if(testX[0]+testX[1]+testX[2]==2 && testY[0]+testY[1]+testY[2]==2)
{
    cout<<"ok"<<endl;

}else
{
   cout<<"NOOO :'("<<endl;

}
}*/

Integration::~Integration()
{
  delete AX;
  delete AY;
  delete AZ;
  delete t;
}














