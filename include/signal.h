#ifndef TRAITEMENTSIGNAL_H
#define TRAITEMENTSIGNAL_H

#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"

//////////////////////// NECESSAIRE POUR TRANSFORM VERIFIER CE QUE CELA FAIT BIEN COMME IL FAUT
#include <algorithm>



using namespace Aquila;

class Signal
{
public:
    Signal(SampleType *,SampleType *,int);
    void passeBas(FrequencyType,FrequencyType,bool);
    void regulariseEchantillonage(float);
    //static float* vecteurColonne(float **,int,int);

private:
    SampleType *_vecteurTemps;
    SampleType *_signal;
    int _taille;
};

#endif // TRAITEMENTSIGNAL_H
