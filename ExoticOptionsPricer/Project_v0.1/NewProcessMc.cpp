#include "NewProcessMC.h"
#include "Function.h"

#include <math.h>
#include <iostream>

using namespace std;

ProcessEuro::ProcessEuro(const PayOff& thePayOff_,
	const Process& theProcess_,
	double Spot_,
	double r_,
	double Expiry_,
	double Vol_,
	unsigned long NumberOfPaths_)
	:
	thePayOff(thePayOff_),
	theProcess(theProcess_),
	Spot(Spot_),
	r(r_), 
	Expiry(Expiry_),
	Vol(Vol_),
	NumberOfPaths(NumberOfPaths_)
{
}
double ProcessEuro::operator()()const
{
	double runningsum = 0.0;
	double runningsum2 = 0.0;
	double sd = 0.0;
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		double thisSpot = theProcess.evolve(Spot, r, Expiry, Vol, thisGaussian);
		double thisPayOff = thePayOff(thisSpot);
		runningsum += thisPayOff;
		runningsum2 += thisPayOff*thisPayOff;
	}
	double mean = runningsum / NumberOfPaths;
	sd = sqrt(runningsum2 / (NumberOfPaths - 1) - (NumberOfPaths / (NumberOfPaths - 1))*mean*mean);
	//cout << "sd:" << sd << endl;
	double stderror = sd / sqrt(NumberOfPaths);
	mean *= exp(-r * Expiry);
	//cout  << stderror << endl;
	return mean;
}

ProcessAs::ProcessAs(
	const PayOff& thePayOff_,
	const Process& theProcess_,
	double Spot_,
	double r_,
	double Expiry_,
	double Vol_,
	unsigned long NumberOfPaths_,
	double NumberOfIntervals_)
	:
	thePayOff(thePayOff_),
	theProcess(theProcess_),
	Spot(Spot_),
	r(r_),
	Expiry(Expiry_),
	Vol(Vol_),
	NumberOfPaths(NumberOfPaths_),
	NumberOfIntervals(NumberOfIntervals_)
{}
double ProcessAs::operator()() const
{
	vector<double> spots(int((Expiry * 360) / NumberOfIntervals), Spot);
	double dt = Expiry / ((Expiry * 360) / NumberOfIntervals);

	double runningsum = 0.0;
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		for (unsigned long i = 1; i<spots.size(); i++)
		{
			double thisGaussian = GetOneGaussianByBoxMuller();
			spots[i] = theProcess.evolve(spots[i-1], r, dt, Vol, thisGaussian);
		}
		double sum = 0.0;
		for (unsigned long i = 0; i<spots.size(); i++)
		{
			sum += log(spots[i]);
		}
		double expMean = exp(sum / spots.size());
		double thisPayOff = thePayOff(expMean);
		runningsum += thisPayOff;
	}
	double mean = runningsum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}



ProcessBarrier::ProcessBarrier(
	const PayOff& thePayOff_,
	const Process& theProcess_,
	double strike_,
	double Spot_,
	double r_,
	double Expiry_,
	double Vol_,
	double barrier_,
	double option_,
	unsigned long NumberOfPaths_,
	double NumberOfIntervals_)
	:
	thePayOff(thePayOff_),
	theProcess(theProcess_),
	strike(strike_),
	Spot(Spot_),
	r(r_),
	Expiry(Expiry_),
	Vol(Vol_),
	barrier(barrier_),
	option(option_),
	NumberOfPaths(NumberOfPaths_),
	NumberOfIntervals(NumberOfIntervals_)
{}
double ProcessBarrier::operator()() const
{
	vector<double> spots(int((Expiry * 360) / NumberOfIntervals), Spot);
	double dt = Expiry / ((Expiry * 360) / NumberOfIntervals);

	double runningsum = 0.0;
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		for (unsigned long i = 1; i < spots.size(); i++)
		{
			double thisGaussian = GetOneGaussianByBoxMuller();
			spots[i] = theProcess.evolve(spots[i - 1], r, dt, Vol, thisGaussian);
		}
		//Up and In
		int length = spots.size();
		double thisSpot = 0.0;
		if (option == 5|| option == 6)
		{
			thisSpot = strike;
			for (unsigned long i = 0; i < spots.size(); i++)
			{
				if (spots[i] >= barrier)
				{
					thisSpot = spots[length - 1];
				}
			}
		}
		//Up and Out
		else if (option == 7 || option == 8)
		{
			thisSpot = spots[length - 1];
			for (unsigned long i = 0; i < spots.size(); i++)
			{
				if (spots[i] >= barrier)
					thisSpot = strike;
			}
		}
		//Down and In
		else if (option == 9 || option == 10)
		{
			thisSpot = strike;
			for (unsigned long i = 0; i < spots.size(); i++)
			{
				if (spots[i] <= barrier)
					thisSpot = spots[length - 1];
			}
		}
		//Down and Out
		else
		{
			thisSpot = spots[length - 1];
			for (unsigned long i = 0; i < spots.size(); i++)
			{
				if (spots[i] <= barrier)
					thisSpot = strike;
			}
		}
		double thisPayOff = thePayOff(thisSpot);
		runningsum += thisPayOff;
	}
	double mean = runningsum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}



ProcessBasket::ProcessBasket(
	const PayOff& thePayOff_,
	const Process& theProcess_,
	vector<vector<double>> basket_,
	vector<vector<double>> correlation_,
	double Expiry_,
	double r_,
	unsigned long NumberOfPaths_)

	:
	thePayOff(thePayOff_),
	theProcess(theProcess_),
	basket(basket_),
	correlation(correlation_),
	Expiry(Expiry_),
	r(r_),
	NumberOfPaths(NumberOfPaths_)
{}
double ProcessBasket::operator()()const
{
	double NumberOfAsset = basket.size();

	vector<vector<double> > correlationMatrix(NumberOfAsset, vector<double>(NumberOfAsset));
	double variance;
	double rootVariance = 0.0;
	double itoCorrection;
	vector<double> moveSpot(NumberOfAsset);
	correlationMatrix = cholesky(correlation);
	//for (unsigned int i = 0; i < NumberOfAsset; i++)
	//{
	//	variance = basket[i][1] * basket[i][1] * Expiry;
	//	rootVariance = sqrt(variance);
	//	itoCorrection = -0.5 * variance;
	//	moveSpot[i] = basket[i][0] * exp(r * Expiry + itoCorrection);
	//	//moveSpot[i] = theProcess.evolve(basket[i][0], r, Expiry, basket[i][1]);
	//}
	double runningsum = 0.0;
	vector<double> thisGaussian(NumberOfAsset);
	vector<double> correlatedGaussian;
	vector<double> thisSpot(NumberOfAsset);
	for (unsigned long i = 0; i < NumberOfPaths; i++)
	{
		double allSpot = 0.0;
		for (int i = 0; i < NumberOfAsset; i++)
		{
			thisGaussian[i] = GetOneGaussianByBoxMuller();
		}
		correlatedGaussian = MatrixMultiply(correlationMatrix, thisGaussian);
		for (int i = 0; i < NumberOfAsset; i++)
		{
			//thisSpot[i] = moveSpot[i] * exp(rootVariance*correlatedGaussian[i]);
			thisSpot[i] = theProcess.evolve(basket[i][0], r, Expiry, basket[i][1], correlatedGaussian[i]);
			allSpot += (basket[i][2] * thisSpot[i]);
		}
		double thisPayOff = thePayOff(allSpot);
		runningsum += thisPayOff;
	}
	double mean = runningsum / NumberOfPaths;
	mean *= exp(-r * Expiry);
	return mean;
}