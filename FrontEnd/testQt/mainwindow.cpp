#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <QTimer>
#include <QStatusBar>
#include <unistd.h>
#include "qcustomplot.h"
#include <vector>
#include <bits/stdc++.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Fazeel's Code
    ui->stockPlot->addGraph();
    ui->stockPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossCircle);
    ui->stockPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plotNewOnButton(int first, int second){
    addpoint(first,second);
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

void MainWindow::addpoint(int x, int y)
{
    qv_x.append(x);
    qv_y.append(y);
    plot();
}

void MainWindow::plot()
{
    ui->stockPlot->graph(0)->setData(qv_x,qv_y);
    ui->stockPlot->replot();
    ui->stockPlot->update();
}

void MainWindow::on_readyButton_clicked()
{
    int tempy;
    tempy = vect.front();
    addpoint(Time,tempy);
    Time++;
    vect.erase(vect.begin());
    plot();
}

//void Vector2Point(vector<int> vector){
//    int NumPoints = 3;

//    vector.pop_back()
//}
