#ifndef TRAITEMENTSIGNAL_H
#define TRAITEMENTSIGNAL_H

#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include <iostream>
//////////////////////// NECESSAIRE POUR TRANSFORM VERIFIER CE QUE CELA FAIT BIEN COMME IL FAUT
#include <algorithm>



using namespace Aquila;

class Signal
{
public:
    Signal(SampleType **,int,int,int);
    ~Signal();
    void passeBas(FrequencyType,FrequencyType,bool);


    double  getSignal(int i);

    void regulariseEchantillonage(SampleType);

    //static float* vecteurColonne(float **,int,int);

    SampleType *getSignal()const;
    SampleType *getTemps()const;
    int getTaille();

private:
    SampleType *_vecteurTemps;
    SampleType *_signal;
    int _taille;
};

#endif // TRAITEMENTSIGNAL_H
