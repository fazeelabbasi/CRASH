#include "mainwindow.h"

#include <QApplication>
#include "qcustomplot.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.horizontalBarLimits(30);
    w.editStockDescription("Testing 1,2");
    w.show();
    w.plot();



    return a.exec();

}
