/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *stockDescription;
    QSlider *amountInvesting;
    QPushButton *buy;
    QPushButton *sell;
    QLCDNumber *lcdNumber;
    QCustomPlot *stockPlot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stockDescription = new QTextBrowser(centralwidget);
        stockDescription->setObjectName(QString::fromUtf8("stockDescription"));
        stockDescription->setGeometry(QRect(210, 330, 381, 191));
        amountInvesting = new QSlider(centralwidget);
        amountInvesting->setObjectName(QString::fromUtf8("amountInvesting"));
        amountInvesting->setGeometry(QRect(280, 290, 160, 22));
        amountInvesting->setOrientation(Qt::Horizontal);
        buy = new QPushButton(centralwidget);
        buy->setObjectName(QString::fromUtf8("buy"));
        buy->setGeometry(QRect(520, 290, 113, 32));
        sell = new QPushButton(centralwidget);
        sell->setObjectName(QString::fromUtf8("sell"));
        sell->setGeometry(QRect(160, 290, 113, 32));
        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(450, 290, 64, 23));
        stockPlot = new QCustomPlot(centralwidget);
        stockPlot->setObjectName(QString::fromUtf8("stockPlot"));
        stockPlot->setGeometry(QRect(160, 10, 461, 271));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(amountInvesting, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        stockDescription->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.SF NS Text';\">About the stock. Data to be filled in.</span></p></body></html>", nullptr));
        buy->setText(QCoreApplication::translate("MainWindow", "Buy", nullptr));
        sell->setText(QCoreApplication::translate("MainWindow", "Sell", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
