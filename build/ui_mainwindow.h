/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCharger_un_nouveau_fichier;
    QAction *actionQuitter;
    QAction *actionAide;
    QAction *actionA_propos;
    QAction *actionCredits;
    QWidget *centralWidget;
    GLWidget *widget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLCDNumber *lcdNumber;
    GLWidget *widget_2;
    QLabel *label;
    GLWidget *widget_3;
    QLabel *label_2;
    GLWidget *widget_4;
    QLabel *label_3;
    GLWidget *widget_5;
    GLWidget *widget_6;
    GLWidget *widget_7;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QComboBox *pOsitionDuCapteurComboBox;
    QLabel *pOsitionDuCapteurLabel;
    GLWidget *widget_8;
    QLabel *label_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuIMUViewer;
    QMenu *menu_propos;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1073, 542);
        actionCharger_un_nouveau_fichier = new QAction(MainWindow);
        actionCharger_un_nouveau_fichier->setObjectName(QString::fromUtf8("actionCharger_un_nouveau_fichier"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionAide = new QAction(MainWindow);
        actionAide->setObjectName(QString::fromUtf8("actionAide"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QString::fromUtf8("actionA_propos"));
        actionCredits = new QAction(MainWindow);
        actionCredits->setObjectName(QString::fromUtf8("actionCredits"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new GLWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 531, 401));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 460, 531, 21));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 430, 41, 22));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 430, 41, 22));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 430, 51, 22));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(170, 430, 61, 23));
        widget_2 = new GLWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(550, 150, 511, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(680, 230, 291, 20));
        widget_3 = new GLWidget(centralWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(550, 270, 511, 71));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(680, 350, 291, 20));
        widget_4 = new GLWidget(centralWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(560, 380, 511, 71));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(690, 460, 291, 20));
        widget_5 = new GLWidget(centralWidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(560, 60, 131, 71));
        widget_6 = new GLWidget(centralWidget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(740, 60, 131, 71));
        widget_7 = new GLWidget(centralWidget);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(920, 60, 131, 71));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(550, 20, 204, 21));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setContentsMargins(0, 0, 0, 0);
        pOsitionDuCapteurComboBox = new QComboBox(formLayoutWidget);
        pOsitionDuCapteurComboBox->setObjectName(QString::fromUtf8("pOsitionDuCapteurComboBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pOsitionDuCapteurComboBox);

        pOsitionDuCapteurLabel = new QLabel(formLayoutWidget);
        pOsitionDuCapteurLabel->setObjectName(QString::fromUtf8("pOsitionDuCapteurLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, pOsitionDuCapteurLabel);

        widget_8 = new GLWidget(centralWidget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(1000, 10, 51, 41));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(810, 20, 181, 20));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1073, 19));
        menuIMUViewer = new QMenu(menuBar);
        menuIMUViewer->setObjectName(QString::fromUtf8("menuIMUViewer"));
        menu_propos = new QMenu(menuBar);
        menu_propos->setObjectName(QString::fromUtf8("menu_propos"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuIMUViewer->menuAction());
        menuBar->addAction(menu_propos->menuAction());
        menuIMUViewer->addSeparator();
        menuIMUViewer->addAction(actionCharger_un_nouveau_fichier);
        menuIMUViewer->addAction(actionQuitter);
        menu_propos->addAction(actionAide);
        menu_propos->addAction(actionA_propos);
        menu_propos->addAction(actionCredits);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionCharger_un_nouveau_fichier->setText(QApplication::translate("MainWindow", "Charger un nouveau fichier", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionAide->setText(QApplication::translate("MainWindow", "Aide", 0, QApplication::UnicodeUTF8));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", 0, QApplication::UnicodeUTF8));
        actionCredits->setText(QApplication::translate("MainWindow", "Credits", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Gyroscope : Evolution de la vitesse angulaire", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Gyroscope : Evolution de la vitesse angulaire", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Gyroscope : Evolution de la vitesse angulaire", 0, QApplication::UnicodeUTF8));
        pOsitionDuCapteurComboBox->clear();
        pOsitionDuCapteurComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Pied", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Poche", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Main", 0, QApplication::UnicodeUTF8)
        );
        pOsitionDuCapteurLabel->setText(QApplication::translate("MainWindow", "Position du capteur", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Type du mouvement d\303\251t\303\251ct\303\251", 0, QApplication::UnicodeUTF8));
        menuIMUViewer->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menu_propos->setTitle(QApplication::translate("MainWindow", "Aide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
