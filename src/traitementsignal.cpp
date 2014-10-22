#include "traitementsignal.h"


TraitementSignal::TraitementSignal(SampleType* unSignal,int taille)
{
    _taille = taille;
    _signal = unSignal;
}

double* TraitementSignal::passeBas(FrequencyType freqFiltre,FrequencyType freqEch)
{
    auto fft = FftFactory::getFft(_taille);

    // Transformée de Fourier du signal
    SpectrumType spectre = fft->fft(_signal);

    // Generation du spectre filtre
    SpectrumType spectreFiltre(_taille);
    for (int i = 0; i < _taille; i++)
    {
        if (i < (_taille * freqFiltre / freqEch))
        {
            // passband
            spectreFiltre[i] = 1.0;
        }
        else
        {
            // stopband
            spectreFiltre[i] = 0.0;
        }
    }

    // Multiplication des deux signaux
    std::transform(std::begin(spectre),std::end(spectre),std::begin(spectreFiltre),std::begin(spectre),[] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; });

    // Fourier inverse ; retour dans l'espace temporel
    double *res = new double[_taille];
    fft->ifft(spectre, res);

    return res;
}

// Régularise le pas d'échantillonage du signal
void TraitementSignal::regulariseEchantillonage(float fEch)
{
    // On
    //for()

}
// Renvoie la colonne col de la matrice sous forme de vecteur

/*float* TraitementSignal::vecteurColonne(float **matrice,int col,int nbLignes)
{
    float *res = new float[nbLignes];

    for(int ligne=0;ligne<nbLignes;ligne++)
    {
        res[ligne] = matrice[ligne][col];

    }
    return res;
}*/
