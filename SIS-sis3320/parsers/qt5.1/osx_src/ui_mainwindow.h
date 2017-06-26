/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QProgressBar>
#include <QPushButton>
#include <QRadioButton>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *read;
    QProgressBar *progressBar;
    QPushButton *readfolder;
    QRadioButton *sis3302;
    QRadioButton *sis3302wrap;
    QRadioButton *sis3320;
    QCheckBox *calFlag;
    QCheckBox *norawFlag;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(300, 168);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(300, 128));
        MainWindow->setMaximumSize(QSize(300, 168));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        read = new QPushButton(centralWidget);
        read->setObjectName(QString::fromUtf8("read"));
        read->setGeometry(QRect(10, 50, 131, 31));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(10, 90, 271, 23));
        progressBar->setValue(0);
        readfolder = new QPushButton(centralWidget);
        readfolder->setObjectName(QString::fromUtf8("readfolder"));
        readfolder->setGeometry(QRect(150, 50, 141, 31));
        sis3302 = new QRadioButton(centralWidget);
        sis3302->setObjectName(QString::fromUtf8("sis3302"));
        sis3302->setGeometry(QRect(10, 0, 61, 17));
        sis3302->setChecked(true);
        sis3302wrap = new QRadioButton(centralWidget);
        sis3302wrap->setObjectName(QString::fromUtf8("sis3302wrap"));
        sis3302wrap->setGeometry(QRect(90, 0, 111, 17));
        sis3320 = new QRadioButton(centralWidget);
        sis3320->setObjectName(QString::fromUtf8("sis3320"));
        sis3320->setGeometry(QRect(210, 0, 82, 17));
        calFlag = new QCheckBox(centralWidget);
        calFlag->setObjectName(QString::fromUtf8("calFlag"));
        calFlag->setGeometry(QRect(0, 20, 141, 22));
        norawFlag = new QCheckBox(centralWidget);
        norawFlag->setObjectName(QString::fromUtf8("norawFlag"));
        norawFlag->setGeometry(QRect(150, 20, 141, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 300, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        read->setText(QApplication::translate("MainWindow", "read SIS data file", 0));
        readfolder->setText(QApplication::translate("MainWindow", "read SIS data folder", 0));
        sis3302->setText(QApplication::translate("MainWindow", "3302", 0));
        sis3302wrap->setText(QApplication::translate("MainWindow", "3302  Wrap", 0));
        sis3320->setText(QApplication::translate("MainWindow", "3320", 0));
        calFlag->setText(QApplication::translate("MainWindow", "Calibrate Energy", 0));
        norawFlag->setText(QApplication::translate("MainWindow", "Event Data Only", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
