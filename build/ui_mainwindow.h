/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "capteurgl.h"
#include "gyrograph.h"
#include "principalcapteurgl.h"

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
    PrincipalCapteurGL *glPrincipal;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLCDNumber *lcdNumber;
    gyrograph *glSignalAcc;
    QLabel *label_1;
    gyrograph *glSignalGyro;
    QLabel *label_2;
    gyrograph *glSignalMagne;
    QLabel *label_3;
    CapteurGL *glCapteurAcc;
    CapteurGL *glCapteurGyro;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *comboBox_1;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuIMUViewer;
    QMenu *menu_propos;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1119, 608);
        actionCharger_un_nouveau_fichier = new QAction(MainWindow);
        actionCharger_un_nouveau_fichier->setObjectName(QStringLiteral("actionCharger_un_nouveau_fichier"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionAide = new QAction(MainWindow);
        actionAide->setObjectName(QStringLiteral("actionAide"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));
        actionCredits = new QAction(MainWindow);
        actionCredits->setObjectName(QStringLiteral("actionCredits"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        glPrincipal = new PrincipalCapteurGL(centralWidget);
        glPrincipal->setObjectName(QStringLiteral("glPrincipal"));
        glPrincipal->setGeometry(QRect(10, 20, 531, 441));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 510, 531, 27));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::NoTicks);
        horizontalSlider->setTickInterval(1);

        verticalLayout->addWidget(horizontalSlider);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 480, 41, 22));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 480, 41, 22));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 480, 51, 22));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(170, 480, 61, 23));
        glSignalAcc = new gyrograph(centralWidget);
        glSignalAcc->setObjectName(QStringLiteral("glSignalAcc"));
        glSignalAcc->setGeometry(QRect(600, 210, 411, 71));
        label_1 = new QLabel(centralWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setGeometry(QRect(740, 290, 161, 20));
        glSignalGyro = new gyrograph(centralWidget);
        glSignalGyro->setObjectName(QStringLiteral("glSignalGyro"));
        glSignalGyro->setGeometry(QRect(600, 330, 411, 71));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(750, 410, 141, 20));
        glSignalMagne = new gyrograph(centralWidget);
        glSignalMagne->setObjectName(QStringLiteral("glSignalMagne"));
        glSignalMagne->setGeometry(QRect(600, 440, 411, 71));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(740, 520, 141, 20));
        glCapteurAcc = new CapteurGL(centralWidget);
        glCapteurAcc->setObjectName(QStringLiteral("glCapteurAcc"));
        glCapteurAcc->setGeometry(QRect(570, 60, 161, 111));
        glCapteurGyro = new CapteurGL(centralWidget);
        glCapteurGyro->setObjectName(QStringLiteral("glCapteurGyro"));
        glCapteurGyro->setGeometry(QRect(760, 60, 161, 111));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(920, 30, 191, 20));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(570, 180, 111, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(760, 180, 111, 16));
        comboBox_1 = new QComboBox(centralWidget);
        comboBox_1->setObjectName(QStringLiteral("comboBox_1"));
        comboBox_1->setGeometry(QRect(1020, 230, 91, 22));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(1020, 350, 91, 22));
        comboBox_3 = new QComboBox(centralWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(1020, 460, 91, 22));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(260, 480, 171, 22));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(546, 210, 51, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(550, 260, 51, 20));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(550, 380, 51, 20));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(550, 330, 51, 20));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(550, 440, 51, 20));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(550, 490, 51, 20));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(960, 170, 151, 20));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(990, 70, 81, 91));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1119, 19));
        menuIMUViewer = new QMenu(menuBar);
        menuIMUViewer->setObjectName(QStringLiteral("menuIMUViewer"));
        menu_propos = new QMenu(menuBar);
        menu_propos->setObjectName(QStringLiteral("menu_propos"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCharger_un_nouveau_fichier->setText(QApplication::translate("MainWindow", "Charger un nouveau fichier", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        actionAide->setText(QApplication::translate("MainWindow", "Aide", 0));
        actionA_propos->setText(QApplication::translate("MainWindow", "A propos", 0));
        actionCredits->setText(QApplication::translate("MainWindow", "Credits", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Play", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Stop", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "Pause", 0));
        label_1->setText(QApplication::translate("MainWindow", "Espace d'affichage 1", 0));
        label_2->setText(QApplication::translate("MainWindow", "Espace d'affichage 2", 0));
        label_3->setText(QApplication::translate("MainWindow", "Espace d'affichage 3", 0));
        label_4->setText(QApplication::translate("MainWindow", "Type du mouvement d\303\251t\303\251ct\303\251 :", 0));
        label_5->setText(QApplication::translate("MainWindow", "(x, y, z) ", 0));
        label_6->setText(QApplication::translate("MainWindow", "(x, y, z) ", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Vue 3D", 0)
         << QApplication::translate("MainWindow", "Projection X", 0)
         << QApplication::translate("MainWindow", "Projection Y", 0)
         << QApplication::translate("MainWindow", "Projection Z", 0)
        );
        label_8->setText(QApplication::translate("MainWindow", "  Max   -", 0));
        label_9->setText(QApplication::translate("MainWindow", "  Min   -", 0));
        label_11->setText(QApplication::translate("MainWindow", "  Min   -", 0));
        label_10->setText(QApplication::translate("MainWindow", "  Max   -", 0));
        label_12->setText(QApplication::translate("MainWindow", "  Max   -", 0));
        label_13->setText(QApplication::translate("MainWindow", "  Min   -", 0));
        label_14->setText(QApplication::translate("MainWindow", "Type_M", 0));
        label_15->setText(QString());
        menuIMUViewer->setTitle(QApplication::translate("MainWindow", "Fichier", 0));
        menu_propos->setTitle(QApplication::translate("MainWindow", "Aide", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
