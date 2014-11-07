#ifndef MY_LCDNUMBER_H
#define MY_LCDNUMBER_H
#include<QLCDNumber>
#include<QWidget>
class My_Lcdnumber:public QLCDNumber
{

    Q_OBJECT
public:
    explicit My_Lcdnumber (QWidget *parent=0);
    My_Lcdnumber();
public slots:
    void tcount();
private:

    float time;
};

#endif // MY_LCDNUMBER_H