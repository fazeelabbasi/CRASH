#ifndef STOCK_CSV_READER_H
#define STOCK_CSV_READER_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Stock_CSV_Reader
{
    public:
        Stock_CSV_Reader();
        virtual ~Stock_CSV_Reader();
        void ReadAndOutput(string, int);

    protected:

    private:
};

#endif // STOCK_CSV_READER_H
