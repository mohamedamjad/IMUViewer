#ifndef TRAITEMENTSIGNAL_H
#define TRAITEMENTSIGNAL_H

#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"

//////////////////////// NECESSAIRE POUR TRANSFORM VERIFIER CE QUE CELA FAIT BIEN COMME IL FAUT
#include <algorithm>



using namespace Aquila;

class TraitementSignal
{
public:
    TraitementSignal(SampleType *,int);
    double* passeBas(FrequencyType,FrequencyType);
    void regulariseEchantillonage(float);
    //static float* vecteurColonne(float **,int,int);

private:
    SampleType *_signal;
    int _taille;
};

#endif // TRAITEMENTSIGNAL_H
