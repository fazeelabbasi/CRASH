#include "Stonks.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <math.h>
#include <random>

#define init_value 1
#define d 0.0022
#define v 0.0298
#define seed 1

using namespace std;

Stonks::Stonks(double avgRet, double volatility)
{
    mu = avgRet;
    sigma = volatility;
    crashPrice = -1;
    crashTime = -1;
}

void Stonks::generateGraph()
{
    graph.clear();
    double stockQuote = init_value;
    int timeStep = 0;
    int crash_chance = -10;
    int delta_crash_chance = 0;

    double drift = mu - (1 / 2) * (sigma * sigma);
    double diffusion = 0;
    double delta = 0;
    graph.push_back(1);

    // variables for testing
    double lowest_delta = 1;
    double average = 0;
    default_random_engine generator;
    normal_distribution<double> random_num(0, 1);

    while(rand() % 10000 > (crash_chance + delta_crash_chance) && timeStep < 300) {
        timeStep++;
        crash_chance++;
        delta_crash_chance = 0;

        //cout << "Random shock: " << diffusion << endl;
        stockQuote *= exp(5*drift + diffusion);
        diffusion = (random_num(generator) * sigma);
        graph.push_back(stockQuote);
        delta = (0.5 * delta) + graph[timeStep] - graph[timeStep - 1];
        // TODO - Increase likelihood of crash while delta is negative
        if(delta < 0)
        {
            delta_crash_chance = delta * 10;
        }
        if(lowest_delta > delta)
        {
            lowest_delta = delta;
        }
        average += delta;
    }
    cout << "Crashed at timestep " << timeStep << " at price " << stockQuote << " with delta " << delta << endl;
    cout << "Lowest delta: " << lowest_delta << endl;
    crashPrice = stockQuote;
    crashTime = timeStep;


    // Uncomment following block to see all values

    average = average / graph.size();
}

int Stonks::getCrashTime()
{
    return crashTime;
}

double Stonks::getCrashPrice()
{
    return crashPrice;
}

vector<double> Stonks::getGraph()
{
    return graph;
}

Stonks::~Stonks()
{
    //dtor
}

int main()
{
    srand(3);
    Stonks test(d,v);
    test.generateGraph();
    cout << "Crash price: " << test.getCrashPrice() << endl;
    cout << "Crash time: " << test.getCrashTime() << endl;
    test.generateGraph();
    cout << "Crash price: " << test.getCrashPrice() << endl;
    cout << "Crash time: " << test.getCrashTime() << endl;
    test.generateGraph();
    cout << "Crash price: " << test.getCrashPrice() << endl;
    cout << "Crash time: " << test.getCrashTime() << endl;
    vector<double> printer = test.getGraph();
    /*for(unsigned i = 0; i < printer.size(); i++)
    {
        std::cout << printer[i] << endl;
    }*/
}
