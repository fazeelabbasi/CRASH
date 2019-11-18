#include "StockGenerator.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <math.h>
#include <random>

#define init_value 1
#define d 0.002
#define v 0.01
#define seed 1

using namespace std;

StockGenerator::StockGenerator(const double& ret, const double& volatility)
{
	srand(time(NULL));
	mu = ret;
	sigma = volatility;
	crashPrice = -1;
	crashTime = -1;
}

StockGenerator::~StockGenerator()
{

}

void StockGenerator::generateGraph()
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

int StockGenerator::getCrashTime()
{
	return crashTime;
}

double StockGenerator::getCrashPrice()
{
	return crashPrice;
}

vector<double> StockGenerator::getGraph()
{
	return graph;
}

/*int main()
{
	StockGenerator test(d,v);
	test.generateGraph();
	cout << "Crash price: " << test.getCrashPrice() << endl;
	cout << "Crash time: " << test.getCrashTime() << endl;
	test.generateGraph();
	cout << "Crash price: " << test.getCrashPrice() << endl;
	cout << "Crash time: " << test.getCrashTime() << endl;
	test.generateGraph();
	cout << "Crash price: " << test.getCrashPrice() << endl;
	cout << "Crash time: " << test.getCrashTime() << endl;
	vector<double> test123 = test.getGraph();
	for (int i = 0; i < test123.size(); i++) {
		cout << test123[i] << endl;
	}
}*/
