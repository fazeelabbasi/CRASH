#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <string>
#include <QTimer>
#include <QStatusBar>
#include <qcustomplot.h>

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
    void horizontalBarLimits(double capital);
    void buyingStocks(double amountBought);
    void sellingStocks(double amountSold);
    void editStockDescription(std::string description);

    void testingGraph(int first,int second);
    //void graphData();
   // void setupRealtimeDataDemo(QCustomPlot *customPlot);
    //void realtimeDataSlot();


    //Fazeel's Code
    void addpoint(int x, int y);
    void plot();

public slots:
    void plotNewOnButton(int x,int y);

private slots:
    void on_readyButton_clicked();

private:
    //All variables defined will not be assigned by us. They only exist for the sake of code readability.
    double currentCapital; //These are doubles since I am not sure how large these numbers will get. I do not think we want these as decimals.
    double amountInvested;
    QTimer dataTimer;

    QVector<double> qv_x, qv_y;
    int Time = 0;
    vector<int> vect{3,4,5};


private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
