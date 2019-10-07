#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <string>
#include <QTimer>
#include <QStatusBar>
#include <qcustomplot.h>

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
    //void graphData();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void realtimeDataSlot();

private:
    //All variables defined will not be assigned by us. They only exist for the sake of code readability.
    double currentCapital; //These are doubles since I am not sure how large these numbers will get. I do not think we want these as decimals.
    double amountInvested;
    QTimer dataTimer;

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
