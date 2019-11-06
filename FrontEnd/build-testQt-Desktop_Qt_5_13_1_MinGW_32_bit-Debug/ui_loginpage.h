/********************************************************************************
** Form generated from reading UI file 'loginpage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINPAGE_H
#define UI_LOGINPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginPage
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QLabel *usernameLabel;
    QLabel *PasswordLabel;
    QLineEdit *Usernamein;
    QLineEdit *Passwordin;
    QPushButton *pushButton;

    void setupUi(QDialog *LoginPage)
    {
        if (LoginPage->objectName().isEmpty())
            LoginPage->setObjectName(QString::fromUtf8("LoginPage"));
        LoginPage->resize(268, 268);
        LoginPage->setStyleSheet(QString::fromUtf8("background-color:black;"));
        gridLayout = new QGridLayout(LoginPage);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(LoginPage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(250, 250));
        groupBox->setStyleSheet(QString::fromUtf8("color:white;\n"
""));
        usernameLabel = new QLabel(groupBox);
        usernameLabel->setObjectName(QString::fromUtf8("usernameLabel"));
        usernameLabel->setGeometry(QRect(10, 30, 186, 16));
        usernameLabel->setStyleSheet(QString::fromUtf8("color:white;"));
        PasswordLabel = new QLabel(groupBox);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));
        PasswordLabel->setGeometry(QRect(10, 80, 186, 16));
        PasswordLabel->setStyleSheet(QString::fromUtf8("color:white;"));
        Usernamein = new QLineEdit(groupBox);
        Usernamein->setObjectName(QString::fromUtf8("Usernamein"));
        Usernamein->setGeometry(QRect(10, 50, 186, 22));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Usernamein->sizePolicy().hasHeightForWidth());
        Usernamein->setSizePolicy(sizePolicy);
        Usernamein->setStyleSheet(QString::fromUtf8("background-color: rgb(81, 81, 81);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-radius: 10px;\n"
"border-color: beige;\n"
"font: 8 px;\n"
"min-width: 10em;"));
        Passwordin = new QLineEdit(groupBox);
        Passwordin->setObjectName(QString::fromUtf8("Passwordin"));
        Passwordin->setGeometry(QRect(10, 100, 186, 22));
        sizePolicy.setHeightForWidth(Passwordin->sizePolicy().hasHeightForWidth());
        Passwordin->setSizePolicy(sizePolicy);
        Passwordin->setStyleSheet(QString::fromUtf8("background-color: rgb(81, 81, 81);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-radius: 10px;\n"
"border-color: beige;\n"
"font: 8 px;\n"
"min-width: 10em;\n"
""));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 130, 201, 31));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color: rgb(81, 81, 81);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-radius: 10px;\n"
"border-color: beige;\n"
"font: bold 14px;\n"
"min-width: 10em;"));

        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(LoginPage);

        QMetaObject::connectSlotsByName(LoginPage);
    } // setupUi

    void retranslateUi(QDialog *LoginPage)
    {
        LoginPage->setWindowTitle(QCoreApplication::translate("LoginPage", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("LoginPage", "Log In", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginPage", "Username (Currently: admin)", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("LoginPage", "Password (Currently:admin)", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginPage", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginPage: public Ui_LoginPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINPAGE_H
