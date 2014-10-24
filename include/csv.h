#ifndef CSV_H
#define CSV_H

class CSV
{
public:
    CSV();
    double **readCSV(char *);

    int getNbLines();

private:
    int _number_of_lines=0;
};

#endif // CSV_H
