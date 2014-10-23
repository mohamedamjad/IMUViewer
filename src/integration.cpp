#include "integration.h"
#include <math.h>
#include <stdio.h>
#include <integration.h>
using namespace std;



Integration::Integration()
{
//ctor
}
Integration::Integration(const float AX[5],const float AY[5],const float AZ[5],const double t[5])
{
   AX=AX;
   AY=AY;
   AZ=AZ;
   t=t;

}


//******************************** get element of table *************************//

float Integration:: getElt(int i)
{
return this->AX[i];
}

//******************************** Size of table *************************//

int Integration:: getSize(float* AX)
{
int i=0;
while(AX!=NULL)
{
  i++;
}

return i;
cout<<"la taille du tableau "<<i<<endl
}

//******************************** Axis X *************************//


float* Integration::Integration_accelo_X()

{

int size= getSize(this->AX);

float* Vtx=new float [size-1];
float* X=new float [size-2];
//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vtx[i]=(this->AX[i]+(this->AX[i+1]-this->AX[i])/2)*(this->t[i+1]-this->t[i])+this->AX[0];
    }
//Calcul of position

int sizevt= getSize(Vtx);

for(int i=0;i<sizevt-1;i++)

    {
    X[i]=(Vtx[i]+(Vtx[i+1]-Vtx[i])/2)*(t[i+1]-t[i])+Vtx[0];
    }
return X;
}

//******************************** Axis Y *************************//

float* Integration::Integration_accelo_Y()

{

int size= getSize(this->AY);
float* Vty=new float [size-1];
float* Y=new float [size-2];

//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vty[i]=(this->AY[i]+(this->AY[i+1]-this->AY[i])/2)*(this->t[i+1]-this->t[i])+this->AY[0];
    }
//Calcul of position

int sizevt= getSize(Vty);

for(int i=0;i<sizevt-1;i++)

    {
    Y[i]=(Vty[i]+(Vty[i+1]-Vty[i])/2)*(t[i+1]-t[i])+Vty[0];
    }
return Y;
}

//******************************** Axis Z *************************//


float* Integration::Integration_accelo_Z()

{

int size= getSize(this->AZ);

float* Vtz=new float [size-1];
float* Z=new float [size-2];
//remove the gravity
for(int i=0;i<size;i++)
    {
    this->AZ[i]=this->AZ[i]-9.81;
    }
//Calcul of velocity
for(int i=0;i<size-1;i++)

    {
    Vtz[i]=(this->AZ[i]+(this->AZ[i+1]-this->AZ[i])/2)*(this->t[i+1]-this->t[i])+this->AZ[0];
    }
//Calcul of position

int sizevt= getSize(Vtz);

for(int i=0;i<sizevt-1;i++)

    {
    Z[i]=(Vtz[i]+(Vtz[i+1]-Vtz[i])/2)*(t[i+1]-t[i])+Vtz[0];
    }
return Z;
}



Integration::~Integration()
{
  //delete A;
  //delete V;
  //delete t;
}













