#ifndef TRAITEMENTSIGNAL_H
#define TRAITEMENTSIGNAL_H

#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include <iostream>
//////////////////////// NECESSAIRE POUR TRANSFORM VERIFIER CE QUE CELA FAIT BIEN COMME IL FAUT
#include <algorithm>

#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"


using namespace Aquila;

class Signal
{
public:
    Signal(SampleType **,int,int,int,int);
    Signal(const Signal&);

    ~Signal();
    Signal* operator+(Signal);
    Signal* operator-(Signal);
    Signal* operator*(Signal);
    void passeBas(FrequencyType,FrequencyType,bool);

    static void changeRepere(Signal*,Signal*,Signal*,Signal,Signal,Signal);


    void regulariseEchantillonage(SampleType);

    //static float* vecteurColonne(float **,int,int);
    double getSignal(int i);
    void setSignal(SampleType val,int i);
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
    void calculStats();
    SampleType getEcartType(int);
    SampleType getMoyenne(int);
    SampleType getMin(int);
private:
    SampleType* produitSignalMultiple2(int* );
    static SampleType* integreUnSignal(SampleType *,SampleType *,int);
    SampleType moyenne(int ,int);
    SampleType ecartType(int,int,SampleType);
    SampleType amplitude(int,int);
    SampleType min(int,int);

    SampleType *_vecteurTemps;

    SampleType *_signal;
    // Signal brut intégré
    SampleType *_signalIntegre;
    // Signal brut doublement intégré
    SampleType *_signalDoubleIntegre;
    // Moyenne du signal calculée en glissant une fenetre
    SampleType *_signalMoyenne;
    // Ecart-type du signal calculé en glissant une fenetre
    SampleType *_signalEcartType;
    // Amplitude calculée en glissant une fenetre
    SampleType *_signalAmplitude;
    // Minimum calculé en glissant une fenetre
    SampleType *_signalMin;
    int _taille;
    bool estIntegre = false;
    bool estDoubleIntegre = false;
    bool _estStatistique = false;
    int _tailleFenetreStats;
};

#endif // TRAITEMENTSIGNAL_H
