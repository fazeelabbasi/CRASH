/*
 * Stock_CSV_Reader.h
 *
 *  Created on: Oct. 27, 2019
 *      Author: holly_atkinson
 */

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
        void ReadAndOutput(int);
        string CompanySelect();

    protected:

    private:
};




#endif /* STOCK_CSV_READER_H_ */
