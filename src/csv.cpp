#include "csv.h"
#include "stdlib.h"
#include "stdio.h"
#include <iostream>

using namespace std;

CSV::CSV()
{
}

double **CSV::readCSV(const char *file_name){
    ;


    FILE *fichier=NULL;
    fichier=fopen(file_name,"r");
    if (fichier!=NULL)
    {
        int ch;

        do
        {
            ch = fgetc(fichier);
            if(ch == '\n')
                _number_of_lines++;
        } while (ch != EOF);

        // On se repositionne au début du fichier
        fseek ( fichier , 0 , SEEK_SET );

        double **sensors=new double*[13];


        for (int col=0;col<13;col++)
            sensors[col] = new double[_number_of_lines];


            // Lire les valeurs et les stocquer dans une matrice
            for (int i=0;i<_number_of_lines;i++)
            {
                fscanf(fichier, "%lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", &sensors[0][i],&sensors[1][i],&sensors[2][i],&sensors[3][i],&sensors[4][i],&sensors[5][i],&sensors[6][i],&sensors[7][i],&sensors[8][i],&sensors[9][i],&sensors[10][i],&sensors[11][i],&sensors[12][i]);
            }
            fclose (fichier);
            return sensors;
    }
    else return NULL;

}

int CSV::getNbLines()
{
    return _number_of_lines;
}
