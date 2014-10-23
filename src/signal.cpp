#include "signal.h"


Signal::Signal(SampleType* unVecteurTemps,SampleType* unSignal,int taille)
{
    _taille       = taille;
    _vecteurTemps = unVecteurTemps;
    _signal       = unSignal;
}

double* Signal::passeBas(FrequencyType freqFiltre,FrequencyType freqEch)
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
double* Signal::regulariseEchantillonage(float fEch)
{
    ////////////////:TESTS SUR LES TAILLES DE TABLEAU A INSERER SINON BUG//////////////////

    // Periode d'échantillonage
    int tEch = 1/fEch;
    // Taille du tableau résultat


    int tailleTabRes = (int)((_vecteurTemps[_taille-2] - _vecteurTemps[1] )/2 );

    double *res = new double[tailleTabRes];

    // Indice de parcours du signal origine
    int iSrc = 0;
    // Indice de parcours du signal résultat
    int iRes = 0;
    // Temps correspondant à l'indice courant dans le signal résutat
    double tRes = _vecteurTemps[iSrc];

    // Parcours du signal résultat
    for (iRes=0;iRes<tailleTabRes;iRes++)
    {
        while (_vecteurTemps[iSrc]<tRes)
            iSrc++;

        // Temps et valeurs à gauche et droite de la valeur courante à remplir
        double tGauche = _vecteurTemps[iSrc-1],tDroite = _vecteurTemps[iSrc];
        double vGauche = _signal[iSrc-1],vDroite   = _signal[iSrc];

        // Interpolation des deux valeurs pour l'entree courante
        double denomi = tDroite-tGauche;
        res[iRes]     = ((tRes-tGauche)*vGauche + (tDroite-tRes)*vDroite)/denomi;

        // Temps suivant...
        tRes    += tEch;
    }

    return res;
}


// Renvoie la colonne col de la matrice sous forme de vecteur

/*float* Signal::vecteurColonne(float **matrice,int col,int nbLignes)
{
    float *res = new float[nbLignes];

    for(int ligne=0;ligne<nbLignes;ligne++)
    {
        res[ligne] = matrice[ligne][col];

    }
    return res;
}*/
