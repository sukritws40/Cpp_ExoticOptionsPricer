#include "InputOption.h"
#include "NewProcessMC.h"
#include "PayOff.h"
#include "Process.h"
#include "InputCheck.h"
#include <string>

using namespace std;

double GetOptionInput(string OptionChoice, string ProcessChoice)
{
	Process* OptionProcess;
	if (ProcessChoice == "1")
	{
		cout << "=======================================================================================================================" << endl;
		cout << "Geometric Brownian Process" << endl;
		OptionProcess = new ProcessGB();
	}
	else
	{
		cout << "=======================================================================================================================" << endl;
		cout << "Bachelier Process" << endl;
		OptionProcess = new ProcessBach();
	}

	if (OptionChoice == "1")
	{
		cout << "European Call Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		
		PayOff* thePayOff;
		thePayOff = new PayOffCall(strike);

		ProcessEuro theProcess(*thePayOff, *OptionProcess, spot, r, Expiry, Vol, NumberOfPaths);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "2")
	{
		cout << "European Put Option" << endl;
		cout << "=======================================================================================================================" << endl;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessEuro theProcess(*thePayOff, *OptionProcess, spot, r, Expiry, Vol, NumberOfPaths);
		double result = theProcess();
		return result;

	}

	else if (OptionChoice == "3")
	{
		cout << "Asian Call Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffCall(strike);

		ProcessAs theProcess(*thePayOff, *OptionProcess, spot, r, Expiry, Vol, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "4")
	{
		cout << "Asian Put Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessAs theProcess(*thePayOff, *OptionProcess, spot, r, Expiry, Vol, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "5")
	{
		cout << "Up & In Barrier Call Option" << endl;
		cout << "=======================================================================================================================" << endl;
		double option = 5;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;

	}
	else if (OptionChoice == "6")
	{
		cout << "Up & In Barrier Put Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double option = 6;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;

	}

	else if (OptionChoice == "7")
	{
		cout << "Up & Out Barrier Call Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double option = 7;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffCall(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "8")
	{
		cout << "Up & Out Barrier Put Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double option = 8;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "9")
	{
		cout << "Down & In Barrier Call Option" << endl;
		cout << "=======================================================================================================================" << endl;
		double option = 9;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffCall(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "10")
	{
		cout << "Down & In Barrier Put Option" << endl;
		cout << "=======================================================================================================================" << endl;
		double option = 10;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}
	else if (OptionChoice == "11")
	{
		cout << "Down & Out Barrier Call Option" << endl;
		cout << "=======================================================================================================================" << endl;

		double option = 11;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffCall(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "12")
	{
		cout << "Down & Out Barrier Put Option" << endl;
		cout << "=======================================================================================================================" << endl;
		double option = 12;
		double spot = double_check("Spot");
		double strike = double_check("Strike");
		double barrier = double_check("Barrier");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		double Vol = double_check("Annualized Volatility");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");
		double NumberOfIntervals = double_check("Number of intervals");

		PayOff* thePayOff;
		thePayOff = new PayOffPut(strike);

		ProcessBarrier theProcess(*thePayOff, *OptionProcess, strike, spot, r, Expiry, Vol, barrier, option, NumberOfPaths, NumberOfIntervals);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "13")
	{
		cout << "Basket Call Option" << endl;
		cout << "=======================================================================================================================" << endl;
		cout << "Please enter number of assets in the basket" << endl;


		double NumberOfWeight;

		unsigned long NumberOfAsset = unsignedlong_check("Number of asset");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");

		PayOff* OptionPayOff;
		OptionPayOff = new PayOffCall(strike);

		vector<vector<double> > correlation(NumberOfAsset, vector<double>(NumberOfAsset));
		vector<vector<double>> basket(NumberOfAsset, vector<double>(3));
		for (unsigned int i = 0; i < NumberOfAsset; i++)
		{
			cout << endl;
			cout << "Underlying " << (i + 1) << endl;
			basket[i][0] = double_check("Spot");
			basket[i][1] = double_check("Volatility");
			basket[i][2] = double_check("Weight");
			for (unsigned int j = 0; j < NumberOfAsset; j++)
			{
				if (i == j)
				{
					correlation[i][j] = 1;
				}
				else
				{
					if (correlation[j][i] == NULL)
					{
						int l = j;
						cout << "Correlation of underlying " << (i + 1) << ", " << (j + 1) << endl;
						correlation[i][j] = corr_check("");
					}
					else
					{
						correlation[i][j] = correlation[j][i];
					}

				}
			}
		}

		//weight check
		double summationofWeight = 0.0;
		for (unsigned int i = 0; i < NumberOfAsset; i++)
		{
			summationofWeight += basket[i][2];
		}

		while (summationofWeight < 0.99 || summationofWeight > 1)
		{
			cout << endl;
			cout << "Summation of weight must be equal to 1" << endl;
			summationofWeight = 0.0;
			for (unsigned int i = 0; i < NumberOfAsset; i++)
			{
				cout << "Underlying " << (i + 1) << endl;
				basket[i][2] = double_check("Weight of underlying");
				summationofWeight += basket[i][2];
			}
		}


		ProcessBasket theProcess(*OptionPayOff, *OptionProcess, basket, correlation, Expiry, r, NumberOfPaths);
		double result = theProcess();
		return result;
	}

	else if (OptionChoice == "14")
	{
		cout << "Basket Put Option" << endl;
		cout << "=======================================================================================================================" << endl;
		cout << "Please enter number of assets in the basket" << endl;


		double NumberOfWeight;

		unsigned long NumberOfAsset = unsignedlong_check("Number of asset");
		double strike = double_check("Strike");
		double Expiry = double_check("Expiry");
		double r = negative_check("Short rate");
		unsigned long NumberOfPaths = unsignedlong_check("Number of path");

		PayOff* OptionPayOff;
		OptionPayOff = new PayOffPut(strike);

		vector<vector<double> > correlation(NumberOfAsset, vector<double>(NumberOfAsset));
		vector<vector<double>> basket(NumberOfAsset, vector<double>(3));
		

		for (unsigned int i = 0; i < NumberOfAsset; i++)
		{
			cout << endl;
			cout << "Underlying " << (i + 1) << endl;
			basket[i][0] = double_check("Spot");
			basket[i][1] = double_check("Volatility");
			basket[i][2] = double_check("Weight");
			for (unsigned int j = 0; j < NumberOfAsset; j++)
			{
				if (i == j)
				{
					correlation[i][j] = 1;
				}
				else
				{
					if (correlation[j][i] == NULL)
					{
						int l = j;
						cout << "Correlation of underlying " << (i+1) << ", " << (j+1);
						correlation[i][j] = corr_check("");
					}
					else
					{
						correlation[i][j] = correlation[j][i];
					}

				}
			}
		}

		//weight check
		double summationofWeight = 0.0;
		for (unsigned int i = 0; i < NumberOfAsset; i++)
		{
			summationofWeight += basket[i][2];
		}

		while (summationofWeight < 0.99 || summationofWeight > 1)
		{
			cout << endl;
			cout << "Summation of weight must be equal to 1" << endl;
			summationofWeight = 0.0;
			for (unsigned int i = 0; i < NumberOfAsset; i++)
			{
				cout << "Underlying " << (i + 1) << endl;
				basket[i][2] = double_check("Weight of underlying");
				summationofWeight += basket[i][2];
			}
		}

		ProcessBasket theProcess(*OptionPayOff, *OptionProcess, basket, correlation, Expiry, r, NumberOfPaths);
		double result = theProcess();
		return result;

	}
	return 0;
}