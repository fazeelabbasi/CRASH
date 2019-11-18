#include "mainwindow.h"

#include <QApplication>
#include "loginpage.h"
#include "qcustomplot.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginPage login;
    login.show();

    //Actual vector being used:
    //vector<double> stockData = test.getGraph();
    //setData(stockData);

//    MainWindow w;
//    w.horizontalBarLimits(30);
//    w.editStockDescription("Testing 1,2");
//    w.show();
//    w.plot();
//    w.showLogin();
    return a.exec();




}
