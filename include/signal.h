#ifndef TRAITEMENTSIGNAL_H
#define TRAITEMENTSIGNAL_H


#include <iostream>
#include <algorithm>
// Librairie de traitement du signal Aquila
#include "aquila/global.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"


using namespace Aquila;

/*
    *\class Signal
    * \brief IMU Viewer : Classe permettant de représenter un signal, des signaux associés issus d'intégrations...
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class Signal
{
public:
    /**
        * \fn Signal
        * \brief  Constructeur
        * \param uneMatrice Double pointeur de SampleType de la forme suivante [colCapteur][nb échantillons] (SampleType**)
        * \param taille Nombre d'échantillons dans le jeu de données (int)
        * \param colTemps Identifiant de la colonne contenant le temps (int)
        * \param colSignal Identifiant de la colonne contenant le signal (int)
        * \param tailleFenetreStats Taille de la fenetre à glisser sur le signal pour le calcul des statistiques (int)
    */
    Signal(SampleType **,int,int,int,int);
    /**
        * \fn Signal
        * \brief  Constructeur par copie
    */
    Signal(const Signal&);
    /**
        * \fn ~Signal
        * \brief  Destructeur
    */
    ~Signal();
    /**
        * \fn Operator+
        * \brief  Addition de signaux terme à terme (recalcule l'intégration et les stats si le signal d'origine était intégré ou avait l'objet de statistiques)
        * \return Signal*
    */
    Signal* operator+(Signal);
    /**
        * \fn Operator-
        * \brief  Soustraction de signaux terme à terme (recalcule l'intégration et les stats si le signal d'origine était intégré ou avait l'objet de statistiques)
        * \return Signal*
    */
    Signal* operator-(Signal);
    /**
        * \fn Operator*
        * \brief  Multiplication de signaux terme à terme (recalcule l'intégration et les stats si le signal d'origine était intégré ou avait l'objet de statistiques)
        * \return Signal*
    */
    Signal* operator*(Signal);

    /**
        * \fn passeBas
        * \brief  Effectue un filtre passe bas sur le signal
        * \param freqFiltre fréquence du filtre en Hz (Aquila::FrequencyType)
        * \param freqFiltre fréquence d'échantillonage en Hz (Aquila::FrequencyType)
        * \param reEchantillone Indique si un rééchantillonage doit être effectué sur le signal (le filtre marche uniquement avec un signal échantilloné de manière régulière)
    */
    void passeBas(FrequencyType,FrequencyType,bool);
    /**
        * \fn regulariseEchantillonage
        * \brief  Rééchantillone le signal par interpolation linéaire
        * \param freqFiltre fréquence du filtre en Hz (Aquila::FrequencyType)
    */
    void regulariseEchantillonage(FrequencyType);
    /**
        * \fn getSignal
        * \brief Accesseur pour un élément du signal
        * \param i Indice de l'élément (int)
        * \return Le ieme élément du signal (SampleType)
    */
    SampleType getSignal(int);
    /**
        * \fn setSignal
        * \brief Méthode d'écriture d'u signa'une valeur du signal
        * \param val Valeur à setter dans le signal (SampleType)
        * \param i Indice de l'élément (int)
    */
    void setSignal(SampleType,int);
    /**
        * \fn getTemps
        * \brief Accesseur pour un élément du vecteur de temps
        * \param i Indice de l'élément (int)
        * \return Le ieme élément du signal (SampleType)
    */
    SampleType getTemps(int);
    /**
        * \fn getTaille
        * \brief Renvoie le nombre d'échantillons du signal
        * \return Le nb d'échantillons (int)
    */
    int getTaille();
    /**
        * \fn integre
        * \brief Intègre le signal (ne modifie pas les valeurs du signal)
    */
    void integre();
    /**
        * \fn doubleIntegre
        * \brief Double intègre le signal (ne modifie pas les valeurs du signal)
    */
    void doubleIntegre();
    /**
        * \fn getSignalIntegre
        * \brief Accesseur pour un élément du signal intégré
        * \param i Indice de l'élément (int)
        * \return Le ieme élément du signal (SampleType)
    */
    SampleType getSignalIntegre(int);
    /**
        * \fn getSignalDoubleIntegre
        * \brief Accesseur pour un élément du signal doublement intégré
        * \param i Indice de l'élément (int)
        * \return Le ieme élément du signal (SampleType)
    */
    SampleType getSignalDoubleIntegre(int);
    /**
        * \fn getMaxSignal
        * \brief Retourne la valeur max du signal
        * \return La valeur max du signal(SampleType)
    */
    SampleType getMaxSignal();
    /**
        * \fn normalizeVector
        * \brief Normalise un nombre en fonction du max du signal
        * \param val Nombre à normaliser (SampleType)
        * \param h  la hauteur de l'espace d'affichage
        * \return Le nombre normalisé (SampleType)
    */
    SampleType normalizeVector(SampleType, int h);
    /**
        * \fn calculStats
        * \brief Lance le calcul des statistiques sur le signal (crée un tableau de taille du vecteur -_tailleFenetreStats+1)
    */
    void calculStats();
    /**
        * \fn getEcartType
        * \brief Recuperation de l'écart type autour du ieme échantillon
        * \param i Indice de l'élément dans le signal (int)
        * \return La valeur de l'écart type (SampleType)
    */
    SampleType getEcartType(int);
    /**
        * \fn getMoyenne
        * \brief Recuperation de la moyenne autour du ieme échantillon
        * \param i Indice de l'élément (int)
        * \return La valeur de la moyenne (SampleType)
    */
    SampleType getMoyenne(int);
    /**
        * \fn getMin
        * \brief Recuperation du minimum autour du ieme échantillon
        * \param i Indice de l'élément (int)
        * \return La valeur du minimum (SampleType)
    */
    SampleType getMin(int);
    /**
        * \fn changeRepere
        * \brief Change trois signaux x y z dans un repère inertiel à un repère absolu en prenant en compte l'orientation
        * \param srcX Signal d'évolution du x (Signal)
        * \param srcY Signal d'évolution du y (Signal)
        * \param srcZ Signal d'évolution du z (Signal)
        * \param orientationX Signal contenant l'orientation selon l'axe X
        * \param orientationY Signal contenant l'orientation selon l'axe Y
        * \param orientationZ Signal contenant l'orientation selon l'axe Z
    */
    static void changeRepere(Signal*,Signal*,Signal*,Signal,Signal,Signal);
private:
    /**
        * \fn produitSignalMultiple2
        * \brief Crée un vecteur basé sur le vecteur signal ayant une taille puissance de 2 immédiatement supérieure à la taille courante du signal en ajoutant des zéros pour combler les vides
        * \param nouvTaille Contiendra la taille du vecteur généré (int*)
        * \return Le vecteur créé
    */
    SampleType* produitSignalMultiple2(int* );
    /**
        * \fn integreUnSignal
        * \brief Intègre un signal (alogirthme basé sur le calcul des aires)
        * \param unTemps Vecteur de temps (SampleType*)
        * \param unSignal Signal à intégrer (SampleType*)
        * \param uenTaille Taille du signal à intégrer (int)
        * \return Le signal intégré (SampleType*)
    */
    static SampleType* integreUnSignal(SampleType *,SampleType *,int);
    /**
        * \fn moyenne
        * \brief Statistiques : lance le calcul des moyennes locales
        * \param iDeb Indice correspondant au début de la fenetre dans le signal
        * \param iFin Indice correspondant à la fin de la fenetre dans le signal
        * \return La moyenne locale (SampleType)
    */
    SampleType moyenne(int ,int);
    /**
        * \fn ecartType
        * \brief Statistiques : lance le calcul des écarts-types locaux
        * \param iDeb Indice correspondant au début de la fenetre dans le signal
        * \param iFin Indice correspondant à la fin de la fenetre dans le signal
        * \param moyenne Moyenne locale
        * \return L'écart-type local (SampleType)
    */
    SampleType ecartType(int,int,SampleType);
    /**
        * \fn amplitude
        * \brief Statistiques : lance le calcul des amplitudes locales (différence entre le max local et le min local)
        * \param iDeb Indice correspondant au début de la fenetre dans le signal
        * \param iFin Indice correspondant à la fin de la fenetre dans le signal
        * \return L'amplitude locale (SampleType)
    */
    SampleType amplitude(int,int);
    /**
        * \fn min
        * \brief Statistiques : lance le calcul des minimums locaux
        * \param iDeb Indice correspondant au début de la fenetre dans le signal
        * \param iFin Indice correspondant à la fin de la fenetre dans le signal
        * \return Le minimum local (SampleType)
    */
    SampleType min(int,int);
    /**
        \var SampleType* _vecteurTemps
        \brief Vecteur contenant le signal temps
    */
    SampleType *_vecteurTemps;
    /**
        \var SampleType* _signal
        \brief Vecteur contenant le signal
    */
    SampleType *_signal;
    /**
        \var SampleType* _signalIntegre
        \brief Vecteur contenant le signal intégré
    */
    SampleType *_signalIntegre;
    /**
        \var SampleType* _signalDoubleIntegre
        \brief Vecteur contenant le signal doublement intégré
    */
    SampleType *_signalDoubleIntegre;
    /**
        \var SampleType* _signalMoyenne
        \brief Vecteur contenant le signal moyennes locales
    */
    SampleType *_signalMoyenne;
    /**
        \var SampleType* _signalEcartType
        \brief Vecteur contenant le signal des écarts-types locaux
    */
    SampleType *_signalEcartType;
    /**
        \var SampleType* _signalAmplitude
        \brief Vecteur contenant le signal des amplitudes locales
    */
    SampleType *_signalAmplitude;
    /**
        \var SampleType* _signalMin
        \brief Vecteur contenant le signal des minimums locaux
    */
    SampleType *_signalMin;
    /**
        \var int _taille
        \brief Taille du signal
    */
    int _taille;
    /**
        \var bool estIntegre
        \brief Drapeau indiquant si le signal a été intégré
    */
    bool estIntegre = false;
    /**
        \var bool estDoubleIntegre
        \brief Drapeau indiquant si le signal a été doublement intégré
    */
    bool estDoubleIntegre = false;
    /**
        \var bool _estStatistique
        \brief Drapeau indiquant si les statistiques ont été déterminées sur le signal
    */
    bool _estStatistique = false;
    /**
        \var int _tailleFenetreStats
        \brief Taille de la fenetre à glisser sur le signal pour calculer les statistiques locales
    */
    int _tailleFenetreStats;
};

#endif // TRAITEMENTSIGNAL_H
