#include "show_result.h"

#include <vector>
#include <stdio.h>
#include <iostream>

using namespace std;

void show_result_basket( vector<vector<double>> basket, vector<vector<double>> correlation, double strike, double r, double Expiry, unsigned long NumberOfPaths, int optionType,double result)
{
	cout << "=======================================================================================================================" << endl;
	cout << "Baket Parameters				                                        " << endl;
	cout << "=======================================================================================================================" << endl;
	for (unsigned int i = 0; i < basket.size(); i++)
	{
		cout << " Spot price of option " << i + 1 << " : " << basket[i][0] << endl;
		cout << " Annualize Volatility of option " << i + 1 << " : " << basket[i][1] << endl;
		cout << " Weight of option " << i + 1 << " in basket: " << basket[i][2] << endl;
	}

	cout << " Strike price: " << strike << endl;
	cout << " Short Rate: " << r << endl;
	cout << " Year to Expiry: " << Expiry << endl;
	cout << " Number Of Paths: " << NumberOfPaths << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "Correlation Matix	                                         	    " << endl;
	cout << "=======================================================================================================================" << endl;
	
	for (unsigned int i = 0; i < correlation.size(); i++)
	{
		for (unsigned int j = 0; j < correlation.size(); j++)
		{
			cout << correlation[i][j] << "     ";
		}
		cout << endl;
	}
	cout << "=======================================================================================================================" << endl;
	cout << "Basket Price                                      				    " << endl;
	cout << "=======================================================================================================================" << endl;
	
	if (optionType == 13) {
		cout << "The price of this Basket Call option is "<<result<<endl<<endl;
	}
	else{
		cout << "The price of this Basket Put option is "<< result << endl<<endl;
	}

}

void show_result_single_asset(double Spot, double strike, double barrier, double Vol, double r, double Expiry,double NumberOfIntervals, unsigned long NumberOfPaths, unsigned int optionType,double result)
{
	cout << "=======================================================================================================================" << endl;
	cout << "Option Parameters" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << " Spot price: " << Spot << endl;
	cout << " Strike price: " << strike << endl;
	
	if (optionType!= 1 && optionType != 2 && optionType != 3 && optionType != 4)
	{
		cout << " barrier: " << barrier << endl;
	}
	
	cout << " Annualize Volatility: " << Vol << endl;
	cout << " Short Rate: " << r << endl;
	cout << " Year to Maturity: " << Expiry << endl;
	
	if (optionType != 1 && optionType != 2)
	{
		cout << " Number Of Intervals: " << NumberOfIntervals << endl;
	}
	cout << " Number Of Paths: " << NumberOfPaths << endl;
	cout << "=======================================================================================================================" << endl;

	string OptionName[12] = { "European Call","European Put","Asian Call","Asian Put","Barrier Call U&I",
		"Barrier Put U&I","Barrier Call U&O","Barrier Put U&O","Barrier Call D&I","Barrier Put D&I","Barrier Call D&O","Barrier Put D&O" };
	cout << OptionName[optionType - 1].c_str() << ": " << result << endl;
	cout << "=======================================================================================================================" << endl;
}