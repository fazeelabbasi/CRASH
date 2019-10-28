/*
 * Stock_CSV_Reader.cpp
 *
 *  Created on: Oct. 27, 2019
 *      Author: holly_atkinson
 */



#include "Stock_CSV_Reader2.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

Stock_CSV_Reader::Stock_CSV_Reader()
{
    //ctor
}

Stock_CSV_Reader::~Stock_CSV_Reader()
{
    //dtor
}

vector<string> Stock_CSV_Reader::CompanySelect(){
	string name;
	ifstream fin;
	string line;
	stringstream s;
	vector <string> all;
	vector<string> ret;
	int i;
	int x;

	fin.open("CompanyNames.txt");

	while(!fin.eof()){
		getline(fin, line);
		s.clear();
		s.str(" ");
		s << line; //add the line to the stringstream object s
		while((s >> line)){ //read the the line from s
			all.push_back(line); //push all three insult adjectives from each line into the vector string from the back

		}
	}
	x = all.size();
	i = rand() % x;
	name = all[i];

	ret.push_back(name);
	ret.push_back("Company Type Here");

	return ret;

}

void Stock_CSV_Reader::ReadAndOutput(int interval)
{
    double avg_ret = 0;
    double stdev = 0;

    vector<string> companyInfo = CompanySelect();
    string name =  companyInfo[0];
    string type = companyInfo[1];
    ifstream fin;
    fin.open(name+".csv");

    vector<vector<string> > data;
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
