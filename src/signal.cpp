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

double Signal::getTemps(int i)
{

    return this->_vecteurTemps[i];
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

    /* Pour le calcul de la transformée de Fourier, il est nécessaire que la taille du signal
       soit un multiple de 2
    */
    // Fabrication du signal temporaire
    int taillePuiss2;
    SampleType * signalPuiss2=produitSignalMultiple2(&taillePuiss2);


    // Recuperation de la meilleure transformée adaptée à la taille
    auto fft = FftFactory::getFft(taillePuiss2);

    // Transformée de Fourier du signal
    SpectrumType spectre = fft->fft(signalPuiss2);

    ////////////// Generation du spectre filtre /////////////////
    SpectrumType spectreFiltre(taillePuiss2);

    for (int i = 0; i < taillePuiss2; i++)
    {
        if (i < (taillePuiss2 * freqFiltre / freqEch))
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
    ////////////////////////////////////////////////////////////
    // Multiplication des deux signaux
    std::transform(std::begin(spectre),std::end(spectre),std::begin(spectreFiltre),std::begin(spectre),[] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; });

    // Fourier inverse ; retour dans l'espace temporel
    SampleType *resIfft = new SampleType[taillePuiss2];
    fft->ifft(spectre, resIfft);

    // Recopie des valeurs qui nous intéressent
    for (int i=0;i<_taille;i++)
        _signal[i] = resIfft[i];

}

/* Produit un nouveau signal (nouvSig) de taille puissance de 2 immédiatement supérieur à la taille du signal (nouvTaille) courant
    Les valeurs supplémentaires sont à zéro

*/
SampleType* Signal::produitSignalMultiple2(int* nouvTaille)
{
    // Identification de la taille
    int t;
    for (t=2;t<_taille;t*=2);

    SampleType* nouvSig= new SampleType[t];

    for (int i=0;i<_taille;i++)// Recopie des valeurs du signal
        nouvSig[i] = _signal[i];
    for (int i=_taille;i<t;i++)// Le reste à zero
        nouvSig[i] = 0;

    *nouvTaille = t;

    return nouvSig;

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


SampleType* Signal::integreUnSignal(SampleType* unTemps,SampleType *unSignal,int uneTaille)
{
    SampleType* res = new SampleType[uneTaille];
    res[0] = 0;
    for (int i=1;i<uneTaille;i++)
    {
        // Formule roots
        //res[i] = ((unSignal[i]-unSignal[i-1])/2)*(unTemps[i]-unTemps[i-1]);
        double deltaX = unTemps[i]-unTemps[i-1];
        double y1     = unSignal[i-1];
        double y2     = unSignal[i];
        double yMinAbs = (abs(y1)<abs(y2)) ? abs(y1):abs(y2);
        double deltaY = abs(y2-y1);
        double deltaIntegre = 0;
        // Cas 1 : aire triangle + aire rectangle
        if ((y1>0) && (y2>0))
        {
            deltaIntegre = deltaY*deltaX/2+deltaX*yMinAbs;
        }
        // Cas 2 : idem en négatif
        else if ((y1<0) && (y2<0))
        {
            deltaIntegre = -(deltaY*deltaX/2+deltaX*yMinAbs);
        }
        // Cas 3 : un y positif un autre négatif
        else
        {
            // Thales
            double a = (y2!=0) ? deltaX*abs(y1/y2) : deltaX;
            double b = (y1!=0) ? deltaX*abs(y2/y1) : deltaX;

            deltaIntegre = a*y1/2+b*y2/2;

        }

        res[i] = res[i-1] + deltaIntegre;

    }
    return res;
}


void Signal::integre()
{
    this->_signalIntegre= Signal::integreUnSignal(this->_vecteurTemps,this->_signal,this->getTaille());
}


void Signal::doubleIntegre()
{
    integre();
    this->_signalDoubleIntegre= Signal::integreUnSignal(this->_vecteurTemps,this->_signalIntegre,this->getTaille());
}


SampleType  Signal::getSignalIntegre(int i)
{
    return this->_signalIntegre[i];
}

SampleType  Signal::getSignalDoubleIntegre(int i)
{
    return this->_signalDoubleIntegre[i];
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

double Signal::getMaxSignal ()
{
    double max=0;

    for(int i=0;i<this->getTaille ();i++)
    {
        if (max>fabs(this->getSignal (i)))
            continue;
        else
            max=fabs(this->getSignal (i));
    }

    return max;
}

double Signal::normalizeVector(double val )
{
    double result;

    result=val*9/this->getMaxSignal();

    return result;
}
