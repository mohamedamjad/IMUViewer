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




    void regulariseEchantillonage(SampleType);

    //static float* vecteurColonne(float **,int,int);
    double  getSignal(int i);
    SampleType *getSignal()const;
    double getTemps(int i);
    SampleType *getTemps()const;
    int getTaille();

    void integre();
    void doubleIntegre();
    SampleType getSignalIntegre(int i);
    SampleType getSignalDoubleIntegre(int i);
    double getMaxSignal();
    double normalizeVector(double val);

private:
    SampleType *_vecteurTemps;


    SampleType *_signal;
    // Signal brut intégré
    SampleType *_signalIntegre;
    // Signal brut doublement intégré
    SampleType *_signalDoubleIntegre;
    int _taille;
};

#endif // TRAITEMENTSIGNAL_H
