#include "loginpage.h"
#include "ui_loginpage.h"
#include "mainwindow.h"
#include "qcustomplot.h"

LoginPage::LoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_pushButton_clicked()
{
    QString username = ui->Usernamein->text();
    QString password = ui->Passwordin->text();


    if(username == "admin" && password == "admin"){
        w = new MainWindow(this);
        w->horizontalBarLimits(30);
        w->editStockDescription("Testing 1,2");
        StockGenerator test(0.01,0.02);
        vector<double> stockData = test.getGraph();
        w->setData({1,2,3});
        w->show();
        w->plot();
//        printf("%d",w->getData()[0]);
        hide();
    }

}
