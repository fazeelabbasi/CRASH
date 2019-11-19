#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <string>
#include <QTimer>
#include <QStatusBar>
#include <qcustomplot.h>
#include "StockGenerator.h"

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Note: making all methods void and public just for using purposes right now. This will need to be changed.
    vector<double> getData();
    void horizontalBarLimits(double capital);
    void buyingStocks(double amountBought);
    void sellingStocks(double amountSold);
    void editStockDescription(std::string description);
    void testingGraph(int first,int second);
    void addpoint(double x, double y);
    void plot();
    void setData(vector<double> data);
    void Win();
    void Lose();

    //TEMP VARIABLES
    int money = 1000 ;
    int assets = 0;

public slots:
    void plotNewOnButton(int x,int y);
    void on_readyButton_clicked();

private slots:
//    void on_readyButton_clicked();

    void on_buy_clicked();

    void on_sell_clicked();

    void on_pushButton_clicked();

private:
    //All variables defined will not be assigned by us. They only exist for the sake of code readability.
    double currentCapital; //These are doubles since I am not sure how large these numbers will get. I do not think we want these as decimals.
    double amountInvested;
    QTimer dataTimer;
    vector<double> Vector2Point();
    QVector<double> qv_x, qv_y;
    int Time = 0;
    //vector<double> rawdata{1,1.5,2,2.5,3,4,4,4,4,4,4,4};
    int NumPoints = 3;// Number of points plotted into the graph at a time
    vector<double> currentData;
    int numPlayers=0;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
