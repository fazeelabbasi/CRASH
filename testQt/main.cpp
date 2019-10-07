#include "mainwindow.h"

#include <QApplication>
#include "qcustomplot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.horizontalBarLimits(30);
    w.editStockDescription("Testing 1,2");
    //w.graphData();
    QCustomPlot x;
    w.setupRealtimeDataDemo(&x);

    w.show();
    return a.exec();
}
