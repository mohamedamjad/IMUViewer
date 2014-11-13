#include "combobox.h"

Combobox::Combobox(QWidget *parent) :
    QComboBox(parent)
{
}

void Combobox::setgyrograph(gyrograph *graph)
{
    _pgyrograph=graph;
}
