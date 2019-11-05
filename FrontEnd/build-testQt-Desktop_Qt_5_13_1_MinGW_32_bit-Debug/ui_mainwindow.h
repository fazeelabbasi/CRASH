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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QSlider *amountInvesting;
    QPushButton *sell;
    QLCDNumber *lcdNumber;
    QPushButton *buy;
    QPushButton *readyButton;
    QCustomPlot *stockPlot;
    QTextBrowser *stockDescription;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        amountInvesting = new QSlider(centralwidget);
        amountInvesting->setObjectName(QString::fromUtf8("amountInvesting"));
        amountInvesting->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(amountInvesting, 1, 1, 1, 1);

        sell = new QPushButton(centralwidget);
        sell->setObjectName(QString::fromUtf8("sell"));

        gridLayout->addWidget(sell, 1, 0, 2, 1);

        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        gridLayout->addWidget(lcdNumber, 1, 2, 1, 1);

        buy = new QPushButton(centralwidget);
        buy->setObjectName(QString::fromUtf8("buy"));

        gridLayout->addWidget(buy, 1, 3, 2, 1);

        readyButton = new QPushButton(centralwidget);
        readyButton->setObjectName(QString::fromUtf8("readyButton"));

        gridLayout->addWidget(readyButton, 2, 1, 1, 1);

        stockPlot = new QCustomPlot(centralwidget);
        stockPlot->setObjectName(QString::fromUtf8("stockPlot"));

        gridLayout->addWidget(stockPlot, 0, 0, 1, 4);

        stockDescription = new QTextBrowser(centralwidget);
        stockDescription->setObjectName(QString::fromUtf8("stockDescription"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(stockDescription->sizePolicy().hasHeightForWidth());
        stockDescription->setSizePolicy(sizePolicy);

        gridLayout->addWidget(stockDescription, 3, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        sell->setText(QCoreApplication::translate("MainWindow", "Sell", nullptr));
        buy->setText(QCoreApplication::translate("MainWindow", "Buy", nullptr));
        readyButton->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        stockDescription->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:9.75pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.SF NS Text'; font-size:13pt;\">About the stock. Data to be filled in.</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
