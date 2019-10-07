#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <QTimer>
#include <QStatusBar>
#include <unistd.h>
#include "qcustomplot.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::horizontalBarLimits(double capital){ // this will set the range for the scroll bar. Amount investing.
    ui->amountInvesting->setRange(0,capital);
}

void MainWindow::buyingStocks(double amountBought){
    //Here we will need to set a trigger invest their money and reduce their capital. The buying will have to become susceptible to their multiplier
    //Code put here

    //To change the amount they can therefore invest use:
    //horizontalBarLimits(currentCapital-amountBought);
    //Note: the amount being effected by the mulitplier will also need to be adjusted (but will not be written yet since this is only for the gui)
}

void MainWindow::sellingStocks(double amountSold){
    //Here we will need to set a trigger to subtract the amount that has been invested and increase the users capital.
    //Code put here

    //To change the amount they can therefore invest use:
    //horizontalBarLimits(amountSold+currentCapital);
    //Note: the amount being effected by the mulitplier will also need to be adjusted (but will not be written yet since this is only for the gui)
}

void MainWindow::editStockDescription(std::string description){
    QString qstr = QString::fromStdString(description);
    ui->stockDescription->setText(qstr);
}

/*void MainWindow::graphData(){
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->stockPlot->addGraph();
    ui->stockPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->stockPlot->xAxis->setLabel("x");
    ui->stockPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->stockPlot->xAxis->setRange(-1, 1);
    ui->stockPlot->yAxis->setRange(0, 1);
    ui->stockPlot->replot();

}*/

/*void MainWindow::graphData(){
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }

    // create graph and assign data to it:
    ui->stockPlot->addGraph();
    ui->stockPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->stockPlot->xAxis->setLabel("x");
    ui->stockPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->stockPlot->xAxis->setRange(-1, 1);
    ui->stockPlot->yAxis->setRange(0, 1);
    ui->stockPlot->replot();
    usleep(1000);

    for (int i=0; i<101; ++i)
    {
      x[i] = i/100.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->stockPlot->addGraph();
    ui->stockPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->stockPlot->xAxis->setLabel("x");
    ui->stockPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->stockPlot->xAxis->setRange(-1, 1);
    ui->stockPlot->yAxis->setRange(0, 1);
    ui->stockPlot->replot();
    usleep(1000);

}*/

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph(customPlot->xAxis, customPlot->yAxis); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->xAxis->setRange(0, 5);
    customPlot->xAxis2->setRange(5, 10);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double keyTime = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    double key = std::fmod(keyTime,10);

    static bool plottingBlue = true;

    // add data to lines:
    double val = qSin(keyTime)+qrand()/(double)RAND_MAX*1*qSin(keyTime/0.3843);
    ui->stockPlot->graph(0)->addData(key, val);
    ui->stockPlot->graph(1)->addData(key, val);

    if(key < 5.0)
    {
        if(!plottingBlue)
        {
            plottingBlue = true;
            ui->stockPlot->graph(0)->data()->clear();
        }
        ui->stockPlot->graph(1)->data()->removeBefore(5+key);
    }
    else
    {
        if(plottingBlue)
        {
            plottingBlue = false;
            ui->stockPlot->graph(1)->data()->clear();
        }
        ui->stockPlot->graph(0)->data()->removeBefore(key-5);
    }

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->stockPlot->yAxis->rescale();
    ui->stockPlot->replot();
}

