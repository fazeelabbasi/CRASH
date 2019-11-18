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

//     w.setData(stockData);

    return a.exec();




}
