#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginPage *ui;
    MainWindow *w;
};

#endif // LOGINPAGE_H
