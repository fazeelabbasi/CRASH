
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QString>
#include <QTimer>
#include <QStatusBar>
//#include <unistd.h>
#include "qcustomplot.h"
#include <vector>
//#include <bits/stdc++.h>
#include "loginpage.h"
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stockPlot->setInteraction(QCP::iRangeDrag,true);
    ui->stockPlot->setInteraction(QCP::iRangeZoom,true);
    ui->stockPlot->addGraph();
    ui->stockPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCrossCircle);
    ui->stockPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->yourStats->setText("Money: 1000");
}

MainWindow::~MainWindow()
{
    delete ui;
}


vector<double> MainWindow::getData(){
    return currentData;
}

void MainWindow::setData(vector<double> outerdata){
   /* currentData = data;*/
    for (int i=0; i<outerdata.size(); i++)
            currentData.push_back(outerdata[i]);
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

void MainWindow::addpoint(double x, double y)
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

vector<double> MainWindow::Vector2Point(){

    vector<double> dataToPlot;
    for (int i=0; i<NumPoints; i++)
            dataToPlot.push_back(currentData[i]);


    return dataToPlot;// data being returned is deleted from currentData when its is plotted(when the ready button is clicked)

}

void MainWindow::on_readyButton_clicked()
{
//    vector<double> temp = Vector2Point();

//    addpoint(Time++,temp[0]);
//    plot();
//    addpoint(Time++,temp[1]);
//    plot();
//    addpoint(Time++,temp[2]);
//    plot();

//    ui->stockPlot->xAxis->setRange(*std::min_element(qv_x.begin(),qv_x.end())-1,*std::max_element(qv_x.begin(),qv_x.end())+1);
//    ui->stockPlot->yAxis->setRange(*std::min_element(qv_y.begin(),qv_y.end())-1,*std::max_element(qv_y.begin(),qv_y.end())+1);
//    plot();

//    currentData.erase(currentData.begin());
//    currentData.erase(currentData.begin());
//    currentData.erase(currentData.begin());

    qv_x = {};
    qv_y = {};
    ui->stockPlot->replot();


    for (int i =0;i<currentData.size();i++) {
        addpoint(Time++,currentData[i]);
        plot();
        ui->stockPlot->xAxis->setRange(*std::min_element(qv_x.begin(),qv_x.end())-1,*std::max_element(qv_x.begin(),qv_x.end())+1);
        ui->stockPlot->yAxis->setRange(*std::min_element(qv_y.begin(),qv_y.end())-1,*std::max_element(qv_y.begin(),qv_y.end())+1);
        plot();
//        Sleep(100);
         QEventLoop obj;
        for (int i = 0; i < 50000;i++) {

           obj.processEvents();
        }
    }





}

void MainWindow::Win(){
    //check if there is more than one user left. If there isn't, we have a winner. This method will need to be checked for every buyout
    if(numPlayers==0){
        //Pop up window that says you won!
        QMessageBox::information(this,"Winner!","Congradulations!!! You Won!!");
        //reset the game
        ui->stockPlot->clearGraphs(); //I think this works to clear the graph
        //are we keeping track of wins?
    }
}

void MainWindow::Lose(){
    //check if current capital and amount invested is zero
    if(currentCapital==0 && amountInvested==0){
        //take away their ability to click the buttons
        ui->buy->setEnabled(false);
        ui->sell->setEnabled(false);
        numPlayers--;
    }
}

void MainWindow::on_buy_clicked()
{
    money++;
   string s = ("Your Money : "+ to_string(money));


   QString qstr = QString::fromStdString(s);
   ui->yourStats->setText(qstr);
}

void MainWindow::on_sell_clicked()
{
    editStockDescription("lol but backwards");
}


