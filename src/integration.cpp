#include <integration.h>
#include <math.h>
#include <stdio.h>
#include <integration.h>
#include <iostream>

using namespace std;



Integration::Integration()
{
//ctor
}
Integration::Integration(const float Ax[5],const float Ay[5],const float Az[5],const double T[5])
{
   AX=new float [5];
   AY=new float [5];
   AZ=new float [5];
   t=new double [5];
   for (int i=0;i<5;i++)
   {
       AX[i]=Ax[i];
       AY[i]=Ay[i];
       AZ[i]=Az[i];
       t[i]=T[i];
   }

}
/******************************** get element of table *************************/

float Integration:: getElt(int i)
{
return this->AX[i];
}
//******************************** Size of table *************************//

int Integration:: getSize(float* AX)
{
int i=0;
for(i=0;i<5;i++)
{

}

return i;

}

//******************************** Axis X *************************//
//récupérer la taille par la fonction qui retourne le nombre de ligne

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

//int sizevt= size-1;

for(int i=0;i<size-2;i++)

    {
    X[i]=(Vtx[i]+(Vtx[i+1]-Vtx[i])/2)*(t[i+1]-t[i])+Vtx[0];
    }
return X;
}

//******************************** Axis Y *************************//
//récupérer la taille par la fonction qui retourne le nombre de ligne
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

//int sizevt= size-1;

for(int i=0;i<size-2;i++)

    {
    Y[i]=(Vty[i]+(Vty[i+1]-Vty[i])/2)*(t[i+1]-t[i])+Vty[0];
    }
return Y;
}

//******************************** Axis Z *************************//
//récupérer la taille par la fonction qui retourne le nombre de ligne

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

//int sizevt= getSize(Vtz);

for(int i=0;i<size-2;i++)

    {
    Z[i]=(Vtz[i]+(Vtz[i+1]-Vtz[i])/2)*(t[i+1]-t[i])+Vtz[0];
    }
return Z;
}

//teeeeeest//
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
}

Integration::~Integration()
{
  delete AX;
  delete AY;
  delete AZ;
  delete t;
}














