#include "Stock_CSV_Reader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

Stock_CSV_Reader::Stock_CSV_Reader()
{
    //ctor
}

Stock_CSV_Reader::~Stock_CSV_Reader()
{
    //dtor
}

void Stock_CSV_Reader::ReadAndOutput(string name, int interval)
{
    double avg_ret = 0;
    double stdev = 0;

    ifstream fin;
    fin.open(name+".csv");

    vector<vector<string>> data;
    string line_in;
    string partial;

    while(getline(fin, line_in))
    {
        vector<string> line;
        istringstream iss(line_in);
        string token;
        while(getline(iss, token, ','))
            line.push_back(token);
        data.push_back(line);
    }

    int length = data.size();

    string::size_type sz;
    double test = stod (data[1][1],&sz);

    vector<double> stock_quotes;
    for(int i = 1; i < length; i += interval)
    {
        stock_quotes.push_back(stod(data[i][1],&sz));
    }

    length = stock_quotes.size();

    vector<double> returns;
    for(int i = 0; i < length - 1; i++) {
        returns.push_back((stock_quotes[i + 1] - stock_quotes[i])/stock_quotes[i]);
        avg_ret += returns[i];
    }
    avg_ret = avg_ret / (length - 1);

    for(int i = 0; i < length - 1; i++) {
        stdev += pow((returns[i] - avg_ret), 2.0);
    }
    stdev = sqrt(stdev / (length - 1));

    cout << "Time interval of " << interval << " days" << endl;
    cout << "Average returns for " << name << ": " << avg_ret << endl;
    cout << "Standard deviation for "<<name<<": "<<stdev<<endl;

    fin.close();



}

/*int main()
{
    Stock_CSV_Reader test;
    test.ReadAndOutput("GOOG",7);
    test.ReadAndOutput("MSFT",7);
    test.ReadAndOutput("AAPL",7);
    test.ReadAndOutput("TSN",7);
    test.ReadAndOutput("KO",7);
    test.ReadAndOutput("MCD",7);
    test.ReadAndOutput("NKE",7);
    test.ReadAndOutput("LULU",7);
    test.ReadAndOutput("ADDYY",7);
}*/
