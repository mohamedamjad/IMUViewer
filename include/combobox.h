#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include "gyrograph.h"

class Combobox : public QComboBox
{
    Q_OBJECT
private:
    gyrograph *_pgyrograph;
public:
    explicit Combobox(QWidget *parent = 0);
    void setgyrograph(gyrograph *graph);

signals:

public slots:

};

#endif // COMBOBOX_H
