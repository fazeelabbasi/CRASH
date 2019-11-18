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

//        StockGenerator test(0.002,0.01);
        StockGenerator test(0.005,0.05);
        test.generateGraph();
        vector<double> stockData = test.getGraph();

        w = new MainWindow(this);
        w->horizontalBarLimits(30);
        w->editStockDescription("Testing 1,2");

//       w->editStockDescription(to_string(stockData[0]));
//        for(int i =0;i< stockData.size();i++){
//        printf("%f",stockData[i]);
//        }

        w->setData(stockData);
        w->show();
        w->plot();


        hide();
    }

}
