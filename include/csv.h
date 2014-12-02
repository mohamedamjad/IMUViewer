#ifndef CSV_H
#define CSV_H


/*
    *\class CSV
    * \brief IMU Viewer : Classe permettant la lecture d'un fichier issue de l'acquisition
    * \author Ferdaousse Chakir, Mohammed-Amjad Lasri, Régis Cuissard
    * \date decembre 2014
*/
class CSV
{
public:
    /**
        * \fn CSV
        * \brief  Constructeur par défaut (ne fait rien)
    */
    CSV();
    /**
        * \fn readCSV
        * \brief  Lit un fichier issu de l'acquisition au format : tps en sec, code, accx, accy, accz, code, gyrox, gyroy, gyroz, code, magnex, magney, magnez
        * \param parent file_name Chemin complet vers le fichier à lire (const char *)
    */
    double **readCSV(const char *);
    /**
        * \fn getNbLines
        * \brief  Renvoie le nombre de lignes du fichier
        * \return Le nombre de lignes (int)
    */
    int getNbLines();

private:
    /**
        * \var _number_of_lines
        * \brief Nombre de lignes du fichier
    */
    int _number_of_lines=0;
};

#endif // CSV_H
