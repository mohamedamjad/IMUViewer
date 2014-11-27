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


Signal::Signal(const Signal& unSignal)
{
    _taille       = unSignal._taille;
    _signal       = new SampleType[_taille];
    _vecteurTemps = new SampleType[_taille];

    // Recopie du temps et du signal
    for (int i=0;i<_taille;i++)
    {
        _vecteurTemps[i] = unSignal._vecteurTemps[i];
        _signal[i]       = unSignal._signal[i];
    }
    // Drapeau d'intégration
    estIntegre      = unSignal.estIntegre;
    estDoubleIntegre= unSignal.estDoubleIntegre;
    // Recopie des signaux intégrés si le signal l'a été
    if (unSignal.estIntegre)
    {
        _signalIntegre = new SampleType[_taille];
        for (int i=0;i<_taille;i++)
        {
            _signalIntegre[i] = unSignal._signalIntegre[i];
        }
    }
    if (unSignal.estDoubleIntegre)
    {
        _signalDoubleIntegre = new SampleType[_taille];
        for (int i=0;i<_taille;i++)
        {
            _signalDoubleIntegre[i] = unSignal._signalDoubleIntegre[i];
        }
    }
}


Signal* Signal::operator-(Signal lautre)
{
    Signal *res = new Signal (*this);

    if (this->_taille == lautre._taille)
    {
        for (int i=0;i<_taille;i++)
        {
            res->_signal[i] -= lautre._signal[i];
        }
    }
    // Si le signal est d'ores et déjà intégré, on réintègre apres soustraction
    if (this->estIntegre)
        res->integre();
    if (this->estDoubleIntegre)
        res->doubleIntegre();
    return res;
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
    if ((_taille > 1) && (fEch != 0))
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

void Signal::changeRepere(Signal *srcX,Signal *srcY,Signal *srcZ, Signal orientationX,Signal orientationY,Signal orientationZ)
{
    int t = srcX->getTaille();
    // On vérifie que les six signaux ont la même taille
    if ((srcX->getTaille() == t) && (srcX->getTaille() == t))
    {

        if ((orientationX.getTaille() == t) && (orientationY.getTaille() == t) && (orientationZ.getTaille() == t))
        {
            for (int i=0;i<t;i++)
            {
                double alpha = orientationX._signal[i];
                double teta  = orientationY._signal[i];
                double gamma = orientationZ._signal[i];

                srcX->_signal[i] = cos(alpha)*cos(gamma)*srcX->_signal[i]-sin(gamma)*cos(alpha)*srcY->_signal[i]
                        +sin(alpha)*srcZ->_signal[i];

                srcY->_signal[i] = (sin(teta)*sin(alpha)*cos(gamma)+cos(teta)*sin(gamma))*srcX->_signal[i]
                        -(sin(gamma)*sin(teta)*sin(alpha)+cos(gamma)*cos(teta))*srcY->_signal[i]
                        -(sin(teta)*cos(alpha)) *srcZ->_signal[i];

                srcZ->_signal[i] = (cos(teta) * sin(alpha) * cos(gamma) - sin(teta)*sin(gamma))*srcX->_signal[i]
                        +(sin(gamma)*cos(teta)*sin(alpha)-cos(gamma)*sin(teta))*srcY->_signal[i]
                        +cos(teta)*cos(alpha)*srcZ->_signal[i];
            }
        }
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
            deltaIntegre = deltaY*deltaX/2.0+deltaX*yMinAbs;
        }
        // Cas 2 : idem en négatif
        else if ((y1<0) && (y2<0))
        {
            deltaIntegre = -(deltaY*deltaX/2.0+deltaX*yMinAbs);
        }
        // Cas 3 : un y positif un autre négatif
        else
        {
            // Thales
            double a = (y2!=0) ? deltaX*abs(y1/y2) : deltaX;
            double b = (y1!=0) ? deltaX*abs(y2/y1) : deltaX;

            deltaIntegre = a*y1/2.0+b*y2/2.0;

        }

        res[i] = res[i-1] + deltaIntegre;

    }
    return res;
}


void Signal::integre()
{
    estIntegre = true;
    this->_signalIntegre= Signal::integreUnSignal(this->_vecteurTemps,this->_signal,this->getTaille());
}


void Signal::doubleIntegre()
{
    if (estIntegre == false)integre();
    estDoubleIntegre = true;
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

void Signal::calculStats()
{
    if (_taille > (tailleFenetreStats+1))
    {
        _signalMoyenne  = new SampleType[_taille-tailleFenetreStats+1];
        _signalEcartType= new SampleType[_taille-tailleFenetreStats+1];
        _signalAmplitude= new SampleType[_taille-tailleFenetreStats+1];

        int delta       = (tailleFenetreStats-1)/2;

        // Parcours du signal
        for (int i=delta;i<_taille-delta;i++)
        {
            _signalMoyenne[i-delta]   = moyenne(i-delta,i+delta);
            _signalEcartType[i-delta] = ecartType(i-delta,i+delta,_signalMoyenne[i-delta]);
            _signalAmplitude[i-delta] = amplitude(i-delta,i+delta);
        }
    }
}
// Calcul la moyenne du signal brut sur une fenetre donnée pour la classif
SampleType Signal::moyenne(int iDeb,int iFin)
{
    SampleType somme = 0;
    for (int i=iDeb;i<=iFin;i++)
        somme += _signal[i];
    return somme/tailleFenetreStats;
}

SampleType Signal::ecartType(int iDeb,int iFin,SampleType moyenne)
{
    SampleType somme = 0;
    for (int i=iDeb;i<=iFin;i++)
    {
        somme += pow(_signal[i]-moyenne,2.0);
    }
    // somme/ taille => variance
    return sqrt(somme/tailleFenetreStats);
}

SampleType Signal::amplitude(int iDeb,int iFin)
{
    SampleType min = INFINITY;
    SampleType max = -INFINITY;
    for (int i=iDeb;i<=iFin;i++)
    {
        if (_signal[i]<min)min=_signal[i];
        if (_signal[i]>max)max=_signal[i];
    }
    return max - min;
}
