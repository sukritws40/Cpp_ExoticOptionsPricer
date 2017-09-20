#include "Portfolio.h"
#include "Payoff.h"
#include <vector>
#include<iostream>

using namespace std;

void Portfolio(const Process& Process, vector<vector<double> > Port)
{
	int NumberOfAsset = Port.size();
	vector<double> price(NumberOfAsset);
	double PortPrice = 0;
	unsigned long NumberOfPaths = Port[0][8];
	PayOff* thePayOff;
	cout << "=======================================================================================================================" << endl;
	cout << "Portfolio" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << endl;
	double maxExpiry = Port[0][6];
	for (int i = 0; i<NumberOfAsset; i++)
	{
		if (Port[i][6]>maxExpiry)
		{
			maxExpiry = Port[i][6];
		}
	}
	unsigned int NumberOfGaussian = NumberOfPaths * 360 * maxExpiry;
	vector<double> thisGaussian(NumberOfGaussian); //as the least number of intervals in Asian and Barrier option is 1
	for (unsigned int i = 0; i<NumberOfGaussian; i++)
	{
		thisGaussian[i] = GetOneGaussianByBoxMuller();
	}

	for (int i = 0; i<NumberOfAsset; i++)
	{
		if (Port[i][0] == 1)//EuCall
		{
			PayOffCall thePayOff(Port[i][2]);
			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				double thisSpot = Process.evolve(Port[i][1], Port[i][5], Port[i][6], Port[i][4], thisGaussian[k * 360 * maxExpiry]); // k * 360 * Expiry
				double thisPayOff = thePayOff(thisSpot);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			cout << "The price of option " << i + 1 << " (European Call): ";
			cout << price[i] << endl;
		}
		else if (Port[i][0] == 2)//EuPut
		{
			PayOffPut thePayOff(Port[i][2]);
			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				double thisSpot = Process.evolve(Port[i][1], Port[i][5], Port[i][6], Port[i][4], thisGaussian[k * 360 * maxExpiry]);// k * 360 * Expiry
				double thisPayOff = thePayOff(thisSpot);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			cout << "The price of option " << i + 1 << " (European Call): ";
			cout << price[i] << endl;
		}
		else if (Port[i][0] == 3)//AsCall
		{
			PayOffCall thePayOff(Port[i][2]);
			vector<double> spots(int((Port[i][6] * 360) / Port[i][7]), Port[i][1]);
			double dt = Port[i][6] / ((Port[i][6] * 360) / Port[i][7]);

			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				for (unsigned long j = 1; j<spots.size(); j++)
				{
					spots[j] = Process.evolve(spots[j - 1], Port[i][5], dt, Port[i][4], thisGaussian[k * 360 * maxExpiry + j*Port[i][7]]);// k * 360 * Expiry + j * numbe of Intervals
				}
				double sum = 0.0;
				for (unsigned long j = 0; j<spots.size(); j++)
				{
					sum += log(spots[j]);
				}
				double expMean = exp(sum / spots.size());
				double thisPayOff = thePayOff(expMean);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			cout << "The price of option " << i + 1 << " (Asian Call): ";
			cout << price[i] << endl;
		}
		else if (Port[i][0] == 4)//AsPut
		{
			PayOffPut thePayOff(Port[i][2]);
			vector<double> spots(int((Port[i][6] * 360) / Port[i][7]), Port[i][1]);
			double dt = Port[i][6] / ((Port[i][6] * 360) / Port[i][7]);

			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				for (unsigned long j = 1; j<spots.size(); j++)
				{
					spots[j] = Process.evolve(spots[j - 1], Port[i][5], dt, Port[i][4], thisGaussian[k * 360 * maxExpiry + j*Port[i][7]]);// k * 360 * Expiry + j * numbe of Intervals
				}
				double sum = 0.0;
				for (unsigned long j = 0; j<spots.size(); j++)
				{
					sum += log(spots[j]);
				}
				double expMean = exp(sum / spots.size());
				double thisPayOff = thePayOff(expMean);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			cout << "The price of option " << i + 1 << " (Asian Call): ";
			cout << price[i] << endl;
		}
		else if (Port[i][0] == 5 || Port[i][0] == 7 || Port[i][0] == 9 || Port[i][0] == 11)//Barrier Call U&I,U&O,D&I,D&O
		{
			PayOffCall thePayOff(Port[i][2]);
			vector<double> spots(int((Port[i][6] * 360) / Port[i][7]), Port[i][1]);
			double dt = Port[i][6] / ((Port[i][6] * 360) / Port[i][7]);
			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				for (unsigned long j = 1; j < spots.size(); j++)
				{
					spots[j] = Process.evolve(spots[j - 1], Port[i][5], dt, Port[i][4], thisGaussian[k * 360 * maxExpiry + j*Port[i][7]]);// k * 360 * Expiry + j * numbe of Intervals
				}
				//Up and In
				int length = spots.size();
				double thisSpot = 0.0;
				if (Port[i][0] == 5)
				{
					thisSpot = Port[i][2];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] >= Port[i][3])
						{
							thisSpot = spots[length - 1];
						}
					}
				}
				//Up and Out
				else if (Port[i][0] == 7)
				{
					thisSpot = spots[length - 1];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] >= Port[i][3])
							thisSpot = Port[i][2];
					}
				}
				//Down and In
				else if (Port[i][0] == 9)
				{
					thisSpot = Port[i][2];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] <= Port[i][3])
							thisSpot = spots[length - 1];
					}
				}
				//Down and Out
				else
				{
					thisSpot = spots[length - 1];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] <= Port[i][3])
							thisSpot = Port[i][2];
					}
				}
				double thisPayOff = thePayOff(thisSpot);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			if (Port[i][0] == 5) {
				cout << "The price of option " << i + 1 << " (Barrier Call U&I): ";
				cout << price[i] << endl;
			}
			else if (Port[i][0] == 7) {
				cout << "The price of option " << i + 1 << " (Barrier Call U&O): ";
				cout << price[i] << endl;
			}
			else if (Port[i][0] == 9) {
				cout << "The price of option " << i + 1 << " (Barrier Put D&I): ";
				cout << price[i] << endl;
			}
			else {
				cout << "The price of option " << i + 1 << " (Barrier Call D&O): ";
				cout << price[i] << endl;
			}
		}
		else if (Port[i][0] == 6 || Port[i][0] == 8 || Port[i][0] == 10 || Port[i][0] == 12)//Barrier Put U&I,U&O,D&I,D&O
		{
			PayOffPut thePayOff(Port[i][2]);
			vector<double> spots(int((Port[i][6] * 360) / Port[i][7]), Port[i][1]);
			double dt = Port[i][6] / ((Port[i][6] * 360) / Port[i][7]);
			double runningsum = 0.0;
			for (unsigned long k = 0; k < NumberOfPaths; k++)
			{
				for (unsigned long j = 1; j < spots.size(); j++)
				{
					spots[j] = Process.evolve(spots[j - 1], Port[i][5], dt, Port[i][4], thisGaussian[k * 360 * maxExpiry + j*Port[i][7]]);// k * 360 * Expiry + j * numbe of Intervals
				}
				//Up and In
				int length = spots.size();
				double thisSpot = 0.0;
				if (Port[i][0] == 6)
				{
					thisSpot = Port[i][2];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] >= Port[i][3])
						{
							thisSpot = spots[length - 1];
						}
					}
				}
				//Up and Out
				else if (Port[i][0] == 8)
				{
					thisSpot = spots[length - 1];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] >= Port[i][3])
							thisSpot = Port[i][2];
					}
				}
				//Down and In
				else if (Port[i][0] == 10)
				{
					thisSpot = Port[i][2];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] <= Port[i][3])
							thisSpot = spots[length - 1];
					}
				}
				//Down and Out
				else
				{
					thisSpot = spots[length - 1];
					for (unsigned long j = 0; j < spots.size(); j++)
					{
						if (spots[j] <= Port[i][3])
							thisSpot = Port[i][2];
					}
				}
				double thisPayOff = thePayOff(thisSpot);
				runningsum += thisPayOff;
			}
			double mean = runningsum / NumberOfPaths;
			mean *= exp(-Port[i][5] * Port[i][6]);
			price[i] = mean;
			if (Port[i][0] == 6) {
				cout << "The price of option " << i + 1 << " (Barrier Put U&I): ";
				cout << price[i] << endl;
			}
			else if (Port[i][0] == 8) {
				cout << "The price of option " << i + 1 << " (Barrier Put U&O): ";
				cout << price[i] << endl;
			}
			else if (Port[i][0] == 10) {
				cout << "The price of option " << i + 1 << " (Barrier Put D&I): ";
				cout << price[i] << endl;
			}
			else
			{
				cout << "The price of option " << i + 1 << " (Barrier Put D&O): ";
				cout << price[i] << endl;
			}
		}
		else
		{
			cout << "Error: No option is " << Port[i][0];
			exit(EXIT_FAILURE);
		}
		PortPrice += price[i];
	}
	cout << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "The price of this portfolio is " << PortPrice << endl;
	cout << "=======================================================================================================================" << endl;
	cout << endl;
}


//void Portfolio(const Process& Process,vector<vector<double> > Port)
//{
//	int NumberOfAsset = Port.size();
//	vector<double> price(NumberOfAsset);
//	vector<double> mean(NumberOfAsset);
//	double PortPrice = 0;
//	PayOff* thePayOff;
//	cout << "=======================================================================================================================" << endl;
//	cout << "Portfolio" << endl;
//	cout << "=======================================================================================================================" << endl;
//	cout << endl;
//
//
//	for (int i = 0; i<NumberOfAsset; i++)
//	{
//		if (Port[i][0] == 1)//EuCall
//		{
//			thePayOff = new PayOffCall(Port[i][2]);
//			ProcessEuro theProcess(*thePayOff,Process, Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][8]);
//			price[i] = theProcess();
//			cout << "The price of option " << i + 1 << " (European Call): ";
//			cout << price[i] << endl;
//
//		}
//		else if (Port[i][0] == 2)//EuPut
//		{
//			thePayOff = new PayOffPut(Port[i][2]);
//			ProcessEuro theProcess(*thePayOff, Process, Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][8]);
//			price[i] = theProcess();
//			cout << "The price of option " << i + 1 << " (European Put): ";
//			cout << price[i] << endl;
//		}
//		else if (Port[i][0] == 3)//AsCall
//		{
//			thePayOff = new PayOffCall(Port[i][2]);
//			ProcessAs theProcess(*thePayOff, Process, Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][8], Port[i][7]);
//			price[i] = theProcess();
//			cout << "The price of option " << i + 1 << " (Asian Call): ";
//			cout << price[i] << endl;
//		}
//		else if (Port[i][0] == 4)//AsPut
//		{
//			thePayOff = new PayOffPut(Port[i][2]);
//			ProcessAs theProcess(*thePayOff, Process,Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][8], Port[i][7]);
//			price[i] = theProcess();
//			cout << "The price of option " << i + 1 << " (Asian Put): ";
//			cout << price[i] << endl;
//		}
//		else if (Port[i][0] == 5 || Port[i][0] == 7 || Port[i][0] == 9 || Port[i][0] == 11)//Barrier Call U&I,U&O,D&I,D&O
//		{
//			thePayOff = new PayOffCall(Port[i][2]);
//			ProcessBarrier theProcess(*thePayOff, Process,Port[i][2], Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][3], Port[i][0], Port[i][8], Port[i][7]);
//			price[i] = theProcess();
//			if (Port[i][0] == 5) {
//				cout << "The price of option " << i + 1 << " (Barrier Call U&I): ";
//				cout << price[i] << endl;
//			}
//			else if (Port[i][0] == 7) {
//				cout << "The price of option " << i + 1 << " (Barrier Call U&O): ";
//				cout << price[i] << endl;
//			}
//			else if (Port[i][0] == 9) {
//				cout << "The price of option " << i + 1 << " (Barrier Put D&I): ";
//				cout << price[i] << endl;
//			}
//			else {
//				cout << "The price of option " << i + 1 << " (Barrier Call D&O): ";
//				cout << price[i] << endl;
//			}
//		}
//		else if (Port[i][0] == 6 || Port[i][0] == 8 || Port[i][0] == 10 || Port[i][0] == 12)//Barrier Put U&I,U&O,D&I,D&O
//		{
//			thePayOff = new PayOffPut(Port[i][2]);
//			ProcessBarrier theProcess(*thePayOff, Process, Port[i][2], Port[i][1], Port[i][5], Port[i][6], Port[i][4], Port[i][3], Port[i][0], Port[i][8], Port[i][7]);
//			price[i] = theProcess();
//			if (Port[i][0] == 6) {
//				cout << "The price of option " << i + 1 << " (Barrier Put U&I): ";
//				cout << price[i] << endl;
//			}
//			else if (Port[i][0] == 8) {
//				cout << "The price of option " << i + 1 << " (Barrier Put U&O): ";
//				cout << price[i] << endl;
//			}
//			else if (Port[i][0] == 10) {
//				cout << "The price of option " << i + 1 << " (Barrier Put D&I): ";
//				cout << price[i] << endl;
//			}
//			else
//			{
//				cout << "The price of option " << i + 1 << " (Barrier Put D&O): ";
//				cout << price[i] << endl;
//			}
//		}
//		else
//		{
//			cout << "Error: No option is "<<Port[i][0];
//			exit(EXIT_FAILURE);
//		}
//		PortPrice += price[i];
//	}
//	cout << endl;
//	cout << "=======================================================================================================================" << endl;
//	cout << "The price of this portfolio is " << PortPrice << endl;
//	cout << "=======================================================================================================================" << endl;
//	cout << endl;
//} 