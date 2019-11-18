#include <vector>

#ifndef STONKS_H
#define STONKS_H

using namespace std;

class Stonks
{
    public:
        Stonks(double,double);
        virtual ~Stonks();
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

#endif // STONKS_H
