#include "signal.h"




Signal::Signal(SampleType** uneMatrice,int taille,int colTemps,int colSignal)
{
    _taille       = taille;
    _signal       = new SampleType[taille];
    _vecteurTemps = new SampleType[taille];

    for (int i=0;i<taille;i++)
    {
        _vecteurTemps[i] = uneMatrice[colTemps][i];
        _signal[i]       = uneMatrice[colSignal][i];

    }

}

double  Signal::getSignal(int i)
{
    return this->_signal[i];


}

Signal::~Signal()
{
    delete _signal;
    delete _vecteurTemps;
}


void Signal::passeBas(FrequencyType freqFiltre,FrequencyType freqEch,bool reEchantillone=false)
{

   if (reEchantillone)this->regulariseEchantillonage(freqEch);

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
    SampleType *res = new SampleType[_taille];
    fft->ifft(spectre, res);

    delete _signal;
    _signal = res;
}

// Régularise le pas d'échantillonage du signal
void Signal::regulariseEchantillonage(SampleType fEch)
{
    if (_taille > 1)
    {

        // Periode d'échantillonage en s
        SampleType tEch = 1/fEch;
        // Taille du tableau résultat

        int tailleTabRes = (int)((_vecteurTemps[_taille-1] - _vecteurTemps[0] )*fEch );

        SampleType *resTemps  = new SampleType[tailleTabRes];
        SampleType *resSignal = new SampleType[tailleTabRes];

        // Indice de parcours du signal origine
        int iSrc = 1;
        // Premieres valeurs du tableau résultat
        resSignal[0] = _signal[0];
        resTemps[0]  = _vecteurTemps[0];

        // Temps correspondant à l'indice courant dans le signal résutat
        SampleType tRes = _vecteurTemps[0]+tEch;

        // Parcours du signal résultat
        for (int iRes=1;iRes<tailleTabRes;iRes++)
        {
            while ((_vecteurTemps[iSrc]<tRes) && (iSrc < _taille-1))
                iSrc++;
            // Temps et valeurs à gauche et droite de la valeur courante à remplir
            SampleType tGauche = _vecteurTemps[iSrc-1],tDroite = _vecteurTemps[iSrc];
            SampleType vGauche = _signal[iSrc-1],vDroite   = _signal[iSrc];

            // Interpolation des deux valeurs pour l'entree courante
            SampleType denomi   = tDroite-tGauche;

            resSignal[iRes] = (1 - ((tRes-tGauche)/denomi))*vGauche + (1 - ((tDroite-tRes)/denomi))*vDroite;
            resTemps[iRes]  = tRes;


            // Temps suivant...
            tRes    += tEch;
        }

        delete _signal;
        delete _vecteurTemps;

        _taille       = tailleTabRes;
        _signal       = resSignal;
        _vecteurTemps = resTemps;
    }
}


SampleType* Signal::getSignal()const
{
    return _signal;

}

SampleType *Signal::getTemps()const
{
    return _vecteurTemps;

}

int Signal::getTaille()
{
    return _taille;

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



