#ifndef STOCKGENERATOR_H
#define STOCKGENERATOR_H

#include <vector>

using namespace std;

class StockGenerator
{
    public:
        StockGenerator(const double& ret, const double& volatility);
        virtual ~StockGenerator();
        void generateGraph();
        int getCrashTime();
        double getCrashPrice();
        vector<double> getGraph();

    protected:

    private:
        double mu, sigma, crashPrice;
        vector<double> graph;
        int crashTime;
};

#endif // STOCKGENERATOR_H
