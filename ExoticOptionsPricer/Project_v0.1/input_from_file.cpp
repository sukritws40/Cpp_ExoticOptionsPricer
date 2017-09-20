#include "input_from_file.h"
#include <vector>
#include <cstdlib>
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include "Portfolio.h"
using namespace std;

bool read_one_asset(const Process& Process,string file)
{
	double optionType, Spot, strike, barrier, r, Vol, Expiry;
	double NumberOfIntervals;
	unsigned long NumberOfPaths;
	string title[11];
	string firstline, nextline;
	string s;
	unsigned int nop;
	int line_number = 0;
	int previous, next;
	typedef vector<double> param;
	typedef vector<param> options;
	typedef vector<double> matrix;
	typedef vector<matrix> correlations;
	bool readgood = true;

	ifstream infile;
	ifstream readline;
	infile.open(file.data());
	readline.open(file.data());
	if (!infile)
	{
		cout << "Programme cannot read this file.";
		readgood = false;
		return readgood;
	}
	else
	{
		while (getline(readline, firstline))
		{
			line_number += 1;
		}
		getline(infile, firstline);

		int row_number = 10 + line_number;
		options option(line_number - 1, param(row_number));
		correlations correlation(line_number - 1, matrix(line_number)); //correlation matrix of assets
		previous = 0;

		next = firstline.find(',');
		for (int i = 0; i < 11; i++)
		{
			title[i] = firstline.substr(previous, next - previous);
			previous = next + 1;
			next = firstline.find(',', previous);
		}
		vector<double> input(row_number);

		for (int i = 0; i < line_number - 1; i++)
		{
			getline(infile, nextline);
			//cout<<nextline<<endl;
			previous = 0;
			next = nextline.find(',');
			for (int j = 0; j<row_number; j++)
			{
				stringstream ss(nextline.substr(previous, next - previous));
				if (j == 8) {
					ss >> nop;
					input[j] = nop;
				}
				else {
					ss >> input[j];
				}
				if (ss.fail())
				{
					cout << endl << title[i] << " is wrong. ";
					readgood = false;
					return readgood;
				}
				else
				{
					option[i][j] = input[j];
				}
				previous = next + 1;
				next = nextline.find(',', previous);

			}
		}
		if (title[0] != "Option type")
		{
			cout << "Error: Your input file is wrong. ";
			readgood = false;
			return readgood;
		}

		for (int i = 0; i<line_number - 1; i++)
		{
			for (int j = 0; j<row_number - 1; j++)
			{
				readgood=input_valid_from_file(double(option[i][0]),double(option[i][j]), j);//check input valid
				if(readgood==false)
					return readgood;
			}
		}

		if (option[0][0] == 13 || option[0][0] == 14) //Basket
		{

			options basket(line_number - 1, param(3));
			for (int i = 0; i < option.size(); i++)
			{
				basket[i][0] = option[i][1];
				basket[i][1] = option[i][4];
				basket[i][2] = option[i][9];
				int corr = 10; // correlation is at 12th

				for (unsigned int j = 0; j < option.size(); j++)
				{
					if (option[i][corr + j] < -1 || option[i][corr + j] > 1) // check correlation value
					{
						cout << "Error: correlation must be between -1 to 1." << endl;
						readgood = false;
						return readgood;
					}
					if (i == j)
					{
						correlation[i][j] = 1;
					}
					else
					{
						if (correlation[j][i] == NULL)
						{
							correlation[i][j] = option[i][corr + j];
						}
						else
						{
							correlation[i][j] = correlation[j][i];
						}

					}
				}
			}
			double SumOfWeights = 0.0;
			for (unsigned int i = 0; i < basket.size(); i++)//check weights of basket
			{
				SumOfWeights += basket[i][2];
			}
			if (SumOfWeights > 1 || SumOfWeights < 0.99)
			{
				cout << "Error: Summation of weights must be equal to 1." << endl;
				readgood = false;
				return readgood;
			}
			else
			{
				optionType = option[0][0];
				strike = option[0][2];
				r = option[0][5];
				Expiry = option[0][6];
				NumberOfPaths = option[0][8];
				for (unsigned int i = 1; i < option.size(); i++) //Check all values of basket option
				{
					if (optionType != option[i][0] || strike != option[i][2] || r != option[i][5] || Expiry != option[i][6] || NumberOfPaths != option[i][8])
					{
						cout << "Error: Option type, strike price, short rate, year to expiry and number of paths should be the same for basket." << endl;
						readgood = false;
						return readgood;
					}
				}

				result_basket(Process,basket, correlation, strike, r, Expiry, NumberOfPaths, optionType);
			}
		}//end of basket
		else if (option[0][0] == 1 || option[0][0] == 2 || option[0][0] == 3 || option[0][0] == 4 || option[0][0] == 5 || option[0][0] == 6 || option[0][0] == 7 || option[0][0] == 8 || option[0][0] == 9 || option[0][0] == 10 || option[0][0] == 11 || option[0][0] == 12)
			//EUROPEAN option, Asian option and Barrier option
		{
			optionType = option[0][0];
			Spot = option[0][1];
			strike = option[0][2];
			barrier = option[0][3];
			Vol = option[0][4];
			r = option[0][5];
			Expiry = option[0][6];
			NumberOfIntervals = option[0][7];
			NumberOfPaths = option[0][8];
			result_single_asset(Process,Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType);

		}
		else
		{
			cout << "Error: The option type is wrong." << endl;
			readgood = false;
			return readgood;
		}


	}
	return readgood;
}

    

bool read_Portfolio(const Process& Process,string file)
{
	string firstline, nextline;
	string title[9];
	string s;
	double input[9];
	unsigned int nop;
	int previous, next, line_number;
	typedef vector<double> param;
	typedef vector<param> options;

	ifstream infile(file);
	ifstream readline(file);
	line_number = 0;
	bool readgood = true;
	if (!infile)
	{
		cout << endl;
		cout << "Programme cannot read this file.";
		readgood = false;
		return readgood;
	}

	else
	{
		while (getline(readline, firstline))
		{
			line_number += 1;
		}
		options option(line_number - 1, param(9));
		getline(infile, firstline);
		previous = 0;
		next = firstline.find(',');
		for (int i = 0; i < 9; i++)
		{
			title[i] = firstline.substr(previous, next - previous);
			previous = next + 1;
			next = firstline.find(',', previous);
		}
		for (int i = 0; i < line_number - 1; i++)
		{
			getline(infile, nextline);
			previous = 0;
			next = nextline.find(',');
			for (int j = 0; j < 9; j++)
			{
				stringstream ss(nextline.substr(previous, next - previous));
				if (j == 8) {
					ss >> nop;
					input[j] = nop;
				}
				else {
					ss >> input[j];
				}
				 if (ss.fail())
				{
				  cout << endl << title[i] << " is wrong.";
				  readgood = false;
				  return readgood;
				 }
				else
				{
				  option[i][j] = input[j];
				}
				previous = next + 1;
				next = nextline.find(',', previous);
			}
		}

		//check short rate and Number of path from file
		double NUmberOfPaths = option[0][8];
		double r = option[0][5];
		for (unsigned long i = 1; i < option.size(); i++)
		{
			if (NUmberOfPaths != option[i][8] || r != option[i][5]) //check number of paths and short rate
			{
				cout << "Error: Short rate or number of paths should be the same for portfolio.";
				readgood = false;
				return readgood;
			}
		}
		for (unsigned long i = 0; i < option.size(); i++)
		{
			if (option[i][0] == 13 || option[i][0] == 14) //check basket option
			{
				cout << "Error: Basket cannot be included in portfolio.";
				readgood = false;
				return readgood;
			}
		}

		if (title[0] != "Option type")
		{
			cout << "Error: Please check your input file.";
			readgood = false;
			return readgood;
		}
		for (int i = 0; i<line_number - 1; i++)
		{
			for (int j = 0; j<9; j++)
			{
				readgood=input_valid_from_file(double(option[i][0]),double(option[i][j]), j);//check input valid
				if (readgood == false)
					return readgood;
			}
		}
		Portfolio(Process,option);

	}
	return readgood;

}